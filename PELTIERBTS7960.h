#ifndef PELTIERBTS7960_H
#define PELTIERBTS7960_H


#include "Arduino.h"


class PELTIERBTS7960
{
public:
    /**
    Get peltier pin values
     */
    PELTIERBTS7960(int INH_R, int IN_R, int IS_R, int INH_L, int IN_L, int IS_L, int DEBUG);
   
    /**
     * control Peltier direction
     */
    void direction(int value, int dir);
   
   /**
    * Initializes the all parameter
    */
   void begin();
   
   /*
   * turn off the power flowing through peltier
   
   */
   void off();   

	
private:

    int ConvertPWM(int s);
    int _inh_r;
	int _in_r;
	int _is_r;
    int _inh_L;
	int _in_L;
	int _is_L;
	int _debug;
	double version = 1.00;


};

#endif
