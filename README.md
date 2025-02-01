## EMBARCATECH ##

  ## Tarefa 5 ##

# Controle de LEDs com PWM

Este projeto demonstra como controlar LEDs usando PWM (Pulse Width Modulation) com o microcontrolador RP2040 (Raspberry Pi Pico).
O código ajusta a frequência e o Duty Cycle dos LEDs vermelho, verde e azul de forma independente.

## Descrição

- **LED Vermelho**: Acionado com PWM de 1 kHz. Duty Cycle inicia em 5% e é atualizado a cada 2 segundos em incrementos de 5%.
- Quando atinge o valor máximo, retorna a 5% e continua incrementando.
- **LED Verde**: Acionado com PWM de 10 kHz. Duty Cycle permanece constante.
- **LED Azul**: Controlado de forma independente. Duty Cycle inicia em 5% e é atualizado a cada 2 segundos em incrementos de 5%.
- Quando atinge o valor máximo, retorna a 5% e continua incrementando.

## Requisitos

- Raspberry Pi Pico
- LEDs (vermelho, verde e azul)
- Resistor apropriado para cada LED
- Breadboard e jumpers
- Feito no visual studio code
- Com a BitDogLab

## Instalação

1. Clone este repositório para o seu ambiente de desenvolvimento:
   ```bash
   git clone https://github.com/CostaDianna/EmbarcaTech.git
