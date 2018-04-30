/**
  UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
  Autor: TODO: Seu nome
  Data:  TODO: data
  Git:  TODO: seu git

  Descrição:  TODO: escrever descrição
*/
#ifndef _ARDUINO_TIMERS_H_
#define _ARDUINO_TIMERS_H_ //Previne quando multiplas inclusões

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
 * Inicia o timer, obs: deve ser configurado antes
 */
void start_T0(void);
/**
 * Para o timer, obs: deve ser configurado antes
 */
void stop_T0(void);

/**
 * Configura o timer indicado quantos tickes ele deve ter antes de chamar a interrupção
 * @param number_beats [description]
 * @param flag_count   [description]
 */
void setup_T0_ticks(uint16_t number_beats);

/**
 * Configura o timer com um intervalo em us
 * @param T_us [description]
 */
void setup_T0_elapsed_us(uint16_t T_us);

/**
 * Configura o timer com um intervalo em ms
 * @param T_ms [description]
 */
void setup_T0_elapsed_ms(uint16_t T_ms);

/**
 * Configura o timer para uma data frequencia
 * @param Freq_Hz [description]
 */
void setup_T0_freq(uin16_t Freq_Hz);

#endif /*_ARDUINO_TIMERS_*/
