Welcome! If you've watched the video, you should *kind of* know what you're doing, but this guide will hopefully make things a lot clearer. It will also explain some inconsistencies betweent the video and the code and schematic you find here (go with the stuff here, I made it more recently so it's better :)


## Guide
![Schematic](/schematic.png)
**STEP 1: WIRING**<br>
Set up your wiring according to this schematic. You may notice the button is connected to D4 and *GND*, whereas in the video it was D4 and *5V*. This is intentional, and you *must* do it this way if you want to use the code without editing anything. (I switched it to this method because it's more reliable.)
<br><br>

**STEP 2: CODING**<br>
a) Download and install the Arduino IDE from [here](https://www.arduino.cc/en/software/).<br>
b) Download the code from [here](/FinalLightsaberCode.ino).<br>
c) Open it up in the Arduino IDE and connect your Arduino Nano to your computer.<br>
d) In the top left (of the IDE), there should be a dropdown where you can click 'Select other board and port'.<br>
e) In that popup, search 'Arduino Nano' on the left side and select your board on the right side (if you don't know which one is your board, unplug and plug it back in to make it disappear and appear)<br>
f) Left of that dropdown there should be an arrow (->), press that to upload to the board
<br><br>

**STEP 3: USING**
Your saber is now ready to go!!!!<br>
Single click to 'activate' or 'deactivate' the blade. (Note that even when the blade is off the Arduino will still use some power, so you have the kill switch to depower the saber completely when you're not using it).<br>
Double click to start color change mode (the saber will smoothly go through a bunch of colors. Single click to pick the current color (the board will save that so you can turn it off and on and it will remember the color).<br>
