//standart gamebuino stuff
//#define DEMO
#include <tinyFAT.h>
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

DateTime rightnow(16,12,18,16,2,15);
DateTime last, now;
TimeSpan seconds(1);
#define MAXSTAMP 40
uint32_t stamps[MAXSTAMP];
uint8_t stampcounter;
uint32_t intime, intime_print;

void setup(){
  gb.begin();
  gb.titleScreen(F("Workhour Plan"));
  gb.battery.show = true;
  /*
  gb.backlight.automatic = false;
  gb.backlight.set(0);
  gb.display.clear();
  gb.display.persistence = true;
  */
  #ifndef DEMO
  rtc.begin();
  #endif
  stampcounter = 0;
  intime = 0;
  intime_print = 0;
}

void loop(){
  if(gb.update()){
    //pause the game if C is pressed
    if(gb.buttons.pressed(BTN_C)){
      gb.titleScreen(F("Workhour Plan"));
      /*
      gb.backlight.automatic = true;
      gb.backlight.set(128);
      gb.persistance = false;
      */
    }
    if((gb.frameCount%20) == 0){
      #ifndef DEMO
      rightnow = rtc.now();
      #else
      rightnow = rightnow + seconds;
      #endif
      if((stampcounter%2 == 1)){
        intime_print += 1;
      }
    }
    if(gb.buttons.pressed(BTN_A)){
      #ifndef DEMO
      gb.sound.playTick();
      #endif
      if(stampcounter < MAXSTAMP){
        stamps[stampcounter] = rightnow.unixtime();
        if((stampcounter%2 == 1) && stampcounter != 0){
          intime += (stamps[stampcounter]-stamps[stampcounter-1]);
          gb.popup(F("Out Clocked"), FPS);
        }
        else {
          gb.popup(F("In Clocked"), FPS);
        }
        stampcounter ++;
      }
    }
    if(gb.buttons.held(BTN_B,FPS*3)){
      gb.popup(F("Saved to SD (not)"), FPS);
    }
    DisplayUpdate(rightnow);
  }
}

