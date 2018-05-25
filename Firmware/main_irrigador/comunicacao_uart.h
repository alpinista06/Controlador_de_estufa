/**
  UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
  Autor: Mario Divino Borges Filho
  Data: 16/04/2018
  Git: github.com/alpinista06

  Descrição: Biblioteca para comunicacao UART em bare metal
  utilizando o microcontrolador ATMEGA328P
*/
#ifndef _COMUNICACAO_UART_H_
#define _COMUNICACAO_UART_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>

///////
// Definicoes //
///////////
#ifndef F_CPU //Se ainda não foi definido, então defina.
#define F_CPU 16000000UL
#endif /*F_CPU*/ //Prevenir que defina 2 vezes.

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

void uart_init(uint32_t baud);

uint8_t uart_read_byte();

void uart_read_bytes(uint8_t *read_bytes, uint8_t qnt);

void uart_send_byte(uint8_t byte_to_send);

void uart_send_bytes(uint8_t *bytes_to_send, uint8_t qnt);

void uart_send_string(const char *string_to_send);

uint8_t uart_in_buffer();
/*
 * read until \0
 */
void uart_read_string(char *read_string, char terminator='\n');
#endif /*_COMUNICACAO_UART_H_*/
