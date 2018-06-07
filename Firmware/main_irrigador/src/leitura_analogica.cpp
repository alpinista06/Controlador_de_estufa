#include "leitura_analogica.h"


//Testes automatizados

void adc_debugger_teste_configura() {


  ADMUX |= ((1 << REFS0) | (1 << MUX0)); //Configura a tensao de referencia como interna do arduino
  //Habilita a porta analogica PC1(A0) a fazer a conversão como
  ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //Habilita a conversão AD
  //Seta o prescaler como 128, valor tabelado
  DDRB |= ((1 << DDB2) | (1 << DDB1) | (1 << DDB0));  //Seta portas digitais como sendo saida
  DDRC &= ~(1 << DDC1);   //Seta a porta analogica como entrada
}

uint16_t adc_debugger_teste_leitura() {

  ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
  uint8_t alto, baixo;
  while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
  baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
  alto = ADCH;  //Este bit deve ser lido por ultimo
  return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits
}

/**
funcao para selecionar a porta do conversor AD
NOTE: funciona so pra porta A1
@param pino_adc porta selecionada
*/
void adc_init(ad_ref referencia_adc, ad_prescaler prescaler_adc) {

  switch (referencia_adc) {
    case AD_REF_5V:
    ADMUX |= (1 << REFS0); //Tensão de referencia como default( 5V no caso do arduino uno)
    break;
    case AD_REF_INTERNAL_1_1V:
    ADMUX |= (1 << REFS1) | (1 << REFS0);   //Tensão de referencia interna (1.1V no caso do arduino uno)
    break;
    default:
    ADMUX |= (1 << REFS0); //Tensão de referencia como default( 5V no caso do arduino uno)
    break;

  }
  switch (prescaler_adc) {
    case AD_PRESCALER_2:
    ADCSRA |= (1 << ADPS0);   //Configurando o prescaler como 8
    break;
    case AD_PRESCALER_4:
    ADCSRA |= (1 << ADPS1);
    break;
    case AD_PRESCALER_8:
    ADCSRA |= (1 << ADPS1) | (1 << ADPS1);
    break;
    case AD_PRESCALER_16:
    ADCSRA |= (1 << ADPS2);
    break;
    case AD_PRESCALER_32:
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
    break;
    case AD_PRESCALER_64:
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
    break;
    case AD_PRESCALER_128:
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    break;
    default:
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    break;
  }
  ADCSRA |= (1 << ADEN);

}

/**
[realizar_leitura AD]
@param  u8_pino_adc [Recebe o pino em que a leitura AD será realizada]
@return          [Retorna a variável com um valor de leitura AD]
*/
uint16_t adc_read(uint8_t u8_pino_adc) {
  uint8_t alto, baixo;
  switch (u8_pino_adc) {
    case 0:
    DDRC &= ~(1 << DDC0); //Setting arduino port A0 like INPUT
    ADMUX &= ~(1 << MUX0);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits



    break;
    case 1:
    DDRC &= ~(1 << DDC1); //Setting arduino port A1 like INPUT
    ADMUX |= (1 << MUX0);
    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits



    break;
    case 2:
    DDRC &= ~(1 << DDC2); //Setting arduino port A2 like INPUT
    ADMUX |= (1 << MUX1);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits


    break;
    case 3:
    DDRC &= ~(1 << DDC3); //Setting arduino port A3 like INPUT
    ADMUX |= (1 << MUX0) | (1 << MUX1);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits


    break;
    case 4:
    DDRC &= ~(1 << DDC4); //Setting arduino port A4 like INPUT
    ADMUX |= (1 << MUX2);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits


    break;
    case 5:
    DDRC &= ~(1 << DDC5); //Setting arduino port A5 like INPUT
    ADMUX |= (1 << MUX2) | (1 << MUX0);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits


    break;
    default:
    DDRC &= ~(1 << DDC0); //Setting arduino port A0 like INPUT
    ADMUX &= ~(1 << MUX0);

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits


    break;
    ADMUX &= ~(1 << ADLAR);
  }
}
