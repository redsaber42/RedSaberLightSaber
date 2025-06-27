Welcome! If you've watched the video, you should *kind of* know what you're doing, but this guide will hopefully make things a lot clearer. It will also explain some inconsistencies betweent the video and the code and schematic you find here (go with the stuff here, I made it more recently so it's better :)<br>
<br>

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

**STEP 3: USING**<br>
Your saber is now ready to go!!!!<br>
Single click to 'activate' or 'deactivate' the blade. (Note that even when the blade is off the Arduino will still use some power, so you have the kill switch to depower the saber completely when you're not using it).<br>
Double click to start color change mode (the saber will smoothly go through a bunch of colors. Single click to pick the current color (the board will save that so you can turn it off and on and it will remember the color).<br>
<br>

## Troubleshooting
*The Arduino isn't turning on!* <br>
If none of the lights on the Arduino board are turning on, it isn't getting any power.<br>
Try directly connecting the battery's positive wire to the Arduino's VIN and the battery's negative wire to the Arduino's GND.<br>
- If the Arduino lights up, the battery has at least some charge and you probably miswired the switch.<br>
- If the Arduino doesn't light up, your battery is probably dead. Try another one. Or try plugging the Arduino into your computer via the USB port and check if that lights it up. If it does you know the Arduino is good and the battery is bad. If it doesn't either your USB cable is bad or the Arduino is damaged.<br>

<br>

*The Arduino turns on, but the LEDs don't light up!* <br>
If the Arduino lights up, you know the power wiring is fine, but there are a couple of issues it could be. In the Arduino IDE, go to `File>Examples>FastLED>DemoReel100` and upload that. It should make a bunch of cool RGB effects on the first 64 LEDs. Whether this works will help narrow down the problem:<br>
&nbsp;&nbsp;&nbsp;&nbsp;- If the `DemoReel100` program *does* work, you know the LED wiring is fine and the power wiring is fine. Most likely the button wiring is wrong. (It's quite likely you did it correctly according to the video, but the way I said to do it there was not the best. So I changed the code to work with the wiring from the image above and you need to do it according to that for it to work.)
&nbsp;&nbsp;&nbsp;&nbsp;- If the `DemoReel100` program does *not* work, it's most likely the wiring between the Arduino and the LEDs, so double check that. Also keep in mind the direction of data. On the LED strips there should be arrows going from one end to the other, you want the Arduino to be connected the the side of the LEDs the arrows point *from* like this:<br>
arduino wires connect here (data flows in) -> -> -> -> (data flows out) connect to other strip here<br>

<br>

*Some other problem, or you tried the above steps and they didn't work!* <br>
You can join the Discord at [https://discord.gg/eXy58xz8kP](https://discord.gg/eXy58xz8kP). There is a channel called `#forum` where you can make a post or a channel called `#diy-lightsabers` where you can ask any smaller questions as well.
