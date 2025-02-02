#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs
#define led_b 11
#define led_r 12
#define led_g 13

// Definição do pino do botão de pressão
#define push_botton 5

// Variável para armazenar o tempo da última ativação do botão
uint32_t tempo = 0;

// Callback para desligar o LED azul
int64_t turn_off_callback_blue(alarm_id_t id, void *user_data) {
    gpio_put(led_b, false);
    return 0;
}

// Callback para desligar o LED verde
int64_t turn_off_callback_green(alarm_id_t id, void *user_data) {
    gpio_put(led_g, false);
    return 0;
}

// Callback para desligar o LED vermelho
int64_t turn_off_callback_red(alarm_id_t id, void *user_data) {
    gpio_put(led_r, false);
    return 0;
}

int main() {
    stdio_init_all(); // Inicializa todas as saídas padrão

    gpio_init(led_b); // Inicializa o pino do LED azul
    gpio_set_dir(led_b, GPIO_OUT); // Define o pino do LED azul como saída

    gpio_init(led_r); // Inicializa o pino do LED vermelho
    gpio_set_dir(led_r, GPIO_OUT); // Define o pino do LED vermelho como saída

    gpio_init(led_g); // Inicializa o pino do LED verde
    gpio_set_dir(led_g, GPIO_OUT); // Define o pino do LED verde como saída

    gpio_init(push_botton); // Inicializa o pino do botão de pressão
    gpio_set_dir(push_botton, GPIO_IN); // Define o pino do botão de pressão como entrada
    gpio_pull_up(push_botton); // Ativa o resistor de pull-up interno no botão de pressão

    while (true) {
        uint32_t tempo_atual = to_ms_since_boot(get_absolute_time()); // Obtém o tempo atual em milissegundos desde a inicialização

        // Verifica se o botão de pressão está pressionado e o LED vermelho está desligado
        if (gpio_get(push_botton) == false && gpio_get(led_r) == false) {

            // Implementa o debounce: verifica se 50 milissegundos se passaram desde a última ativação
            if ((tempo_atual - tempo) > 50) {
                
                tempo = tempo_atual; // Atualiza o tempo da última ativação

                // Verifica novamente se o botão ainda está pressionado
                if (gpio_get(push_botton) == false) {

                    gpio_put(led_b, true); // Liga o LED azul
                    gpio_put(led_g, true); // Liga o LED verde
                    gpio_put(led_r, true); // Liga o LED vermelho

                    // Configura alarmes para desligar os LEDs após intervalos específicos
                    add_alarm_in_ms(3000, turn_off_callback_blue, NULL, false); // Desliga o LED azul após 3 segundos

                    add_alarm_in_ms(6000, turn_off_callback_red, NULL, false); // Desliga o LED vermelho após 6 segundos

                    add_alarm_in_ms(9000, turn_off_callback_green, NULL, false); // Desliga o LED verde após 9 segundos
                }
            }
        }

        sleep_ms(10); // Atraso de 10 milissegundos para reduzir o uso da CPU
    }
}
