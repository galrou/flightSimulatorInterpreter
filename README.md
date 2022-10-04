# flightSimulatorInterpreter
flightSimulatorInterpreter is an interpreter for a language that Dr. Eliahu Khalastchi has invented.
The project acts as both server (in order to send data to the flightgear simulator) and client (in order to receive data from the flightgear simulator).
It converts a text file into a running program (which flies an airplane), using the [Flightgear](https://www.flightgear.org/) simulator.

# Running the program
In order to run the project you need to clone it and use the following command:
```
 g++ -std=c++14 */*.cpp */*/*.cpp  *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
 ```
 
In addition, you need to provide a text file for the program to interpret, and a xml file of the flight simulator values.


## Usage

- The program takes as CommandLine Argument the txt file you wish to Interpret, the txt file should be in the same folder you run the program from,
for Example if you wish to run The file fly.txt the following command should execute:
"./a.out fly.txt". and the fly.txt should be in the same folder a.out is.

- The program should show it waits for connection.

- Afterwards run the FlightGear Simulator or Alternatively Run the script Simulating it, the program should print it Accepted connection for both the server thread and the client thread, and will start interpreting the file supplied to it.

- The Following Commands Are Allowed:

- openDataServer(port) - open server using sockets for the simulator to send data 

- connectControlClient(ip, port) - open client socket and connecting to the simulator for changing controls of the plane.

- var - creating a new var , 
can be simluator depending/changing var - will be declered by (->) for changing and (<-) for depending or non for exapmple: 
(var h0 = 3)
 (var breaks -> sim(** breaks path**) will change the simualtor breaks.)
 (var alt <- sim(** altitude path**) will be changed by the data supplied by the simulator.)

- Print(data) - print the paramater supplied to it can be string or expession.
   
- Sleep(time) - stops the main thread for the specified time, can be string or expession.
   
- while(condition) { commands } - while loop.
   
- if(conddition) { command } - will execute the commands only if the condition is true.
    
- also the use of functions is Allowed but must be Declared Before the call to the function.

# Github link
[Our Project] https://github.com/galrou/flightSimulator-part1


