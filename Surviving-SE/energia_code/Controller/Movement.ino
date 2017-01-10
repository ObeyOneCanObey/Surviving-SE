#include <Wire.h>

static TwoWire orbitWire(0);
float accelVal[3];

void WireWriteByte(int address, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void WireWriteRegister(int address, uint8_t reg, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();
}


void WireRequestArray(int address, uint32_t* buffer, uint8_t amount)
{
  orbitWire.requestFrom(address, amount);
  do 
  {
    while(!orbitWire.available());
    *(buffer++) = orbitWire.read();
  } while(--amount > 0);
}


static float const    SensorMaximumReading= 512.0;
static float const    SensorMaximumAccel  = 9.81 * 4.0;
static uint8_t const  SensorAccelerometer = 0x1D;
static uint32_t const ShakeThreshold      = 16;
static float          ShakeAccumulator    = 0;


void ShakeTick()
{
  size_t const DataLength = 6;
  uint32_t data[DataLength] = { 0 };
  
  WireWriteByte(SensorAccelerometer, 0x32);
  WireRequestArray(SensorAccelerometer, data, DataLength);

  uint16_t xi = (data[1] << 8) | data[0];
  uint16_t yi = (data[3] << 8) | data[2];
  uint16_t zi = (data[5] << 8) | data[4];
  float x = *(int16_t*)(&xi) / SensorMaximumReading * SensorMaximumAccel;
  float y = *(int16_t*)(&yi) / SensorMaximumReading * SensorMaximumAccel;
  int z = *(int16_t*)(&zi) / SensorMaximumReading * SensorMaximumAccel;
  accelVal[0] = z;
  accelVal[1] = x;
  accelVal[2] = y;

}


void ShakeInit()
{
  WireWriteRegister(SensorAccelerometer, 0x31, 1);
  WireWriteRegister(SensorAccelerometer, 0x2D, 1 << 3);
}
/*
 * [5][1][6]
 * [3][0][4]
 * [7][2][8]
 */

float threshAxis = 1.5;
float threshDiag = 3;

int playerMove(void){
  ShakeTick();
  float xCor = accelVal[1];
  float yCor = accelVal[2];
  if(xCor > threshDiag && yCor > threshDiag){ return 7;} // DOWNLEFT
  else if(xCor > threshDiag && yCor < -threshDiag){ return 5;} //UPLEFT
  else if(xCor < -threshDiag && yCor < -threshDiag){ return 6;} //UPRIGHT
  else if(xCor < -threshDiag && yCor > threshDiag){ return 8;} //DOWNRIGHT
  else if(xCor > threshAxis){ return 3;} //LEFT
  else if(xCor < -threshAxis){ return 4;} //RIGHT
  else if(yCor > threshAxis){ return 2;} //DOWN
  else if(yCor < -threshAxis){ return 1;} //UP
  else if( xCor < threshAxis && xCor > -threshAxis && yCor < threshAxis && yCor > -threshAxis){return 0;}
  
  }

int xCoordinate = 0;
int yCoordinate = 0;

int xEdge = 25;
int yEdge = 25;

void Movement(/*int xCoordinate , int yCoordinate , */int PlayerMoved){
    if(fabs(xCoordinate) <= xEdge && fabs(yCoordinate) <= yEdge){
      if(PlayerMoved == 1){
        yCoordinate+=1;
      }else if(PlayerMoved == -1){
        yCoordinate-=1;
      }else if(PlayerMoved == -2){
        xCoordinate-=1;
      }else if(PlayerMoved == 2){
        xCoordinate+=1;
      }else if(PlayerMoved == 3){
        xCoordinate+=1;
        yCoordinate+=1;    
      }else if(PlayerMoved == -3){
        xCoordinate-=1;
        yCoordinate+=1;
      }else if(PlayerMoved == -4){
        xCoordinate-=1;
        yCoordinate-=1;
      }else if(PlayerMoved == 4){
        xCoordinate+=1;
        yCoordinate-=1;
      }
      if(fabs(xCoordinate) == xEdge+1){
        xCoordinate = (-xCoordinate/(xEdge+1))*(xEdge);
      }
      if(fabs(yCoordinate) == yEdge+1){
        yCoordinate = (-yCoordinate/(yEdge+1))*(yEdge);  
      }
    }  
}

void MovementInit(void){
  orbitWire.begin();
  ShakeInit();
}


