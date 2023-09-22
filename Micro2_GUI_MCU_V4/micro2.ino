#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
#include "control.h"
#include <semphr.h>
#include "ethernet.h"

/*******************************************************************************
 *                              Gloabal Variables                              *
 *******************************************************************************/
const int dstPort PROGMEM = 1234;

currentStatus Status = 0;
uint8_t numberOfProductStored = 0;

SemaphoreHandle_t semaphoreX;
uint8_t ethernetRec = 0;

static TaskHandle_t task1Handler;
static TaskHandle_t task2Handler;
static TaskHandle_t task3Handler;

LiquidCrystal_I2C lcd(0x27, 16, 2);  //set 0x27 for 16 char

/*******************************************************************************
 *                              Interface MCU                                  *
 *******************************************************************************/

static void udpRecFunc(uint16_t dest_port, uint8_t src_ip[IP_LEN], uint16_t src_port, const char *data, uint16_t len)
{
  IPAddress src(src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
  
  char recChar = (char)data[0];
  uint8_t prevStatusEqualCurStatus = 0;

  if('H' == recChar)
  {
    if(HOMING == Status)
    {
      prevStatusEqualCurStatus = 1;        
    }
    else
    {
      Status = HOMING;
    }    
  }
  else if('F' == recChar)
  {
    if(FEEDING == Status)
    {
      prevStatusEqualCurStatus = 1;      
    }
    else
    {
      Status = FEEDING;    
    }  
  }
  else if('M' == recChar)
  {
    if(METAL == Status)
    {
      prevStatusEqualCurStatus = 1;  
    }
    else
    {
      Status = METAL;      
    }   
  }
  else if('N' == recChar)
  {
    if(NON_METAL == Status)
    {
      prevStatusEqualCurStatus = 1;
    }
    else
    {
      Status = NON_METAL;      
    }
  }  
  else if('S' == recChar)
  {
    if(STORING == Status)
    {
      prevStatusEqualCurStatus = 1;      
    }
    else
    {
      Status = STORING;
      numberOfProductStored++;  
    }         
  }
  else if('Z' == recChar)
  {
    if(FINISHED == Status)
    {
      prevStatusEqualCurStatus = 1;      
    }
    else 
    {
      Status = FINISHED;
    }
  }

  if(!prevStatusEqualCurStatus)
  {
    ethernetRec = 1;
  }
  
} 

void setup() {
  // put your setup code here, to run once:

  semaphoreX = xSemaphoreCreateBinary();  

  /*  LCD intialization:   */
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);  
  lcd.printstr("Waiting for");
  lcd.setCursor(0, 1);
  lcd.printstr("Ethernet");
  
  /*************************************/

  /*    uart intialization:   */
  Serial.begin(9600);

  /*************************************/
  if(ETHERNET_init())
  {
    lcd.clear();
    lcd.printstr("Ether: Ready");
    lcd.setCursor(0, 1);
    lcd.printstr("Loading...");
  }
  else
  {
    lcd.clear();
    lcd.printstr("Ethernet ERROR");   
  }
  ether.udpServerListenOnPort(&udpRecFunc, dstPort);  
    
  /*    Rtos Tasks:   */
  xTaskCreate(RTOS_TASK1_GUI_SENDER, "GUI Sender", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2Handler);
  xTaskCreate(RTOS_TASK2_ETHERNET_RECEIVER, "Ethernet Receiver", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &task3Handler);
  lcd.setCursor(0, 1);
  lcd.printstr("Tasks: Created");
}

void loop() {
}

static void RTOS_TASK1_GUI_SENDER(void* ptr) {
  while (1) {
    xSemaphoreTake(semaphoreX, portMAX_DELAY);
    lcd.clear();
    lcd.backlight();
    switch (Status) {
      lcd.clear();  //to not overwrite something
      case HOMING:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Homing");  //current status
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");    //product stored
        lcd.setCursor(4, 1);  //second row 4th col.
        lcd.print(numberOfProductStored);
        Serial.write('h');
        break;

      case FEEDING:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Feeding");  //current status
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");    //product stored
        lcd.setCursor(4, 1);  //second row 4th col.
        lcd.print(numberOfProductStored);
        Serial.write('f');
        break;

      case METAL:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Metal");  //16 char
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");
        lcd.setCursor(4, 1);
        lcd.print(numberOfProductStored);
        Serial.write('m');
        break;

      case NON_METAL:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Non Metal");  //16 char
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");
        lcd.setCursor(4, 1);
        lcd.print(numberOfProductStored);
        Serial.write('n');
        break;

      case STORING:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Storing");
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");
        lcd.setCursor(4, 1);
        lcd.print(numberOfProductStored);
        Serial.write('s');
        break;

    case FINISHED:
        lcd.setCursor(0, 0);
        lcd.printstr("CS: Finished");
        lcd.setCursor(0, 1);
        lcd.printstr("PS: ");
        lcd.setCursor(4, 1);
        lcd.print(numberOfProductStored);
        Serial.write('z');
        break;    
    }
  }
}

static void RTOS_TASK2_ETHERNET_RECEIVER(void* ptr) {
  while (1) {
    ETHERNET_waitForRec();
    if(ethernetRec)
    {
      xSemaphoreGive(semaphoreX);
      ethernetRec = 0;
    }
  }
}