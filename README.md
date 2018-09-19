# HC_05_PairingExample
Arduino IDE code for sending data between two HC-05 Bluetooth Modules using one Arduino

1: In order to pair two HC-05 modules together you must first make sure to set up one of the devices as a 'slave' and one as a 'master'

2: You must retrieve the device address of the 'slave' first and then setup the second device as the 'master' and link it to the 'slave'
   address that you just retrieved using AT commands

3: Now if done correctly the two devices should be linked and automatically connect to each other when powered on, make sure to pull EN pins low now to go into 'Data Tansfer' mode rather than 'AT Command Mode'
   
Note: If at any point you mess up or want to reset the device settings you can put the device into 'AT Command Mode' and send it
         the command "AT+ORGL" to go back to factory defaults. This might change the baud rate to something different than what it
         previously was so you may have to try a different rate if you experience issues communicating with it after the reset
