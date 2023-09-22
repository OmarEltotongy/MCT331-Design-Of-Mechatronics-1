#include "control_mcu_rtos.h"
#include "hardware_pins.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "limit_switch.h"
#include "stepper.h"
#include "ir.h"
#include "solenoid.h"
#include "proximity.h"
#include "products.h"
#include "suction_cup.h"

#include "ethernet.h"

static TaskHandle_t task1Handler;
static TaskHandle_t task2Handler;
static TaskHandle_t task3Handler;
static TaskHandle_t task4Handler;

static SemaphoreHandle_t semaphore23Handler;
static SemaphoreHandle_t semaphoreHomingHandler;
static SemaphoreHandle_t semaphoreSolHandler;
static SemaphoreHandle_t semaphorePackHandler;

/*************** Limit Switch *****************/
static LimitSwitch robotZLimitSwitch(ROBOT_Z_LIMIT_SWITCH_SIGNAL_PIN);
static LimitSwitch robotYLimitSwitch(ROBOT_Y_LIMIT_SWITCH_SIGNAL_PIN);
static LimitSwitch robotXLimitSwitch(ROBOT_X_LIMIT_SWITCH_SIGNAL_PIN);
/**********************************************/

/************* Stepper Motor ******************/
static StepperMotor robotZStepper(ROBOT_Z_STEPPER_DIRECTION_PIN, ROBOT_Z_STEPPER_STEP_PIN);
static StepperMotor robotYStepper(ROBOT_Y_STEPPER_DIRECTION_PIN, ROBOT_Y_STEPPER_STEP_PIN);
static StepperMotor robotXStepper(ROBOT_X_STEPPER_DIRECTION_PIN, ROBOT_X_STEPPER_STEP_PIN);
static StepperMotor conveyorStepper(CONVEYOR_STEPPER_DIRECTION_PIN, CONVEYOR_STEPPER_STEP_PIN);
/*********************************************/

/*************** Infrared ********************/
static Infrared conveyorInfrared(CONVEYOR_INFRARED_SIGNAL_PIN, CONVEYOR_INFRARED_NEGATIVE_LOGIC);
static Infrared feedingInfrared(FEEDING_INFRARED_SIGNAL_PIN, FEEDING_INFRARED_NEGATIVE_LOGIC);
/*********************************************/

/*************** Proximity *******************/
static Proximity proximity(PROXIMITY_SIGNAL_PIN, PROXIMITY_METAL_ON_LOGIC_ONE);
/*********************************************/

/*************** Solenoid ********************/
static Solenoid solenoid(SOLENOID_SIGNAL_PIN);
/*********************************************/

/************** Suction Cup ******************/
static SuctionCup suctionCup(SUCTION_SIGNAL_PIN, false);
/*********************************************/

/**************** Products ******************/
static Products* products = NULL;
/*********************************************/

uint8_t solTaskSuspended = 0;

static void RTOS_TASK0_initializer(void* ptr)
{
  ETHERNET_init();
  
  robotZLimitSwitch.init();
  robotYLimitSwitch.init();
  robotXLimitSwitch.init();

  robotZStepper.init();
  robotYStepper.init();
  robotXStepper.init();
  conveyorStepper.init();

  conveyorInfrared.init();
  feedingInfrared.init();

  solenoid.init();

  proximity.init();

  suctionCup.init();

  products = Products::getInstance(8);      
  
  vTaskDelete(NULL);

  while(1)
  {

  }  
}

static void RTOS_TASK1_robotHoming(void* ptr)
{
#if DEBUG_TASK_1   
  while(1)
  {  
    ETHERNET_send(HOMING_STR);  
    while(robotZLimitSwitch.detect() == BTN_RELEASED){
      robotZStepper.step(1000, STEPPER_CW);
    }
    while(robotYLimitSwitch.detect() == BTN_RELEASED){
      robotYStepper.step(1000, STEPPER_CW);
    }
    while(robotXLimitSwitch.detect() == BTN_RELEASED){
      robotXStepper.step(1000, STEPPER_CW);
    }
    if(products->allProductsStored())
    {
      vTaskSuspendAll();
      while(1)
        ETHERNET_send("Z");
      
    }
    else
    {
      ETHERNET_send(FEEDING_STR);    
      xSemaphoreTake(semaphoreHomingHandler, portMAX_DELAY);
    }

  }
#else
  vTaskDelete(NULL); 
#endif
}

