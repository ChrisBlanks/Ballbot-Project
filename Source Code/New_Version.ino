/*
 * Programmer: Chris Blanks
 * Last update: April 28th, 2018
 * Notes:
 * This code is still being refined and tested. The control portion of
 * the code is responsive to changes in the gyro and encoder angles,
 * but there is usually too much actuation.
 *
 */


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Encoder.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define a_gc 0.8

Adafruit_BNO055 bno = Adafruit_BNO055(55);
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //Sets up motor shield (makes AFMS object)
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1); //Creates motor objects from getMotor function
Adafruit_DCMotor *myMotor2= AFMS.getMotor(2);

Encoder Y_encoder(18, 19);
Encoder X_encoder(2, 3);

//Input pins
const byte light_sens_pin = A1;
const byte button_pin = 11;
const byte batt_volt_pin = A0;

//Initial values for encoders
long positionY  = -999;
long positionX = -999;

//Value that the light sensor has to be under in order for
//the program to jump states.
long threshold = 600;

int button_state;
double light_sens_val;
double batt_volt_val;
double new_b_v;
double temp,pwm1,pwm2;


//Variables that will either control the state or
//be inputs into the control algorithm
double battery;
double final_gyro_y, final_gyro_x,final_phi_m_y, final_phi_m_x;
double gyro_y_offset,gyro_x_offset,motor_y_offset ,motor_x_offset;

//Local control variables
double DSTATEk, DSTATEb, DSTATEj, DSTATE, DSTATEm, DSTATEd, DSTATE_b,DSTATEz, DSTATEp, Dstate1;
double Gain_m, Inverter, sum_n,switch_j, switch_k, switch_c, switch_n, Switch;
int ROp1,i;
double tmp[5];
int DSTATE_o[2];
const double gain_of_sys[]= {100.0, -1.2, 15.0, -1.0, -0.3};

//Output of control algorithm that is sent to the servos
double PwmY,PwmX;

//flags
int state, run_check, stop_run = 0, calibrate = 1, control = 2; //State control
int flag_firstcycle = 1; /* boolean that is used in the control code and flow code */

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  Serial.println("Orientation Sensor Test"); Serial.println("");
  Serial.println("TwoKnobs Encoder Test:");
  
  pinMode(button_pin,INPUT);
  pinMode(light_sens_pin,INPUT_PULLUP);


  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  //delay(1000);
  initialization();
}



void loop() {
  encoder_read(&final_phi_m_x,&final_phi_m_y);
  sensor_calibrate();
  state_check();
  
}





void Instrument_Test(void){
  
  sensors_event_t event;
  bno.getEvent(&event);
  light_sens_val = analogRead(light_sens_pin);
  batt_volt_val = analogRead( batt_volt_pin);
  button_state = digitalRead(button_pin);

  new_b_v = (batt_volt_val/1023)*5*10; //converted to actual voltage reading
  pwm1 = 50;
  pwm2 = 50;
  
  Serial.println("Gyro Angles: ");
  Serial.print("Gyro X Angle: ");
  Serial.println(((float)event.gyro.x)*3.1415926535/180); //Converted to rad/s
  Serial.print("Gyro Y Angle: ");
  Serial.println(((float)event.gyro.y)*3.1415926535/180);
  Serial.print("Light sensor: ");
  Serial.println(light_sens_val);
  Serial.print("Button State: ");
  Serial.println(button_state);
  Serial.print("Battery Voltage: ");
  Serial.println(new_b_v);
  Serial.println("");
  
  long newY, newX;
  newY = Y_encoder.read()*0.5;
  newX = X_encoder.read()*-0.5; //Inverted position to match ballbot model

  if (newY != positionY || newX != positionX) {
    Serial.print("Encoder Y-Angle = ");
    Serial.print(newY);
    Serial.print(", Encoder X-Angle = ");
    Serial.print(newX);
    Serial.println("");
    Serial.println("");
    positionY = newY;
    positionX = newX; 
  }
  
}

void command_Motor(float duty_cycle_x, float duty_cycle_y){
  /* NJB 3/3/18 - Command_Motor(float duty_cycle_x, float duty_cycle_y)
   *  INFO - Takes the duty cycle produced by the control algorithm and converts it into an output that the 
   *  Adafruit Motor Shield can use to control the motors.
   *  
   *  Input Variables account for a negative value produced by the control algorithm 
  */
  float adj_duty_cycle_x = 0, adj_duty_cycle_y = 0;
  
  Serial.println("Motor Code");
  
  //Inverted the logic to fit ballbot model
  if (duty_cycle_x < 0){
    myMotor1 -> run(FORWARD);
    duty_cycle_x = (-1 * duty_cycle_x);
    adj_duty_cycle_x = map(duty_cycle_x,0, 100, 0, 255);
    myMotor1 -> setSpeed(adj_duty_cycle_x);
  }
  else{
    myMotor1 -> run(BACKWARD); 
    adj_duty_cycle_x = map(duty_cycle_x, 0, 100, 0, 255);
    myMotor1 -> setSpeed(adj_duty_cycle_x);  
  }
  if(duty_cycle_y < 0){
    myMotor2 -> run(FORWARD);
    duty_cycle_y = (-1 * duty_cycle_y);
    adj_duty_cycle_y = map(duty_cycle_y, 0, 100, 0, 255);
    myMotor2 -> setSpeed(adj_duty_cycle_y);
  }
  else{
    myMotor2 -> run(BACKWARD);
    adj_duty_cycle_y = map(duty_cycle_y, 0 , 100, 0, 255);
    myMotor2 -> setSpeed(adj_duty_cycle_y);
  }
  delay(100);
  myMotor1 -> run(RELEASE);
  myMotor2 -> run(RELEASE);
  
}

