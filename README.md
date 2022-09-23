# Trabalho 3 - 2022-1

Trabalho 3 da disciplina de Fundamentos de Sistemas Embarcados (2022/1)

Para acessar o projeto, clique [aqui](https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-3-2022-1).

***

## Aluno
|Matrícula | Aluno |
| -- | -- |
| 18/0117548  |  [Bruno Carmo Nunes](https://github.com/brunocmo) |
| 17/0150747  |  [Marcos Vinícius Rodrigues da Conceição](https://github.com/marcos-mv ) |

## Requisitos

O software foi feito para utilização em uma esp32doit-devkit-v1.

É necessário a utilização do framework de desenvolvimento da Espressif IoT - https://github.com/espressif/esp-idf

Também é possivel com a utilização da extensão do Visual Studio Code chamada Platform IO - https://platformio.org/

***
## Instalação 
Baixe o repositório e acesse a pasta.

`git clone https://github.com/brunocmo/FSE_Project_3.git`

`cd FSE_Project_3`

Por praticidade, foi utilizado os comandos vindos do terminal da Platform IO.
Para fazer a configuração do wifi no menu do programa:

`platformio run -t menuconfig`

Para fazer a build do programa:

`platformio run --environment esp32doit-devkit-v1`

Para carregar o programa na esp32:

`platformio run --target upload --environment esp32doit-devkit-v1`

Para monitorar a esp32:

`platformio device monitor --environment esp32doit-devkit-v1`

***
## Uso

Configure o wifi pelo menuconfig na opção "Configuração do Wifi Configuration"

Ao iniciar o programa, veja as funcionalidades implementadas na dashboard.

***
## Imagens

1. Imagem da esp32

![esp32](/doc/esp32.jpeg)


2. Dashborad com os valores implementados

![Controle1](/doc/thinkboard.png)

***
