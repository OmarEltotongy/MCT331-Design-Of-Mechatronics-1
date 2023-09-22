#ifndef HARDWARE_PINS_H
#define HARDWARE_PINS_H

/*************** Limit Switch *****************/
#define ROBOT_Z_LIMIT_SWITCH_SIGNAL_PIN     22
#define ROBOT_Y_LIMIT_SWITCH_SIGNAL_PIN     25
#define ROBOT_X_LIMIT_SWITCH_SIGNAL_PIN     27
/**********************************************/


/************* Stepper Motor ******************/
#define ROBOT_Z_STEPPER_DIRECTION_PIN       7
#define ROBOT_Y_STEPPER_DIRECTION_PIN       6
#define ROBOT_X_STEPPER_DIRECTION_PIN       5
#define CONVEYOR_STEPPER_DIRECTION_PIN      13

#define ROBOT_Z_STEPPER_STEP_PIN            4
#define ROBOT_Y_STEPPER_STEP_PIN            3
#define ROBOT_X_STEPPER_STEP_PIN            2
#define CONVEYOR_STEPPER_STEP_PIN           12
/*********************************************/

/*************** Infrared ********************/
#define CONVEYOR_INFRARED_SIGNAL_PIN        23
#define FEEDING_INFRARED_SIGNAL_PIN         28

#define CONVEYOR_INFRARED_NEGATIVE_LOGIC    false
#define FEEDING_INFRARED_NEGATIVE_LOGIC     true
/*********************************************/

/*************** Proximity *******************/
#define PROXIMITY_SIGNAL_PIN                26
#define PROXIMITY_METAL_ON_LOGIC_ONE        false  
/*********************************************/

/*************** Solenoid ********************/
#define SOLENOID_SIGNAL_PIN                 24
/*********************************************/

/************** Suction Cup ******************/
#define SUCTION_SIGNAL_PIN                  30
/*********************************************/

#endif