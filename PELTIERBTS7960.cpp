
#include "Arduino.h"
#include "PELTIERBTS7960.h"


// -- constructor
PELTIERBTS7960::PELTIERBTS7960(int INH_R, int IN_R, int IS_R, int INH_L, int IN_L, int IS_L, int DEBUG)
{
    //  Pins defined
    _inh_r =INH_R;
	_in_r =IN_R;
	_is_r =IS_R;
	
    _inh_L =INH_L;
	_in_L =IN_L;
	_is_L =IS_L;
	
	_debug = DEBUG;


}

void PELTIERBTS7960::begin()
{
	pinMode(this->_inh_r, OUTPUT);
	pinMode(this->_in_r, OUTPUT);
	pinMode(this->_is_r, INPUT);	
	
	pinMode(this->_inh_L, OUTPUT);
	pinMode(this->_in_L, OUTPUT);
	pinMode(this->_is_L, INPUT);	

	if(this->_debug){
		Serial.println("BTS7960 Peltier Control");
		
	}	

}

// direction control function
void PELTIERBTS7960::direction(int value, int dir) {

    digitalWrite(this->_inh_r, HIGH);
	digitalWrite(this->_inh_L, HIGH);
	int pwm1Pin, pwm2Pin;
	if(dir ==1){
		pwm1Pin =this->_in_L;
		pwm2Pin =this->_in_r;
	}

	else
	{
		pwm1Pin =this->_in_r;
		pwm2Pin =this->_in_L;		
	}
	if(this->_debug){
		digitalWrite(pwm1Pin, LOW);
		
	}
     

    if(value >=0 && value <=100 ){
		
		analogWrite(pwm2Pin, ConvertPWM(value));
	}

 
}//direction

/*
*
*
*/
void PELTIERBTS7960::off(){
    digitalWrite(this->_in_r, LOW);
	digitalWrite(this->_in_L, LOW);
	if(this->_debug){
		Serial.println("Peltier off");
	}	
}//off()

/*
 * @converts % value from 0 to 100% to 0-255
 * @parameter s is integer value representing % from 0-100
 * @return will return value from 0 to 255
 */
int PELTIERBTS7960::ConvertPWM(int s){
  return map(s, 0,100,0,255);
}//conversion of 0 to 100% to 0-255

