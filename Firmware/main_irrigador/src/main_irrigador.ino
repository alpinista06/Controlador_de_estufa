#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <leitura_analogica.h>
#include <comunicacao_uart.h>
#include <library_PWM.h>


//#define ENVIAR_COMO_PACOTE
//#define ENVIAR_COMO_STRING

#define INICIADOR_DO_PACOTE_DE_LEITURA 'L'
#define TERMINADOR_DO_PACOTE '\n'

#define SREG_GLOBAL_INT 7

#define ESPERA 1000

////////////
//Estados //
////////////
enum MAQUINA {ler_umidade, ler_temperatura, enviar_dados, ventilando, irrigando, receber_dados, enviar_umidade, enviar_temperatura, controlar_temperatura, controlar_umidade};


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


////////////////
//Global Data //
////////////////
//Leituras//
float temperatura_lida;
uint16_t umidade_lida;
//Controle dos atuadores//
float tempo_regando;
bool estou_regando;
float tempo_ventilando;
bool estou_ventilando;
uint16_t valor_lido_u;
float valor_lido_T;
uint8_t contador_T;
char comando;

char string_umidade[3]; //string que será de fato enviada pela uart, usado no itoa
char string_temperatura[3];

int main (void) {
  uart_init(9600);
  adc_init(AD_REF_5V, AD_PRESCALER_128);
  init_PWM(9);
  DDRB |= (1 << DDB4); // pino digital 12
  enum MAQUINA estado = ler_umidade;
  //enum MAQUINA estado = ler_temperatura;
  //enum MAQUINA estado = controlar_temperatura;
  while (1) {
    if (uart_in_buffer()) {
      comando = uart_read_byte();
      if (comando == 'V'){
        estado = ventilando;
      }else if (comando == 'R'){
        estado = irrigando;
      }else if (comando == 'V'){
        estado = ventilando;
      }
    }
    switch (estado) {

      case ler_umidade:
      SREG  &=  ~(1  <<  SREG_GLOBAL_INT);    //Desabilita as interrupções globais.
      valor_lido_u = adc_read(3);
      umidade_lida = 100 - ((valor_lido_u / 1023.0) * 100);
      itoa(umidade_lida, string_umidade , 10);
      SREG  |=  (1  <<  SREG_GLOBAL_INT);    // Restaura as interrupções globais.
      _delay_ms(25);    //Necessário para que os registradores de leitura analógica se atualizem de forma completa
      //estado = ler_temperatura;
      estado = enviar_umidade;
      break;

      case ler_temperatura:
      SREG  &=  ~(1  <<  SREG_GLOBAL_INT);    //Desabilita as interrupções globais.
      valor_lido_T = adc_read(0); //ATENÇAO Parametro 0 significa porta analogica A2
      temperatura_lida = (valor_lido_T * 0.48875855);
      //temperatura_lida = (valor_lido_T / 1023.0) * 100;
      itoa(temperatura_lida, string_temperatura, 10);
      SREG  |=  (1  <<  SREG_GLOBAL_INT);    // Restaura as interrupções globais.
      _delay_ms(25);
      //estado = ler_umidade;
      //estado = enviar_umidade;
      estado = enviar_temperatura;
      //estado = enviar_dados;
      //estado = controlar_temperatura;
      break;


      case controlar_umidade:
      Pulso_PWM(9, (umidade_lida));
      estado = ler_temperatura;
      break;

      case ventilando:
      PORTB |= (1 << PORT4);
      _delay_ms(2000);
      PORTB &= ~(1 << PORT4);
      estado = ler_umidade;
      break;

      case irrigando:
      Pulso_PWM(9, 250);
      _delay_ms(2000);
      estado = ler_umidade;
      break;


      case controlar_temperatura:
      //SREG  &=  ~(1  <<  SREG_GLOBAL_INT);
      if (temperatura_lida > 45)
      {
        PORTB |= (1 << PORT4);
      } else if (temperatura_lida < 45)
      {
        PORTB &= ~(1 << PORT4);
      }
      //SREG  |=  (1  <<  SREG_GLOBAL_INT);
      //estado = ler_temperatura;
      estado = ler_umidade;
      //estado = controlar_umidade;

      break;

      case enviar_umidade:

      SREG  &=  ~(1  <<  SREG_GLOBAL_INT);
      uart_send_byte(UART_PACKET_START);
      uart_send_byte(UART_PACKET_UMID);
      uart_send_bytes(string_umidade, 2);
      uart_send_byte(UART_PACKET_END);
      SREG  |=  (1  <<  SREG_GLOBAL_INT);

      _delay_ms(ESPERA);
      //estado = enviar_temperatura;
      //estado = ler_temperatura;
      estado = controlar_umidade;
      break;

      case enviar_temperatura:
      SREG  &=  ~(1  <<  SREG_GLOBAL_INT);
      uart_send_byte(UART_PACKET_START);
      uart_send_byte(UART_PACKET_TEMP);
      uart_send_bytes(string_temperatura, 2);
      uart_send_byte(UART_PACKET_END);
      SREG  |=  (1  <<  SREG_GLOBAL_INT);

      _delay_ms(ESPERA);
      //estado = ler_temperatura;
      //estado = ler_umidade;
      estado = controlar_temperatura;
      //estado = controlar_umidade;
      break;

      case receber_dados:
      SREG |= (1 << SREG_GLOBAL_INT);
      estado = ler_umidade;

      break;

    }
  }
}
