#include <stdio.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "dht11.h"

#include "wifi.h"
#include "http_client.h"

// xSemaphoreHandle conexaoWifiSemaphore;

// void RealizaHTTPRequest(void * params)
// {
//   while(true)
//   {
//     if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
//     {
//       ESP_LOGI("Main Task", "Realiza HTTP Request");
//       http_request();
//       //https_request();
//     }
//   }
// }

// void app_main(void)
// {
//     // Inicializa o NVS
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//       ESP_ERROR_CHECK(nvs_flash_erase());
//       ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);
    
//     conexaoWifiSemvoid app_main(void) {
//     semaphore = xSemaphoreCreateBinary();
//     wifi_start();

//     xTaskCreate(&RealizaHTTPRequest,  "Processa HTTP", 4096, NULL, 1, NULL);
    
// }

void pegaTemperatura(void * params) {
    DHT11_init(GPIO_NUM_4);
    while(1) {
        printf("Temperature is %d \n", DHT11_read().temperature);
        printf("Humidity is %d\n", DHT11_read().humidity);
        printf("Status code is %d\n", DHT11_read().status);
        vTaskDelay( 1000 / portTICK_PERIOD_MS);
    }

}

void app_main()
{

  xTaskCreate(&pegaTemperatura, "Pega temperatura", 4096, NULL, 1, NULL);


}