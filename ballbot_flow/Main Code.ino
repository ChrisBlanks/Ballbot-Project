#include <Wire.h>            /*Allows I2C communication */
#include <Adafruit_Sensor.h> /* Allows for easy integration of sensors */
#include <Adafruit_BNO055.h> /* Inheirits from Adafruit_Sensor; The sensor type used */
#include "utility/imumaths.h"
#include <Adafruit_MotorShield.h> // Opens the the Motor Shield Library
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include <stddef.h>
#include <stdio.h>
#include "feedback_control.h"
#include "rtwtypes.h"
#include "ert_main.h"

#define a_gc 0.8 //initial gyro offset in calibration

Adafruit_BNO055 bno = Adafruit_BNO055(55); // Sets up IMU sensor (makes bno object)

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); //Sets up motor shield (makes AFMS object)

Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1); //Creates motor objects from getMotor function
Adafruit_DCMotor *myMotor2= AFMS.getMotor(2);

/* paramaters that hold sensor and control data */
double battery,light_sens_val, threshold, final_pwm_x, final_pwm_y;
double final_gyro_y, final_gyro_x,final_phi_m_y, final_phi_m_x;
double gyro_y_offset,gyro_x_offset,motor_y_offset ,motor_x_offset;

int state, run_check, stop_run = 0, calibrate = 1, control = 2; //State control
int flag_firstcycle = 1; /* boolean that is used in the control code and flow code */
//Needs to be matched up with the control code still

const int button_pin = 10; /* Pin that will start the calibration and run process */
const int light_sens_pin = 9; /* Pin that will sense if the ball is present */

void setup() {
 AFMS.begin();
 bno_Setup(); //Abstracted into a subfunction
 
 Serial.begin(9600);
 pinMode(button_pin,INPUT);
 pinMode(light_sens_pin,INPUT);
 
 initialization(); //Runs intiliazation task and sets up initial parameters before calibration
 
}

void loop() {
  state_check();
}




/* subfunctions */


void bno_Setup(void){
  
  if( !bno.begin() ) /* If the sensor is not read by the arduino */
  {
    Serial.print("Connection Issue. Check the wiring or I2C address.");
    while(1); /* Infinite loop that will restart the arduino and check the status of the sensor */
  }
  
  delay(1000);

  bno.setExtCrystalUse(true); /* sets an external 32.768 kHZ crystal for the clock (more accurate) */
  }

  
void initial_offset(void){
  
  sensors_event_t event;
  bno.getEvent(&event);
  
  double initial_y_ang, initial_x_ang; //local variables for encoder data
  
  gyro_y_offset = event.gyro.y;
  gyro_x_offset = event.gyro.x;
  
  encoder_read_y(&initial_y_ang);
  encoder_read_x(&initial_x_ang);
  
  motor_y_offset = initial_y_ang ; //Waiting on method to obtain phi angles from encoders
  motor_x_offset = initial_x_ang ;
  }

 
void motors_off(void){
  myMotor1 -> setSpeed(0);
  myMotor2 -> setSpeed(0);
  }

  
void initialization(void){
  battery = read_voltage();
  motors_off();
  flag_firstcycle = 1;
  state = 0;
  initial_offset();
  }

  
void state_est_and_control(double gyro_y_val, double gyro_x_val,double phi_angle_y,
               double phi_angle_x,real_T *pwm_y_direction, real_T *pwm_x_direction){
  //Inputs to control code
   rtU.gyro_y = gyro_y_val;
   rtU.gyro_x = gyro_x_val;
  
   rtU.phi_m_y = phi_angle_y;
   rtU.phi_m_x = phi_angle_x;

  // Data Store items used in control
   rtDWork.flag_firstcycle = flag_firstcycle ;
   rtDWork.battery = battery ;
   rtDWork.gyro_y_offset = gyro_y_offset ;
   rtDWork.gyro_x_offset = gyro_x_offset ;
   rtDWork.motor_y_offset = motor_y_offset ;
   rtDWork.motor_x_offset = motor_x_offset ;

  feedback_control_initialize();
  rt_OneStep();

  
  *pwm_y_direction = rtY.pwm_y;
  *pwm_x_direction = rtY.pwm_x;
  
  } 

  
double read_voltage(void){
  /* This sub-function is for reading the battery voltage  */
  
  int batt_volt = 5;   //placeholder value
  //batt_volt = analogRead(pin_number);
  return batt_volt;
  }


