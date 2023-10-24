# UCR-CS120B-Final-Project


This was my final project that I created for my embedded systems class at the University of California, Riverside. The system uses an Arduino Uno that holds the code for the system and uses state machine logic for the logic flow of the program. 

## Controls
The project has four buttons for inputs, one to cycle through different colors, one to go into party mode, one to choose a random color, and one to reset the color back to white. 

## ST7789
The project also uses a ST7789 LCD display. Using a library provided by the screen's manufacturer, I called some built in methods that allowed me to draw graphics onto the screen to display certain texts and color. 

## EEPROM
An external EEPROM is used to store the state of the current color so that if power is lost in the system, the next power up on the system will remember what color the system was last set to before power loss.

[What I Wrote](https://github.com/ATranZone/UCR-CS120B-Final-Project/blob/main/rgbANDlcd.ino)

Video Demo: 

<a href="https://youtu.be/eSMH8A6l3ds" target="_blank">
 <img src="demo.png" width=400px/>
</a>
