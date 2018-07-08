//#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "freertos/portmacro.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "tcpip_adapter.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/api.h"

#include "string.h"

#define delay(ms) (vTaskDelay(ms/portTICK_RATE_MS))

const static char http_html_hdr[]  = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
       
const int CONNECTED_BIT = BIT0;          

void WiFiSrv(wifi_config_t sta_config);
esp_err_t event_handler(void *ctx, system_event_t *event);
void initialise_wifi(wifi_config_t sta_config);
void http_server_netconn_serve(struct netconn *conn);
void http_server(void *pvParameters);
