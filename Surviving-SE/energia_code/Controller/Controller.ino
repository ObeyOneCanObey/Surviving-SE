#include <Wire.h>

//Movement
/*
 * [5][1][6]
 * [3][0][4]
 * [7][2][8]
 * MAP FOR REF
 * (Sends in specific byte of data for specific movement)
 */
const int OverworldState = 3;
int playerMove(void);
//void Movement(int playerMoved);
void MovementInit(void);

//buttonsSwitches
/*
 *     [13]
 *  [12]  [11]
 *     [14]
 *     
 *  MAP FOR REF
 *     
 *  9 recieved for switch up   
 *  10 recieved for switch down
 *  
 *  
 *  
 */
int buttonStates[4];
int switchStates[2];
void inputInit(void);
void inputSWUpdate(void);
void inputBTUpdate(void);
int switchCheck(void);
int buttonWrite(void);

void setup() {
  inputInit();
  MovementInit();
  Serial.begin(9600);
}

int currentSwitch;

void loop() {
  inputSWUpdate();
  //if(switchCheck()){}
  if(switchCheck() == 9){
    currentSwitch = switchCheck();  
    Serial.write( currentSwitch );
    while(currentSwitch == 9){
      inputSWUpdate();
      if(switchCheck() != currentSwitch){
        currentSwitch = switchCheck();  
        if(currentSwitch){Serial.write( currentSwitch );}      
      }
      inputBTUpdate();
      if(buttonWrite()){
        Serial.write(buttonWrite());
      }
      delay(170);
    }  
  }else{
      if(playerMove()){
        Serial.write(playerMove());
        }
      delay(250);
  } 
}
