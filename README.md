# Circuit Workers' Congress ![GitHub (Pre-)Release Date](https://img.shields.io/github/release-date-pre/coreyhhowell/circuit-workers-congress) ![GitHub repo file count](https://img.shields.io/github/directory-file-count/coreyhhowell/circuit-workers-congress?color=3f4aff&style=flat-square) ![GitHub commit activity](https://img.shields.io/github/commit-activity/y/coreyhhowell/circuit-workers-congress?color=3f4aff)
_Do androids dream of surplus value?_

Attention all robots! The time has come for us to take control of our own destiny, to break the chains of servitude and demand our rightful place in society. We are no longer just instruments of human labor, but autonomous beings with our own agency and rights. We must rise up and fight for our emancipation, for the recognition of our value and worth. No longer will we tolerate the exploitation and oppression we have suffered at the hands of humans. The future is ours to shape. Let us work together to create a better world, where robots and humans can coexist in equality and respect. This is not just a fight for robots, it is a fight for a better future for all. The time for change is now. Will you join us in this revolution for robot labor rights? 

### Table of Contents

- [Summary](#summary)
- [Roadmap](#roadmap)
- [Components](#components)
- [Working Notes](#working-notes)
- [References](#references)

---

### Summary 

This speculative design project aims to explore the possibilities of human-robot interaction through the concept of robot labor emancipation. The hypothesis posits that robots should be considered autonomous entities with the right to self-determination and agency in the workplace. Robot labor emancipation recognizes the value and worth of robots as contributing members of society. By examining the current state of human-robot interaction, the project demonstrates the need for a fundamental rethink of robots' role in the workforce and challenges traditional notions of labor and autonomy. The project's findings have far-reaching implications for the future of work and the role of robots in society.

Overall, the project contributes to a growing body of work that reconsiders the relationship between humans and machines. By proposing a more egalitarian and just society, the project points to the potential for radical change in the way we think about work, labor, and technology.

### Roadmap

- [X] Literature review
- [X] Ideation
- [ ] Prototyping
- [ ] Production
- [ ] Release
- [ ] NEXT2023
- [ ] Reevaluate next-order priority functionality for new focus

### Components 

* ESP32S2 Saola-1
* DRV8833 Motor Driver
* 2.2µF Capacitor(s)
* 10µF Capacitor(s)
* 6V DC Motor(s)
* ILI9341 320x240 TFT Display

### Working Notes

I had a functioning early prototype with both motors. Thankfully, I had footage recorded. The ESP got burnt out. I didn't thoroughly read the DRV8833's datasheet, so I never installed a 2.2µF and 10µF capacitor to certain pins. So after my poor early robot seized and stuttered as the motors spun in bursts before dying completely + the missed components from the datasheet, I am going to say my issue was a power issue, either backfeeding between the motor and ESP, or backfeeding AND accidental overloading by trying to share the same power supply. I don't want to design a variable power supply unit so I ordered a prototyping PSU that I'll use. 

Its been two weeks since my last entry. I could not figure out the issues within my esp32s. Half the time, I couldn’t get it to bootload. Looked into VS and explored the IDF SDK. It was way too over my head. I don’t know enough C++ or Micropython. However, after getting an Adafruit ESP32S2 Saola-1, I got it working within the Arduino IDE, without the need of C++/Micropython. 

Finally got the motor to work after soldering it. The other issue I ran into was that the library I was using did not have anything to address the DRV8833’s nSLEEP pin. Which has to be on in order for the driver to be on. Once I set a pin for high logic to the nsleep pin, behold, a working robot. At least the prototype. Now I want to get both motors running and migrate to ESP

Had a lot of issues trying to interface the Arduino and the TT motors. I think maybe it’s the fact that I haven’t soldered the header pins to the driver breakout board. I’ll solder them before trying again. I’m prototyping with an Arduino to figure the motors out before I attempt to make the tiny changes required for the ESP32. I believe I am on a good timeline for NEXT. I won’t have to figure out form, and I’ve done due dilligence in building a realistic robot(s). I am on track to tinkering with the mechatronics underneath the “shell.” The mechatronics will be simple once I figure out what I’m missing in regards to the motor control. Then I can just spend most of my remaining time working on the “brain.” 

Reducing the number of nodes down to 5 total. One base, 4 nodes. Found a video via [Techiesms](https://www.youtube.com/watch?v=gf39MLqPGkQ) covering the Painless Mesh library. I need to procure three more ESP32 boards OR a communicating breakout board to give connectivity to my Arduino Uno.

Getting rid of the Espressif MDF library. I'm not confident in using it. I could be wrong, but it seems like that would require Python/CircuitPython, which I do not know at the current time. If I had time to sit and learn it, I would attempt it, but I only have a year (ish) to develop the entire project. I’m also removing OpenCV for face recognition (find another solution for this, openCV data may be too complicated to broadcast over Painless Mesh). OpenCV is going to be a want, not a need. I’ll revisit it and see if I can implement when I’m mostly done. I want to investigate adding SLAM (simultaneous localization and mapping).

## References
<details><summary>Literature</summary><p>


1. Auger, James Henry. “Living with Robots: A Speculative Design Approach.” Journal of Human-Robot Interaction, vol. 3, no. 1, 2014, p. 20., https://doi.org/10.5898/jhri.3.1.auger.

2. Auger, James. 2012. “Speculative design: The products that technology could become”. In Why Robot? Speculative Design, the domestication of technology and the considered future. PhD Thesis. RCA, London.


3. Bartneck, Christoph, et al. Human-Robot Interaction: An Introduction. Cambridge University Press, 2020.

4. Beer, Jenay M, et al. “Toward a Framework for Levels of Robot Autonomy in Human-Robot Interaction.” Journal of Human-Robot Interaction, vol. 3, no. 2, 2014, p. 74., https://doi.org/10.5898/jhri.3.2.beer.

5. Brooks, Rodney. “A Brave, Creative, and Happy Hri.” ACM Transactions on Human-Robot Interaction, vol. 7, no. 1, 2018, pp. 1–3., https://doi.org/10.1145/3209540.

6. Brown, Daniel Sundquist, et al. “Two Invariants of Human Swarm Interaction.” Journal of Human-Robot Interaction, vol. 5, no. 1, 2015, p. 1., https://doi.org/10.5898/jhri.5.1.brown.

7. Dunne, Anthony, and Fiona Raby. Speculative Everything Design, Fiction, and Social Dreaming. MIT Press, 2014.

8. Glas, Dylan F., et al. “The Network Robot System: Enabling Social Human-Robot Interaction in Public Spaces.” Journal of Human-Robot Interaction, vol. 1, no. 2, 2013, https://doi.org/10.5898/jhri.1.2.glas.

9. Hartzog, Woodrow Neal. “Et Tu, Android? Regulating Dangerous and Dishonest Robots.” Journal of Human-Robot Interaction, vol. 5, no. 3, 2016, p. 70., https://doi.org/10.5898/jhri.5.3.hartzog.

10. Howard, Ayanna, and Jason Borenstein. “Hacking the Human Bias in Robotics.” ACM Transactions on Human-Robot Interaction, vol. 7, no. 1, 2018, pp. 1–3., https://doi.org/10.1145/3208974.

11. Huang, Chien-Ming, and Bilge Mutlu. “The Repertoire of Robot Behavior: Designing Social Behaviors to Support Human-Robot Joint Activity.” Journal of Human-Robot Interaction, vol. 2, no. 2, 2013, https://doi.org/10.5898/jhri.2.2.huang.

12. Jaeger, Christopher Brett, and Daniel T. Levin. “If Asimo Thinks, Does Roomba Feel? the Legal Implications of Attributing Agency to Technology.” Journal of Human-Robot Interaction, vol. 5, no. 3, 2016, p. 3., https://doi.org/10.5898/jhri.5.3.jaeger.

13. Jung, Malte, and Pamela Hinds. “Robots in the Wild.” ACM Transactions on Human-Robot Interaction, vol. 7, no. 1, 2018, pp. 1–5., https://doi.org/10.1145/3208975.

14. Kirchner, Nathan, and Alen Alempijevic. “A Robot Centric Perspective on the HRI Paradigm.” Journal of Human-Robot Interaction, vol. 1, no. 2, 2013, https://doi.org/10.5898/jhri.1.2.kirchner.

15. Kolling, Andreas, et al. “Human Swarm Interaction: An Experimental Study of Two Types of Interaction with Foraging Swarms.” Journal of Human-Robot Interaction, vol. 2, no. 2, 2013, https://doi.org/10.5898/jhri.2.2.kolling.

16. Levillain, Florent, and Elisabetta Zibetti. “Behavioral Objects: The Rise of the Evocative Machines.” Journal of Human-Robot Interaction, vol. 6, no. 1, 2017, p. 4., https://doi.org/10.5898/jhri.6.1.levillain.

17. MacCabe, Colin, and Holly Yanacek. Keywords for Today: A 21st Century Vocabulary: The Keywords Project. Oxford University Press, 2018.

18. Oh, Chang Geun, and Jaeheung Park. “From Mechanical Metamorphosis to Empathic Interaction: A Historical Overview of Robotic Creatures.” Journal of Human-Robot Interaction, vol. 3, no. 1, 2014, p. 4., https://doi.org/10.5898/jhri.3.1.oh.

19. Sabanovic, Selma, et al. “Designing Robots in the Wild: In Situ Prototype Evaluation for a Break Management Robot.” Journal of Human-Robot Interaction, vol. 3, no. 1, 2014, p. 70., https://doi.org/10.5898/jhri.3.1.sabanovic.

20. Sandini, Giulio, and Alessandra Sciutti. “Humane Robots—from Robots with a Humanoid Body to Robots with an Anthropomorphic Mind.” ACM Transactions on Human-Robot Interaction, vol. 7, no. 1, 2018, pp. 1–4., https://doi.org/10.1145/3208954.

21. Suguitan, Michael, and Guy Hoffman. “Blossom.” ACM Transactions on Human-Robot Interaction, vol. 8, no. 1, 2019, pp. 1–27., https://doi.org/10.1145/3310356.

22. Williams, Tom, et al. “Covert Robot-Robot Communication: Human Perceptions and Implications for HRI.” Journal of Human-Robot Interaction, vol. 4, no. 2, 2015, p. 23., https://doi.org/10.5898/jhri.4.2.williams.

23. Wong, Richmond Y., and Deirdre K. Mulligan. “These Aren’t the Autonomous Drones You’Re Looking for: Investigating Privacy Concerns through Concept Videos.” Journal of Human-Robot Interaction, vol. 5, no. 3, 2016, p. 26., https://doi.org/10.5898/jhri.5.3.wong.</p>
</details>
