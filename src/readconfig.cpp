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
	if (myfile.is_open()){
		while ( getline(myfile, line) ){
			line = removeComment(line);
			line = trim(line);
			if (line != ""){
				cout << line << endl;
			}
		}
		myfile.close();
	}
	else{cout << "Unable to open file" << endl;}

	return 0;
}