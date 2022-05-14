# Arduino Game - Melodic Memory
This is the final individual project for ECE 387. My project is a simple arduino game called "Melodic Memory". I found it is also known as "Simon says" in US. 

And on this page, I will introduce how to play this game, explain how to rebuild this project with the circuit diagram. Also I will talk aboud the difficulties I encountered during doing the final project and the unfinished functions. 
## Introduction
This game is designed to test your memory. The basic gameplay is the LED lights will light up in sequence with the buzzer sounding. For example, the first round of blue light is on, the second round of blue light is turned on, then the yellow light is turned on, the third round of blue light, yellow light, red light is turned on in sequence. All you need to do is try to remember the order in which each light came on each turn, then press the corresponding button to replicate the melody. 
## Inspiration
The inspiration I chose to do this project came from an online game called World of Warcraft that I played recently. In the latest patch, when I go to the new map called Zereth Mortis for the first time. I started exploring the map, and while exploring the map I came across a hidden treasure quest "Symphonic Vault". Here is the details of this quest: "Treasure is initially not interactable - Interact with the nearby Broken Automa to hear a melody. You will need to replicate the melody from the Broken Automa with the nearby Broken Consoles to unlock the treasure". The Broken Automa will play a full melody, and there are four Broken Consoles scattered in the cave, and each Broken Consoles will only play a small part of this melody, You need to interact with the Broken Consoles in order to make them play the correct full melody. I spent some time memorizing the melody before I checked the guide, later I found this little game very interesting. 

And also our topic is "Kids Toy", so your toy should designed for kids or teenager, and the rules of the game should not be so complicated. So I came up with the idea of turning this game into an actual toy.

## Tools
| Tools | Number |
| :-----: | :------: |
| Arduino UNO | 1 |
| LCD Screen 16 x 2| 1 |
| Jumper wires | a lot |
| Push Buttons | 4 |
| LED Lights(Different Colors) | 4 |
| Buzzer | 1 |
| Breadboard | 1 |
| 220Ω Resistor | 5 |

You can easily find all the tools in Arduino Starter Kit from Amazon, the cheapest price is $39.99 and contains all the tools we need.

## Software
Before build this project, please check if you have installed following in your computer:

    Arduino IDE 1.8.19(Latest Version)
    Arduino library of LiquidCrystal.h

## Circuit Diagram
We learned LCD in lab assignment, so 100% make sure all of us know how connect LCD to Arduino UNO, also here is the connection pin mapping for LCD Display 16 x 2:

![image](https://user-images.githubusercontent.com/98714679/168403796-d13e0811-1db3-4440-8fe8-0861e69a9e0d.png)
1. VSS : Ground(0V)
2. VCC : Power Supply(+5V)
3. VEE : LCD Contrast Adjustment
4. RS : Instruction/Data Register Selection
5. RW : Read/Write Selection
6. E : Enable Signal
7. DB0 - DB7 : Data Input/Output Lines
8. LED+ : Supply Voltage For LED+(+5V)
9. LED- : Supply Voltage For LED-(0V)

| LCD PIN | UNO PIN|
| :---: | :---: |
| LCD_D4 | B,2(Arduino 10) |
| LCD_D5 | B,1(Arduino 9) |
| LCD_D6 | B,0(Arduino 8) |
| LCD_D7 | D,7(Arduino 7) |
| LCD_RS | B,4(Arduino 12) |
| LCD_EN | B,3(Arduino 11) |

Now the whole circuit:

![image](https://user-images.githubusercontent.com/98714679/168403345-052d96fe-9e5d-4a72-b87a-5ab5d0aeab89.png)

## Functions
You can select two game mode, mode 1 is "Rpeat mode"(Progressive mode). It will repeat previous melody in the last round and generate a new random tone in current round.

Mode 2 is "Random mode", each round the melody are totally random! You cannot pass your round by memorizing the sequence in the last round. 

You can press button 1 to select "Repeat mode" and button 2 to select "Random mode". And also button 3 can control the buzzer on/off, it will let you react without any audible prompts, just by observing the sequence of LED lights, this option is available for those who want to challenge a higher difficulty.

![image](https://user-images.githubusercontent.com/98714679/168404392-6e2bef13-2465-400a-9bcc-223a93442580.png)


## Reference
https://github.com/Narenthan009/SIMON-SAYS