void encoder_read(double *x_read,double *y_read){
  double temp1,temp2;
  
  *y_read = temp1 = Y_encoder.read()*0.5;
  *x_read = temp2 = X_encoder.read()*-0.5;

  if (*y_read != positionY || *x_read != positionX) {
    /*Serial.print("Encoder Y-Angle = ");
    Serial.print(*y_read);
    Serial.print(", Encoder X-Angle = ");
    Serial.print(*x_read);
    Serial.println("");
    Serial.println("");*/
    positionY = temp1;
    positionX = temp2; 
  }
}

void sensor_calibrate(void){
  
  sensors_event_t event;
  bno.getEvent(&event);
  
  gyro_y_offset = (gyro_y_offset * a_gc) + (event.gyro.y * (1.0 - a_gc) );
  gyro_x_offset = (gyro_x_offset * a_gc) + (event.gyro.x * (1.0 - a_gc) );
  
  
  motor_y_offset = -1.0 * final_phi_m_y; // Inverts readings 
  motor_x_offset = -1.0 * final_phi_m_x;
  
  Serial.println("Calibrate complete.");
}


void state_check(void){
  Serial.println("Began state check.");
  
  light_sens_val = analogRead(light_sens_pin);
  run_check = digitalRead(button_pin); //Checks to see if button has been pressed during this loop
  battery = read_voltage(); //Continuously check battery voltage
                            
  sensors_event_t event;
  bno.getEvent(&event);
  
  final_gyro_y = event.gyro.y ; // deg/s
  final_gyro_x = event.gyro.x ;// will be changed to rad/s control alg
  
  /* Below are If statements control state of ballbot.
   *  
   * If the button is pressed, the initial state is stop_run, 
   * and the light sensor's value is low (due to blockage by the ball) 
   * then the sensors will be calibrated again
   *  
   *  Note about light sensor:
   *  
   *  The light sensor reads a new value every loop. 
   *  These values are representative of the voltage generated
   *  by the amount of light that is being received by the 
   *  phototransistor in the light sensor. The span of the values
   *  is from 0 to 1023 (10 bit).
   *  
   *  Normally, the actual readings in an envirnoment with typical 
   *  amounts of ambient light will range from 450 to 700. 
   *  For this project, a reading of 450 indicates that the ball is
   *  in place. A value over 550 usually indicates that the ball has been
   *  lost. The ballbot will only operate under a value of 550. For different
   *  environments, this threshold value may need to be adjusted.
   *  
   */
   
  if(run_check == HIGH && light_sens_val <= threshold && state == stop_run){
    sensor_calibrate();
    state = calibrate ; //Allows ballbot to enter the next loop
    }
  if(state == calibrate && light_sens_val <= threshold){
    balance_and_control(); //Function that initiates the control portion of the code
    flag_firstcycle = 0; //First cycle has passed
    }
  if(state == calibrate && light_sens_val >= threshold){
    state = stop_run;
    Serial.println("GAME OVER.");
    Serial.println("Catch me.");
    Y_encoder.write(0);
    X_encoder.write(0);
    motors_off();//Ballbot is turned off if ball is lost
    }
}

double read_voltage(void){
  /* This sub-function is for reading the battery voltage  */
  
  batt_volt_val = analogRead( batt_volt_pin);
  new_b_v = (batt_volt_val/1023)*5*10;
  
  return new_b_v;
}

void initialization(void){
  battery = read_voltage();
  motors_off();
  flag_firstcycle = 1;
  state = 0;
  initial_offset();
  Serial.println("Finished initialization.");
}

void motors_off(void){
  myMotor1 -> setSpeed(0);
  myMotor2 -> setSpeed(0);
  Serial.println("Motors off.");
  }

void initial_offset(void){
  
  double init_phi_x, init_phi_y;
  
  sensors_event_t event;
  bno.getEvent(&event);
  
  gyro_y_offset = event.gyro.y;
  gyro_x_offset = event.gyro.x;

  light_sens_val = analogRead(light_sens_pin);
  
  motor_y_offset = 0 ; //Initial position is set for encoders
  motor_x_offset = 0 ;
  Serial.println("Initial offset done.");
  Serial.println(gyro_y_offset);
  Serial.println(gyro_x_offset);
  Serial.println(light_sens_val);
  Serial.println(battery);
  }
