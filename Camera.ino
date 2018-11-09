#include <Servo.h> 

int PixelArray[128] ;           
int CLK = 13;                    
int SI  = 12;                   
int i   =  0;                   
char Star[128][11];         
int expose = 20000;
int motorPin = 5;
int brakePin = 10;
bool flag = 0;
bool out = 0;

double midpoint;
double error;
double lasterror;
double lasttime=0;
double thistime;
const double Kp = 0.45;
const double Kd = 9.0;
const double Ks = 1.0;



Servo myservo;
int th = 9;
int PixelTH = 300;
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  pinMode(CLK, OUTPUT);          
  pinMode(SI, OUTPUT);          
  Serial.begin(9600);

  digitalWrite(SI, HIGH);                            
  digitalWrite(CLK, HIGH);                               
  digitalWrite(SI, LOW);                                 
  digitalWrite(CLK, LOW);   
  myservo.attach(11);  
                                          
 for(i = 0; i < 128; i ++)
 {                                                                                              
 digitalWrite(CLK, HIGH);                                                                                            
 digitalWrite(CLK, LOW);                                                       
 } 

}

void loop() 
{   

 
 digitalWrite(SI, HIGH);      
 digitalWrite(CLK, HIGH);
          
 digitalWrite(SI, LOW);                       
 digitalWrite(CLK, LOW);      
                                                                   
  for(i = 0; i < 128; i ++)
  {                             
  delayMicroseconds(50);                                 
  PixelArray[i] = analogRead(A1); 
                                                                                                
  digitalWrite(CLK, HIGH);       
  digitalWrite(CLK, LOW);                                                                                               
  }         
 //Serial.println(arraymax);                                                    
 delayMicroseconds(expose);
 
 digitalWrite(SI, HIGH);      
 digitalWrite(CLK, HIGH);
          
 digitalWrite(SI, LOW);                       
 digitalWrite(CLK, LOW); 

//PixelArray[23] = 0;
//PixelArray[39] = 0;
//PixelArray[40] = 0;

 for (i = 0; i < 128; i++)
 {
  //PixelArray[i] = map(PixelArray[i],0,500,0,9);
     
  if(PixelArray[i] > PixelTH)
     PixelArray[i] = 9;
  else
     PixelArray[i] = 0;
  
 }
  
if (flag)
{ 
  for (i = 0; i < 128; i++)
  {
    Star[i][9]=PixelArray[i]+'0';
    for(int j=0;j<9;j++)
    {
      if(j< PixelArray[i])
        Star[i][8-j]='*';
      else
        Star[i][8-j]=' ';
    }
 Star[i][10] = '.';
  }
} 



int firstpos;
int lastpos;
for(firstpos =0; firstpos<126;firstpos++)
{ 
  if(PixelArray[firstpos] == th && PixelArray[firstpos+1] == th && PixelArray[firstpos+2] == th)
{
    Star[firstpos][10] = '|';
    break;
}

}

for(lastpos = 127; lastpos >= 2;lastpos--)
{ 
  if(PixelArray[lastpos] == th && PixelArray[lastpos-1] == th && PixelArray[lastpos-2] == th)
  {   
    Star[lastpos][10] = '|';
    break;
  }
}
if(firstpos < 126 && lastpos > 1)
  {
    midpoint = (firstpos+ lastpos) / 2;
    out = 0;
  }
else
  {
     out =1;  
  }
//Serial.println(midpoint);
//Star[(int)midpoint][10] = '*';
if (flag)
{
for(int i=0;i<11;i++)
{
  for(int j=0;j<128;j++)
  {
    Serial.print(Star[j][i]);
  }
  Serial.print('\n');
}
 Serial.print('\n');
 Serial.print('\n');
}

//  int p = 115-(midpoint/2); 
// Serial.println(midpoint);


// myservo.write(40);
  error = 62-midpoint;
  thistime = millis();
  Serial.print(error-lasterror);
  double d = Kd*(error-lasterror)/(thistime-lasttime);
  double p = Kp*error;
  lasttime = thistime;
  lasterror = error;
  myservo.write(40-p-d);
  
  if(!out)
  {
  analogWrite(motorPin, 65-Ks*abs(error));
  }
   else
  {
    analogWrite(motorPin, 50);
  }
}    

  


