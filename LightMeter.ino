#include <Wire.h>

int BH1750address = 0x23;
byte buff[2];
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}
void loop()//MyBlgo:http://blog.sina.com.cn/u/3909624897, if you have some question

{
  int i;
  uint16_t val = 0;
  BH1750_Init(BH1750address);
  delay(1000);
  if (2 == BH1750_Read(BH1750address))
  {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
     //Serial.println("==================================");
    LuxToEV(val);
       
  EVandIrisToCountOutSpeed();
   SerialPrint();
   Serial.println(" ");
    Serial.print(val, DEC);
    Serial.println(" lux");
    Serial.print("==================================");


   // LuxToShutterSpeed(val);
  }
  
}



 

 

 


