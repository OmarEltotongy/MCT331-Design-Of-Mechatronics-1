#ifndef CONTROL_H
#define CONTROL_H

#define TASK1_STACK_SIZE      100
#define TASK2_STACK_SIZE      100
#define TASK3_STACK_SIZE      100
#define TASK1_PRIORITY        2
#define TASK2_PRIORITY        2
#define TASK3_PRIORITY        1

typedef enum currentStatus {
  HOMING = 1,
  FEEDING,
  METAL,
  NON_METAL,
  STORING,
  FINISHED
} currentStatus;

#endif