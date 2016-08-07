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


class LaserPrinter{

 private:
  unsigned int current_width;
  unsigned int current_length;
  bool laser;

 public:
  LaserPrinter(){
   current_width = current_length = laser =0;
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
        Serial.println("error1");
        return false;
      }
    
      if( not dir && (current_width < 0)){
        Serial.println("error2");

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
         Serial.println("error3");

        return false;
      }
    
      if( dir && (current_length < 0)){
        Serial.println("error4");

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
    Serial.print("current position: width: ");
    Serial.print(current_width);
    Serial.print(" length: ");
    Serial.println(current_length);
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
  
 
};







void setup() 
{  Serial.begin(9600);
  // The stepper motor used in the IO pin is set to output
   pinMode(X_DIR, OUTPUT); 
   pinMode(X_STP, OUTPUT);
   pinMode(Y_DIR, OUTPUT); 
   pinMode(Y_STP, OUTPUT);
   pinMode(LASER, OUTPUT); 
   pinMode(9, INPUT);
   pinMode(EN, OUTPUT);
   digitalWrite(EN, LOW);
 
   LaserPrinter l1;
    
 /*  for(int i = 0; i< 500; i++) {
    l1.step_forward();
    delayMicroseconds(10);
   }
   
  for(int i = 0; i< 370; i++) {
    l1.step_right();
    delayMicroseconds(10);
  }
  */
  int w;
  int l;

  
 l1.toggle_laser();
  delay(10);
  for(double angle = 0; angle<2*M_PI; angle +=M_PI/60.0  ){
    w = 50+(50.0*cos(angle));
    l = 50+(50.0*sin(angle));
    
    Serial.print("objective: width: ");
    Serial.print(w);
    Serial.print(" length: ");
    Serial.println(l);
    Serial.print(" angle: ");
    Serial.println(angle);

    
    while(not l1.InWidth(w) ) {
      if(l1.CurrentWidth() > w) l1.step_left();
      else l1.step_right();
      delayMicroseconds(300);
     }
    while(not l1.InLength(l) ) {
      if(l1.CurrentLength() >l) l1.step_backward();
      else l1.step_forward();
      delayMicroseconds(300);
     }
  }

   l1.toggle_laser();

  /*while(not l1.InOriginLength()){
    l1.step_backward();
    delayMicroseconds(100);
  }
  while(not l1.InOriginWidth()){
    l1.step_left();
    delayMicroseconds(100);
  }
  */
}

void loop() 
{ 


  /*int i=0;
  while(true){  
  Serial.print("current pos: ");
  Serial.println(i);
  step(DIR_FORW, Y_DIR,  Y_STP,1) ;
  delay(50);
  i++;
}
  /*for(int i=0; i<200; i++){
   step(DIR_FORW, X_DIR,  X_STP,1) ;
   delay(500);
  }
  for(int i=0; i<200; i++){
   step(DIR_FORW, Y_DIR,  Y_STP,1) ;
   delay(500);
  }
  for(int i=0; i<200; i++){
   step(DIR_BACK, X_DIR,  X_STP,1) ;
   delay(500);
  }
  for(int i=0; i<200; i++){
   step(DIR_BACK, Y_DIR,  Y_STP,1) ;
   delay(500);
  }
 */
 
 
}

//Please note:

//When inserting the A4988 module, must be careful not to insert opposite. Stepper motor wiring as follows:
//2A, 2B is a group (red, green), 1A, 1B is a group (blue, yellow), if want to change direction, can be change the position of one group , for example 2A, 2B mutually exchanged

