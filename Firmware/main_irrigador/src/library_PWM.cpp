#include "library_PWM.h"


//Testes automatizados

void debbuger_init_PWM() {
  DDRB |= (1 << DDB1); // | 1 << DDB2 | 1 << DDD6);   PB1(arduino D9) como saida
  TCCR1A |= (1 << COM1A1); // Substitui a funcionalidade normal do pino(I/O), para a saida PWM.
  // COM1A1 seta o é ligado ao registrador OCR1A; COM1B1 e ligado ao registrador OCR1B
  // Estes controlam o duty cycle das portas PB1(D9) e PB2(D10) respectivamente
  TCCR1A |= (1 << WGM11) | (1 << WGM10); // TCCR1A Contador/Timer setando o modo de operação = Fast PWM-10-bit, Valor máx = 0x03FF(1023),
  // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior
  // Valores  tabelados dados pelo fabricante
  TCCR1B |= (1 << WGM12); // Timer/Counter Setando o modo de operação desse registrador = Fast PWM-10-bit, Valor máx = 0x03FF,
  // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior
  TCCR1B |= (1 << CS11);  // setando o  prescaler to 8(valor tabelado) e iniciando PWM
}

void debbuger_write_PWM(uint16_t u16_VALOR) {
  OCR1A = u16_VALOR; // Este registrador controla o duty cycle do PWM do PB1(D9)
}

//Inicio da biblioteca
void init_PWM(uint8_t u8_pino_pwm) {
  switch (u8_pino_pwm) {
    case 3:
      DDRD |= (1 << DDD3);
      TCCR2A |= (1 << COM2B1);
      TCCR2B |= (1 << WGM21) | (1 << WGM20);   //Resetar quando atinge o valor máximo em OC2B, modo não inversor; Fast-PWMM
      TCCR2B |= (1 << CS21);
    case 5:
      DDRD |= (1 << DDD5);
      TCCR0A |= (1 << COM0B1);      //Resetar quando atinge o valor máximo em OC2B, modo não inversor
      TCCR0A |= (1 << WGM01) | (1 << WGM00);
      TCCR1B |= (1 << CS01);
    case 6:
      DDRD |= (1 << DDD6);
      TCCR0A |= (1 << COM0A1);
      TCCR0A |= (1 << WGM01) | (1 << WGM00);
      TCCR0B |= (1 << CS01);
    case 9:
      DDRB |= (1 << DDB1); // | 1 << DDB2 | 1 << DDD6);   PB1(arduino D9) como saida
      TCCR1A |= (1 << COM1A1); // Substitui a funcionalidade normal do pino(I/O), para a saida PWM.
      // COM1A1 seta o é ligado ao registrador OCR1A; COM1B1 e ligado ao registrador OCR1B
      // Estes controlam o duty cycle das portas PB1(D9) e PB2(D10) respectivamente
      TCCR1A |= (1 << WGM11) | (1 << WGM10); // TCCR1A Contador/Timer setando o modo de operação = Fast PWM-10-bit, Valor máx = 0x03FF(1023),
      // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior
      // Valores  tabelados dados pelo fabricante
      TCCR1B |= (1 << WGM12); // Timer/Counter Setando o modo de operação desse registrador = Fast PWM-10-bit, Valor máx = 0x03FF,
      // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior
      TCCR1B |= (1 << CS11);  // setando o  prescaler to 8(valor tabelado) e iniciando PWM
    case 10:
      DDRB |= (1 << DDB2);
      TCCR1A |= (1 << COM1B1);
      TCCR1A |= (1 << WGM11) | (1 << WGM10);
      TCCR1B |= (1 << WGM12);
      TCCR1B |= (1 << CS11);
    case 11:
      DDRB |= (1 << DDB3);
      TCCR2A |= (1 << COM2A1);
      TCCR2A |= (1 << WGM21) | (1 << WGM20);
      TCCR2B |= (1 << CS21);
  }
}


void Pulso_PWM(uint8_t u8_pino_PWM, uint8_t u8_Valor )
{
  uint8_t u8_duty = u8_Valor;
  switch (u8_pino_PWM) {

    case 3:
      OCR2B = u8_duty;
    case 5:
      OCR0B = u8_duty;
    case 6:
      OCR0A = u8_duty;
    case 9:
      OCR1A = u8_duty;
    case 10:
      OCR1B = u8_duty;
    case 11:
      OCR2A = u8_duty;

  }
}
