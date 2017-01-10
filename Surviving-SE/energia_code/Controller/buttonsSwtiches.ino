#define led1 RED_LED
#define led2 GREEN_LED
#define led3 BLUE_LED

const uint32_t switch1 = PA_6;
const uint32_t switch2 = PA_7;
const uint32_t left = PF_4;
const uint32_t up = PE_0;
const uint32_t down = PD_2;
const uint32_t right = PF_0;

//int buttonStates[4];
//int switchStates[2];


void inputInit(void){
    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);
    pinMode(left, INPUT_PULLUP);      
    pinMode(right, INPUT);
    pinMode(up, INPUT);
    pinMode(down, INPUT);
}

void inputSWUpdate(void){
  //Read state of switches 
  switchStates[0] = digitalRead(switch1);
  switchStates[1] = digitalRead(switch2);    
}
void inputBTUpdate(void){
  //Read State of buttons
  buttonStates[0] = digitalRead(left);
  buttonStates[1] = digitalRead(right);
  buttonStates[2] = digitalRead(up);
  buttonStates[3] = digitalRead(down);  
}

int switchCheck(void){ 
  if (switchStates[0] == HIGH){ return 9;}
  else if (switchStates[0] == LOW) { return 10;}
}

int buttonWrite(void){
  if (buttonStates[0] == LOW){ return 12; } // Back 
  else if(buttonStates[1] == LOW){ return 11;} // Enter
  else if(buttonStates[2] == HIGH){ return 13; } // Up 
  else if(buttonStates[3] == HIGH){ return 14; } // Down    
}


