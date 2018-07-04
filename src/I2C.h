//#include "Arduino.h"
#include <rom/ets_sys.h>

class I2C
{
  void inline DELAY()
  {
    //delayMicroseconds(1);
    ets_delay_us(1);
  }

  void inline SCLLOW()
  {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<SCL));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SCL, 0);
    
    //pinMode(SCL, OUTPUT);
    //digitalWrite(SCL, 0);
  }

  void inline SCLHIGH()
  {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = ((1ULL<<SCL));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SCL, 1);
    
    //pinMode(SCL, INPUT_PULLUP);  
    //digitalWrite(SCL, 1);
  }

  void inline CLOCK()
  {
    DELAY();
    SCLHIGH();
    DELAY();
    DELAY();
    SCLLOW();
    DELAY();
  }
  
  void inline SDALOW()
  {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<SDA));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SDA, 0);
    
    //pinMode(SDA, OUTPUT);
    //digitalWrite(SDA, 0);  
  }
  
  void inline SDAHIGH()
  {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<SDA));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SDA, 1);
    
    //pinMode(SDA, OUTPUT);
    //digitalWrite(SDA, 1);  
  }

  void inline SDAPULLUP()
  {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = ((1ULL<<SDA));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    //pinMode(SDA, INPUT_PULLUP);  
  }

  void pushByte(unsigned char b)
  {
    for(char i = 0; i < 8; i++)
    {
      if(b & 0x80)
        SDAHIGH();
      else
        SDALOW();
      b <<= 1;
      CLOCK();
    }  
  }
  
  bool getAck()
  {
    SDAPULLUP();
    DELAY();
    SCLHIGH();
    DELAY();
    //int r = digitalRead(SDA);
    int r = gpio_get_level((gpio_num_t)SDA);
    SDALOW();
    DELAY();
    SCLLOW();
    DELAY();
    return r == 0;
  }

  void start()
  {
    SDAPULLUP();
    DELAY();
    SCLHIGH();
    DELAY();
    SDALOW();
    DELAY();
    SCLLOW();
    DELAY();
  }
  
  void end()
  {
    SCLHIGH();
    DELAY();
    SDAPULLUP();
    DELAY();
  }
  
  public:
  int SDA;
  int SCL;
  I2C(const int data, const int clock)
  {
    SDA = data;
    SCL = clock;
    
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = ((1ULL<<SCL));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SDA, 0);
    
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = ((1ULL<<SCL));
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_set_level((gpio_num_t)SCL, 0);
    
    //pinMode(SDA, INPUT_PULLUP);
    //pinMode(SCL, INPUT_PULLUP);
    //digitalWrite(SDA, 0);
    //digitalWrite(SCL, 0);
  }
  
  bool writeRegister(unsigned char addr, unsigned char reg, unsigned char data)
  {
    start();
    pushByte(addr);
    
    if(!getAck())
    {
      end();
      return false;
    }
    
    pushByte(reg);
    if(!getAck())
    {
      end();
      return false;
    }
  
    pushByte(data);
    if(!getAck())
    {
      end();
      return false;
    }
  
    end();
    return true;
  }
};
