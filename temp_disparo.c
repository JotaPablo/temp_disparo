#include <stdio.h>
#include "pico/stdlib.h"

#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12

#define BUTTON_A 5


static volatile bool leds_ativos = false;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
static void gpio_irq_handler(uint gpio, uint32_t events);
int64_t turn_off_BLUE_callback(alarm_id_t id, void *user_data);
int64_t turn_off_RED_callback(alarm_id_t id, void *user_data);
int64_t turn_off_GREEN_callback(alarm_id_t id, void *user_data);

int main()
{
    stdio_init_all();

    gpio_init(RED_PIN);              // Inicializa o pino do LED
    gpio_set_dir(RED_PIN, GPIO_OUT); // Configura o pino como saída
    gpio_init(GREEN_PIN);              // Inicializa o pino do LED
    gpio_set_dir(GREEN_PIN, GPIO_OUT); // Configura o pino como saída
    gpio_init(BLUE_PIN);              // Inicializa o pino do LED
    gpio_set_dir(BLUE_PIN, GPIO_OUT); // Configura o pino como saída

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        
    }
}


void gpio_irq_handler(uint gpio, uint32_t events)
{   
    // Verifica se os leds estão desativados
    if( leds_ativos == false){

        uint32_t current_time = to_us_since_boot(get_absolute_time());

        //Verifica se o tempo de debounce passou
        if (current_time - last_time > 200000) {
            last_time = current_time; // Atualiza o tempo do último evento
            
            //Liga todos os leds
            gpio_put(RED_PIN, true);
            gpio_put(BLUE_PIN, true);
            gpio_put(GREEN_PIN, true);

            //Marca que os leds estão ligados
            leds_ativos = true;

            //Agenda o alarme daqui 3 segundo para desligar o led azul
            add_alarm_in_ms(3000, turn_off_BLUE_callback, NULL, false);

        }
    }
}

int64_t turn_off_BLUE_callback(alarm_id_t id, void *user_data){
    //Desliga Led Azul, resta o Vermelho e Verde
    gpio_put(BLUE_PIN, false);

    //Agenda o alarme daqui 3 segundo para desligar o led vermelho
    add_alarm_in_ms(3000, turn_off_RED_callback, NULL, false);

    return 0; //Para o alarme não se repetir
}

int64_t turn_off_RED_callback(alarm_id_t id, void *user_data){
    //Desliga Led Vermelho, resta o Verde
    gpio_put(RED_PIN, false);

    //Agenda o alarme daqui 3 segundo para desligar o led verde
    add_alarm_in_ms(3000, turn_off_GREEN_callback, NULL, false);

    return 0; //Para o alarme não se repetir
}

int64_t turn_off_GREEN_callback(alarm_id_t id, void *user_data){
    //Desliga Led Verde. Agora todos os Leds estão desligados
    gpio_put(GREEN_PIN, false);

    leds_ativos = false; //Todos os leds estão apagados

    return 0; //Para o alarme não se repetir
}