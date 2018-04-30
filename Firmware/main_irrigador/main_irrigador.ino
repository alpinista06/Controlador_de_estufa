#include "leitura_analogica.h"
#include "comunicacao_uart.h"
#include "library_PWM.h"

//#define ENVIAR_COMO_PACOTE
#define ENVIAR_COMO_STRING

#define INICIADOR_DO_PACOTE_DE_LEITURA 'L'
#define TERMINADOR_DO_PACOTE '\n'

uint16_t valor_lido;
char valor_lido_como_string[8]; //Exemplo: 5.00\n\0

int main (void) {
  uart_init(9600);
  adc_init(1, AD_REF_5V, AD_PRESCALER_128);
  //adc_debugger_teste_configura();

   debbuger_init_PWM();

  while (1) {
    //valor_lido = adc_debugger_teste_leitura();
    valor_lido = adc_read();

    debbuger_write_PWM(valor_lido);

    //Opcao A: enviar numero como um pacote - Exemplo de 5V: ['L'] [0x03] [0xFF] ['\n']
#ifdef ENVIAR_COMO_PACOTE
    uart_send_byte(INICIADOR_DO_PACOTE_DE_LEITURA); //Enviar MSB
    uart_send_byte((uint8_t) (valor_lido >> 8)); //Enviar MSB
    uart_send_byte((uint8_t) (valor_lido)); //Enviar LSB
    uart_send_byte(TERMINADOR_DO_PACOTE); //Enviar MSB
#endif

    //Opcao B: enviar numero como um string - Exemplo de 5V: 5.00\n
#ifdef ENVIAR_COMO_STRING
    itoa (valor_lido, valor_lido_como_string, 10);
    uart_send_string(valor_lido_como_string);
    uart_send_byte('\n');
#endif
  }
}
