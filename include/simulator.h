#ifndef SIMULATOR_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SIMULATOR_H

#include <vector>
#include <iostream>
#include <stdlib.h>     /* rand */

using namespace std;

#define DEFAULT_LENGTH 10
#define DEFAULT_WIDTH 4

struct coords{
	int x;
	int y;
};

coords operator +(coords a, coords b);

coords operator -(coords a, coords b);

class Vehicle{
public:
	// Fix Variables for an object
	string id;
	char type;
	coords size;
	int max_speed=1;
	int max_acc=1;
	int max_side_speed=0;
	// Dynamic Variables for an object
	coords location;
	coords c_speed;
	coords c_acc;
	int stopping_dis;

	Vehicle();
	Vehicle(string color, int l, int w, int speed, int acc);
	
	void run();
	void print();
};

class Signal{
public:
	Signal();
	int id;
	int time;						// Signal Timer
	int change_time;		// Time after which signal changes
	int pos;
	char status;			// RED, GREEN

	void run();
};

class Road{
public:
	// Fix Variables for an object
	int id;										// Unique for each road
	int length;									// Length of road
	int width;									// width of road
	vector<Signal> traf_signal_list;			// Traffic Signal on Road
	int max_speed_road;							// Speed limit of road
	int VEHICLE_DEFAULT_MAX_SPEED;				// Default max speed of vehicle on road
	int VEHICLE_DEFAULT_MAX_ACCELERATION;		// Default max acc of vehicle on road

	// Dynamic Variables for an object
	int global_time=0;
	int new_vehicle_id=0;
	vector<Vehicle> vehicles_list;
	vector<vector<char> > map;					// Array to display vehicles on road

	// Constructor
	Road();
	Road(int i, int w, int l);
	void setWidth(int w);
	void setLength(int l);
	// Functions
	void display();
	void run();
	void spawn_vehicle(Vehicle veh);
	void spawn_signal(Signal sig);
	void update_map();
	void print_cars();
};

#endif
