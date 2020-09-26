#include <Arduino.h>
#include <U8g2lib.h>
#include <stdbool.h>
#include <VescUart.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 0);   // ESP32 Thing, HW I2C with pin remapping

//debug mode
#define DEBUG 1


//DEFS
#define MAX_SPEED 24 //max speed when limiter on
#define MINPEDAL_SPEED 4 // Rounds per 10s
#define MIN_VOLTAGE 30 // 10 cell x 3.0v 
#define MAX_THROTTLE_LIMITED 80
#define BRAKE_POWER 0
#define MOTOR_POLE_COUNT 14



//PINS DEFS
#define THROTTLE_PIN 
#define PEDAL_PIN 
#define BRAKE_PIN 

//handlebarbutton
#define HBB_PLUS 
#define HBB_MINUS
#define HBB_MODE

//UI defs
#define UI_NOLIMIT 1
#define UI_LIMIT 2


void readInputs();
int calcSpeed(int currentrpm);
void printDebug();
void oledUpdate();
void bootScreen();
