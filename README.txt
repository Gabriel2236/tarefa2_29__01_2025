## Projeto de Controle de LEDs com Raspberry Pi Pico

Este projeto demonstra como controlar três LEDs (azul, verde e vermelho) usando um botão de pressão com um Raspberry Pi Pico. Os LEDs são ligados quando o botão é pressionado e desligados após intervalos de tempo específicos, utilizando funções de callback e timers.

### Hardware Utilizado

- Raspberry Pi Pico
- LEDs (azul, verde e vermelho)
- Botão de pressão
- Resistores
- Protoboard e jumpers

### Pinos de Conexão

- LED azul: GPIO 11
- LED verde: GPIO 13
- LED vermelho: GPIO 12
- Botão de pressão: GPIO 5

### Código

O código está escrito em C e utiliza a biblioteca `pico/stdlib.h` e `hardware/timer.h` do SDK do Raspberry Pi Pico.

### Descrição do Código

1. **Definições de Pinos:** Os pinos dos LEDs e do botão de pressão são definidos.
2. **Inicializações:** Inicializa os pinos dos LEDs e do botão de pressão, configura os pinos dos LEDs como saída e o pino do botão como entrada com resistor de pull-up.
3. **Funções de Callback:** Define três funções de callback para desligar os LEDs azul, verde e vermelho após intervalos específicos.
4. **Loop Principal:** No loop `while(true)`, o tempo atual é obtido e verificado se o botão foi pressionado e se o LED vermelho está desligado.
   - A lógica de debounce é aplicada para garantir que o botão não seja ativado várias vezes devido a oscilações elétricas.
   - Se o botão ainda estiver pressionado após o debounce, os LEDs são ligados e os alarmes são configurados para desligá-los após 3, 6 e 9 segundos, respectivamente.
5. **Atraso de 10 ms:** Adiciona um pequeno atraso de 10 milissegundos para reduzir o uso da CPU.
