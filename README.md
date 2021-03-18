# Nanobox

Nanobox is a hobby project with the goal of developing a stand-alone system, based on an Arduino Nano 33 IoT, that can host simple games. Think of it as a gaming-controller that contains its own games.

The hardware consists of low-cost parts, specifically the Arduino at its core, 7 push-buttons, 5 colored LEDs, 1 common cathode multicolor LED, a potentiometer, a piezo-element, and a couple of resistors. That's it. The hardware will be housed in a plastic casing the size of a small gaming-controller for comfort and to fixate all its components. 

The project is under development on both fronts: Coding the first games and building the hardware. Once I created a satisfactory casing, I will post images of the completed system, in the meantime you can look at this breadboard-version of it: 

<p align="center">
<img src="prototype.jpg" alt="prototype" width="350"/>
</p>

And here is the wiring diagram, if you want to hook up your own, **please note that Fritzing does not know the Nano 33 IoT**, yet, which is why I just use a Nano in the wiring diagram, the pinouts are mostly the same:

![Image of Wiring](wiring.png)

## Usage of the library
The library consists of two parts: games and examples. The examples double as hardware-tests, meaning as you go through them you will not only see the new functions accessible through the NanoboxClass, but if you load them one by one to your board you can use them to test that you hardware and wiring operates correctly. After building your own Nanobox I recommend going through the examples one by one to first understand what functionality the Nanobox-class provides and then testing with it the hardware of your box.

The following examples are available: 
### Switch Time
This example uses `switchTime` to communicate via the serial connection for how long a button is pressed or not pressed. Test the correct hook-up of Button2 with it, especially using the internal pull-up.
### Edge Detection
In many applications you want to recognize when a button is pressed and do something in immediate response, instead of doing something *while* the button is being pressed down. This example uses the `reactiveButton` function to detect rising or falling actions of your buton. Test the correct hook-up of Button1, the red LED, and the yellow LED with it.
### Multiple Blink
Triggering multiple LEDs at once results in cluttering your code with for-loops and what-not\*. The Nanobox introduces the overloaded `blinkLED` function. You can use it to repeatedly blink a single or multiple LEDs. To use several LEDs at once you need to define a vector as presented in the example. Notice how the off-durations are shorter than the on-durations and that the LEDs blink three times, all within a single line of code. Load this code to test that your LEDs are hooked up correctly. 

\*Unless you use port-manipulation. Which brings us to another point: `blinkLED` still uses a loop in the background, so it is not fully "at once". The purpose of this function is to keep your code compact not to manipulate ports synchronously. 
### RGB LED
This code uses `buttonPressed` as a convenient way to readout all button-signals from Button1 to Button6. You can either detect rising edges (default) or falling edges. The first button pressed will make the function respond with the pin-number of that button. The second part in this example shows the `RGB_Code`struct. Those consist of three integers betwen 0-255 addressing the red-, green-, and blue-channel. This is exactly the same as [how images are encoded for color-displays](https://en.wikipedia.org/wiki/RGB_color_space). The Nanobox comes with RGB_Codes for White and Black, the 3 primary colors and the 3 secondary colors. The example shows how you can define your own colors. Use this example to check the correct hook-up of all your buttons and your common cathode multicolor LED.

## Games
Each game has its own readme.md that you can find in the respective folder.
This is the list of games that this library has implemented so far, click the names to get their detailed description and game-instructions:
- [Zimon](https://github.com/mabeckgit/Nanobox/tree/main/examples/Games/Zimon): The classic memory game where you press buttons in a sequence presented. The sequence grows as you progress. I added a few extra-wrinkles into the game, though.
