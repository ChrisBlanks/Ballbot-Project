/*
 * Purpose: This code is meant to interface the UNO with the Inertial Measurement
 * Unit (IMU) and two motors, and it will include control equations that will keep the 
 * ballbot perpendicular to the X-Y plane.
 *
 * Date Modified: 2/14/2018
 */
 
#include <Wire.h>            /*Allows I2C communication */
#include <Adafruit_Sensor.h> /* Allows for easy integration of sensors */
#include <Adafruit_BNO055.h> /* Inheirits from Adafruit_Sensor; The sensor type used */
#include "utility/imumaths.h"
#include <Adafruit_MotorShield.h> // Opens the the Motor Shield Library
#include "utility/Adafruit_MS_PWMServoDriver.h" 

Adafruit_BNO055 bno = Adafruit_BNO055(55); /* Sets up IMU */

//Motor Shield Setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2= AFMS.getMotor(2);


void setup() {
  AFMS.begin();
  Serial.begin(9600);
  
  // Default Motor Speed
  myMotor1 -> setSpeed(0);
  myMotor2 -> setSpeed(0);
  
  if( !bno.begin() ) /* If the sensor is not read by the arduino */
  {
    Serial.print("Connection Issue. Check the wiring or I2C address.");
    while(1); /* Infinite loop that will restart the arduino and check the status of the sensor */
  }
  
  delay(1000);

  bno.setExtCrystalUse(true); /* sets an external 32.768 kHZ crystal for the clock (more accurate) */
  displaySensorDetails();

}


void loop() {
  float IMU_data[6] = {0,0,0,0,0,0};
  IMU_data[0], IMU_data[1], IMU_data[2], IMU_data[3], IMU_data[4], IMU_data[5] = IMU_Sensor_Read();
  command_Motor(100, 100); // Placement Values
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

  // May Not Be Needed After - Releases The Motors After Use
  //myMotor1 -> run(RELEASE);
  //myMotor2 -> run(RELEASE);
  
  
  }
  
void displaySensorDetails(void) /* Shows basic sensor details */
{
  sensor_t sensor; /* 'sensor_t' type allows for basic features of the sensor to be accessed */
  bno.getSensor(&sensor);
  
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); 
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); 
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); 
  Serial.println("");
  
  delay(250); //250ms Delay njb 2/17/18
}

float IMU_Sensor_Read(void){
  /* NJB 2/27/18 - INFO: Gathers the relavent sensor data from the Inertial Mesurement Unit and stores that data into an 
   *  array to be used by the control algorithm
   *  
   *  float data[6] = [accel x, accel y, gyro x, gyro y, orientation x, orientation y]
  */
  
  sensors_event_t event; /* Event variable created to capture data from a specific time  */

  bno.getEvent(&event);  /* Stores collected data into event variable's location */
                         /* and converts the data into SI units and scales them */
  float data[6] = {0,0,0,0,0,0}; 
  for(int i = 0; i < 6; i++){
    switch(i){
      case 0:
      if(event.acceleration.x){
        Serial.print("Working.");
        Serial.println("Data:");
        data[0] = event.acceleration.x;
        Serial.print(data[0], 4); /* second argument: 4 decimal places */
      }
      break;
      
      case 1:
      if(event.acceleration.y){
        Serial.print("Working.");
        Serial.println("Data:");
        data[1] = event.acceleration.y;
        Serial.print(data[1], 4);
      }
      break;
      
      case 2:
      if(event.gyro.x){
        Serial.print("Working.");
        Serial.println("Data:");
        data[2] = event.gyro.x;
        Serial.print(data[2], 4);
      }
      break;
     
      case 3:
      if(event.gyro.y){
        Serial.print("Working.");
        Serial.println("Data:");
        data[3] = event.gyro.y;
        Serial.print(data[3], 4);
      }
      break;
     
      case 4:
      if(event.orientation.x){
        Serial.print("Working.");
        Serial.println("Data:");
        data[4] = event.orientation.x;
        Serial.print(data[4], 4);
      }
      break;
      
      case 5:
      if(event.orientation.y){
        Serial.print("Working.");
        Serial.println("Data:");
        data[5] = event.orientation.y;
        Serial.print(data[5], 4);
      }
      break;
      
      default: // if error occured in the for loop it will let the user know through the serial monitor
      Serial.println("Invalid Location: Check IMU_Sensor_Read");
      break;
    }
  }
  return data[0], data[1], data[2], data[3], data[4], data[5]; 
}

