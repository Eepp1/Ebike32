///////////////////////////////////////////////////INCLUDET
#include <main.h>

int bikeSpeed = 0;
bool Limiter = 1;
int curMode = UI_NOLIMIT;
int voltage = 0;
int watt = 0;
int current = 0;
int motorRpm = 0;

bool brakeSens = 0;
int throttleScaled = 0;
int throttle = 0;
int pedalSens = 0;


void setup() {  
  u8g2.begin();
  bootScreen();
  while (!Serial2) {;}
  UART.setSerialPort(&Serial2);
  delay(5000); 
}

void loop() {
  //inputs + vesc telemetry
  readInputs();
  //calc speed from rpm telemetry
  bikeSpeed= calcSpeed(motorRpm);
  //handle throttle related stuff like brakes and limiter
  throttle = throttleHandle(bikeSpeed,Limiter,throttleScaled,brakeSens);

  controlMotor(throttle);


  oledUpdate();

  #ifdef DEBUG
    void printDebug();
  #endif
}

void readInputs(){
  if ( UART.getVescValues() ) {
    Serial.println(UART.data.rpm);
    Serial.println(UART.data.inpVoltage);
    Serial.println(UART.data.ampHours);
    Serial.println(UART.data.tachometer);
  }
  brakeSens = digitalRead(BRAKE_PIN); //brakes in parallel
  throttleScaled = map(analogRead(THROTTLE_PIN),0,THROTTLE_ADC_MAX_VALUE,0,127);
  //reserve for pedalpin //pedalSens = analogRead(PEDAL_PIN);

}

void controlMotor(int throttle1){
  UART.nunchuck.valueY = throttle1;
  UART.setNunchuckValues();//Call the function setNunchuckValues to send the current nunchuck values to the VESC
}

void handleInputs(){

}

void bootScreen(){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_lucasarts_scumm_subtitle_o_tf); // choose a suitable font
  u8g2.setCursor(30, 36);  //separate setCursor(), print() accepts all Print.h arguments
  u8g2.print("Ebike");
  u8g2.setCursor(61, 48);  //separate setCursor(), print() accepts all Print.h arguments
  u8g2.print("32");
  u8g2.sendBuffer(); 
}


int throttleHandle(int curSpeed,bool limiter, int curthrottle,bool brake){ 
  int throttle=curthrottle;
  if(limiter){
    if(curSpeed > MAX_SPEED){
      if(curthrottle > MAX_THROTTLE_LIMITED) //if limiter is on and throt is higher than def. throt is set to max throttle def
        throttle = MAX_THROTTLE_LIMITED;
    }  
  }
  if(brake){ //if brake is pressed then disable throttle. this can be negative if brake power set to neg.
    throttle = BRAKE_POWER;
  }//otherwise throttle keeps same as before.
  return throttle;
}

int calcSpeed(int currentrpm){
  int curRpm= currentrpm / MOTOR_POLE_COUNT; //real rpm
  int curSpeed = (curRpm * 2091) / 10000; 
  curSpeed = curSpeed*3.6;
  return curSpeed; // return speed of bike
}

void printDebug(){
  Serial.println("Current speed: "+ bikeSpeed); //bike speed (calc by rpm)

}

void oledUpdate(){
  
  u8g2.clearBuffer();          // clear the internal memory

  switch (curMode){
    case UI_NOLIMIT:
      u8g2.setFont(u8g2_font_fub35_tr); // choose a suitable font
      u8g2.setCursor(0, 38);  //separate setCursor(), print() accepts all Print.h arguments
      //u8g2.print(i);  //
      u8g2.setFont(u8g2_font_VCR_OSD_tf); // choose a suitable font
      u8g2.setCursor(75, 18); 
      u8g2.print("VOLT");  //
      u8g2.setCursor(75, 39); 
      //u8g2.print(c);  //
  
      u8g2.setCursor(3, 62); 
      //u8g2.print(watts);  //watit
      u8g2.setCursor(75, 62);
      //u8g2.print(amps);  //virta
  
      u8g2.sendBuffer();          // transfer internal memory to the display
    break;
    case UI_LIMIT:
      u8g2.setFont(u8g2_font_fub35_tr); // choose a suitable font
      u8g2.setCursor(0, 38);  //separate setCursor(), print() accepts all Print.h arguments
      //u8g2.print(i);  //
      u8g2.setFont(u8g2_font_VCR_OSD_tf); // choose a suitable font
      u8g2.setCursor(75, 18); 
      u8g2.print("VOLT");  //
      u8g2.setCursor(75, 39); 
      //u8g2.print(c);  //
  
      u8g2.setCursor(3, 62); 
      //u8g2.print(watts);  //watit
      u8g2.setCursor(75, 62);
      //u8g2.print(amps);  //virta

      u8g2.drawLine(68,5,68,60);
  
      u8g2.sendBuffer();          // transfer internal memory to the display
    break; 
  }

  
  
  
  
}