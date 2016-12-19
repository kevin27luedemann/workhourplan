void printtime(const DateTime& dt, uint8_t mode){
  if(mode == 0 || mode == 2){
    gb.display.print(dt.day(),DEC);
    gb.display.print(F("."));
    gb.display.print(dt.month(),DEC);
    gb.display.print(F("."));
    gb.display.print(dt.year()-2000,DEC);
    gb.display.print(F(" "));
  }
  if(mode == 0 || mode == 1)
  {
    gb.display.print(dt.hour(),DEC);
    gb.display.print(F(":"));
    gb.display.print(dt.minute(),DEC);
    gb.display.print(F(":"));
    gb.display.print(dt.second(),DEC);
  }
}

void DisplayUpdate(const DateTime& dt){
  gb.display.clear();
  //Print header
  gb.display.print(F("\20"));
  printtime(dt,0);
  gb.display.print(F("\n"));
  if(stampcounter < 5){
    for(uint8_t i=startposition; i<startposition+stampcounter;i++){
      printtime(stamp[i],0);
      gb.display.print(F("\n"));
    }
  }
  else {
    for(uint8_t i=startposition; i<endposition;i++){
      printtime(stamp[i],0);
      gb.display.print(F("\n"));
    }
  }
  //print footer
  //printtime(dt,0);
  gb.display.println(gb.getFreeRam());
}
