#include <PELTIERBTS7960.h>
#define RPWM 3 // define pin 3 for RPWM pin (output)
#define R_EN 4 // define pin 2 for R_EN pin (input)
#define R_IS 5 // define pin 5 for R_IS pin (output)

#define LPWM 6 // define pin 6 for LPWM pin (output)
#define L_EN 7 // define pin 7 for L_EN pin (input)
#define L_IS 8 // define pin 8 for L_IS pin (output)
#define HEAT 1 //do not change
#define COOL 0 //do not change
#define debug 1 //change to 0 to hide serial monitor debugging infornmation or set to 1 to view


PELTIERBTS7960 peltier(R_EN,RPWM,R_IS, L_EN,LPWM,L_IS,debug);

void setup() {
 
  Serial.begin(9600);

   peltier.begin();
   
}

void loop() {
  
    peltier.direction(100,HEAT);// Flow current in peltier with 100% duty cycle in heating mode
    delay(6000);//In heating mpde for 6 seconds
    
    peltier.off();// cut current flow of current in peltier
    delay(4000);// cut current flow of current in peltier for 4 seconds  
    
    peltier.direction(100,COOL);// Flow current in peltier with 100% duty cycle in cooling mode
    delay(6000);//Flow current in peltier with 100% duty cycle in cooling mode for 6 sec
   
    peltier.off();// cut current flow of current in peltier
    delay(4000);  // cut current flow of current in peltier for 4 seconds  
 
  // increase the temperature in peltier from  0 to 100% duty cycle 
    for(int i=0; i<=100; i++){ 
        peltier.direction(i,HEAT);
        delay(100);
    } 
  
   // reduce the temperature  in peltier from 100% to 0 duty cycle
    for(int i=100; i>0; i--){ 
        peltier.direction(i,COOL);
        delay(100);
    } 
    peltier.off();// cut current flow of current in peltier
    delay(6000); // cut current flow of current in peltier for 6 seconds        
  
}// loop ends
