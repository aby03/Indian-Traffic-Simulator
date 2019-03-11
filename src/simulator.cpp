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

class Signal{
public:
	Signal(){
		time = 0;
		change_time = -1;
		status = 'r';
	}
	int id;
	int time;						// Signal Timer
	int change_time;		// Time after which signal changes
	int pos;
	char status;			// RED, GREEN

	void run(){
		if (change_time != -1){
			time = (time + 1) % change_time;
			if (time == 0){
				if (status == 'r'){
					status = 'g';
				}else{
					status = 'r';
				}
			}
		}		
	}
};

class Vehicle{
public:
	// Fix Variables for an object
	int id;
	string color;
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
	Vehicle(int i, string col, int l, int w, int speed, int acc){
		id = i;
		color = col;
		size.x = l;
		size.y = w;
		int max_speed = speed;
		int max_acc = acc;
		c_speed.x=0;
		c_speed.y=0;
	}

	void run(vector<Vehicle> veh_list, vector<Signal> signal_list){
		// Modify Dynamic variables
		// Get Stopping Distance
		// cout << "Vehicle: " << id << endl;
		stopping_dis = 0;
		int tmp = c_speed.x - max_acc;
		while (tmp > 0){
			stopping_dis += tmp;
			tmp = tmp - max_acc;
		}
		// Check for signal and get target_speed_signal
		int sig_index = get_ahead_signal(signal_list);int target_speed_signal = max_speed;
		if (sig_index != -1){
			if (signal_list[sig_index].pos <= location.x + stopping_dis + max_speed && signal_list[sig_index].status == 'r'){
				if (signal_list[sig_index].pos - location.x > 1){
					target_speed_signal = 1;
					cout << "Found Signal Speeding Down" << endl;
				}else{
					target_speed_signal = 0;
					cout << "Found Signal Stopping" << endl;
				}
			}
		}

		// Check for ahead car and get target_speed_car
		int ahead_car_index = get_ahead_car(veh_list);
		int target_speed_car = max_speed;
		if (ahead_car_index != -1){
			Vehicle ahead_car = veh_list[ahead_car_index];
			int ahead_car_back = ahead_car.location.x - ahead_car.size.x;
			if (ahead_car_back < location.x + stopping_dis){
				// Collision Inbound
				target_speed_car = 0;
				if (ahead_car_back < location.x){
					cout << "Colliding with: " << ahead_car.id << endl;
				}else{
					cout << "Collision Inbound with: " << ahead_car.id << endl;
				}
			}else if (ahead_car_back >= location.x + stopping_dis && ahead_car_back <= location.x + stopping_dis + max_speed + 1){
				// Match Speed and decrease distance
				if (ahead_car_back - location.x > 2){
					target_speed_car = ahead_car.c_speed.x;
					cout << "Closing gap with ahead car" << endl;
				}else{
					target_speed_car = ahead_car.c_speed.x;
					cout << "Matching speed with ahead car" << endl;
				}
				target_speed_car = min(max_speed, target_speed_car);
			}else{
				// Accelerate to max speed
				cout << "Accelerating to max speed. NOT POSSIBLE CASE" << endl;
			}
		}
		
		if (sig_index == -1 && ahead_car_index == -1){
			// Accelerate to max speed
			goto_speed(max_speed);
		}else if (sig_index != -1 && ahead_car_index == -1){
			// Only Signal Ahead
			int target_speed = target_speed_signal;
			goto_speed(target_speed);
		}else if (sig_index == -1 && ahead_car_index != -1){
			// Only Car Ahead
			int target_speed = target_speed_car;
			goto_speed(target_speed);
		}else if (sig_index != -1 && ahead_car_index != -1){
			// Both Car and Signal Ahead
			int target_speed = min(target_speed_signal, target_speed_car);
			goto_speed(target_speed);
		}
		// Move according to modified speed
		location = location + c_speed;
	}

	int get_ahead_signal(vector<Signal> signal_list){
		int sig=-1;
		int dis=2*max_speed*max_speed;
		for (int i=0; i<signal_list.size(); i++){
			if (signal_list[i].pos > location.x && signal_list[i].pos - location.x <= dis){
				sig = i;
				dis = signal_list[i].pos - location.x;
			}
		}
		return sig;
	}

