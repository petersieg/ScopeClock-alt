# ScopeClock-alt

Addons / Changes to:

http://dutchtronix.com/ScopeClockH3-1-Enhanced.htm

(The excellent work of Copyright © 2010 Johannes P.M. de Rie: jdr@dutchtronix.com - see license.txt)

---

ScopeClockSource*.zip:

Contains also firmware to invert X display, to allow correct display on some scopes with inverted X.
See ScopeClock-X.*
Check ClkRender-X.s

---

Very small pcb changes (allow to solder BNC connector stands at 1,2,3,4): Oclock2008-H31-PS.zip

Has been verified working on 2021-04-27.

![pcb_changes](https://github.com/petersieg/ScopeClock-alt/blob/main/pcb_changes.jpeg)

---

dt-ardu.ino: combines philo, reverse and mmind in one arduino sketch. Uses ps2 kbd for input and serial for output to dutchtronix.

dt-ardu-ir.ino: combines philo, reverse and mmind in one arduino sketch. Uses ir receiver for input and serial for output to dutchtronix.

Directory B&O IR: Some files to utilize a Beo4 IR remote with this. Based on excellent adafruit IR Raw lib and code!

Hardware: dutchtronix pcb plus arduino uno with ps2 female connector for kbd:

![dt-ardu-hw](https://github.com/petersieg/ScopeClock-alt/blob/main/dt-ardu-hw.jpeg)

Main menue:

![dt-ardu-menue](https://github.com/petersieg/ScopeClock-alt/blob/main/menue.jpeg)

Connect 4:

![c4](https://github.com/petersieg/ScopeClock-alt/blob/main/c4.jpeg)

---

sertest: send msg and vector to display in TERM mode at 19200 baud (default).

serphilo: send philosophical saying at 115200 baud

loopphilo: bash schript to repeadtedly send such msgs

![serphilo](https://github.com/petersieg/ScopeClock-alt/blob/main/serphilo.jpeg)

---

reverse: reverse the numbers to yield 1 2 3 4 5 6 7 8 9

![reverse](https://github.com/petersieg/ScopeClock-alt/blob/main/reverse.jpeg)

---

mmind: mastermind. Guess 4 digit number. No doubles. # = right digit & right place. + = right digit but wrong place

![mmind](https://github.com/petersieg/ScopeClock-alt/blob/main/mmind.jpeg)

---

VectorGen.zip: Source, Project and exe compiled under and for WinXP with Pelles-C 8

VectorGen-Lin.zip: Source, Project and program compiled under and for Linux Mint 20.1 with gcc

(Use: a,s,w,' ',x)
  
