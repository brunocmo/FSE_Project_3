#include <stdio.h>
#include <stdlib.h>
// Include FreeRTOS for delay
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "heartbeat.h"

#define LED 2 // LED connected to GPIO2

int app_main() {

    heartbeat_init();

    return 0;

}