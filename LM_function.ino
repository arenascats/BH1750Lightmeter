//测光表函数文件，包含有转换EV数值，进行快门-光圈-EV表格筛选等函数

int H, E, T; //H = E x T;E = I x T;
const int ISO[10] ={100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
int Iris , SpeedM = 0, R = 2 , M=0, I=1;//R is iris area number,M is speed area number,I is is number ,default is ISO 100
int Elux;//AS the balance reference of expose and lux;
float EV;
int i,j;//MyBlgo:http://blog.sina.com.cn/u/3909624897, if you have some question
int EVSeries[14][11] = {//The matrix of EV,x is iris num,y is shutter speed num
                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                    3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                    4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                    5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                    6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                    7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
                    8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
                    9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                   
                    };
                   
float IrisR[11] = {1.0, 1.4, 2.0, 2.8, 4.0, 5.6, 8.0, 11.0, 16.0, 22.0, 32.0};
int Speed[14] = { 8000, 4000, 2000, 1000, 500, 250, 125, 60, 30, 15, 8, 4, 2 , 1 };
int CankaoLUX[18] = {2.5, 5, 10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480, 40960, 81920, 163840};
 void LuxToEV(int lux)
{
  for (i = 0; i < 18; i++)
  {
    if (lux > CankaoLUX[i] && lux < CankaoLUX[i + 1])
    {
      EV = float((lux-CankaoLUX[i])/ (CankaoLUX[i+1]-CankaoLUX[i])) +i;
     
      Serial.print(EV);
      Serial.println("EV");
      break;
    }
  }
}
void EVandIrisToCountOutSpeed()
{
 
  for(i=1;i<14;i++)
    {
      if (EV== EVSeries[i][R-1])
      {
        //Serial.println(EVSeries[i][R]);
        M = i-1;//Make M(the speed vs number) equal to count number;
        break;
      }
    }
     
}

int BH1750_Read(int address) //
{

  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) //
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}

void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();

}

void SerialPrint()
{
 
  Serial.print(" Iris:");
  Serial.print(IrisR[R]);
  Serial.print(" Speed:1/");
  Serial.print(Speed[13-M-I]);//The speed is 13-M and I(ISO number)
   Serial.println("s ");
  Serial.print(" ISO:");
  Serial.print(ISO[I]);
 
 // Serial.print(SpeedM);
}
