# Self Winding Clock Company hourly time synchronization
Self Winding Clock Company hourly time synchronization using ESP8266 ESP-12E and a relay

The Self Winding Clock Company clocks received an hourly synchronization signal from the telegraph lines.  

This project will enable the clock to synchronize the time over Wi-Fi every hour from a server on the internet.

# Hardware parts (approximate pricing):
$6 2 D batteries and D battery holder - can last 18 months.  Connect to the 2 screw terminals on the left side of the clock movement - powers the winding every hour. 

$6 USB-A phone charger with USB-A to micro-USB wire for easy ESP8266 programming

$6 USB-A male to USB-A female extension cable

$3 CE009 DC-DC Buck Converter USB Power Module 5V to 3.3V Step-Down Regulator Module https://www.amazon.com/dp/B07PHX7L49

$6 ESP8266 NodeMCU CP2102 ESP-12E Development Board https://www.amazon.com/dp/B081CSJV2V

$3 3V Relay Power Switch Board, Icstation 1 Channel Optocoupler Module Opto Isolation High Level Trigger for IOT ESP8266 Development Board https://www.amazon.com/dp/B01M0E6SQM

Total cost: ~$30

# Hardware steps:
1. Wire 3v3 on ESP8266 board to VCC on the relay, GND on ESP8266 to GND on relay, and D1 on ESP8266 to IN on relay

2. Wire GND on buck converter to one of the 2 solenoid connectors on the Self Winding Clock, 3.3v on buck converter to COM on relay, and NO on relay to the other solenoid connector on the Self Winding Clock.  In my testing, the ESP8266 ESP-12E could not pass through the ~250ma of power needed to power the solenoid so that is why the power needs to be wired as noted above.

3. For programming:  connect computer-->micro USB cable-->ESP8266 board-->3.3v relay-->solenoid on the clock

4. Final setup: Connect wall outlet charger-->extension cable-->buck converter-->ESP8266 board-->3.3v relay-->solenoid on the clock
Warning - mains voltages are dangerous and potentially lethal, be careful.


# Software/firmware steps:
1. Download the Arduino IDE, the latest version.
2. Install the IDE
3. Set up your Arduino IDE as: Go to File->Preferences and copy the URL below to get the ESP board manager extensions: https://github.com/esp8266/Arduino/releases/download/3.0.2/package_esp8266com_index.json

go to this webpage:
https://github.com/esp8266/Arduino/releases/

and look at what the current version is and then replace the 3.0.2 part with the newest current version number.

Save that, and restart the Arduino IDE.

4. Go to Tools > Board > Board Manager> Type "esp8266" and download the Community esp8266 and install.

5. Set up your chip as: Tools -> Board -> NodeMCU 1.0 (ESP-12E Module) 
Tools -> Flash Size -> 4M (3M SPIFFS) 
Tools -> CPU Frequency -> 80 Mhz 
Tools -> Upload Speed -> 921600 
Tools-->Port--> (whatever it is)

6. Test the setup:  Go to FILE> EXAMPLES> ESP8266> BLINK, and flash this firmware, it will start blinking.

7.  To load a library for a project, click Tools - Manage Libraries - (or click the book icon on the left) - search for ntpclient by fabrice weinberg and click install - this one is needed for the self winding clock project.  Set the wifi user name and password in the code as well

8. Load the code shown on the other page into the Arduino IDE program.  Update the wifi details with your own details, and update the minute that you would like the synchronization lever to operate.  In my Self Winding Clock, the synchronization lever brings the clock to the 59 minute mark, not the exact top of the hour 00 minute mark, so the code says to operate the sync lever at the 59 minute mark of each hour.  You can also update the time offset from GMT in seconds (-14400 in my case).

9. After flashing the project's firmware, click serial monitor window in the arduino IDE to confirm the time is accurate.  It will display the updated time with one new line per second.
