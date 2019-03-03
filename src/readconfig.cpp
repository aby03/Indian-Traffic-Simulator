#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
//#include "simulator.cpp"

using namespace std;

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

int main(){
	string line;
	ifstream myfile ("./config/config.ini");
	string curr = "";
	if (myfile.is_open()){
		while ( getline(myfile, line) ){
			line = removeComment(line);
			line = trim(line);
			if (line != ""){
				if (line.front() == '[' && line.back() == ']'){
					curr = line;
				}
				else{
					if (curr == "[Road]"){
						// Storing road parameters
						cout << "Road: " << line << endl;
					}
					else if (curr == "[Default]"){
						// Storing default parameters
						cout << "Default: " << line << endl;
					}
					else if (curr == "[Vehicles]"){
						// Storing vehicle parameters
						cout << "Vehicles: " << line << endl;
					}
					else if (curr == "[Simulation]"){
						// Running simulation
						cout << "Simulation: " << line << endl;
					}
					else{cout << "No headers given yet" << endl;}
				}

			}
		}
		myfile.close();
	}
	else{cout << "Unable to open file" << endl;}

	return 0;
}