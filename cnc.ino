#include <math.h>

#define EN 8 // stepper motor enable , active low
#define X_DIR 5 //X -axis stepper motor direction control
#define Y_DIR 6 // y -axis stepper motor direction control
#define X_STP 2 // x -axis stepper control
#define Y_STP 3 // y -axis stepper control
#define LASER 7 // z axis stepper motor direction control
#define DIR_BACK true
#define DIR_FORW false
#define DIR_LEFT true
#define DIR_RIGHT false
#define MAX_LENGTH 1000
#define MAX_WIDTH 740
#define CM_STEP 0.021
/*
//Function : step . function: to control the direction of the stepper motor , the number of steps .
//Parameters : dir direction control , dirPin corresponding stepper motor DIR pin , stepperPin corresponding stepper motor " step " pin , Step number of step of no return value.
*/
//Define com protocol
#define OK 0x00
#define PEN_MODE 0x00
#define LINE_MODE =0xFF
//PEN_MODE protocol
#define CIRCLE_REQUEST 0x00
#define LINE_REQUEST 0xFF
#define ACK 0x01
#define FINISH 0x02


#define DEBUG 0
class LaserPrinter{

 private:
  unsigned int current_width;
  unsigned int current_length;
  bool laser;

 public:
  LaserPrinter(){
   current_width = current_length = laser =0;
   pinMode(X_DIR, OUTPUT); 
   pinMode(X_STP, OUTPUT);
   pinMode(Y_DIR, OUTPUT); 
   pinMode(Y_STP, OUTPUT);
   pinMode(LASER, OUTPUT); 
   pinMode(9, INPUT);
   pinMode(EN, OUTPUT);
   digitalWrite(EN, LOW);
   digitalWrite(LASER, LOW);
  }

  unsigned int CurrentWidth(){
    return current_width;
  }

  unsigned int CurrentLength(){
    return current_length;
  }
  
  bool InLength(int _length){

    return (current_length == _length);
  }
  
  bool InWidth(int width){

    return (current_width == width);
  }

  bool InOriginLength(){

    return (current_length == 0);
  }
  
  bool InOriginWidth(){

    return (current_width == 0);
  }

  
  void toggle_laser(){
    laser = not laser;
    digitalWrite(LASER, laser);
  }
  
  bool step(boolean dir, byte pin_stp, byte pin_dir){
    if( X_STP == pin_stp){
       if(dir && (current_width >= MAX_WIDTH)){
        return false;
      }
    
      if( not dir && (current_width < 0)){
       

        return false;
      }
      if(dir){
        current_width--;
      }
      else{
        current_width++;
      }
    }
    else{
      if(not dir && (current_length >= MAX_LENGTH)){
      

        return false;
      }
    
      if( dir && (current_length < 0)){
       

        return false;
      }
      if(not dir){
        current_length++;
      }
      else{
        current_length--;
      }
    }
 
    digitalWrite(pin_dir, dir);
    delay(50);
    digitalWrite(pin_stp, HIGH);
    delayMicroseconds(800);
    digitalWrite(pin_stp, LOW);
    delayMicroseconds(800);
    #ifdef
      Serial.print("current position: width: ");
      Serial.print(current_width);
      Serial.print(" length: ");
      Serial.println(current_length);
    #endif
    return true;
  }

  bool step_right(){
  return step(DIR_RIGHT, X_STP, X_DIR);
  }
  bool step_left(){
  return step(DIR_LEFT, X_STP, X_DIR);
  }
  bool step_backward(){
  return step(DIR_BACK, Y_STP, Y_DIR);
  }
  bool step_forward(){
  return step(DIR_FORW,Y_STP, Y_DIR);
  }
  
  bool MoveTo(int l, int w){
    
    while(not InWidth(w) ) {
      if(CurrentWidth() > w){
        if(not step_left()) return false;
      }
      
      else{
        if(not step_right()) return false;
      }
      delayMicroseconds(300);
     }
    while(not InLength(l) ) {
      if(CurrentLength() >l) {
        if(not step_backward()) return false;
      }
      else{
        if(not step_forward())  return false;
      }
      delayMicroseconds(300);
     }
     return true;
     
  }
  bool DrawCircle(int Radius, int c_l, int c_w ,  double initial_angle=0.0, double final_angle=2*M_PI){
    int w, l;
    if(final_angle < initial_angle){
        initial_angle +=2*M_PI; 
      }
    w = c_w+(Radius*cos(initial_angle));
    l = c_l+(Radius*sin(initial_angle));
    if (not MoveTo(l, w)){
       return false;
    }
    toggle_laser();
    delay(50);
    for(double angle = initial_angle ; angle<final_angle; angle +=M_PI/60.0  ){
      
      w = c_w+(Radius*cos(angle));
      l = c_l+(Radius*sin(angle));
      
       if (not MoveTo(l, w)){
        return false;
       }
    }
    toggle_laser();
    return true;
  }
  bool DrawLine(int orig_l, int orig_w, int dest_l, int dest_w ){
    int d_w = dest_w-orig_w;
    int d_l = dest_l-orig_l;

    //euclides alg's
    int a, b, r;
    if (abs(d_w) > abs( d_l)){
      a=abs(d_w);
      b=abs(d_l);
    }
    else{
      a=abs(d_l);
      b=abs(d_w);
    }
    if(b!=0){
      r=a%b;
      while(r>0){
        a=b;
        b=r;
        r=a%b;
      }
    }
    else
      b=1;
    d_w = d_w/b;
    d_l = d_l/b;

    MoveTo(orig_l, orig_w);
    toggle_laser();
    delay(50);

    while(not InLength(dest_l) || not InWidth(dest_w)){
      if (not MoveTo(CurrentLength()+d_l, CurrentWidth()+d_w)) return false;
    }

    toggle_laser();
    return true;
  }
  bool ReturnLaser(){
    while(not InOriginLength()){
      if(not step_backward()){
        return false;
      }
    }
    while(not InOriginWidth()){
      if(not step_left()){
        return false;
      }
    }
   return true;
  }
};







void setup() 
{  Serial.begin(9600);
  // The stepper motor used in the IO pin is set to output
   
 
   LaserPrinter l1;
   /*while(!Serial){
    //Wait till serial is ready
   }
*/
   
    
}

void loop() 
{ 
 /*
 //Initial handshake
 while(Serial.available() < 0){}
 if(Serial.read() ==  OK){
  //MODE SELECTION
  if(Serial.read() == PEN_MODE){
    Serial.write(OK);
     if(Serial.read() == CIRCLE_REQUEST){
      Serial.write(OK);
      
     }
  }
  else{
    //Under construction
  }
 }

  */
 
}

//Please note:

//When inserting the A4988 module, must be careful not to insert opposite. Stepper motor wiring as follows:
//2A, 2B is a group (red, green), 1A, 1B is a group (blue, yellow), if want to change direction, can be change the position of one group , for example 2A, 2B mutually exchanged

