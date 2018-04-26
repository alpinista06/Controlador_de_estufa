#include <library_PWM.h>

void debbuger_init_PWM() {
    DDRB |= (1 << DDB1 | 1 << DDB2 | 1 << DDD6);  // PB1(arduino D9) como saida
    TCCR1A |= (1 << COM1A1 | 1 << COM1B1); // Substitui a funcionalidade normal do pino(I/O), para a saida PWM.
                                           // COM1A1 seta o é ligado ao registrador OCR1A; COM1B1 e ligado ao registrador OCR1B
                                           // Estes controlam o duty cycle das portas PB1(D9) e PB2(D10) respectivamente




    TCCR1A |= (1 << WGM11) | (1 << WGM10); // TCCR1A Contador/Timer setando o modo de operação = Fast PWM-10-bit, Valor máx = 0x03FF(1023),
                                           // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior
                                           // Valores  tabelados dados pelo fabricante

    TCCR1B |= (1 << WGM12); // Timer/Counter Setando o modo de operação desse registrador = Fast PWM-10-bit, Valor máx = 0x03FF,
                            // Atualiza OCR1x para o limite inferior e  o sinalizador TOV1 para o limite superior

    TCCR1B |= (1 << CS11);  // setando o  prescaler to 8(valor tabelado) e iniciando PWM
}

void debbuger_write_PWM(uint16_t VALOR) {
  OCR1A = VALOR; // Este registrador controla o duty cycle do PWM do PB1(D9)
}

/*
void configura_PWM(uint8_t u8_pino_PWM, uint8_t u8_PWM_mode, uint8_t u8_prescaler_PWM);{


}


void Pulso_PWM(uint8_t Valor);{


}
*/
