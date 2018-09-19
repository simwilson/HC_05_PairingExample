/* 
 Purpose: Sets up 1 BT (bluetooth) module as a 'Master' and 1 as a 'Slave' to send data between them
          Sends data / text from the Serial Monitor to the Master BT module which sends it via BT to the Slave BT module and is read back from the Slave BT module into the Serial Monitor
 - STEPS: 
   1: Upload sketch with adjustments to put 'Slave' module into AT Mode and retrieve module address from 'Slave' module
   2: Upload sketch again with different lines uncommented / commented to put the other BT module into AT mode to make it
      the 'Master' and link it to the 'Slave' module using retrieved address
   3: Upload sketch again with corresponding lines for Data Transfer mode between BT modules

 NOTE: Default Baud Rate for BT module Serial can be different, typically 9600 or 38400, so you may have to try multiple options
      - Adjust Serial Monitor settings to 'Both NL & CR' and Baud Rate to match setting below (9600)

  CONNECTIONS:
   - GND to GND
   - 5V to VCC
   - Pin 2 to 1st HC-05 TXD  ** No voltage divider resistor needed for this pin
   - Pin 3 to 1st HC-05 RXD  ** Important to use resistor voltage divider to reduce line voltage from Arduino (pin 3) to RX on HC-05 to 3.3V instead of 5V
   - Pin 4 to 1st HC-05 EN      (pin next to VCC)
   - Pin 5 to 2nd HC-05 TXD
   - Pin 6 to 2nd HC-05 RXD  ** Important to use resistor voltage divider to reduce line voltage from Arduino (pin 6) to RX on HC-05 to 3.3V instead of 5V
   - Pin 7 to 2nd HC-05 EN

/*----- Libraries -----*/
#include <SoftwareSerial.h>  /*  If using Arduino with multiple hardware Serial Interfaces (such as Arudino Mega), you can use regular Serial Library instead of SoftwareSerial
/*----- Pin Numbers -----*/
#define HC_05_TX_1ST   2
#define HC_05_RX_1ST   3
#define HC_05_EN_PIN_1ST   4
#define HC_05_TX_2ND   5
#define HC_05_RX_2ND   6
#define HC_05_EN_PIN_2ND   7


SoftwareSerial BT1(HC_05_TX_1ST, HC_05_RX_1ST); // Software Serial setup for RX / TX pins Bluetooth module 1
SoftwareSerial BT2(HC_05_TX_2ND, HC_05_RX_2ND); // Software Serial setup for RX / TX pins Bluetooth module 2


void setup() 

{
  pinMode(HC_05_EN_PIN_1ST, OUTPUT);  // Setting up pins on Arduino as output to pull HC-05 EN pin high to go into AT Command Mode for adjusting settings
  pinMode(HC_05_EN_PIN_2ND, OUTPUT);

  /* AT Commands to setup BT Module as 'Master' only needs to be done once, 
     after initial setup is complete then you no longer need to go into AT Command Mode so pull EN Pin LOW instead of HIGH
     BT module defaults to 'Slave' */
     
  //digitalWrite(HC_05_EN_PIN_1ST, HIGH);  // Put HC-05 into module 1 AT Mode, must uncomment this line to send AT commands below to convert BT module 1 to master
  //digitalWrite(HC_05_EN_PIN_2ND, HIGH);  // Put HC-05 module 2 into AT Mode 
  
  digitalWrite(HC_05_EN_PIN_1ST, LOW);  // Put HC-05 module 1 into Data Transfer Mode
  digitalWrite(HC_05_EN_PIN_2ND, LOW);  // Put HC-05 module 2 into Data Transfer Mode
  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud'"); // Just a Reminder
  
  BT1.begin(38400);  // HC-05 default UART Serial speed = 38400
  BT1.flush();
  delay(250); // small delay to setup connection
  BT2.begin(38400); // Repeat for 2nd Bluetooth module
  BT2.flush();
  delay(250);

  /* ----- To retrieve the address of the Slave module, make sure BT module 2 is in AT Mode ----- */
  /*     change any BT1 in 'loop' section of code to BT2 to get Serial feedback               */
 
  // BT2.println("AT+ADDR"); // request module address from BT module
  /* module address returned will look something like "98d3:51:fd8eb0"
     write this address down to be used in the following section
     IMPORTANT: replace colons : in module address with commas , when using using "AT+LINK" command below */
       
     
  /* ----- Here are the AT Commands to Set BT Module 1 as the Master ----- 
       change any BT2 in 'loop' section of code to BT1 to get Serial feedback   */
  
  /*BT1.println("AT+ROLE=1");  // Chnage Mode to 'Master'
  delay(250);
  BT1.println("AT+CMODE=1");   // Connect to only 1 specific BT address
  delay(250);  // short delay for sending data
  BT1.println("AT+LINK=98d3,51,fd8eb0"); // Linking 'Master' module to module at specified address
  //IMPORTANT: the values after the '=' is the address of the 'Slave' module (BT module 2)
  delay(250);
  */
  // end of AT Setup Commands 

  
  Serial.println("Ready to Transmit Data\n");
  

}  /*--- end setup --- */


void loop() 
{
  // READ from 2nd HC-05 (BT2) and WRITE to Arduino Serial Monitor
  if (BT2.available()){
    while(BT2.available()){
      Serial.write(BT2.read());
    }
  }
    

  // READ Arduino Serial Monitor and WRITE to 1st HC-05 (BT1)
  if (Serial.available()){
    while(Serial.available()){
       BT1.write(Serial.read());
    }
  }

}/*--- end main loop ---*/
