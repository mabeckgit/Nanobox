# Hardware

## Parts-List

* 5 LEDs (5 mm) in the colors: White, Green, Yellow, Blue, and Red
* 1 common cathode RGB-LED (5 mm)
* 7 Pushbuttons
* 1 Potentiometer 10 kOhm
* 1 Piezo
* 5 Resistors (220 Ohm), 3 Resistors (10 kOhm), 1 Resistor (5 kOhm)
* 1 Proto-board 3x7 cm
* 3d-printed Nanobox
* 3d-printed Protoboard slot

## Comments
The resistors I used are adjusted to have comfortable light-levels in the LEDs. Your best resistor levels could be different. Once commited to a resistor value, remember, that you can also change the brightness of the LEDs through changing the duty-cycles in the PWM in Nanobox.h. I recommend picking rather small resistance in hardware and tune down the brightness over PWM, because once your hardware is fixed you cannot get any brighter anymore beyond 100% duty-cycles.