	int get_ahead_car(vector<Vehicle> veh_list){

		int forw_car = -1;
		int min = 2*max_speed * max_speed / max_acc;	
		for (int i=0; i<veh_list.size(); i++){
			int dis_bw_cars = veh_list[i].location.x - veh_list[i].size.x - location.x;
			if ((location.y - size.y < veh_list[i].location.y && veh_list[i].location.y <= location.y) || (location.y - size.y <= (veh_list[i].location.y-veh_list[i].size.y) && veh_list[i].location.y-veh_list[i].size.y < location.y))
			{
				if (dis_bw_cars >= 0 && dis_bw_cars < min){
					min = dis_bw_cars;
					forw_car = i;
				}
			}
		}
		return forw_car;
	}

	void goto_speed(int target){
		// cout << "Target:" << target;
		if (target > c_speed.x){
			c_speed.x = c_speed.x + max_acc;
			if (c_speed.x > max_speed){
				c_speed.x = max_speed;
			}
			if (c_speed.x > target){
				c_speed.x = target;
			}
		}else if (target < c_speed.x){
			c_speed.x = c_speed.x - max_acc;
			if (c_speed.x < -1*max_speed){
				c_speed.x = max_speed;
			}
			if (c_speed.x < target){
				c_speed.x = target;
			}
		}
		// cout << " Set: " << c_speed.x << endl;
	}

	void print(){
		cout << "Vehicle: " << type << endl;
		cout << "ID: " << id << endl;
		cout << "Size: " << size.x << "," << size.y << endl;
		cout << "Location: " << location.x << "," << location.y << endl;
		cout << "Current speed: " << c_speed.x << "," << c_speed.y << endl;
		cout << "----------------------------" << endl;
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
	Road(){
		Road(0,DEFAULT_WIDTH,DEFAULT_LENGTH);
	}
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

	void setWidth(int w){
		width = w;
				map.resize(width);
		for (int i=0; i<width; i++){
			map[i].resize(length);
			for (int j=0; j<length; j++){
				map[i][j] = ' ';
			}
		}
	}

	void setLength(int l){
		length = l;
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
		// modify signals
		// for (int i=0; i<traf_signal_list.size(); i++){
		// 	traf_signal_list[i].run();
		// }
		// modify vehicles/road
		for (int i=0; i<vehicles_list.size(); i++){
			vehicles_list[i].run(vehicles_list, traf_signal_list);
		}

		for (int i=0; i<vehicles_list.size(); i++){
			if (vehicles_list[i].location.x - vehicles_list[i].size.x + 2 > length){
				vehicles_list.erase(vehicles_list.begin()+i);
				i--;
			}
		}
		update_map();
		// print_cars();
	}

	void spawn_vehicle(Vehicle veh){
		srand (time(0));
		veh.location.x = -1;
		veh.location.y = -1;
		while (veh.location.y == -1 || occupied(veh.location.y)){
			veh.location.y = rand()%(width-veh.size.y + 1) + veh.size.y-1;
		}
		vehicles_list.push_back(veh);
		// print_cars();
	}

	bool occupied(int pos){
		for (int i=0; i<vehicles_list.size(); i++){
			Vehicle ve = vehicles_list[i];
			if (ve.location.x - ve.size.x <= 0 && (ve.location.y >= pos && ve.location.y - ve.size.y < pos ) ){
				return true;
			} 
		}
		return false;
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

	void print_cars(){
		for (int i = 0; i < vehicles_list.size(); i++){
			vehicles_list[i].print();
		}
	}

};

// int main(){
// 	// Define Road
// 	Road road1(0, 4, 10);			// id, width, length
// 	// Add Signal to road
// 	Signal traf1;
// 	traf1.pos = 5;
// 	road1.spawn_signal(traf1);
// 	// Add Car
// 	Vehicle car1;
// 	car1.size.x = 2;
// 	car1.size.y = 2;
// 	car1.location.x = -1;
// 	car1.location.y = 1;
// 	car1.type = 'c';
// 	road1.spawn_vehicle(car1);
// 	// Update Map
// 	road1.update_map();
// 	road1.display();

// 	// Run Simulation
// 	for (int i=0; i<8; i++){
// 		road1.run();
// 		road1.update_map();
// 		road1.display();
// 	}
// }