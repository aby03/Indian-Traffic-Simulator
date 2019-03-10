#include "simulator.cpp"
#include <iostream>


int main(){
	// Define Road
	Road road1(0, 6, 20);			// id, width, length
	// Add Signal to road
	Signal traf1;
	traf1.pos = 18;
	traf1.change_time = 8;
	road1.spawn_signal(traf1);
	// Add Car
	Vehicle car1;
	car1.size.x = 2;
	car1.size.y = 2;
	car1.id = "A";
	car1.location.x = -1;
	car1.location.y = 1;
	car1.max_speed = 1;
	car1.max_acc = 1;
	car1.type = 'c';
	road1.spawn_vehicle(car1);
	// Update Map
	road1.update_map();
	road1.display();
	// Run few Steps
	for (int i=0; i<10; i++){
		road1.run();
		road1.update_map();
		road1.display();
	}

	// Add 2nd Car
	Vehicle car2;
	car2.size.x = 2;
	car2.size.y = 2;
	car2.id = "B";
	car2.location.x = -1;
	car2.location.y = 1;
	car2.max_speed = 2;
	car2.max_acc = 1;
	car2.type = 'c';
	road1.spawn_vehicle(car2);
	// Update Map
	road1.run();
	road1.update_map();
	road1.display();

	// Run Simulation
	for (int i=0; i<15; i++){
		road1.run();
		road1.update_map();
		road1.display();
	}
}