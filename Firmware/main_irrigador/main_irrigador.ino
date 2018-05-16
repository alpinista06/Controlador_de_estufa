#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "leitura_analogica.h"
#include "comunicacao_uart.h"


//#define ENVIAR_COMO_PACOTE
//#define ENVIAR_COMO_STRING

#define INICIADOR_DO_PACOTE_DE_LEITURA 'L'
#define TERMINADOR_DO_PACOTE '\n'

#define SREG_GLOBAL_INT_ENABLE 7


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
//Leituras
float temperatura_lida;
uint16_t umidade_lida;
//Controle dos atuadores
float tempo_regando;
bool estou_regando;
float tempo_ventilando;
bool estou_ventilando;
uint16_t valor_lido;


char valor_string[3]; //string que será de fato enviada pela uart, usado no itoa



ISR(TIMER1_COMPA_vect)
{
  valor_lido = adc_read();

  umidade_lida = (valor_lido / 1023.0) * 100.0;
  itoa(umidade_lida, valor_string, 10);
  uart_send_byte(UART_PACKET_START);
  uart_send_byte(UART_PACKET_UMID);
  uart_send_bytes(valor_string, 2);
  uart_send_byte(UART_PACKET_END);
}


void InitializeTimer1(void )
{
  // ICIE1: Hailita o Timer/Counter1, Input Capture Interrupt Enable
  // OCIE1B: Habilita a comparaão de interrupão B Timer/Counter1, Output Compare B Match Interrupt Enable
  // OCIE1A: Habilita a comparaão de interrupão A Timer/Counter1, Output Compare A Match Interrupt Enable
  // TOIE1: Seta no modo de overflow Timer/Counter1, Overflow Interrupt Enable
  TIMSK1 &= ~((1 << ICIE1) | (1 << OCIE1B) | (1 << OCIE1A) | (1 << TOIE1));
  //TIMSK1 |= (1 << TOIE1);
  TIMSK1 |= (1 << OCIE1A);


  //--- Clear Timer on Compare or CTC mode Configuration ------------------
  // Modo CTC ou seja o contador atinge o valor de comparação gera a interrupçao (TCNT1)
  // matches either the OCR1A (WGM13:0 = 4) - (Item 16.9.2 - Pag. 122)
  TCCR1B |= (1 << WGM12);

  //--- Prescaler Configuration ------------------------------------
  TCCR1B |= (1 << CS12) | (1 << CS10);  // clk/1024 (From prescaler)
  //TCCR1B |= (1 << CS12);  // clk/256 (From prescaler)
  //TCCR1B |= (1 << CS11) | (1 << CS10);  // clk/64 (From prescaler)
  //TCCR1B |= (1 << CS11);  // clk/8 (From prescaler)
  //TCCR1B |= (1 << CS10);  // clkI/1 (No prescaling)
}





int main (void) {
  uart_init(9600);
  adc_init(1, AD_REF_5V, AD_PRESCALER_128);

  InitializeTimer1();
  OCR1A = 15624;  // 1Hz com clk/1024 (From prescaler)

  while (1) {

    // Restore the global interrupt bit to previous value.
    SREG |= (1 << SREG_GLOBAL_INT_ENABLE);

  }

}
