/**
  UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
  Autor: Mario Divino Borges Filho
  Data: 16/04/2018
  Git: github.com/alpinista06

  Descrição: Biblioteca para leitura analógica em bare metal
  utilizando o microcontrolador ATMEGA328P
*/
#ifndef _LEITURA_ANALOGICA_H_
#define _LEITURA_ANALOGICA_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>

///////////////////
//Tipos de dados //
///////////////////

typedef enum {
  AD_REF_5V,
  AD_REF_INTERNAL_1_1V,
  AD_REF_EXTERNAL
} ad_ref;

typedef enum {
  AD_PRESCALER_2,
  AD_PRESCALER_4,
  AD_PRESCALER_8,
  AD_PRESCALER_16,
  AD_PRESCALER_32,
  AD_PRESCALER_64,
  AD_PRESCALER_128
} ad_prescaler;

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

/**
   [configura_porta description]
   @param u8_pino_adc [Configura a porta analógica à qual a leitura será realizada, default porta A0]
   @param u8_referencia_adc [Configura a tensão de referencia para a conversão, default referencia interna]
   @param u8_prescaler_adc [Configura o prescaler da conversão, default 128]
*/
void adc_init(ad_ref referencia_adc, ad_prescaler prescaler_adc);

/**
   [realizar_leitura analógica]
   @param u8_pino_adc [Recebe o pino em que se deseja realizar a leitura AD]
   @return          [retorna o resultado da conversão AD]
*/
uint16_t adc_read(uint8_t u8_pino_adc);

void adc_debugger_teste_configura();
uint16_t adc_debugger_teste_leitura();

#endif /*_LEITURA_ANALOGICA_H_*/
