#include <stdio.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"


#include "wifi.h"
#include "http_client.h"
#include "mqtt.h"

#include "dht11.h"

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

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
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {
       float temperatura = 20.0 + (float)rand()/(float)(RAND_MAX/10.0);
       sprintf(mensagem, "{\"temperature\": %f}", temperatura);
       mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

       sprintf(JsonAtriubutos, "{\"quantidade de pinos\": 5,\n\"umidade\": 20}");
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
}


void pegaTemperatura(void * params) {
    DHT11_init(GPIO_NUM_4);
    while(1) {
        printf("Temperature is %d \n", DHT11_read().temperature);
        printf("Humidity is %d\n", DHT11_read().humidity);
        printf("Status code is %d\n", DHT11_read().status);
        vTaskDelay( 1000 / portTICK_PERIOD_MS);
    }

}