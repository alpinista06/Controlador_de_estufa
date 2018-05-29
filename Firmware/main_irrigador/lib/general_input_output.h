/**
  UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
  Autor: TODO: Seu nome
  Data:  TODO: data
  Git:  TODO: seu git

  Descrição:  TODO: escrever descrição
*/
#ifndef _GENERAL_INPUT_OUTPUT_H_
#define _GENERAL_INPUT_OUTPUT_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>

///////////////
//Definições //
///////////////
/* Caso você utilize difições, coloque-as aqui */

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

/**
 * Equivale a função pinMode, seta o pino desejado como uma saida ou entrada.
 * @param pino_desejado    [description]
 * @param saida_ou_entrada [description]
 */
void io_configure_pin(uint8_t pino_desejado, bool saida_ou_entrada);

/**
 * Equivale a digitalRead
 * @param  pino_desejado [description]
 * @return               [description]
 */
bool io_read_pin_state(uint8_t pino_desejado);

/**
 * equivale a digitalWrite
 * @param novo_estado_do_pino [description]
 */
void io_write_pin_state(bool novo_estado_do_pino);
#endif /*_GENERAL_INPUT_OUTPUT_*/
