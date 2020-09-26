///////////////////////////////////////////////////INCLUDET
#include <main.h>



int i = 0;
int a = 0;
double c = 0;

String w = "W";  
String amp = "A";


void setup() {  
  u8g2.begin();
}

void loop() {
  String watts = a + w;
  String amps = i + amp;
  
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_fub35_tr); // choose a suitable font
  u8g2.setCursor(0, 38);  //separate setCursor(), print() accepts all Print.h arguments
  u8g2.print(i);  //
  u8g2.setFont(u8g2_font_VCR_OSD_tf); // choose a suitable font
  u8g2.setCursor(75, 18); 
  u8g2.print("VOLT");  //
  u8g2.setCursor(75, 39); 
  u8g2.print(c);  //
  
  u8g2.setCursor(3, 62); 
  u8g2.print(watts);  //watit
  u8g2.setCursor(75, 62);
  u8g2.print(amps);  //virta
  
  u8g2.sendBuffer();          // transfer internal memory to the display

  
  
  delay(100);  
  i++;
  a = a+10;
  c = c+0.5;
  if(i>=50)i=0;
  if(a>=1500)a=0;
  if(c>=23)c=0;
}