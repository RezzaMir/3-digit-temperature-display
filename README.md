# 3-Digit Temperature Display
Purpose:  The purpose of this project is to use the Arduino as a CPU for a temperature sensor with a 3-digit display in C°.
1) A 3 digit seven segment display will be used
2) Shift register will be used
3) We will use a temp sensor which goes from -40 to 125°C, the same is in TinkerCAD
4) We will add 13 transistors and 3 displays to control the digits of the display to the circuit breadboard

A flow chart is given to help you realize the way it must flow but this is just an eagle’s eye view.  To get all digits to appear on at the same time we are multiplexing them very fast and utilizing the optical persistence of our eyes to make it ‘look’ like they are all on at the same time when they are going on and off.  The flow chart that I am giving you is a starter to do to make that happen.  If you notice, there is a delay for how long the display is on.  We are starting at 5 ms for that but we will also experiment with that value to see its effect.  We want to make the display of the temperature as clear and as stable as possible and that will involve the stability of your readings as well.

![Picture4](https://user-images.githubusercontent.com/102126445/162957471-09ee89ca-55de-4ff5-a1de-9ac59fb71314.png)

All connections to the shift register are the same as before.

Add two new 7 segment displays to the layout and connect all the like segments together.
Each digit will now be switched on and off using the PNP transistors driven by the Arduino.  Only one Display is on at one time – they are multiplexed.
Our input will be a temp sensor.   Since it only goes up to 1.75V max we will set the Aref input to 2V.  Make sure that you put in the program that you are using the external reference with the instruction:    analogRefrence(EXTERNAL);  To calculate the voltage from the ADC remember that 1023 equals 2V (not 5V).    1.75V should equal 895.
The temp sensor operates like this.   Temp in C° = (Vout – 0.5)*100 (Remember to make this variable a FLOAT type or you will not get any decimals flowchart this is shown as CENTS).  
Note that the output enable is now controlled too to prevent ghosting.  This really turns the segments off.

# Software graphic and flow chart

This is a graphic of the timing for the loading of segments, and the timing of the transistors which must be coordinated in the code.  Note how only one digit is on at a time but all are off when the shift register is loaded to prevent ghosting which is when more than 2 numbers are trying to show at the same time with one of them much dimmer.  To avoid this, you have to turn all the digits off before loading the next digit.

![Picture5](https://user-images.githubusercontent.com/102126445/162957808-4dd2a1e9-5a97-496b-83c5-42a2ec2a2326.jpg)

The temperature is shown as the CENTS in the flow chart and the formula is also shown above.
The flow chart shows where the ADC is read and the values are converted.  Ignore the bit about a running average.

It is assumed that Digit 1, 2 and 3 values are stored as variables. The rest of the code is just loading turning-on and turning-off each of the three digits and then going to the top and starting all over again reading etc.  
Once you have a value for CENTS, it needs to be converted to 3 numbers for each digit.  Start by dividing it by 100 and using that value for Digit1.  Then execute a modulo instruction (Remainder= CENTS%100) to find the remainder and divide that by 10 to get Digit2.  Digit3 is then the remainder from digit2 found by using the modulo again (e.g., Digit3 = Remainder%10).
You will notice that there is a negative number if the temp goes low enough, and it also goes above 100 C°.  The 3 digits will be used to go above 100 but when the temperature goes negative the left digit must show a negative sign.

![Picture6](https://user-images.githubusercontent.com/102126445/162958005-441d8d77-048c-4bfe-b8d4-746a5cabac12.jpg)

# Troubleshooting:

Once you have written your program use the Serial.print and Serial.println instructions to help visualize your data.  In other words if you are wondering what the ADC value is, use the Serial.println(adc) to send that value to the serial monitor where you can determine if it is correct or not.  You can do this for other variables as well.  This is probably the most valuable tool for debugging Arduino programs.  Once you figure things out you may have to comment out the serial commands as they do tend to slow things down.

# Appendix

Functional Diagram

![Picture1](https://user-images.githubusercontent.com/102126445/162955051-914b9a16-030e-48aa-a163-f12ef898c75b.png)

7 Segment Displays

![Picture2](https://user-images.githubusercontent.com/102126445/162955338-d6486d01-654b-4b46-9c51-9442e8bcdd76.png)

Seven Segment Pinout

![Picture3](https://user-images.githubusercontent.com/102126445/162955775-5574f02a-6e2e-4218-9ac3-048631a2d78c.png)

# Circuit and Display 'OFF/ON'

Display is 'On' with 3 digits

![M 1](https://user-images.githubusercontent.com/102126445/162612708-85bd3461-f2f5-48e9-885d-58e562ad2547.jpg)

Display is 'Off'

![M 2](https://user-images.githubusercontent.com/102126445/162612710-f25053f4-9967-40ce-b285-a6b36adc2ebe.jpg)

