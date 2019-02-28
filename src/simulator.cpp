#include <vector>
#include <iostream>

using namespace std;

struct coords{
	int x;
	int y;
};

class Vehicle{
public:
	// Fix Variables for an object
	int id;
	char type;
	coords size;
	int max_speed;
	int max_acc;
	int max_side_speed;
	// Dynamic Variables for an object
	coords location;
	coords c_speed;
	coords c_acc;
	int stopping_dis;

	void move(){
		// Modify Dynamic variables
	}
};

class Signal{
public:
	Signal(){
		time = 0;
		change_time = 15;
		status = 'r';
	}
	int id;
	int time;						// Signal Timer
	int change_time;		// Time after which signal changes
	int pos;
	char status;			// RED, GREEN
};

class Road{
public:
	// Fix Variables for an object
	int id;																	// Unique for each road
	int length;															// Length of road
	int width;															// width of road
	vector<Signal> traf_signal_list;											// Traffic Signal on Road
	int max_speed_road;											// Speed limit of road
	int VEHICLE_DEFAULT_MAX_SPEED;					// Default max speed of vehicle on road
	int VEHICLE_DEFAULT_MAX_ACCELERATION;		// Default max acc of vehicle on road

	// Dynamic Variables for an object
	int new_vehicle_id=0;
	vector<Vehicle> vehicles_list;
	vector<vector<char> > map;								// Array to display vehicles on road

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
		cout << endl;
	}

	void run(){
		// modify vehicles/road
		// modify signals
	}

	void spawn_vehicle(){}

	void spawn_signal(Signal sig){
		traf_signal_list.push_back(sig);
	}

	void update_map(){
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
	}

};



int main(){
	Road road1(0, 4, 10);
	Signal traf1;
	traf1.pos = 5;
	road1.spawn_signal(traf1);
	road1.update_map();
	road1.display();
	road1.traf_signal_list[0].status = 'g';
	road1.update_map();
	road1.display();
}