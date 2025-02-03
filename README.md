# Controle de LEDs com Raspberry Pi Pico - BitDogLab

Projeto desenvolvido para controlar LEDs (vermelho, verde e azul) utilizando um **Raspberry Pi Pico** e a função `add_alarm_in_ms()` do **Pico SDK** para temporização. O sistema é acionado por um botão e simula a sequência de LEDs acesos, com mudanças de estado a cada 3 segundos.

## Descrição
Este projeto utiliza um **Raspberry Pi Pico** com três LEDs (vermelho, verde e azul) e um botão. Ao pressionar o botão, os LEDs são ativados um a um, com intervalos de **3 segundos** entre as transições.

## Funcionalidades
- **Acionamento dos LEDs**:
  - 🔵 LED Azul → 🔴 LED Vermelho → 🟢 LED Verde
- **Temporização controlada**:
  - Utiliza a função `add_alarm_in_ms()` para desligar os LEDs em sequência após 3 segundos.
  - 3 segundos → 🔵 Desliga LED Azul → 3 segundos → 🔴 Desliga LED Vermelho → 3 segundos → 🟢 Desliga LED Verde
- **Desabilitação do botão durante o processo**:
  - O botão só pode ser acionado após todos os LEDs terem sido desligados.
- **Debounce do botão**:
  - Implementação de debounce para evitar múltiplos acionamentos durante a execução das rotinas de temporização.

## Estrutura do Projeto

| Arquivo           | Descrição                                             |
|-------------------|-------------------------------------------------------|
| `temp_disparo.c`  | Código principal com controle dos LEDs e do botão     |
| `CMakeLists.txt`  | Arquivo de build do CMake                             |
| `diagram.json`   | Arquivo de configuração para simulação no Wokwi |
| `wokwi.toml`  | Configurações do simulador Wokwi              |

## Instalação
1. **Pré-requisitos**
   - Clone o repositório:
     ```bash
     git clone https://github.com/JotaPablo/temp_disparo.git
     cd temp_disparo
     ```
   - Instale o **Visual Studio Code** com as seguintes extensões:
     - **Raspberry Pi Pico SDK**
     - **WokWi**
2. **Compilação**
   - Compile o projeto no terminal:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
   - Ou através da extensão da Raspeberry Pi Pico no VS CODE


3. **Execução**
   - **Na placa física**: 
     - Conecte o Raspberry Pi Pico ao computador em modo **BOOTSEL**.
     - Copie o arquivo `.uf2` gerado na pasta `build` para o dispositivo identificado como `RPI-RP2` ou através da extensão da Raspeberry Pi Pico no VS CODE
.
   - **No simulador Wokwi**: 
     - Utilize o Wokwi para simular o comportamento do projeto.

## Hardware
| Componente       | GPIO | Função                  |
|------------------|------|-------------------------|
| LED Vermelho     | 13   | LED configurável      |
| LED Verde        | 11   | LED configurável    |
| LED Azul         | 12   | LED configurável    |
| Botão (Button A) | 5    | Aciona os LEDs          |

## Requisitos Atendidos
✅ Quando o botão é pressionado, todos os LEDs são ativados.

✅ LEDs são desativados um por um com intervalos de 3 segundos.

✅ O botão só pode ser acionado novamente após todos os LEDs estarem apagados.

✅ Implementação de debounce para o botão.

✅ O sistema utiliza a função `add_alarm_in_ms()` para gerenciar o tempo entre as mudanças de estado dos LEDs.

