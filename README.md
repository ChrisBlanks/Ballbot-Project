# Ballbot-Project
This project is an adaptation of the Ballbot project done by a few 
University of Adelaide students. This adaptation uses the 
Arduino MEGA platform (instead of the Lego Mindstorms NXT brick),
a motor shield from Adafruit,NXT motors/encoders, Lego Mindstorms structure pieces, a battery detecting circuit, two battery packs
(each with 4 AA batteries), and the IMU sensor from Adafruit. The other components are similar to the UA students' project.

The control algorithm portion of the code ( balance_and_control() ) originated from the control theory diagrams located in the
appendix of the UA students report. I used the "Embedded Coder", "Arduino Support from Simulink", and "Embedded Coder Target 
for Arduino" packages in order to make Arduino Mega specific code. There seemed to be missing dependencies, so I just replicated
the generated C code into the main source code file. There may be errors.

Link to pdf for UA students' report:
http://data.mecheng.adelaide.edu.au/robotics/projects/2009/Ballbot/Ballbot_Final_Report.pdf

(WORK IN PROGRESS)
