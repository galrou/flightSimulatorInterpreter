# flightSimulator-part1
flightSimulator-part1 is an interpreter for a language that Dr. Eliahu Khalastchi has invented.
The project acts as both server (in order to send data to the flightgear simulator) and client (in order to receive data from the flightgear simulator).
It converts a text file into a running program (which fly an airplane), using the [Flightgear](https://www.flightgear.org/) simulator.

# Running the program
In order to run the project you need to clone it and use the following command:
```
 g++ -std=c++14 */*.cpp */*/*.cpp  *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
 ```
 
In addition, you need to provide a text file for the program to interpret, and a xml file of the flight simulator values.

# Github link
[Our Project] https://github.com/galrou/flightSimulator-part1
