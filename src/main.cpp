// https://github.com/igrr/esp32-cam-demo/issues/29
// http://web.mit.edu/6.111/www/f2015/tools/OV7670_2006.pdf
// https://github.com/bitluni/ESP32CameraI2S
// https://github.com/igrr/esp32-cam-demo
// https://github.com/tekker/esp32-ov7670-hacking

// https://github.com/spotify/linux/blob/master/drivers/media/video/ov7670.c
// https://github.com/torvalds/linux/blob/master/drivers/media/i2c/ov7670.c


// https://github.com/cmmakerclub/esp32-webserver

#undef EPS
#include <unistd.h> // add to gzguts.h
//#include "opencv2/calib3d.hpp"
//#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc.hpp"
#define EPS		192

#include "OV7670.h"
//#include <WiFi.h>
//#include <WiFiMulti.h>
//#include <WiFiClient.h>
#include "BMP.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

using namespace std;
using namespace cv;

cv::Mat* img1;

const int SIOD = 22; //SDA
const int SIOC = 23; //SCL

const int VSYNC = 21;
const int HREF = 19;

const int XCLK = 5;
const int PCLK = 18;

const int D0 = 14;
const int D1 = 12;
const int D2 = 15;
const int D3 = 2;
const int D4 = 27;
const int D5 = 4;
const int D6 = 16;
const int D7 = 17;

//const int TFT_DC = 2;
//const int TFT_CS = 5;
//DIN <- MOSI 23
//CLK <- SCK 18

#define ssid1        "Tomato24"
#define password1    "Stephen123"
//#define ssid2        ""
//#define password2    ""

OV7670 *camera;

//WiFiMulti wifiMulti;
//WiFiServer server(80);

unsigned char bmpHeader[BMP::headerSize];

// Function Headers
//void detectAndDisplay(cv::Mat frame);

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
std::string face_cascade_name = "c:/haarcascade_frontalface_alt.xml";
//cv::CascadeClassifier face_cascade;
std::string window_name = "Capture - Face detection";
int filenumber; // Number of file to be saved
std::string filename;

static bool endsWith(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

void serve()
{/*
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
        //Serial.write(c);
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
            
            for(int i = 0; i < BMP::headerSize; i++)
               client.write(bmpHeader[i]);
            //for(int i = 0; i < camera->xres * camera->yres * 2; i++)
            //   client.write(camera->frame[i]);
            client.write((const uint8_t*)(camera->frame), (size_t)(camera->xres * camera->yres * 2));
            
        }
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("Client Disconnected.");
  }  */
}

void loop(void *pvParameter)
{
  camera->oneFrame();
  //serve();
  //displayRGB565(camera->frame, camera->xres, camera->yres);
}

extern "C" {
  void app_main();
}

void app_main()
{
  //Mat mat(160, 120, cv::DataType<int>::type);
//  Serial.begin(115200);
/*
  wifiMulti.addAP(ssid1, password1);
  //wifiMulti.addAP(ssid2, password2);
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }
  */
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
  
  //server.begin();
  xTaskCreate(&loop, "loop_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}



