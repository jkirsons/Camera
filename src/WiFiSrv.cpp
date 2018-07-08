#include "WiFiSrv.h"

static EventGroupHandle_t wifi_event_group;
char* json_unformatted;

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        printf("got ip\n");
        printf("ip: " IPSTR "\n", IP2STR(&event->event_info.got_ip.ip_info.ip));
        printf("netmask: " IPSTR "\n", IP2STR(&event->event_info.got_ip.ip_info.netmask));
        printf("gw: " IPSTR "\n", IP2STR(&event->event_info.got_ip.ip_info.gw));
        printf("\n");
        fflush(stdout);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void initialise_wifi(wifi_config_t sta_config)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}

void http_server(void *pvParameters)
{
  //ESP_LOGI("http", "Begin Server Loop");    
  struct netconn *conn, *newconn;
  err_t err;
  conn = netconn_new(NETCONN_TCP);
  ESP_ERROR_CHECK( netconn_bind(conn, NULL, 80) );
  ESP_ERROR_CHECK( netconn_listen(conn) );
  do {
     err = netconn_accept(conn, &newconn);
     if (err == ERR_OK) {
       http_server_netconn_serve(newconn);
       ESP_ERROR_CHECK( netconn_delete(newconn) );
     }
     vTaskDelay(100 / portTICK_PERIOD_MS);
   } while(err == ERR_OK);
   ESP_ERROR_CHECK( netconn_close(conn) );
   ESP_ERROR_CHECK( netconn_delete(conn) );
   //ESP_LOGI("http", "End Server Loop");    
  
}

void WiFiSrv(wifi_config_t sta_config) {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    ESP_ERROR_CHECK( nvs_flash_init() );
    initialise_wifi(sta_config);
    xTaskCreate(http_server, "http_server", 2048, NULL, 5, NULL);
}