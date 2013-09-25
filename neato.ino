


double angle=0;
int r=115;
int rMin=15;
int x2;
int y2;
int cY;
int cX;
unsigned int distance;
unsigned int distance_array[360];
unsigned char distanceLow=0;
unsigned char distanceHigh=0;
unsigned char flag1=0;
unsigned char flag2=0;

const int DesiredRPM=300;  // Setting Desired RPM Here.
const int MotorPWMPin=8;


int inByte = 0;         // incoming serial byte
unsigned char Data_status=0;
unsigned char Data_4deg_index=0;
unsigned char Data_loop_index=0;
unsigned char SpeedRPHhighbyte=0; // 
unsigned char SpeedRPHLowbyte=0;

int SpeedRPH=0;
const unsigned char PWM4dutyMax=255;
const unsigned char PWM4dutyMin=100;
//const unsigned char PWM4dutyMin=178;
unsigned char PWM4duty=PWM4dutyMin;  // have to set a default value make motor start spining

 void setup() {
    pinMode(MotorPWMPin, OUTPUT); 
    
    analogWrite(MotorPWMPin, PWM4dutyMin);    
    Serial.begin(115200);  // USB serial
    Serial3.begin(115200);  // XV-11 LDS data 
    

  // prints title with ending line break 
  Serial.println("Arduino Neato XV-11 Motor control board v0.1 by Cheng-Lung Lee");  // thanks!
  
  // Pick your magic number and drive your motor , 178 is 178/255*5V=3.49V
    analogWrite(MotorPWMPin, PWM4duty);
    
    
 
    char CharMsg[4];
    itoa(r,CharMsg,10);
  
}

void loop() {
    // if we get a valid byte from LDS, read it and send it to USB-serial
  if (Serial3.available() > 0) {
    // get incoming byte:
    inByte = Serial3.read();
    //Serial.write(inByte);
    decodeData(inByte);
  }

}

void decodeData(unsigned char inByte){
  
  switch (Data_status){
    
  case 0: // no header
    if (inByte==0xFA){
      Data_status=1;
      Data_loop_index=1;
    }
  break;
  
  case 1: // Find 2nd FA
    if (Data_loop_index==22){
      if (inByte==0xFA){
        Data_status=2;
        Data_loop_index=1;
      }else // if not FA search again
       Data_status=0;
    }else{
      Data_loop_index++;
    }
    break;
    
  case 2: // Read data out
  
    if (Data_loop_index==22){
      if (inByte==0xFA){
        Data_loop_index=1;
      } 
      else // if not FA search again
      Data_status=0;
    }else{
      readData(inByte);
      Data_loop_index++;
    }
    break;
  }
  
}
void readData(unsigned char inByte){
  
  switch (Data_loop_index){
    
    case 1: // 4 degree index
    Data_4deg_index=inByte-0xA0;
//      Serial.print(Data_4deg_index, HEX);  
    
 
    break;
    
    case 2: // Speed in RPH low byte
    SpeedRPHLowbyte=inByte;
    break;
    
    case 3: // Speed in RPH high byte
    SpeedRPHhighbyte=inByte;
    SpeedRPH=(SpeedRPHhighbyte<<8)|SpeedRPHLowbyte;
    
    SpeedControl(DesiredRPM);    
    
    
    break;
   
    
    case 4:
    case 8:
    case 12:
    case 16:
    distanceLow=inByte;
    break; 
    
    case 5:
    case 9:
    case 13:
    case 17:
    distanceHigh=inByte & B00111111; //mask 14 and 15 bits
    //distanceHigh=inByte & B11111100; //mask 14 and 15 bits
    
    flag1=inByte & B10000000;
    flag2=inByte & B01000000;
    
    distance=(distanceHigh<<8)|distanceLow;
    
    
  
     if (true){

      int dataIndex;
      switch (Data_loop_index){
       case 5:
         dataIndex=0;
       break;
       case 9:
         dataIndex=1;       
       break;
       case 13:
         dataIndex=2;       
       break;
       case 17:
         dataIndex=3;       
       break;
      }
            
      int angleIndex=Data_4deg_index*4 + dataIndex;

  if (flag1==0 && flag2==0){

        distance_array[angleIndex]=distance;
      
      }else{
        distance_array[angleIndex]=0;
      }



      

  if (dataIndex==3 && Data_4deg_index==89) drawMap();

   }
   break;    
   
    
    default: // others do checksum
    
    break;
    
   
  } 
 
  
 
  
}


// Very simple speed control
void SpeedControl ( int RPMinput)
{
// if (Data_4deg_index%30==0) {  // I only do 3 updat I feel it is good enough for now
 if (Data_4deg_index%40==0) {  // I only do 3 updat I feel it is good enough for now
  if (SpeedRPH<RPMinput*60)
     if (PWM4duty<PWM4dutyMax) PWM4duty++; // limit the max PWM make sure it don't overflow and make LDS stop working
  if (SpeedRPH>RPMinput*60)
     if(PWM4duty>PWM4dutyMin) PWM4duty--;  //Have to limit the lowest pwm keep motor running
  }     
  analogWrite(MotorPWMPin, PWM4duty ); // update value
}


void drawMap(){
  for (int i=0;i<360;i++){
    int distMax=6000;
    int d=distance_array[i];
    distance_array[i]=0;
    if (d==0 || d>distMax)continue;

    
    int r2=map(d, 0, distMax, 0, 115);
    
   
    Serial.print(i);
    Serial.print(" D:");
    Serial.println(r2);
    //to radians
    double rad_angle= i * 3.1415 / 180;
  }
}