void status_check(void){
  Serial.println("Gyro(Y,X).");
  Serial.println(final_gyro_y);
  Serial.println(final_gyro_x);
  Serial.println("Encoder(Y,X).");
  Serial.println(final_phi_m_y);
  Serial.println(final_phi_m_x);
  Serial.println("Light & Voltage.");
  Serial.println(light_sens_val);
  Serial.println(battery);
  Serial.println("First cycle flag");
  Serial.println(flag_firstcycle);
  Serial.println("Gyro offsets (Y,X).");
  Serial.println(gyro_y_offset);
  Serial.println(gyro_x_offset);
  Serial.println("Encoder offsets (Y,X).");
  Serial.println(motor_y_offset);
  Serial.println(motor_x_offset);

  }
  
void balance_and_control(void){
  
  Serial.println("Made it to balance and control.");
  status_check();

//Control Algorithm
  Inverter = -1*(final_gyro_x - (0.999*gyro_x_offset + 0.001*final_gyro_x)); 
  
  if (flag_firstcycle == 1){
    switch_k = 0;
    }
  else{
  switch_k = Dstate1;
    }
  Dstate1 = (0.004* Inverter)+ switch_k;

  sum_n = (-final_phi_m_x - motor_x_offset)*0.0174532924 * 0.2 + (0.8 * DSTATE);

  if (flag_firstcycle == 1) {
    switch_j = sum_n;
    switch_c = 0.0;
  } else {
    switch_j = DSTATEb;
    switch_c = DSTATEp;
  } 
  
  DSTATEb = sum_n;
  
  Inverter = 0.75*Inverter + 0.25*DSTATEj;
  
  DSTATEp = 0.004 * (DSTATE_o[0] ? sum_n : 0.0) + switch_c; //it used a ternary operator

  Gain_m = (0.001089 *new_b_v) - 0.625;
  
  tmp[0] = 0.0174532924 * switch_k; //degree to rad
  tmp[1] = sum_n;
  tmp[2] = 0.0174532924 * Inverter;
  tmp[3] = (sum_n - switch_j) * 250.0;
  tmp[4] = switch_c;
  
  switch_c = 0.0;
  
  for (i = 0; i < 5; i++) {
    switch_c += gain_of_sys[i] * tmp[i]; //need to make an array for the ConstP
  }

  switch_c = (switch_c / Gain_m) * 100.0;

  if (switch_c > 100.0) {
    switch_k = 100.0;
  } else if (switch_c < -100.0) {
    switch_k = -100.0;
  } else {
    switch_k = switch_c;
  }

  PwmX = -1*switch_k; //Final pwm value
  Serial.println("For pwmX");
  Serial.println(switch_c);
  Serial.println(Gain_m);
  
  switch_c = fabs(switch_c);
  switch_k = fabs(switch_k);
  ROp1 = (switch_c <= switch_k);
  
  switch_j = (final_gyro_y - (0.999*gyro_y_offset + 0.001*final_gyro_y));

  if (flag_firstcycle == 1) {
    switch_c = 0.0;
  } else {
    switch_c = DSTATEz;
  }

  DSTATEz = 0.004 * switch_j + switch_c;

  switch_k = (-1*final_phi_m_y - motor_y_offset) * 0.0174532924 *0.2 + (0.8 * DSTATE_b);

  if (flag_firstcycle == 1) {
  switch_n = switch_k;
  Switch = 0.0;
  } else {
  switch_n = DSTATEd;
  Switch = DSTATEm;
  }

  DSTATEd = switch_k;
  DSTATEm = 0.004*(DSTATE_o[1] ? switch_k : 0.0) + Switch;
  
  switch_j = (0.75*switch_j) + (0.25*DSTATEk);

  tmp[0] = 0.0174532924 * switch_c;
  tmp[1] = switch_k;
  tmp[2] = 0.0174532924 * switch_j;
  tmp[3] = (switch_k - switch_n) * 250.0;
  tmp[4] = Switch;
  
  for (i = 0; i < 5; i++) {
    switch_c += gain_of_sys[i] * tmp[i];
  }
  
  Gain_m = (switch_c / Gain_m)* 100;
  
  if (Gain_m > 100.0) {
    switch_c = 100.0;
  } else if (Gain_m < -100.0) {
    switch_c = -100.0;
  } else {
    switch_c = Gain_m;
  }
  
  PwmY = -1*switch_c; //Some error in model
  Serial.println("For pwmY");
  Serial.println(switch_c);
  Serial.println(Gain_m);
  switch_c = fabs(switch_c);
  Gain_m = fabs(Gain_m);
  DSTATE = sum_n;
  DSTATEj = Inverter;  

  DSTATE_o[0] = ROp1;
  DSTATE_o[1] = (Gain_m <= switch_c);

  DSTATEb = switch_k;
  DSTATEk = switch_j;

  Serial.println("PWM commands (Y,X):");
  Serial.println(PwmY);
  Serial.println(PwmX);
  command_Motor(PwmX,PwmY);
  }



