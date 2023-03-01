# Circuit Workers' Congress

# Materials 
ESP32S2 Saola-1

DRV8833

2 x 6V DC Motor

---

its been two weeks since my last entry. I could not figure out the issues within my esp32s. Half the time, I couldn’t get it to bootload. Looked into VS and explored the IDF SDK. It was way too over my head. I don’t know enough C++ or Micropython. However, after getting an Adafruit ESP32S2 Saola-1, I got it working within the Arduino IDE, without the need of C++/Micropython. 

---

Finally got the motor to work after soldering it. The other issue I ran into was that the library I was using did not have anything to address the DRV8833’s nSLEEP pin. Which has to be on in order for the driver to be on. Once I set a pin for high logic to the nsleep pin, behold, a working robot. At least the prototype. Now I want to get both motors running and migrate to ESP

---

Had a lot of issues trying to interface the Arduino and the TT motors. I think maybe it’s the fact that I haven’t soldered the header pins to the driver breakout board. I’ll solder them before trying again. I’m prototyping with an Arduino to figure the motors out before I attempt to make the tiny changes required for the ESP32. I believe I am on a good timeline for NEXT. I won’t have to figure out form, and I’ve done due dilligence in building a realistic robot(s). I am on track to tinkering with the mechatronics underneath the “shell.” The mechatronics will be simple once I figure out what I’m missing in regards to the motor control. Then I can just spend most of my remaining time working on the “brain.” 

---

Reducing the number of nodes down to 5 total. One base, 4 nodes. Found a video via [**Techiesms](https://www.youtube.com/watch?v=gf39MLqPGkQ)** covering the Painless Mesh library. I need to procure three more ESP32 boards OR a communicating breakout board to give connectivity to my Arduino Uno. 

---

Getting rid of the Espressif MDF library. It’s not as well documented as PM. I’m also removing OpenCV for face recognition (find another solution for this, openCV data may be too complicated to broadcast over Painless Mesh). OpenCV is going to be a want, not a need. I’ll revisit it and see if I can implement when I’m mostly done. I want to investigate adding **SLAM** (simultaneous localization and mapping). MoSCoW exercise below.

************Words to remember:************ social proxemics, epistemology
