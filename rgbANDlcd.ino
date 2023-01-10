#include <Wire.h> //I2C library
#include <SPI.h>
#include "LCD_Driver.h" //LCD LIBRARY
#include "GUI_Paint.h"  //LCD LIBRARY
#include "externalEEPROM.h"
eepromLib eeprom = eepromLib();

int button = A0;
int party = A1;
int reset = A2;
int randomButton = A3;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int r = 2;
int g = 3;
int b = 4;
int gen = 0; //private
int temp = 0; //private
int rtime=0; //private rainbow(party) light time

long long rantime = 0; //goes to timer
int rngResult=0;

int singleState = 0;
int lcdState = 0;

int add = 0;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;


long long seed = 0; //SM3 sets seed to how many ticks have happened
int parkMillerRNG() {
    long long a = 16807;
    long long m = 2147483647;
    long long q = 127773; 
    long long r = 2836;
    long long hi = seed/q;
    long long lo = seed%q;
    long long test = a * lo - r * hi;
    if (test > 0){
        seed = test;
    }
    else{
        seed = test + m;
    }
    return seed;
}

 int randomNumber(int maxVal){
  int tempRNG = 0;
  int result = 0;
  tempRNG = parkMillerRNG();
  if(tempRNG < 0){
    tempRNG = tempRNG * -1;
  }
  else{
    result = tempRNG % maxVal;
  }
  return result;
 }


const unsigned short tasksNum = 5;
task tasks[tasksNum];


enum SM1_States {sm_init, wait, addrainbow, addbutton, resetbutton, randBut}; //BUTTON INPUT READING
int SM1_Tick(int state1){
  
  switch (state1){ //state transitions
    case sm_init:
      state1 = wait;
      break;
      
    case wait:
      if(analogRead(party) < 500){
        state1 = addrainbow;
      }
      if (analogRead(button) < 500){
        state1 = addbutton;
      }
      if (analogRead(reset) < 500){
        state1 = resetbutton;
      }
      if (analogRead(randomButton) < 500){
        state1 = randBut;
      }
      break;
      
    case addrainbow: //state 10
      if(singleState == 11){
        singleState = 10;
      }
      if(singleState != 10){ //implementing this rn
        singleState = 10; 
      } 
      eeprom.write(singleState,add); 
      state1=wait;
      break;
      
    case addbutton:
      if(singleState == 10){
        singleState = 0;
      }
      if(singleState == 6){
        singleState = 0;
      }
      if(singleState == 20){
        singleState = 0;
      }
      singleState++;
      eeprom.write(singleState,add);
      state1=wait;
      break;
    case resetbutton:
      singleState = 0;
      eeprom.write(singleState,add);
      state1=wait;
      break;

    case randBut:
      singleState = 20;
      eeprom.write(singleState,add);
      gen = 1;
      state1=wait;
      break;
  }

  switch (state1){ //state actions
    
    case sm_init:   
      
      break;
    case wait:
      
      break;
    case addrainbow:
      
      break;
    case addbutton:
      
      break;
    case resetbutton:
      
      break;
    case randBut:

      break;
  }
  return state1;
}

