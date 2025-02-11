// Embarcatec
// Tarefa - Aula Sincrona - 06/02/2025
// Discente: Alexsami Lopes

#include <stdio.h> //biblioteca padrão da linguagem C
#include "pico/stdlib.h" //subconjunto central de bibliotecas do SDK Pico
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define PWM_LED 22 //pino do LED conectado a GPIO como PWM
const uint16_t WRAP_PERIOD = 50000; //valor máximo do contador - WRAP, valor encontrado substituindo 50hz na função 𝑓𝑃𝑊𝑀
const float PWM_DIVISER = 50.0; //divisor do clock para o PWM, valor encontrado substituindo 50hz na função 𝑓𝑃𝑊𝑀
const uint16_t LED_STEP = 5; //passo de incremento/decremento para o duty cycle do LED
uint16_t led_level = 1250; //nível inicial do pwm (duty cycle) OBS: na verdade o mínimo deveria ser 1360 através de testes, mas como na Tarefa pediu 0.025, decidi usar o da Tarefa

//função para configurar o módulo PWM
void pwm_setup()
{
    gpio_set_function(PWM_LED, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(PWM_LED); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, PWM_DIVISER); //define o divisor de clock do PWM

    pwm_set_wrap(slice, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_gpio_level(PWM_LED, 6000); //definir o cico de trabalho (duty cycle) do pwm

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente
}


//função principal
int main()
{
    stdio_init_all(); //inicializa o sistema padrão de I/O
    
    pwm_setup(); //configura o PWM
    pwm_set_gpio_level(PWM_LED, 6000); //define o nível atual do PWM (duty cycle) 0.12 * 50000
    sleep_ms(5000); // Atraso de 1 segundo

    pwm_set_gpio_level(PWM_LED, 3675); //define o nível atual do PWM (duty cycle) 0.0735 * 50000 OBS: Em testes iniciais encontrou-se que o melhor valor deveria ser 3680 = (6000 + 1360)/2, ou seja a média
    sleep_ms(5000); // Atraso de 1 segundo

    pwm_set_gpio_level(PWM_LED, 1250); //define o nível atual do PWM (duty cycle) 0.025 * 50000  OBS: na verdade o mínimo deveria ser 1360 através de testes, mas como na Tarefa pediu 0.025, decidi usar o da Tarefa
    sleep_ms(5000); // Atraso de 1 segundo    

    uint up_down = 1; //variável para controlar se o nível do LED aumenta ou diminui

    //loop principal
    while (true) {

        printf("Ciclo ativo:%d\n", led_level);//imprimir ciclo ativo do PWM - valor máximo é 6000
        
        pwm_set_gpio_level(PWM_LED, led_level); //define o nível atual do PWM (duty cycle)


        sleep_ms(10); // Atraso de 1 segundo

        if (up_down) 
        {
            led_level += LED_STEP; // Incrementa o nível do LED
            if (led_level >= 6000) // 0.12 * 50000
                up_down = 0; // Muda direção para diminuir quando atingir o período máximo
        }
        else
        {
            led_level -= LED_STEP; // Decrementa o nível do LED
            if (led_level <= 1250) // 0.025 * 50000 OBS: na verdade o mínimo deveria ser 1360 através de testes, mas como na Tarefa pediu 0.025, decidi usar o da Tarefa
                up_down = 1; // Muda direção para aumentar quando atingir o mínimo
        }

    }
}
