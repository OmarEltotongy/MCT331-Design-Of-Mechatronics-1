#ifndef CONTROL_MCU_RTOS_H
#define CONTROL_MCU_RTOS_H

#include <Arduino.h>

#define TASK0_STACK_SIZE    200
#define TASK1_STACK_SIZE    300
#define TASK2_STACK_SIZE    200
#define TASK3_STACK_SIZE    300
#define TASK4_STACK_SIZE    600

#define TASK0_PRIORITY      3
#define TASK1_PRIORITY      2
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      1
#define TASK4_PRIORITY      3

#define DEBUG_TASK_1        true
#define DEBUG_TASK_2        true
#define DEBUG_TASK_3        true
#define DEBUG_TASK_4        true

#define ROBOT_Z_STEPS       1100
#define ROBOT_X_ZERO_BIAS   1800

#define HOMING_STR          "H"
#define FEEDING_STR         "F"
#define METAL_STR           "M"
#define NON_METAL_STR       "N"
#define STORED_STR          "S"

void RTOS_init(void);

#endif