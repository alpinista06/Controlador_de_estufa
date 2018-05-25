#include "comunicacao_uart.h"

void uart_init(uint32_t baud) {
  uint16_t baud_prescaller = (((F_CPU / (baud * 16UL))) - 1);
  //TODO: explicar esse registradores dps
  UBRR0H = (uint8_t)(baud_prescaller >> 8);
  UBRR0L = (uint8_t)(baud_prescaller);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (3 << UCSZ00);
}
uint8_t uart_in_buffer()
{
  return (UCSR0A & (1 << RXC0)); //Retorna 1 quando tem, e 0 quando tem dados do buffer 
}

uint8_t uart_read_byte() {
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

void uart_read_bytes(uint8_t *read_bytes, uint8_t qnt) {
  uint8_t i;
  for (i = 0; i < qnt; i++) {
    read_bytes[i] = uart_read_byte();
  }
}

void uart_send_byte(uint8_t byte_to_send) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = byte_to_send;
}

void uart_send_bytes(uint8_t *bytes_to_send, uint8_t qnt) {
  uint8_t i;
  for (i = 0; i < qnt; i++) {
    uart_send_byte(bytes_to_send[i]);
  }
}

void uart_send_string(const char *string_to_send) {
  //Todo string termina com '\0'. Exemplo: "Ola!" vale { 'O', 'l', 'a', '!', '\0'}
  while (*string_to_send != '\0') { //Enquanto não chegou no final da string
    uart_send_byte(*string_to_send);
    string_to_send++;
  }
}

void uart_read_string(char *read_string, char terminator = '\n'){
  uint8_t i;
  i = 0;
  while(true){
    read_string[i] = uart_read_byte();
    if(read_string[i] == terminator){
      break;
    }
    i++;
  }
}
