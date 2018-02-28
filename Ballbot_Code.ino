

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

const int x_motor_Pin = 2; /* Motor controlling movement in the x_direction */
const int y_motor_Pin = 3; /* Motor controlling y-movement */

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  
  pinMode(x_motor_Pin,OUTPUT); 
  pinMode(y_motor_Pin,OUTPUT);

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
  float IMU_data[6] = [0,0,0,0,0,0];
  IMU_data = IMU_Sensor_Read();
}


void command_Motor(){
  
  Serial.print("Motor Code");
  
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

void IMU_Sensor_Read(void){
  /* NJB 2/27/18 - INFO: Gathers the relavent sensor data from the Inertial Mesurement Unit and stores that data into an 
   *  array to be used by the control algorithm
   *  
   *  float data[6] = [accel x, accel y, gyro x, gyro y, orientation x, orientation y]
  */
  
  sensors_event_t event; /* Event variable created to capture data from a specific time  */

  bno.getEvent(&event);  /* Stores collected data into event variable's location */
                         /* and converts the data into SI units and scales them */
  float data[6] = [0,0,0,0,0,0];
  
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
  return data;
}

