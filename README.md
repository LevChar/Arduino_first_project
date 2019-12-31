# Arduino_first_project
My first project with Arduino board

## **Purpose:**

This is a toy program, Which simulates the following situation:

1. There is a parking with one way access and exit lane, which means that 2 cars cannot be found on this lane at the same time. 
Either a vehicle exits or enters.

2. The system I built is a system with 2 traffic lights, a traffic light for the incoming vehicles and a traffic light for the outgoing vehicles.

3. Each traffic light has a button, pressing the button will turn on the green light on this traffic light(if the traffic light was red).

4. There is also an external system (which in this example I simulate using the middle button) which determines the prioritization in the direction of movement. That is, the priority is in the morning for vehicles exiting the parking lot, so the default is that the traffic light in the exit direction is green, while at noon the priority is for vehicles returning to the parking, and therefore, by default, the green traffic light will be at the entrance.

5. The simulation of the switch from morning to noon, i.e. switching between priorities, is done by pressing the middle button, the yellow led indicates the priority - when it is on, the priority is for the incoming vehicles, while when switched off, the priority is for the outgoing vehicles.

## **To run the program:**
Upload the code to the Arduino board, using Arduino IDE, 
and enjoy the show! :)

## **Compatibility:**
Program was compiled and tested in Arduino uno environment.
