#define SelectPin 3
#define inputCLK 12
#define inputDT 11
volatile int ISRRan = 0;  // this variable is set in your ISR to trigger a break in the while loop

uint32_t currentStateCLK;
uint32_t previousStateCLK;
bool ButtonState = HIGH;

//structure Menu to set time and temperature
typedef struct
{
volatile  float Temperature[5];
 volatile uint32_t Time[5];
volatile uint8_t RUN = 0;//Variable for start running RUN=1 start PCR
volatile uint8_t cycle =20 ;//Total cycle of PCR
}Menu;

volatile Menu set_temperature; //Variable for temperatures
volatile uint32_t Select = 0;//Variable to select temperatures,time,cycle and run

                          
 
 uint8_t MainMenu =1;//variable for main menu
uint8_t MainSelect =0;//variable to select default net setup


void setup() {
  //set encoder pin as input
  pinMode(SelectPin,INPUT_PULLUP);
  pinMode(inputCLK,INPUT);
  pinMode(inputDT,INPUT);
  attachInterrupt(digitalPinToInterrupt(SelectPin),buttonpressed,LOW);//config interrupt for Button press
  Serial.begin(9600);

previousStateCLK=digitalRead(inputCLK); 
                                           //default Parameter
                                           set_temperature.Temperature[0]=95.0;
                                           set_temperature.Time[0]= 600;
                                           set_temperature.Temperature[1]=95.0;
                                           set_temperature.Time[1]= 30;
                                           set_temperature.Temperature[2]=65.0;
                                           set_temperature.Time[2]= 20;
                                           set_temperature.Temperature[3]=72.0;
                                           set_temperature.Time[3]= 10;
                                           set_temperature.Temperature[4]=60.0;
                                           set_temperature.Time[4]= 600;

}

void loop() {
  
MainMENU();

//add PCR CODE or function here
Serial.println("you are in loop");
delay(5000);
MainMenu=1;


}


void MainMENU(){
  
  
   while(MainMenu==1){
  
   if ( ISRRan==1 && MainSelect==0 ) {//default config of Temperature,time,cycle and start RUN
    int s=0;
                                            while(1)
                                            {  
                                               ISRRan=0;
                                              Serial.println("Default");
                                              //default Parameter
                                           set_temperature.Temperature[0]=95.0;
                                           set_temperature.Time[0]= 600;
                                           set_temperature.Temperature[1]=95.0;
                                           set_temperature.Time[1]= 30;
                                           set_temperature.Temperature[2]=65.0;
                                           set_temperature.Time[2]= 20;
                                           set_temperature.Temperature[3]=72.0;
                                           set_temperature.Time[3]= 10;
                                           set_temperature.Temperature[4]=60.0;
                                           set_temperature.Time[4]= 600;
                                           s++;
                                           if(s>=500)
                                           {
                                            break;
                                           
                                           }
                                         
                                          }
                                      MainMenu=0;//GO to PCR Reaction
                                     }
        
   else if(ISRRan==1 && MainSelect)//Config Temperature,time,cycle and start RUN
                                     {
                                         Serial.println("you are in Setup");
                                         ISRRan=0;
                                         Setup();
                                         MainMenu=0; //GO to PCR Reaction  
                                     }
   
    
  
else if(ISRRan==0 && MainSelect==0)//defult selected 
                                {
                                    
                                    Serial.println("Press button for Default");
                                     currentStateCLK=digitalRead(inputCLK);
                    //if the previous and current state of the inputCLK are different then pulse hase occured
                  if (currentStateCLK != previousStateCLK)
                                        {
                                          //if the inputDT state is different than inputCLK state then
                                          //the encoder is rotating clock wise
                                          if(digitalRead(inputDT)!=currentStateCLK){ 
                                            MainSelect=MainSelect-1;
                                        }
                                      
                 else
                                        {
                                        
                                        MainSelect=MainSelect+1;
                                        }
                                    
                                      }
                                      
                      previousStateCLK=currentStateCLK; 
                                                  
       }

else if(ISRRan==0 && MainSelect) // Setup is selected
                     {
  
          Serial.println("press button Setup");

                                     currentStateCLK=digitalRead(inputCLK);
                    //if the previous and current state of the inputCLK are different then pulse hase occured
                  if(currentStateCLK != previousStateCLK)
                                        {
                                          //if the inputDT state is different than inputCLK state then
                                          //the encoder is rotating clock wise
                                          if(digitalRead(inputDT)!=currentStateCLK){ 
                                            MainSelect=MainSelect-1;
                                        }
                                      
                 else
                                        {
                                        
                                        MainSelect=MainSelect+1;
                                        }
                                    
                                      }
                                      
                      previousStateCLK=currentStateCLK;
          
                     }
  
  
  }
  
  }