static void RTOS_TASK2_feeding(void* ptr)
{
#if DEBUG_TASK_2 
  while(1)
  {
    xSemaphoreTake(semaphore23Handler, portMAX_DELAY);    
    solenoid.sendPulse(SOLENOID_PULSE_DELAY);
    solTaskSuspended = 1;
    xSemaphoreTake(semaphoreSolHandler, portMAX_DELAY);
  }
#else
  vTaskDelete(NULL);
#endif
}

static void RTOS_TASK3_infraredDetect(void* ptr)
{
#if DEBUG_TASK_3
  while(1)
  {
    if(conveyorInfrared.detect() == IR_DETECTS_OBJECT)
    {
      xSemaphoreGive(semaphorePackHandler);
    }    
    else
    {
      // ETHERNET_send(FEEDING_STR);
      conveyorStepper.step(200, STEPPER_CW);
      if(feedingInfrared.detect() == IR_DETECTS_OBJECT)
      {
        if(!solTaskSuspended)
        {
          delay(2000);
          xSemaphoreGive(semaphore23Handler);
        }
      }
      else
      {
        
      }  
    }
  }
#else
  vTaskDelete(NULL);
#endif
}

static void RTOS_TASK4_robotPlaceProduct(void* ptr)
{
#if DEBUG_TASK_4
  uint8_t materialDetected;
  uint32_t stepsX;
  uint32_t stepsY;
  
  while(1)
  {
    xSemaphoreTake(semaphorePackHandler, 0xffffffff);
    robotXStepper.makeSteps(ROBOT_X_ZERO_BIAS, 1000, STEPPER_CCW);    
    robotZStepper.makeSteps(ROBOT_Z_STEPS, 1000, STEPPER_CCW);   

    materialDetected = proximity.detect();

    if(PROXIMITY_READS_METAL == materialDetected)
    {
      ETHERNET_send(METAL_STR);      
    }
    else
    {
      ETHERNET_send(NON_METAL_STR);
    }

    suctionCup.suck();
    stepsX = products->calculateProductPositionX(materialDetected);
    stepsY = products->calculateProductPositionY(materialDetected);
    
    robotZStepper.makeSteps(ROBOT_Z_STEPS, 1000, STEPPER_CW);
    xSemaphoreGive(semaphoreSolHandler);
    solTaskSuspended = 0;
    robotYStepper.makeSteps(stepsY, 1000, STEPPER_CCW);
    robotXStepper.makeSteps(stepsX, 1000, STEPPER_CCW);    
    
    robotZStepper.makeSteps(ROBOT_Z_STEPS, 1000, STEPPER_CCW);
    suctionCup.unSuck();
    ETHERNET_send(STORED_STR);
    products->ackProductStored(materialDetected);

    xSemaphoreGive(semaphoreHomingHandler);      
  }
#else
  vTaskDelete(NULL);
#endif  
}

void RTOS_init(void)
{
  xTaskCreate(
    RTOS_TASK0_initializer,     
    "Init hardware",
    TASK0_STACK_SIZE,
    NULL,
    TASK0_PRIORITY,
    NULL          
  );

  xTaskCreate(
    RTOS_TASK1_robotHoming,     
    "Robot Homing",
    TASK1_STACK_SIZE,
    NULL,
    TASK1_PRIORITY,
    &task1Handler          
  );

    xTaskCreate(
    RTOS_TASK2_feeding,     
    "Feeding",
    TASK2_STACK_SIZE,
    NULL,
    TASK2_PRIORITY,
    &task2Handler          
  );

    xTaskCreate(
    RTOS_TASK3_infraredDetect,     
    "Infrared detection and conveyor movement",
    TASK3_STACK_SIZE,
    NULL,
    TASK3_PRIORITY,
    &task3Handler          
  );

    xTaskCreate(
    RTOS_TASK4_robotPlaceProduct,     
    "Task for Robot to grab the product and place it in the correct position",
    TASK4_STACK_SIZE,
    NULL,
    TASK4_PRIORITY,
    &task4Handler          
  );
  
  semaphore23Handler = xSemaphoreCreateBinary();
  semaphoreHomingHandler = xSemaphoreCreateBinary();
  semaphoreSolHandler = xSemaphoreCreateBinary();
  semaphorePackHandler = xSemaphoreCreateBinary();
}
