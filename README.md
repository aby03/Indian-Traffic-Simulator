# Indian-Traffic-Simulator
Discrete Traffic Simulator tailored according to Indian roads. The traffic in India has really different properties, owing to its large population, than other countries. Vehicles are less restricted by rules and change lanes & overtake very often. Owing to lesser space, Indian traffic has the property  to fit perfectly into spaces to fill the roads, unlike in foreign countries where there are plenty of gaps between each vehicle. Cars also try to go at their maximum speed and occasionally break rules. We have tried to reciprocate the same in our simulation. 

## Description

Description of each file in `/src`:
- `gl_sim.cpp` - Takes in user input from `/config/config.ini` files, creates the desired road, vehicle and signal properties. Then, it run the simulation using openGL. 
- `simulator.cpp` - Contains all the required classes - road, signal and vehicle class with their respective `run()` functions which when called, runs the object for one timestep.

## Getting Started

### Prerequisites

- Standard C++ libraries (g++)
- freeGLUT (*Note:* Used for simulation image rendering)
  ```
  $ sudo apt-get update
  $ sudo apt-get install build-essential
  $ sudo apt-get make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev
  $ sudo apt-get install freeglut3 freeglut3-dev libglew-dev
  //Last line is important for download. However, if some problem is encountered, the 3rd command will usually resolve it.
  ```
  
### How to run

- After cloning/downloading the repo, in the main folder, use `make` to compile all the files.
- Inside `/config/config.ini`, create the necessary road, signal and vehicle properties for simulation. More details about the `config.ini` file is given below
- Run the simulation using `./bin/gl_sim`

### Configuration file

The configuration file is designed as follows:-
- It has headers for each section which are enclosed in square brackets (*like [Road]*).
- Every section header is followed by key, value pairs (in different lines) which denote the property of the respective header under which the pair is present.
- The config file can also handle comments which start by the character `#`. Any word or line after this comment symbol will not be read.
- These are the following headers and properties that the `config.ini` file can handle for now. (*Note:* It is case-sensitive)
  1) Road: Road_ID, Road_Length, Road_Width
  2) Signal: Road_Position
  3) Default: Default_MaxSpeed, Default_Acceleration
  4) Vehicles: Vehicle_Type, Vehicle_Length, Vehicle_Width, Vehicle_MaxSpeed, Vehicle_Acceleration, Vehicle_Bike_Feature (All the properties should be under one Vehicle_Type only)
  5) Simulation: 
    - Pass *number of passes that will be run*
    - Signal RED/GREEN
    - *Vehicle_Type* *Color* (OPTIONAL) *X Coord Y Coord* 
    - END
- The properties in *italics* need to be replaced by their respective values. The properties under the simulation header, which should be the last header, are **NOT** key, value pairs.

## Working

To simulate Indian traffic, we have a `run()` function for the road which contains all the cars. This runs all the cars present on the road (as stored in a vector `vehicles_list`). It then runs each of these vehicles by calling the vehicles `run()` function. While runnning every car, the car checks various properties in front of it like stopping distance and takes necessary steps to move at the maximum speed. It is assumed that vehicle uses its full acceleration and deceleration while moving.

Spawning of cars takes place at random if the spawn coordinates are not given. If there is no space for vehicle to spawn, it does not spawn.

## Authors

* **Kaustubh Prakash** - 2016MT10647
* **Abhay Saxena** - 2016MT60648