void Setup(){
  int     i=0;
  int     j=0;
  set_temperature.RUN=0;
  Select=0;

  while(Select<=12){
                              if(Select==0||Select==2||Select==4||Select==6||Select==8){//selection for temperature
                                         
                                         if(Select==0)
                                            {
                                          i=0;
                                            }
                                          else
                                         i=Select/2;
                                         
                                               currentStateCLK=digitalRead(inputCLK);
                                            //if the previous and current state of the inputCLK are different then pulse hase occured
                                            if(currentStateCLK != previousStateCLK)
                                            {
                                              //if the inputDT state is different than inputCLK state then
                                              //the encoder is rotating clock wise
                                              if(digitalRead(inputDT)!=currentStateCLK){ 
                                                set_temperature.Temperature[i]=set_temperature.Temperature[i]-0.1;
                                                }
                                              
                                              else{
                                                
                                                set_temperature.Temperature[i]=set_temperature.Temperature[i]+0.1;
                                                }
                                            
                                              }
                                              
                                                previousStateCLK=currentStateCLK;
                                                
                                                Serial.println(" T");
                                                Serial.println(Select);
                                                Serial.println("    ");
                                            Serial.println(set_temperature.Temperature[i]);

      }
    else if (Select==1||Select==3||Select==5||Select==7||Select==9)//selection for time
                                { 
                                       j=0;
                                      switch (Select) {
                                      case 1:
                                      j=0;
                                      break;
                                      case 3:
                                     j=1;
                                      break;
                                       case 5:
                                      j=2;
                                      break;
                                       case 7:
                                      j=3;
                                      break;
                                      case 9:
                                      j=4;
                                      break;
                                  }
                                        
                                   currentStateCLK=digitalRead(inputCLK);
                                  //if the previous and current state of the inputCLK are different then pulse hase occured
                                  if(currentStateCLK != previousStateCLK)
                                  {
                                    //if the inputDT state is different than inputCLK state then
                                    //the encoder is rotating clock wise
                                    if(digitalRead(inputDT)!=currentStateCLK){ 
                                      set_temperature.Time[j]--;
                                      }
                                    
                                    else{
                                      
                                      set_temperature.Time[j]++;
                                      }
                                  
                                  
                                     }
                                    
                                    
                                    previousStateCLK=currentStateCLK;
                                        
                                      //set_temperature.Time[j]= tim;
                                                          Serial.println(" T");
                                                          Serial.println(Select);
                                                          Serial.println("    ");
                                  Serial.println(set_temperature.Time[j]);
                                 }    
    
  else if(Select==10||Select==11){//selection for cycle and RUN

        if(Select==10){//selection for cycle
                                         currentStateCLK=digitalRead(inputCLK);
                                  //if the previous and current state of the inputCLK are different then pulse hase occured
                                  if(currentStateCLK != previousStateCLK)
                                  {
                                    //if the inputDT state is different than inputCLK state then
                                    //the encoder is rotating clock wise
                                    if(digitalRead(inputDT)!=currentStateCLK){ 
                                       set_temperature.cycle--;
                                      }
                                    
                                    else{
                                      
                                      set_temperature.cycle++;
                                      }
                                  
                                    }
                                  previousStateCLK=currentStateCLK;
                                  Serial.println("T10 ");
                                  Serial.println(set_temperature.cycle);
                      }

     else if(Select==11){//selection for RUN
                      currentStateCLK=digitalRead(inputCLK);
                      //if the previous and current state of the inputCLK are different then pulse hase occured
                      if(currentStateCLK != previousStateCLK)
                      {
                        //if the inputDT state is different than inputCLK state then
                        //the encoder is rotating clock wise
                        if(digitalRead(inputDT)!=currentStateCLK){ 
                            set_temperature.RUN = 0;
                          }
                        
                        else{
                          
                          set_temperature.RUN = 1;
                          }
                        }
                        
                        previousStateCLK=currentStateCLK;
                           
                          
                          Serial.println("T11 ");
                      Serial.println(set_temperature.RUN);
                      
                         }
    
    }
else if (set_temperature.RUN==0&&Select==12)// if Run is 0 then go to initial selection
                            {
                               Select=0;
                            }

 else if(set_temperature.RUN==1&&Select==12){// if Run is 1 then Start PCR Reaction 
                                Select=0;
                                set_temperature.RUN=0;
                                break;  
                             }
                
                  if ( ISRRan ) { //button pressed then go to nex config. temperature or time or cycle or run
                          Select++;
                                }
                            ISRRan=0;
                  
  }
 
  Select=0;
}



void buttonpressed(){//button pressed interrupt function
 delay(500);
//Select++;
 ISRRan = 1;
  }
