/**
* UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
* Autor: Mario Divino Borges Filho
* Data: 21/04/2018
* Git: github.com/alpinista06
*
* Descrição: Biblioteca para escrita de PWM em bare metal
* utilizando o microcontrolador ATMEGA328P
*/
#ifndef library_PWM_H_
#define library_PWM_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

////////////
//Defines //
////////////

//////////////////
//Tipos de dados//
/////////////////

typedef enum {
  PWM_prescaler_1
  PWM_prescaler_8
  WM_prescaler_64
  _prescaler_1024
}PWM_prescaler;

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

/**
* [configura_porta description]
* @param u8_pino_adc [Configura a porta analógica à qual a leitura será realizada, default porta A0]
* @param u8_referencia_adc [Configura a tensão de referencia para a conversão, default referencia interna]
* @param u8_prescaler_adc [Configura o prescaler da conversão, default 128]
*/
void configura_PWM(uint8_t u8_pino_PWM, PWM_prescaler prescaler_PWM);


void debbuger_init_PWM();

/**
* [realizar_leitura analógica]
* @param   [sem parametros de entrada]
* @return          [retorna o resultado da conversão AD]
*/
void Pulso_PWM(uint8_t u8_pino_PWM, uint8_t Valor );


void debbuger_write_PWM(uint16_t VALOR);

#endif /*_LEITURA_ANALOGICA_H_*/
