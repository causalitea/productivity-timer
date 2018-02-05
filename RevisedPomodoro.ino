#include<elapsedMillis.h>
elapsedMillis timeElapsed;
elapsedMillis timeElapsed2;


int red_light = 3;
int green_light = 4;
int button_state = 0;
long work_time = 25;  // time in minutes
long break_time = 5;   // time in minutes **might want to make these floating point values for exact times?
long long_break_time = 20;
int stage=0;
int work_count=0;

int multiplier=1000; // the amount the psudo timer increases by everytime
long long_break_bonus=0;
bool up = true;
bool down = false;
bool gyro_reversed = false;
int gyro_1 = 5;
int gyro_2 = 6;
long bonus_time=0;
bool x;
bool y;
bool x2;
bool y2;

void setup() 
{
      digitalWrite(green_light, HIGH);
     
      pinMode(red_light, OUTPUT);
      pinMode(green_light, OUTPUT);
      pinMode(gyro_1,INPUT);
      pinMode(gyro_2,INPUT);
            
      work_time= (work_time*multiplier*60);
      break_time= (break_time*multiplier*60);
      long_break_time= (long_break_time*multiplier*60);
      x=digitalRead(gyro_1);
      y=digitalRead(gyro_2);
      digitalWrite(red_light, HIGH);

}

void loop() 
{


while(stage == 0) // lets say this is the beginning stage where we are waiting for a start command
   {
      

      x2=digitalRead(gyro_1);
      y2=digitalRead(gyro_2);
        if(x2!=x && y2!=y) // if the reading is reversed then gyro_reversed is true
            {
              stage=5;
              digitalWrite(red_light, HIGH);
              delay(1500);
              digitalWrite(red_light, LOW);
              break;
            }      

                                  
         if(timeElapsed<1000)
            {
            digitalWrite(green_light, LOW);
            digitalWrite(red_light, LOW);
            }

        if(x2!=x && y2!=y) // if the reading is reversed then gyro_reversed is true
            {
              stage=5;
              digitalWrite(red_light, HIGH);
              delay(1500);
              digitalWrite(red_light, LOW);
              break;
            } 
            
         if(timeElapsed>1000)
            {
            digitalWrite(green_light, HIGH);
            digitalWrite(red_light, HIGH);
            }
        if(x2!=x && y2!=y) // if the reading is reversed then gyro_reversed is true
            {
              stage=5;
              digitalWrite(red_light, HIGH);
              delay(1500);
              digitalWrite(red_light, LOW);
              break;
            } 
          if(timeElapsed>2000)
            {
            digitalWrite(green_light, LOW);
            digitalWrite(red_light, LOW);
            timeElapsed=0;
            }                    
           
      
      
   }  
  
  while(stage==5) // lets flash on and off to show the user we felt the work initialization
   {
      delay(100); 
      digitalWrite(red_light, HIGH);

      delay(100);
      digitalWrite(red_light, LOW);

      delay(100);      
      digitalWrite(red_light, LOW);

      delay(100);      
      digitalWrite(red_light, HIGH);
      digitalWrite(green_light, LOW);
      delay(100);
      digitalWrite(red_light, HIGH);

      delay(100);
      digitalWrite(red_light, LOW);

      delay(200);      
      digitalWrite(red_light, LOW);

      delay(200);      
      digitalWrite(red_light, HIGH);

    
      
      stage=1;
  
   }



   while(stage == 1) // This is the 25 min work stage
    {
            
     digitalWrite(red_light, HIGH);
     digitalWrite(green_light, LOW);
     delay(500);
     timeElapsed=0; // lets use time Elapsed to count our work time 
     timeElapsed2=0; //prepare the secnd time elapsed var for use with LEDs
     x=digitalRead(gyro_1);
     y=digitalRead(gyro_2);        
               
           while(timeElapsed<=work_time)
              {
              x=digitalRead(gyro_1);
              y=digitalRead(gyro_2);          
                            
              }             
                            
           while(timeElapsed>=work_time)
               {     
                   x2=digitalRead(gyro_1);
                   y2=digitalRead(gyro_2);
                   if(x2!=x && y2!=y) // if the reading is matched then gyro_reversed is true
                         {
                              gyro_reversed=true;
                         }   
                  
                  if(timeElapsed2<2500)
                    {
                    digitalWrite(green_light, HIGH);

                    }
                                   
                 if(timeElapsed2>5000)
                    {
                    digitalWrite(green_light, LOW);
                    }
        
                  if(timeElapsed2>7500)
                    {
                    digitalWrite(green_light, HIGH);

                    timeElapsed2=0;
                    }                    
                   
                    if(gyro_reversed==true)
                     {         
                      gyro_reversed= false;
                      long_break_bonus=long_break_bonus+(timeElapsed-work_time); // lets find how much extra we worked past our need                           
                      work_count=work_count+1;
                      if(work_count>3)
                              {
                              work_count=0;
                              stage=3;
                              timeElapsed=0;    
                              timeElapsed2=0;
                              break; //we dont want to execute the code saying its stage 2 so we need to leave here for our looong break
                              }
                      timeElapsed2=0;
                      timeElapsed=0; // reset our handy time variables
                      if(stage != 3);
                        {
                        stage=2; // lets go to our short break and make sure we dont escape our long break
                        }
                      break; // lets get out of the while loop toget on our break
                     }


               }
             
             
             
             
             
    }  

   while(stage == 2) // 5 min break time
    { 

     
     digitalWrite(red_light,LOW);
     digitalWrite(green_light, HIGH);
     delay(1000);
   
        while(timeElapsed>=break_time*1000*60)
        {
        digitalWrite(green_light, LOW);
        delay(300);
        digitalWrite(green_light, HIGH);
        delay(200);      
        digitalWrite(green_light, LOW);
        delay(200);       
        digitalWrite(green_light, HIGH);
        delay(100);        
        if(gyro_reversed==true)
            {
            long_break_bonus=long_break_bonus-timeElapsed2;
            timeElapsed2=0;
            stage=1; 
            gyro_reversed = false;
            break;
            }
        
        
        }
    
    }

while(stage == 3) // the long break stage
    { 


      
      digitalWrite(red_light,LOW);
      digitalWrite(green_light, HIGH);
      delay(1000);
     // INSERT long break reward song HERE
     
      if(long_break_bonus>0) // lets check if we deserve a long break bonus
        {
          bonus_time=long_break_bonus;
        }
        while(timeElapsed<=long_break_time)
        
        {
        x=digitalRead(gyro_1);
        y=digitalRead(gyro_2);
        }
        
        while(timeElapsed>=long_break_time+bonus_time)
            { // Breaks over
              digitalRead(gyro_1);
              digitalRead(gyro_2);
              if(x2!=x && y2!=y) // if the reading is reversed then gyro_reversed is true
                      {
                        gyro_reversed=true;
                      }
              if(timeElapsed2<500)
                  {
                    digitalWrite(green_light, LOW);
                    digitalWrite(green_light, HIGH);
                  }
              if(timeElapsed2>500)
                  {
                    digitalWrite(green_light, HIGH);
                    digitalWrite(green_light, LOW);
                  }
              if(timeElapsed2>1000)
                  {
                    timeElapsed2=0;
                  }
                               
              if(gyro_reversed==true)
                        {
                        bonus_time=0;
                        long_break_time=0;
                        timeElapsed=0; // lets clear the militime so we can use it again
                        stage=1; // back to work!
                        break;
                        }
          }
    
    }


}
