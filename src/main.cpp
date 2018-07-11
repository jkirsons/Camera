// https://github.com/igrr/esp32-cam-demo/issues/29
// http://web.mit.edu/6.111/www/f2015/tools/OV7670_2006.pdf
// https://github.com/bitluni/ESP32CameraI2S
// https://github.com/igrr/esp32-cam-demo
// https://github.com/tekker/esp32-ov7670-hacking

// https://github.com/spotify/linux/blob/master/drivers/media/video/ov7670.c
// https://github.com/torvalds/linux/blob/master/drivers/media/i2c/ov7670.c

// https://github.com/cmmakerclub/esp32-webserver

#undef EPS
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/opencl/ocl_defs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ximgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc.hpp"
#define EPS 192

#include "OV7670.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include "BMP.h"

//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "WiFiSrv.h"
#include "esp_log.h"

using namespace cv;

const int SIOD = 22; //SDA
const int SIOC = 23; //SCL

const int VSYNC = 21;
const int HREF = 19;

const int XCLK = 25;
const int PCLK = 18;

const int D0 = 14;
const int D1 = 12;
const int D2 = 15;
const int D3 = 32;
const int D4 = 27;
const int D5 = 4;
const int D6 = 16;
const int D7 = 17;

#define ssid1 "Tomato24"
#define password1 "Stephen123"

OV7670 *camera;
unsigned char bmpHeader[BMP::headerSize];
/*
void http_server_netconn_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  err_t err;
  char http_index_hml[] = "<style>body{margin: 0}\nimg{height: 100%; width: auto}</style>"
                          "<img id='a' src='/camera' onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now(); '>"
                          "<img id='b' style='display: none' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now(); '>\n";

  // Read the data from the port, blocking if nothing yet there.
  // We assume the request (the part we care about) is in one netbuf 
  err = netconn_recv(conn, &inbuf);
  if (err == ERR_OK)
  {
    netbuf_data(inbuf, (void **)&buf, &buflen);
    //printf("buffer = %s \n", buf);
    if (buflen >= 5 && buf[0] == 'G' && buf[1] == 'E' && buf[2] == 'T' && buf[3] == ' ' && buf[4] == '/')
    {
      netconn_write(conn, http_html_hdr, sizeof(http_html_hdr) - 1, NETCONN_NOCOPY);
      if (buf[5] == 'c')
      {
        //netconn_write(conn, json_unformatted, strlen(json_unformatted), NETCONN_NOCOPY);
        netconn_write(conn, (const uint8_t *)(bmpHeader), (size_t)(BMP::headerSize), NETCONN_NOCOPY);
        netconn_write(conn, (const uint8_t *)(camera->frame), (size_t)(camera->xres * camera->yres * 2), NETCONN_NOCOPY);
      }
      else
      {
        netconn_write(conn, http_index_hml, sizeof(http_index_hml) - 1, NETCONN_NOCOPY);
      }
    }
  }
  // Close the connection (server closes in HTTP) 
  netconn_close(conn);
  netbuf_delete(inbuf);
}
*/

WiFiMulti wifiMulti;
WiFiServer server(80);

static bool endsWith(const std::string &str, const std::string &suffix)
{
  return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

void serve()
{
  WiFiClient client = server.available();
  if (client) 
  {
    //Serial.println("New Client.");
    std::string currentLine = "";
    while (client.connected()) 
    {
      //camera->oneFrame();
      if (client.available()) 
      {
        char c = client.read();
        if (c == '\n') 
        {
          if (currentLine.length() == 0) 
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(
              "<style>body{margin: 0}\nimg{height: 100%; width: auto}</style>"
              "<img id='a' src='/camera' onload='this.style.display=\"initial\"; var b = document.getElementById(\"b\"); b.style.display=\"none\"; b.src=\"camera?\"+Date.now(); '>"
              "<img id='b' style='display: none' src='/camera' onload='this.style.display=\"initial\"; var a = document.getElementById(\"a\"); a.style.display=\"none\"; a.src=\"camera?\"+Date.now(); '>");
            client.println();
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {
          currentLine += c;
        }
        
        if(endsWith(currentLine, "GET /camera"))
        {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:image/bmp");
            client.println();
            
            //for(int i = 0; i < BMP::headerSize; i++)
            //   client.write(bmpHeader[i]);
            //for(int i = 0; i < camera->xres * camera->yres * 2; i++)
            //   client.write(camera->frame[i]);
            client.write((const uint8_t*)(bmpHeader), (size_t)(BMP::headerSize));
            client.write((const uint8_t*)(camera->frame), (size_t)(camera->xres * camera->yres * 2));
            
        }
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("Client Disconnected.");
  }  
}


//void loop(void *pvParameter)
void loop()
{
  camera->oneFrame();
  //vTaskDelay(100 / portTICK_PERIOD_MS);
  //ESP_LOGI("loop", "Frame Captured");
  serve();
}
/*
extern "C"
{
  void app_main();
}
*/
//void app_main()
void setup()
{
  Serial.begin(115200);
  
  Mat right_for_matcher;
  Mat left_for_matcher = Mat(camera->xres, camera->yres,	CV_8UC1, camera->frame, 1);
  

  Mat left_disp,right_disp;
  Mat filtered_disp;
  int max_disp = 160;
  int wsize = 21;
  Ptr<StereoBM> left_matcher = StereoBM::create(max_disp,wsize);
  Ptr<cv::ximgproc::DisparityWLSFilter> wls_filter = cv::ximgproc::createDisparityWLSFilter(left_matcher);
  Ptr<StereoMatcher> right_matcher = cv::ximgproc::createRightMatcher(left_matcher);
  cvtColor(left_for_matcher,  left_for_matcher,  COLOR_BGR2GRAY);
  cvtColor(right_for_matcher, right_for_matcher, COLOR_BGR2GRAY);
  left_matcher-> compute(left_for_matcher, right_for_matcher,left_disp);
  right_matcher->compute(right_for_matcher,left_for_matcher, right_disp);
  

  wifiMulti.addAP(ssid1, password1);
  //wifiMulti.addAP(ssid2, password2);
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }

  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
/*
  wifi_config_t sta_config;
  memmove(sta_config.sta.ssid, ssid1, sizeof(sta_config.sta.ssid));
  memmove(sta_config.sta.password, password1, sizeof(sta_config.sta.password));
  WiFiSrv(sta_config);
*/  
  server.begin();
  //xTaskCreate(&loop, "loop_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