enum SM2_States {sm2_init, off, white, red, orange, yellow, green, blue, indigo, rainbow, randLight}; //RGB LIGHT CONTROLS
int SM2_Tick(int state2){

  switch (state2){ //state transitions
    case sm2_init:
      state2 = off;
      break;
      
    case off:
      singleState = int(eeprom.read(add));
      if (singleState == 0){
        state2 = white;
      }
      if (singleState == 1){
        state2 = red;
      }
      if (singleState == 2){
        state2 = orange;
      }
      if (singleState == 3){
        state2 = yellow;
      }
      if (singleState == 4){
        state2 = green;
      }
      if (singleState == 5){
        state2 = blue;
      }
      if (singleState == 6){
        state2 = indigo;
      }
      if (singleState == 10){
        state2 = rainbow;
      }
      if (singleState == 20){
        state2 = randLight;
      }
      break;
         
    case white:
      if (singleState == 1){
        lcdState = 1;
        state2 = red;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      break;
    case red:
      if (singleState == 2){
        lcdState = 1;
        state2 = orange;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break; 
    case orange:
      if (singleState == 3){
        lcdState = 1;
        state2 = yellow;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case yellow:
      
      if (singleState == 4){
        lcdState = 1;
        state2 = green;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case green:
      
      if (singleState == 5){
        lcdState = 1;
        state2 = blue;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case blue:
      
      if (singleState == 6){
        lcdState = 1;
        state2 = indigo;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case indigo:  
      if (singleState == 1){
        lcdState = 1;
        state2 = red;
      }
      if (singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case rainbow:
      if (singleState == 1){
        lcdState = 1;
        state2 = red;
      }
      
      if (singleState == 20){
        lcdState = 1;
        state2 = randLight;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    case randLight:
      
      if (singleState == 1){
        lcdState = 1;
        state2 = red;
      }
      if(singleState == 10){
        lcdState = 1;
        state2 = rainbow;
      }
      if (singleState == 0){
        lcdState = 1;
        state2 = white;
      }
      break;
    
  }

  switch (state2){ //state actions
    
    case sm2_init:   
      digitalWrite(r, 0);
      digitalWrite(g, 0);
      digitalWrite(b, 0);
      break;
    case off:
      break;
    case white:
      digitalWrite(r, 255);
      digitalWrite(g, 255);
      digitalWrite(b, 255);
      break;
    case red:
      digitalWrite(r, 255);
      digitalWrite(g, 0);
      digitalWrite(b, 0);
      break;
    case orange:
      digitalWrite(r, 255);
      digitalWrite(g, 128);
      digitalWrite(b, 0);
      break;
    case yellow:
      digitalWrite(r, 255);
      digitalWrite(g, 255);
      digitalWrite(b, 0);
      break;
    case green:
      digitalWrite(r, 0);
      digitalWrite(g, 255);
      digitalWrite(b, 0);
      break;
    case blue:
      digitalWrite(r, 0);
      digitalWrite(g, 0);
      digitalWrite(b, 255);
      break;
    case indigo:
      digitalWrite(r, 75);
      digitalWrite(g, 0);
      digitalWrite(b, 130);
      break;
    case rainbow:
      if(rtime==0){
        digitalWrite(r, 255);
        digitalWrite(g, 0);
        digitalWrite(b, 0);
      }
      if(rtime==1){
        digitalWrite(r, 255);
        digitalWrite(g, 255);
        digitalWrite(b, 0);
      }
      if(rtime==2){
        digitalWrite(r, 0);
        digitalWrite(g, 255);
        digitalWrite(b, 0);
      }
      if(rtime==3){
        digitalWrite(r, 0);
        digitalWrite(g, 0);
        digitalWrite(b, 255);
      }
      if(rtime==4){
        digitalWrite(r, 75);
        digitalWrite(g, 0);
        digitalWrite(b, 130);
      }
      rtime++;
      if(rtime==5){
        rtime=0;
      }
      break;
    case randLight:    
      digitalWrite(r, val1);
      digitalWrite(g, val2);
      digitalWrite(b, val3);
      //Serial.println(val1);
      //Serial.println(val2);
      //Serial.println(val3);
      break;
  }
  return state2;
}

enum SM3_States {sm3_init, inc}; //TIMER
int SM3_Tick(int state3){
  
  switch (state3){ //state transitions
    case sm3_init:
      state3 = inc;
      break;
    case inc:
      state3 = inc;
      break;
  }

  switch (state3){ //state actions
    case sm3_init:
      
      break;  
    case inc:
      seed = rantime++;
      break;
  }
  return state3;
}

enum SM4_States {idle, generate}; //RANDOM NUMBER GENERATOR
int SM4_Tick(int state4){
  
  switch (state4){ //state transitions
    case idle:
    if(gen == 1){
      state4 = generate;
    }
      break;
    case generate:
    gen = 0;
    if(gen==0){
      state4 = idle;
    }
      break;
  }

  switch (state4){ //state actions
    case idle:
      
      break;  
    case generate:
      val1 = randomNumber(255);
      val2 = randomNumber(255);
      val3 = randomNumber(255);
      if(val1 > 127){
        val1 = 255;
      }
      else{
        val1 = 0;
      }
      if(val2 > 127){
        val2 = 255;
      }
      else{
        val2 = 0;
      }
      if(val3 > 127){
        val3 = 255;
      }
      else{
        val3 = 0;
      }

      if((val1 == 0) && (val2 == 0) && (val3 == 0)){ //THIS IS TO AVOID GETTING R, G, AND B VALUES TO BE ALL 0
        temp = randomNumber(3);
        if(temp == 0){
          val1 = 255;
        }
        if(temp == 1){
          val2 = 255;
        }
        if(temp == 2){
          val3 = 255;
        }
      }
      
      
      break;
  }
  return state4;
}

enum SM5_States {sm5_init, off5, waitLCD, LCDwhite, LCDred, LCDorange, LCDyellow, LCDgreen, LCDblue, LCDindigo, LCDrainbow, LCDrandLight}; //LCD DISPLAY
int SM5_Tick(int state5){

  switch (state5){ //state transitions
    case sm5_init:
      state5 = off5;
      break;
      
    case off5:
      singleState = int(eeprom.read(add));
      if (singleState == 0){
        state5 = LCDwhite;
      }
      if (singleState == 1){
        state5 = LCDred;
      }
      if (singleState == 2){
        state5 = LCDorange;
      }
      if (singleState == 3){
        state5 = LCDyellow;
      }
      if (singleState == 4){
        state5 = LCDgreen;
      }
      if (singleState == 5){
        state5 = LCDblue;
      }
      if (singleState == 6){
        state5 = LCDindigo;
      }
      if (singleState == 10){
        state5 = LCDrainbow;
      }
      if (singleState == 20){
        state5 = LCDrandLight;
      }
      break;

    case waitLCD:
      if ((singleState == 0)&&(lcdState==1)){
        state5 = LCDwhite;
      }
      if ((singleState == 1)&&(lcdState==1)){
        state5 = LCDred;
      }
      if ((singleState == 2)&&(lcdState==1)){
        state5 = LCDorange;
      }
      if ((singleState == 3)&&(lcdState==1)){
        state5 = LCDyellow;
      }
      if ((singleState == 4)&&(lcdState==1)){
        state5 = LCDgreen;
      }
      if ((singleState == 5)&&(lcdState==1)){
        state5 = LCDblue;
      }
      if ((singleState == 6)&&(lcdState==1)){
        state5 = LCDindigo;
      }
      if ((singleState == 10)&&(lcdState==1)){
        state5 = LCDrainbow;
      }
      if ((singleState == 20)&&(lcdState==1)){
        state5 = LCDrandLight;
      }
      break;
    
    case LCDwhite:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDred:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break; 
    case LCDorange:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDyellow:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDgreen:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDblue:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDindigo:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDrainbow:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    case LCDrandLight:
      lcdState = 0;
      if(lcdState == 0){
        state5 = waitLCD;
      }
      break;
    
  }

  switch (state5){ //state actions
    
    case sm5_init:   
      
      break;
    case off5:

      break;
      
    case waitLCD:
      
      break;
      
    case LCDwhite:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  WHITE  ", &Font24, BLACK, WHITE);
      break;
    case LCDred:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  RED  ", &Font24, RED, WHITE);      
      break;
    case LCDorange:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  ORANGE  ", &Font24, ORANGE, WHITE);
      break;
    case LCDyellow:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  YELLOW  ", &Font24, YELLOW, WHITE);
      break;
    case LCDgreen:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  GREEN  ", &Font24, GREEN, WHITE);
      break;
    case LCDblue:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  BLUE  ", &Font24, BLUE, WHITE);
      break;
    case LCDindigo:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  INDIGO  ", &Font24, BLUE, WHITE);
      break;
    case LCDrainbow:
      Paint_Clear(BLACK);
      Paint_DrawString_EN(60,110, "  PARTY  ", &Font24, BLACK, WHITE);
      break;
    case LCDrandLight:   
      Paint_Clear(BLACK); 
      Paint_DrawString_EN(60,110, "  RANDOM  ", &Font24, BLACK, WHITE);
      break;
  }
  return state5;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(BLACK);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  unsigned char i = 0;
  tasks[i].state = sm_init;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;                              
  tasks[i].state = sm2_init;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = sm3_init;
  tasks[i].period = 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  i++;
  tasks[i].state = idle;
  tasks[i].period = 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;
  i++;
  tasks[i].state = sm5_init;
  tasks[i].period = 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM5_Tick;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i){
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis();
    }
  } 
}
