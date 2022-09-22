#include <stdio.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"

#include "wifi.h"
#include "http_client.h"
#include "mqtt.h"

#include "dht11.h"
#include "heartbeat.h"

#include <driver/adc.h>

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

int temperatura = 0;
int humidade = 0; 

int valorPwm;

#define LED_1 2

void ledTeste(void * params) {

    // Configuração do Timer
    ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_8_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 10000,
      .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);

    // Configuração do Canal
    ledc_channel_config_t channel_config = {
      .gpio_num = LED_1,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0
    };
    ledc_channel_config(&channel_config);


    // Utilizando o PWM
    while(true)
    {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (int)valorPwm);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void conectadoWifi(void * params)
{
  while(true)
  {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }

  }

}

void trataComunicacaoComServidor(void * params)
{
  char mensagem[50];
  char JsonAtriubutos[200];
  adc1_config_width(ADC_WIDTH_BIT_12);
  DHT11_init(GPIO_NUM_4);
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {

      sprintf(mensagem, "{\"batimento\": %d}", batimentos);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      temperatura  =  DHT11_read().temperature;
      humidade = DHT11_read().humidity;

      sprintf(mensagem, "{\"temperature\": %d}", temperatura);
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      int hall = hall_sensor_read();
      // touch_pad_init();
      // int touch = touchRead(35);
      // printf("%d",touch);

      sprintf(JsonAtriubutos, "{\"magnetismo\": %d,\n\"humidade\": %d}", hall, humidade);
      mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtriubutos);   

      vTaskDelay(3000 / portTICK_PERIOD_MS);

    }
  }
}

void app_main(void)
{
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

      ESP_ERROR_CHECK(nvs_flash_erase());

      ret = nvs_flash_init();

    }

    ESP_ERROR_CHECK(ret);

    conexaoWifiSemaphore = xSemaphoreCreateBinary();

    conexaoMQTTSemaphore = xSemaphoreCreateBinary();

    wifi_start();



    xTaskCreate(&conectadoWifi,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
    xTaskCreate(&heartbeat_init, "Batimento cardiaco", 4096, NULL, 1, NULL);
    xTaskCreate(&ledTeste, "PWD Led", 4096, NULL, 1, NULL);





}