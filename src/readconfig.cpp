#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <vector>
#include "simulator.cpp"

using namespace std;

Road road(0,4,10);
Signal traf1;

struct vinfo{
	char type;
	int length = 1;
	int width = 1;
	int maxspeed = 1;
	int acc = 1;
};

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

	vector<vinfo> vlist;
	vinfo veh;
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
								vlist.push_back(veh);
								vinfo veh;
							}
							veh.type = sval.front();
							flag = 1;
						}
						else if (key == "Vehicle_Length"){
							veh.length = stoi(sval);
						}
						else if (key == "Vehicle_Width"){
							veh.width = stoi(sval);
						}
						else if (key == "Vehicle_MaxSpeed"){
							veh.maxspeed = stoi(sval);
						}
						else if (key == "Vehicle_Acceleration"){
							veh.acc = stoi(sval);
						}
					}

					else if (curr == "[Simulation]"){
						// Running simulation
						if (line == "END"){
							//TODO: run till road is clear
							break;
						}
						string str1 = "";
						string str2 = "";
						if (line.find(" ") != string::npos){
							str1 = line.substr(0,line.find(" "));
							str2 = line.substr(line.find(" ")+1);
						}

						if (str1 == "Signal"){
							if (str2 == "RED"){
								traf1.status = 'r';
							}
						}
						else if (str1 == "Pass"){
							//TODO: run till str2 time
						}

						else{
							for (int i = 0; i < vlist.size(); i++){
								vinfo veh = vlist[i];
								if (veh.type == str1.front()){
									Vehicle vehicle1(str2,veh.length,veh.width,veh.maxspeed,veh.acc);
									vehicle1.type = str1.front();
									road.spawn_vehicle(vehicle1);
									break;
								}
							}
							road.run();
							// road.display();
							road.print_cars();
						}

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
	// road.print_cars();
	// road.display();
	for (int i=0; i<20; i++){
		road.run();
		// road.display();
		// road.print_cars();
	}

	return 0;
}