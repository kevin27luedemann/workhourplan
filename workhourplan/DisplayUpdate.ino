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
  //Display stats
  gb.display.print(F("\n"));
  gb.display.print(F("In Time: "));
  gb.display.print((uint8_t)(intime/3600));
  gb.display.print(F(":"));
  gb.display.print((uint8_t)(intime/60%60));
  gb.display.print(F(":"));
  gb.display.print((intime%60));
  gb.display.print(F("\n"));
  gb.display.print(F("Pause left: "));
  gb.display.println((uint8_t)(MAXSTAMP/2)-(uint8_t)(stampcounter/2));
  gb.display.print(F("Clock Status: "));
  if(stampcounter%2==1){
    gb.display.println(F("In"));
  }
  else {
    gb.display.println(F("Out"));
  }
  gb.display.print(F("\n"));
  //print footer
  gb.display.print(gb.getFreeRam());
  gb.display.print(F(" "));
  gb.display.println(gb.getCpuLoad());
}
