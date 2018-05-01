# Controlador de estufa
Projeto de um sistema de estufa automatizada para a disciplina de SEMB.

## Neste repositório

Os arquivos estão divididos da seguinte maneira:
* **Aplicativo**: Código para ser importado no AppInvetor.
* **Firmware**: Códigos desenvolvidos para o microcontrolador **ATMEGA328P**.
* **Hardware**: Circuito eletrônico, diagramas de conexão e esquemas de montagem.
* **resourses**: Images utilizadas neste README, referências, artigo, etc.

## Aplicativo

O aplicativo foi desenvolvido no AppInvetor, abaixo uma imagem da sua interface:

![](Aplicativo/print_do_app.jpeg)

## Firmware

O Firmware foi feito através da seguinte máquina de estados:

![](resourses/state_machine_diagram.jpeg)

Para isso, o software foi separado em diversas partes:
* **main_irrigador.ino**: Máquina de estados e código unindo todas as bibliotecas;
* **leitura_analogica**: Biblioteca desenvolvida para configurar e realizar leituras do conversor AD do arduino.
* **comunicacao_uart**: Códigos de comunicação serial, configurando, enviando e recebendo informações.
* **library_pwm**: Biblioteca de controle do pwm do arduino.
* **general_input_output**: Biblioteca de I/O.
* **arduino_timers**: Controle dos timers internos do arduino.

## Licence

Se isso foi util de alguma forma, nos pague uma cerveja. Vlws.

## Autores

* **Mário Borges** - github.com/alpinista06
* **Talles Rodrigues**

Colaborador: Ítalo Fernandes - github.com/italogfernandes
