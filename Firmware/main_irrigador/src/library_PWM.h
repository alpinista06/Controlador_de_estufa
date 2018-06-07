/**
  UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
  Autores: Mario Divino Borges Filho
          Thales Silva Rodrigues 
  Data: 21/04/2018
  Git: github.com/alpinista06

  Descrição: Biblioteca para escrita de PWM em bare metal
  utilizando o microcontrolador ATMEGA328P
*/
#ifndef library_PWM_H_
#define library_PWM_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


//////////////////
//Tipos de dados//
/////////////////

typedef enum {
  PWM_prescaler_1,
  PWM_prescaler_8,
  PWM_prescaler_64,
  PWM_prescaler_256,
  PWM_prescaler_1024
} pwm_prescaler;

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

/**
  [configura_porta description]
  @param u8_pino_adc [Configura a porta analógica à qual a leitura será realizada, default porta A0]
  @param u8_referencia_adc [Configura a tensão de referencia para a conversão, default referencia interna]
  @param u8_prescaler_adc [Configura o prescaler da conversão, default 128]
*/
void init_PWM(uint8_t u8_pino_pwm);


/**
  [escrita analógica]
  @param u8_pino_PWM [Seta o pino em que o pulso será escrito]
  @param u8_Valor [Recee o valor que será controla o duty cycle do PWM]
  @return          [Sem retorno]
*/
void Pulso_PWM(uint8_t u8_pino_PWM, uint8_t u8_Valor );

void debbuger_init_PWM();
void debbuger_write_PWM(uint16_t VALOR);

#endif /*_LEITURA_ANALOGICA_H_*/
