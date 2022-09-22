#include "heartbeat.h"

static const char *TAG = "ADC EXAMPLE";
esp_adc_cal_characteristics_t adc1_chars;

void heartbeat_init() {
    
    // gpio_config_t io_conf;
    // io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    // io_conf.mode = GPIO_MODE_OUTPUT;
    // io_conf.pin_bit_mask = (1ULL << LED);
    // io_conf.pull_down_en = 0;
    // io_conf.pull_up_en = 0;
    // gpio_config(&io_conf);

    // gpio_set_level(LED, 1);
    // vTaskDelay(1000 / portTICK_RATE_MS);
    // gpio_set_level(LED, 0);
    // vTaskDelay(1000 / portTICK_RATE_MS);

    int toVivo = 0;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0));
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));



    int incrementador = 0;
    int minimo = 3000;
    int maximo = 0;

    int minimoSecond = 3000;
    int maximoSecond = 0;

    int limit = 0;

    while(1) {
        batimentos = adc1_get_raw(ADC1_CHANNEL_6);


        if(batimentos > limit) {
            if(!toVivo) {
                ESP_LOGI(TAG, "BATIDA!");
            }
            toVivo = 1;
        } else {
            toVivo = 0;
        }

        vTaskDelay(200 / portTICK_RATE_MS);

        if (batimentos > maximo) maximo = batimentos;
        if (batimentos < minimo) minimo = batimentos;

        limit = maximo - minimo;
        limit = (int)((float)(limit) * 0.2);
        limit = maximo - limit;

        // ESP_LOGI(TAG, "valor: %d || %d ", batimentos, limit);
        
        incrementador++;


        if(incrementador > 32 && incrementador < 42 ){
            if (batimentos > maximoSecond) maximoSecond = batimentos;
            if (batimentos < minimoSecond) minimoSecond = batimentos;
        }

        if (incrementador>43) {
            incrementador = 0;
            maximo = maximoSecond;
            minimo = minimoSecond;
            minimoSecond = 3000;
            maximoSecond = 0;
        }

    }

}