//standart gamebuino stuff
#define DEMO
#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;
#define FPS 20

//I2C and RTC library
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void printtime(const DateTime& dt, uint8_t mode);
void DisplayUpdate(const DateTime& dt);

DateTime now(16,12,18,16,2,15);
#define MAXSTAMP 10
DateTime stamp[MAXSTAMP];
uint8_t stampcounter;
TimeSpan seconds(1);
uint8_t startposition,endposition;

void setup(){
  gb.begin();
  gb.titleScreen(F("Workhour Plan"));
  gb.battery.show = true;
  #ifndef DEMO
    rtc.begin();
  #endif
  stampcounter = 0;
  startposition = 0;
  endposition = 5;
}

void loop(){
  if(gb.update()){
    //pause the game if C is pressed
    if(gb.buttons.pressed(BTN_C)){
      gb.titleScreen(F("Workhour Plan"));
      gb.battery.show = true;
      //gb.display.fontSize = 2;
    }
    if((gb.frameCount%20) == 0){
      #ifndef DEMO
      now = rtc.now();
      #else
      now = now + seconds;
      #endif
    }
    if(gb.buttons.pressed(BTN_A)){
		gb.popup(F("Time Saved"), FPS);
		#ifndef DEMO
		  gb.sound.playtick()
		#endif
      if(stampcounter < MAXSTAMP){
        stamp[stampcounter] = now;
        stampcounter += 1;
        if((endposition < MAXSTAMP) && (endposition <stampcounter)){
		    startposition ++;
		    endposition ++;
        }
      }
    }
    if(gb.buttons.pressed(BTN_DOWN)){
		gb.popup(F("Down"), FPS);
		#ifndef DEMO
		  gb.sound.playTick()
		#endif
      if((endposition < MAXSTAMP) && (endposition <stampcounter)){
		  startposition ++;
		  endposition ++;
      }
    }
    if(gb.buttons.pressed(BTN_UP)){
		gb.popup(F("Up"), FPS);
		#ifndef DEMO
		  gb.sound.playTick()
		#endif
      if((startposition > 0)){
		  startposition --;
		  endposition --;
      }
    }
    //DateTime now = rtc.now();
    DisplayUpdate(now);
  }
}

