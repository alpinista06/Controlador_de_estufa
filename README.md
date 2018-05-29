# Estufa Automatizada
Projeto de um sistema para uma estufa automatizada e controlada para a disciplina de Sistemas Embarcados na Universidade Federal de Uberlândia.

## Descrição

>Tudo começou com o desejo de um jovem entusiasta das novas tecnologias de tomar um suco de abacaxi com hortelâ. Para o cultivo caseiro de hortelâs veio a tona a ideia de criar um estufa automatizada e controlada por uma aplicação móvel. Abaixo temos as informações sobre o projeto.  

## Sobre o projeto

>Os arquivos estão divididos da seguinte maneira:
* **Aplicativo**: Código para ser importado no [AppInvetor](http://appinventor.mit.edu/explore/).
* **Firmware**: Códigos desenvolvidos para o microcontrolador [ATMEGA328P](https://www.microchip.com/wwwproducts/en/ATmega328P).
* **Hardware**: Circuito eletrônico, diagramas de conexão e esquemas de montagem.
* **resourses**: Images utilizadas neste README, referências, artigo, etc.

## Aplicativo

>O aplicativo foi desenvolvido no AppInvetor e faz a interface Homem-Máquina do sistema. Abaixo uma imagem da sua interface:

![](Aplicativo/print_do_app.jpeg)

## Firmware

>O Firmware foi feito usando programação C em modo Bare Metal para o microcontrolador [ATMEGA328P](https://www.microchip.com/wwwproducts/en/ATmega328P), que é usando na [**arduino UNO R3**](https://www.arduino.cc/). O seu código pode ser resumindo através da seguinte máquina de estados:

![](Maquina_de_estados_Estufa_controlada.jpg)

>Para isso, o software foi separado em diversas partes:
* **main_irrigador.ino**: Máquina de estados e código unindo todas as bibliotecas e demais funções;
* **leitura_analogica**: Biblioteca desenvolvida para configurar e realizar leituras do [conversor AD](https://pt.wikipedia.org/wiki/Conversor_anal%C3%B3gico-digital) do microcontrolador.
* **comunicacao_uart**: Biblioteca desenvolvida para realizar a [comunicação serial](https://pt.wikipedia.org/wiki/Comunica%C3%A7%C3%A3o_serial) do sistema, configurando os registradores do microcontrolador, enviando e recebendo informações da aplicação móvel.
* **library_pwm**: Biblioteca de controle do *pwm* [Pulse Width Modulation](https://pt.wikipedia.org/wiki/Modula%C3%A7%C3%A3o_por_largura_de_pulso) do microcontrolador.
* **general_input_output**: Biblioteca de I/O (não utilizada nesta aplicação).
* **arduino_timers**: Controle dos timers internos do arduino (não utilizada nesta aplicação).

## Licence

Se isso foi util de alguma forma, nos pague uma cerveja. Vlws.

## Autores

* **Mário Borges** - github.com/alpinista06
* **Talles Rodrigues**

Colaborador: Ítalo Fernandes - github.com/italogfernandes
