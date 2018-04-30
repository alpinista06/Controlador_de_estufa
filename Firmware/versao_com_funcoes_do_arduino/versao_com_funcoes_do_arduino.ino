//////////
//TIMER //
//////////
#include <TimeOne.h> //Baixada em: https://github.com/PaulStoffregen/TimerOne
#define TIMER_INTERVAL_S  0.1
#define TIMER_INTERVAL_MS 100
#define TIMER_INTERVAL_US 100000

//////////
//Pinos //
//////////
#define PINO_LM35       A0
#define PINO_HIGROMETRO A1
#define PINO_VALVULA    4
#define PINO_COOLER     5

/////////////////////////////
//Protocolo de comunicacao //
/////////////////////////////
#define UART_BAUDRATE       9600
#define UART_PACKET_START   '$'
#define UART_PACKET_END     '\n'
#define CMD_HANDSHAKE       'H'
#define CMD_REGAR           'R'
#define CMD_VENTILAR        'V'
#define UART_PACKET_UMID    'U'
#define UART_PACKET_TEMP    'T'
char cmd_from_app;

////////////////////////
//Procolo de controle //
////////////////////////
#define PROTOCOLO_MAX_TEMPO_REGANDO       1
#define PROTOCOLO_MAX_TEMPO_VENTILANDO    1
#define PROTOCOLO_MIN_UMIDADE_ACEITAVEL   30
#define PROTOCOLO_MAX_TEMP_ACEITAVEL      40
#define PROTOCOLO_VALOR_PWM_VALVULA_ON    200

///////////////////////
//Máquina de Estados //
///////////////////////
typedef enum {
  ESTADO_HANDSHAKE,
  ESTADO_AGUARDANDO_COMANDO
} estados_t;
estados_t estado_atual;

typedef enum {
  ESTADO_HANDSHAKE,
  ESTADO_AGUARDANDO_COMANDO,
  ESTADO_REGANDO,
  ESTADO_VENTILANDO
} estados_t;
estados_t estado_atual;

////////////////
//Global Data //
////////////////
//Leituras
float temperatura_lida;
float umidade_lida;
//Controle dos atuadores
float tempo_regando;
bool estou_regando;
float tempo_ventilando;
bool estou_ventilando;

//////////
//Setup //
//////////
void setup(){
  //Inicialização da comunicação UART
  Serial.begin(UART_BAUDRATE);
  //Configuração dos pinos
  pinMode(PINO_LM35,        INPUT);
  pinMode(PINO_HIGROMETRO,  INPUT);
  pinMode(PINO_VALVULA,     OUTPUT);
  pinMode(PINO_COOLER,      OUTPUT);
  //Configuração da máquina de estados
  estado_atual = ESTADO_HANDSHAKE;
  //Configuração do Timer
  Timer1.initialize()

}
//////////
// loop //
//////////
void loop(){
  switch (estado_atual) {
    case ESTADO_HANDSHAKE:
    if(Serial.available()){
      cmd_from_app = Serial.read();
      if(cmd_from_app == CMD_HANDSHAKE){ //Se recebeu um pedido de handshake
        //Responde o pedido
        Serial.write(UART_PACKET_START);
        Serial.write(CMD_HANDSHAKE);
        Serial.write(UART_PACKET_START);
        //Inicia o timer
        Timer1.attachInterrupt(timer_interrupt_callback, TIMER_INTERVAL_US);
        //E muda de estado para o aguardando comando
        estado_atual = ESTADO_AGUARDANDO_COMANDO;
      }
    }
    break;
    case ESTADO_AGUARDANDO_COMANDO:
    if(Serial.available()){
      cmd_from_app = Serial.read();
      switch (cmd_from_app) { //Compara o comando recebido com as opções
        case CMD_REGAR: //Caso seja um 'R' começa a regar.
        analogWrite(PINO_VALVULA, PROTOCOLO_VALOR_PWM_VALVULA_ON);
        tempo_regando = 0;
        estou_regando = true;
        break;
        case CMD_VENTILAR: //Caso seja um 'V' começa a ventilar.
        digitalWrite(PINO_COOLER, HIGH);
        tempo_ventilando = 0;
        estou_ventilando = true;
        break;
        case CMD_HANDSHAKE: //Caso seja um 'H' desativa tudo e volta ao estado anterior
        //Desativa o regador
        estou_regando = false;
        digitalWrite(PINO_VALVULA, LOW);
        //Desativa o cooler
        estou_ventilando = false;
        digitalWrite(PINO_COOLER, LOW);
        //Desativa o timer
        Timer1.stop();
        //Volta ao estado anterior
        estado_atual = ESTADO_HANDSHAKE;
        default:
        break;
      }
    }
  }
  break;
  default:
  //Caso não haja nenhum dos estados reconhecidos selecionados, não faz nada
  break;
}

void timer_interrupt_callback(){
  //A cada 100ms ele sempre lê os sensores e envia
  ler_sensores();
  enviar_pacotes_de_leituras();
  //Caso esteja regando
  if(estou_regando){
    tempo_regando += TIMER_INTERVAL_S; //Incrementa 100ms
    if(tempo_regando >= PROTOCOLO_MAX_TEMPO_REGANDO){
      //Desativa o regador
      estou_regando = false;
      digitalWrite(PINO_VALVULA, LOW);
    }
  }
  //Caso esteja ventilando também
  if(estou_ventilando){
    tempo_ventilando += TIMER_INTERVAL_S; //Incrementa 100ms
    if(tempo_ventilando >= PROTOCOLO_MAX_TEMPO_VENTILANDO){
      //Desativa o cooler
      estou_ventilando = false;
      digitalWrite(PINO_COOLER, LOW);
    }
  }
}

void ler_sensores(){
  //Leitura da temperatura
  temperatura_lida = (analogRead(PINO_LM35) * 5.0 / 1023.0) * 0.01;
  //Leitura da umidade
  //TODO: Corrigir está leitura
  umidade_lida = (analogRead(PINO_HIGROMETRO) / 1023.0) * 100.0;
}

void enviar_pacotes_de_leituras(){
  //Enviando os valores de temperatura
  Serial.write(UART_PACKET_START);    // '$' - Indica que será enviada uma leitura
  Serial.write(UART_PACKET_TEMP);     // 'T' - Indica que é uma leitura de temperatura
  Serial.print(temperatura_lida, 1);  // '28.0' - Temperatura com 1 casa decimal
  Serial.write(UART_PACKET_END);      // '\n' - Indica que terminou de enviar
  //Enviando os valores de umidade
  Serial.write(UART_PACKET_START);    // '$' - Indica que será enviada uma leitura
  Serial.write(UART_PACKET_TEMP);     // 'T' - Indica que é uma leitura de Umidade
  Serial.print(umidade_lida, 0);      // '72' - Umidade com 0 casas decimais
  Serial.write(UART_PACKET_END);      // '\n' - Indica que terminou de enviar
}
