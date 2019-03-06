#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include "simulator.cpp"

using namespace std;

Road road(0,4,10);
Signal traf1;

string removeComment(string& str){
	if (str.find("#") != string::npos){
		return str.substr(0,str.find("#"));
	}
	else{
		return str;
	}
	return "";
}

string trim(string& str){
	str.erase(0, str.find_first_not_of(" \t\n"));
	str.erase(str.find_last_not_of(" \t\n") + 1);
	return str;
}

string retKey(string& str){
	if (str.find("=") != string::npos){
		string line = str.substr(0,str.find("="));
		return trim(line);
	}
	return "";
}

string retVal(string& str){
	if (str.find("=") != string::npos){
		string line = str.substr(str.find("=")+1);
		return trim(line);
	}
	return "";
}

int main(){
	string line;
	ifstream myfile ("./config/config.ini");
	string curr = ""; //Current header operation
	int def_speed=1;
	int def_acc=1;
	Vehicle veh(def_speed,def_acc);
	int flag = 0;
	if (myfile.is_open()){

		while ( getline(myfile, line) ){
			line = removeComment(line);
			line = trim(line);

			if (!line.empty()){
				if (line.front() == '[' && line.back() == ']'){
					if (curr == "[Signal]"){
						road.spawn_signal(traf1);
					}

					curr = line;
				}
				else{

					string key = retKey(line);
					string sval = retVal(line);

					if (curr == "[Road]"){
						//Storing road parameters
						int val = stoi(sval);
						if (key == "Road_Id"){
							road.id = val;
						}
						else if (key == "Road_Length"){
							road.setLength(val);
						}
						else if (key == "Road_Width"){
							road.setWidth(val);
						}
						
					}
					else if (curr == "[Signal]"){
						// Storing default parameters
						int val = stoi(sval);
						if (key == "Road_Signal"){
							traf1.change_time = val;
						}
						else if (key == "Road_Position"){
							traf1.pos = val;
						}
					}
					else if (curr == "[Default]"){
						// Storing default parameters
						int val = stoi(sval);
						if (key == "Default_MaxSpeed"){
							def_speed = val;
						}
						else if (key == "Default_Acceleration"){
							def_acc = val;
						}
					}
					else if (curr == "[Vehicles]"){
						if (key == "Vehicle_Type"){
							if (flag == 1){
								road.spawn_vehicle(veh);
								veh.setDefault(def_speed,def_acc);
							}
							veh.type = sval.front();
							flag = 1;
						}
						else if (key == "Vehicle_Length"){
							veh.size.x = stoi(sval);
						}
						else if (key == "Vehicle_Width"){
							veh.size.y = stoi(sval);
						}
						else if (key == "Vehicle_MaxSpeed"){
							veh.max_speed = stoi(sval);
						}
						else if (key == "Vehicle_Acceleration"){
							veh.max_acc = stoi(sval);
						}

					}

					else if (curr == "[Simulation]"){
						// Running simulation
					}
					else{cout << "No headers given yet" << endl;}
				}	
			}
		}
		myfile.close();
	}
	else{cout << "Unable to open file" << endl;}
	// Run Simulation

	Vehicle car1;
	car1.size.x = 2;
	car1.size.y = 2;
	car1.type = 'c';
	road.spawn_vehicle(car1);
	road.update_map();
	road.print_cars();
	road.display();
	for (int i=0; i<20; i++){
		road.run();
		// road.display();
		road.print_cars();
	}

	return 0;
}