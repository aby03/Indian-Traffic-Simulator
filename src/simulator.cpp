#include <vector>
#include <iostream>

using namespace std;

struct coords{
	int x;
	int y;
};

coords operator +(coords a, coords b){
	coords res;
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return res;
}

coords operator -(coords a, coords b){
	coords res;
	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return res;
}

class Vehicle{
public:
	// Fix Variables for an object
	int id;
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

	Vehicle(){
		c_speed.x=0;
		c_speed.y=0;
		c_acc.x=1;
		c_acc.y=0;
		stopping_dis=0;
	}

	void run(){
		// Modify Dynamic variables
		// Set Location
		location = location + c_speed;
		// Set Speed
		if (c_speed.x < max_speed){
			c_speed.x = c_speed.x + c_acc.x;
		}
		if (c_speed.x > max_speed){
			c_speed.x = max_speed;
		}
		if (c_speed.y < max_side_speed){
			c_speed.y = c_speed.y + c_acc.y;
		}
		if (c_speed.y > max_side_speed){
			c_speed.y = max_side_speed;
		}
		// Decide new acceleration
		c_acc.x = max_acc;
	}
};

class Signal{
public:
	Signal(){
		time = 0;
		change_time = 2;
		status = 'r';
	}
	int id;
	int time;						// Signal Timer
	int change_time;		// Time after which signal changes
	int pos;
	char status;			// RED, GREEN

	void run(){
		time = (time + 1) % change_time;
		if (time == 0){
			if (status == 'r'){
				status = 'g';
			}else{
				status = 'r';
			}
		}
	}
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
	Road(int i, int w, int l){
		id = i;
		length = l;
		width = w;
		map.resize(width);
		for (int i=0; i<width; i++){
			map[i].resize(length);
			for (int j=0; j<length; j++){
				map[i][j] = ' ';
			}
		}
	}

	// Functions
	void display(){
		vector<char> border(length);
		for (int i=0; i<length; i++){
			border[i] = '-';
		}
		for (int i=0; i<traf_signal_list.size(); i++){
			border[traf_signal_list[i].pos] = 'T';
		}
		// Display
		for (int j=0; j<length; j++){
			cout << border[j];
		}
		cout << endl;
		for (int i=0; i<width; i++){
			for (int j=0; j<length; j++){
				cout << map[i][j];
			}
			cout << endl;
		}
		for (int j=0; j<length; j++){
			cout << border[j];
		}
		cout << "\t\t" << "Global Time = " << global_time << endl;
		cout << endl;
	}

	void run(){
		global_time++;
		// modify vehicles/road
		for (int i=0; i<vehicles_list.size(); i++){
			vehicles_list[i].run();
		}
		// modify signals
		for (int i=0; i<traf_signal_list.size(); i++){
			traf_signal_list[i].run();
		}
	}

	void spawn_vehicle(Vehicle veh){
		vehicles_list.push_back(veh);
	}

	void spawn_signal(Signal sig){
		traf_signal_list.push_back(sig);
	}

	void update_map(){
		for (int i=0; i<width; i++){
			for (int j=0; j<length; j++){
				map[i][j] = ' ';
			}
		}
		// Open - Close Traffic Signal
		for (int i=0; i<traf_signal_list.size(); i++){
			if (traf_signal_list[i].status == 'r'){
				for (int j=0; j<width; j++){
					if (map[j][traf_signal_list[i].pos] == ' '){
						map[j][traf_signal_list[i].pos] = '|';
					}
				}
			}else{
				for (int j=0; j<width; j++){
					if (map[j][traf_signal_list[i].pos] == '|'){
						map[j][traf_signal_list[i].pos] = ' ';
					}
				}
			}
		} // Open - Close Traffic Signal

		// Update Vehicles
		for (int i=0; i<vehicles_list.size(); i++){
			for (int j=0; j<vehicles_list[i].size.y; j++){
				for (int k=0; k<vehicles_list[i].size.x; k++){
					int y = vehicles_list[i].location.y - j;
					int x = vehicles_list[i].location.x - k;
					if (x >= 0 && x < length && y >=0 && y < length){
						map[y][x] = vehicles_list[i].type;
					}
				}
			}
		}
	}

};

int main(){
	// Define Road
	Road road1(0, 4, 10);			// id, width, length
	// Add Signal to road
	Signal traf1;
	traf1.pos = 5;
	road1.spawn_signal(traf1);
	// Add Car
	Vehicle car1;
	car1.size.x = 2;
	car1.size.y = 2;
	car1.location.x = -1;
	car1.location.y = 1;
	car1.type = 'c';
	road1.spawn_vehicle(car1);
	// Update Map
	road1.update_map();
	road1.display();

	// Run Simulation
	for (int i=0; i<8; i++){
		road1.run();
		road1.update_map();
		road1.display();
	}
}