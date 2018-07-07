#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "freertos/portmacro.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "tcpip_adapter.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/api.h"

#include "string.h"
#include "cJSON.h"

#define LED_BUILTIN 16
#define delay(ms) (vTaskDelay(ms/portTICK_RATE_MS))

const static char http_html_hdr[]  = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_hml[] = "<!DOCTYPE html>"
          "<html>\n"
          "<head>\n"
          "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
          "  <style type=\"text/css\">\n"
          "    html, body, iframe { margin: 0; padding: 0; height: 100%; }\n"
          "    iframe { display: block; width: 100%; border: none; }\n"
          "  </style>\n"
          "<title>HELLO ESP32</title>\n"
          "</head>\n"
          "<body>\n"
          "<h1>Hello World, from ESP32!</h1>\n"
          "</body>\n"
          "</html>\n";  
const int CONNECTED_BIT = BIT0;          

void WiFiSrv();
esp_err_t event_handler(void *ctx, system_event_t *event);
void initialise_wifi(void);
void http_server_netconn_serve(struct netconn *conn);
void http_server(void *pvParameters);
void generate_json(void *pvParameters);
