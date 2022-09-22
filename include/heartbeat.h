#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <driver/gpio.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void heartbeat_init();

uint32_t batimentos;

#endif