void state_check(void){
  light_sens_val = analogRead(light_sens_pin);
  run_check = digitalRead(button_pin);
  battery = read_voltage(); //Continuously check battery voltage
                            //May need to use low pass filter
  double phi_angle_y, phi_angle_x; //local variables for transfering encoder readings
  
  sensors_event_t event;
  bno.getEvent(&event);
  
  encoder_read_y(&phi_angle_y);
  encoder_read_x(&phi_angle_x);
  
  final_gyro_y = event.gyro.y ;
  final_gyro_x = event.gyro.x ;
  
  final_phi_m_y = phi_angle_y;
  final_phi_m_x = phi_angle_x;

  /* If statements control state of ballbot.
   * If the button is pressed, the initial state is stop_run, 
   * and the light sensor's value is low (due to blockage by the ball) 
   * then the sensors will be calibrated again
   *  
   *  
   */
   
  if(run_check == HIGH && light_sens_val <= threshold && state == stop_run){
    sensor_calibrate();
    state = calibrate ;
    }
  if(state == calibrate && light_sens_val <= threshold){
    balance_and_control();
    state = control;
    }
  if(state == control && light_sens_val >= threshold){
    state = stop_run;
    motors_off();
    }

  }


void balance_and_control(void){
  //need to pass these values to control theory code
  
  state_est_and_control(final_gyro_y, final_gyro_x,
                        final_phi_m_y, final_phi_m_x, &final_pwm_y,&final_pwm_x);
  
  command_Motor(final_pwm_x,final_pwm_y); //Sends duty cycle values to servos
}


void sensor_calibrate(void){
  motors_off();
  
  double e_angle_y, e_angle_x;
  
  sensors_event_t event;
  bno.getEvent(&event);
  
  gyro_y_offset = (gyro_y_offset * a_gc) + (event.gyro.y * (1.0 - a_gc) );
  gyro_x_offset = (gyro_x_offset * a_gc) + (event.gyro.x * (1.0 - a_gc) );
  
  encoder_read_y(&e_angle_y);
  encoder_read_x(&e_angle_x);

  
  motor_y_offset = -1.0 * e_angle_y; // Inverts readings
  motor_x_offset = -1.0 * e_angle_x;
  }


void encoder_read_x(double *x_read){ //function for reading X encoder value and getting an
   
  *x_read= 1.0;
  
  }


void encoder_read_y(double *y_read){ //function for reading Y encoder value and getting an angle
  
  *y_read = 1.0;
  
  }


void command_Motor(float duty_cycle_x, float duty_cycle_y){
  /* NJB 3/3/18 - Command_Motor(float duty_cycle_x, float duty_cycle_y)
   *  INFO - Takes the duty cycle produced by the control algorithm and converts it into an output that the 
   *  Adafruit Motor Shield can use to control the motors.
   *  
   *  Input Variables account for a negative value produced by the control algorithm 
  */
  float adj_duty_cycle_x = 0, adj_duty_cycle_y = 0;
  
  Serial.print("Motor Code");
  if (duty_cycle_x < 0){
    myMotor1 -> run(BACKWARD);
    duty_cycle_x = (-1 * duty_cycle_x);
    adj_duty_cycle_x = map(duty_cycle_x,0, 100, 0, 255);
    myMotor1 -> setSpeed(adj_duty_cycle_x);
  }
  else{
    myMotor1 -> run(FORWARD);
    adj_duty_cycle_x = map(duty_cycle_x, 0, 100, 0, 255);
    myMotor1 -> setSpeed(adj_duty_cycle_x);  
  }
  if(duty_cycle_y < 0){
    myMotor2 -> run(BACKWARD);
    duty_cycle_y = (-1 * duty_cycle_y);
    adj_duty_cycle_y = map(duty_cycle_y, 0, 100, 0, 255);
    myMotor2 -> setSpeed(adj_duty_cycle_y);
  }
  else{
    myMotor2 -> run(FORWARD);
    adj_duty_cycle_y = map(duty_cycle_y, 0 , 100, 0, 255);
    myMotor2 -> setSpeed(adj_duty_cycle_y);
  }

  //myMotor1 -> run(RELEASE);
  //myMotor2 -> run(RELEASE);
  
  }
