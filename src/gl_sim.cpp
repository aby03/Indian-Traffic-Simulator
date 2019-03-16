#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include <thread>
#include <chrono>

#include <fstream>
#include <bits/stdc++.h> 
#include <vector>
#include "simulator.cpp"

using namespace std;

// ------------ Config File Variables --------------------
struct vinfo{
    char type;
    int length = 1;
    int width = 1;
    int maxspeed = 1;
    int acc = 1;
};
Road road(0,4,10);
Signal traf1;
int id_counter = 0;
vector<vinfo> vlist;
vector<string> sim_cmd;
int sim_index = 0;
int pass_count = 0;
bool flag_end = false;
// ------------ OpenGL Variables --------------------
int time_step = 500;
//Units used
float ux = 0.1f;
float uy = 0.1f;
float uz = 0.1f;
// angle of rotation for the camera direction
float angle1=0.0;
float angle2=0.0;
// Camera coordinates
float x=0.0f, y=0.0f, z=5.0f;
// actual vector representing the camera's direction
float lx=0.0f, ly=0.0f, lz=-1.0f;
// Spherical position of the camera
float r=5.0f;
// Road Variables
int roadLength = 21;
int roadWidth = 6;

// ------------ Config File Functions --------------------
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

// ------------ OpenGL Functions --------------------
void drawCar(int carl, int carw, string color)
{
    float top_color_r = 0;
    float top_color_g = 0;
    float top_color_b = 0;
    if (color == "GREEN"){
        top_color_r = 0;
        top_color_g = 0.6;
        top_color_b = 0;
    }else if (color == "RED"){
        top_color_r = 1;
        top_color_g = 0;
        top_color_b = 0;
    }else if (color == "BLUE"){
        top_color_r = 0;
        top_color_g = 0;
        top_color_b = 1;
    }
    float carX = carl*ux/2.0;
    float carY = carw*uy/2.0;
    float carZ = 0.1f;

    //To create gaps in between adjacent cars
    carX -= 0.03f;
    carY -= 0.03f; 

    glPushMatrix();

    float initcarX = - ((carl-1.0)/2) * ux;
    float initcarY = ((carw-1.0)/2) * uy;

    glTranslatef(initcarX,initcarY,0);

    //bottom
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(carX, -carY, 0);
    glVertex3f(carX, carY, 0);
    glVertex3f(-carX, carY, 0);
    glVertex3f(-carX, -carY, 0);
    glEnd();

    //side
    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0f, 0.0f, 0.0f);
    glVertex3f(carX, -carY, 0);
    glVertex3f(carX, carY, 0);
    glVertex3f(carX, carY, carZ);
    glVertex3f(carX, -carY, carZ);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0f, 0.0f, 0.0f);
    glVertex3f(-carX, carY, 0);
    glVertex3f(carX, carY, 0);
    glVertex3f(carX, carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0f, 0.0f, 0.0f);
    glVertex3f(-carX, carY, 0);
    glVertex3f(-carX, -carY, 0);
    glVertex3f(-carX, -carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0f, 0.0f, 0.0f);
    glVertex3f(carX, -carY, 0);
    glVertex3f(-carX, -carY, 0);
    glVertex3f(-carX, -carY, carZ);
    glVertex3f(carX, -carY, carZ);
    glEnd();

    //top
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(carX, -carY, carZ);
    glVertex3f(carX, carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glVertex3f(-carX, -carY, carZ);
    glEnd();


    //Square Pyramid Top
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f+top_color_r, 0.0f+top_color_g, 0.0f+top_color_b);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f+top_color_r, 0.0f+top_color_g, 0.0f+top_color_b);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(-carX, -carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f+top_color_r, 0.0f+top_color_g, 0.0f+top_color_b);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, -carY, carZ);
    glVertex3f(-carX, -carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f+top_color_r, 0.0f+top_color_g, 0.0f+top_color_b);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, carY, carZ);
    glVertex3f(carX, -carY, carZ);
    glEnd();
    //

    //Wheel
    

    glPopMatrix();
}

void renderScene(){
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(  x, y, z,
               0.0f, 0.0f,  0.0f,
               0.0f, 1.0f,  0.0f);

    // glTranslatef(0.0, 0.0, -5.0);
    // Add an ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add a positioned light
    // GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    // GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);


    // Rotate when user changes rX and rY
    // glRotatef( rX, 1.0, 0.0, 0.0 );
    // glRotatef( rY, 0.0, 1.0, 0.0 );

    float rl = roadLength*ux/2;
    float rw = roadWidth*uy/2;

    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(rl, rw, 0);
    glVertex3f(-rl, rw, 0);
    glVertex3f(-rl, -rw, 0);
    glVertex3f(rl, -rw, 0);
    glEnd();

    float initX = -((roadLength-1.0)/2)*ux;
    float initY = ((roadWidth-1.0)/2)*uy;

    //Translate to position (0,0) on road 
    //It is the centre point of 0.1x0.1 box
    glTranslatef(initX, initY, 0.0f);

    // Draw Signals
    for (int i=0; i<road.traf_signal_list.size(); i++){
        glPushMatrix();
        glTranslatef(road.traf_signal_list[i].pos*ux, uy, 0);
        glBegin(GL_POLYGON);
        if (road.traf_signal_list[i].status == 'r'){
            glColor3f(1.0f, 0.0f, 0.0f);
        }else{
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        glVertex3f(-ux/2, uy/2, 0);
        glVertex3f(-ux/2, -uy/2, 0);
        glVertex3f(ux/2, -uy/2, 0);
        glVertex3f(ux/2, uy/2, 0);
        glEnd();
        glPopMatrix();
        // White Line
        glPushMatrix();
        glTranslatef(road.traf_signal_list[i].pos*ux, 0, 0.0001f);
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-ux/2, uy/2, 0);
        glVertex3f(-ux/2, -roadWidth*uy+uy/2, 0);
        glVertex3f(ux/2, -roadWidth*uy+uy/2, 0);
        glVertex3f(ux/2, uy/2, 0);
        glEnd();
        glPopMatrix();
    }

    // Draw Vehicles
    for (int i=0; i<road.vehicles_list.size(); i++){
        glPushMatrix();
        glTranslatef(road.vehicles_list[i].location.x*ux, road.vehicles_list[i].location.y*-uy, 0);
        drawCar(road.vehicles_list[i].size.x, road.vehicles_list[i].size.y, road.vehicles_list[i].color);
        glPopMatrix();
    }

    glFlush();
    glutSwapBuffers();
}

// Initializes 3D rendering
void initRendering()
{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);

        // Set the color of the background
        glClearColor(0.7f, 0.8f, 1.0f, 1.0f);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
}


// Called when the window is resized
void handleResize(int w, int h)
{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
        glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT :
            angle1 -= 0.05f;
            break;
        case GLUT_KEY_RIGHT :
            angle1 += 0.05f;
            break;
        case GLUT_KEY_UP :
            angle2 += 0.05f;
            break;
        case GLUT_KEY_DOWN :
            angle2 -= 0.05f;
            break;
        case GLUT_KEY_PAGE_UP:
            r -= 0.1f;
            break;
        case GLUT_KEY_PAGE_DOWN:
            r += 0.1f;
            break;

    }

    x = r*cos(angle2)*sin(angle1);
    z = r*cos(angle2)*cos(angle1);
    y = r*sin(angle2);

}
int timer = 0;
void update(int value){
    if (value != 1){
        timer++;
        cout << "TIME: " << timer << endl;
    }
    // Run Simulation
    if (flag_end){
        road.run();
        road.display();
        if (road.vehicles_list.size() == 0){
            flag_end = false;
        }else{
            glutPostRedisplay(); // Inform GLUT that the display has changed
            glutTimerFunc(time_step,update,0);
        }
    }else{
        if (pass_count > 0){
            road.run();
            road.display();
            pass_count--;
            glutPostRedisplay(); // Inform GLUT that the display has changed
            glutTimerFunc(time_step,update,0);//Call update after each 25 millisecond
        }else{
            if (sim_index < sim_cmd.size()){
                string line = sim_cmd[sim_index];
                cout << line << endl;
                sim_index++;
                // Simulation Start
                if (line == "END"){
                    //TODO: run till road is clear
                    flag_end = true;
                    glutPostRedisplay(); // Inform GLUT that the display has changed
                    glutTimerFunc(0,update,1);
                    return;
                }
                string str1 = "";
                string str2 = "";
                if (line.find(" ") != string::npos){
                    str1 = line.substr(0,line.find(" "));
                    str2 = line.substr(line.find(" ")+1);
                }

                if (str1 == "Signal"){
                    if (str2 == "RED"){
                        road.traf_signal_list[0].status = 'r';
                    }
                    if (str2 == "GREEN"){
                        road.traf_signal_list[0].status = 'g';
                    }
                    glutPostRedisplay(); // Inform GLUT that the display has changed
                    glutTimerFunc(0,update,1);//Call update after each 25 millisecond
                    return;
                }
                else if (str1 == "Pass"){
                    pass_count = stoi(str2);
                    glutTimerFunc(0,update,1);//Call update after each 25 millisecond
                    return;
                }
                else{
                    for (int i = 0; i < vlist.size(); i++){
                        vinfo veh = vlist[i];
                        if (veh.type == str1.front()){
                            Vehicle vehicle1(id_counter, str2,veh.length,veh.width,veh.maxspeed,veh.acc);
                            id_counter++;
                            vehicle1.type = str1.front();
                            road.spawn_vehicle(vehicle1);
                            break;
                        }
                    }
                    road.run();
                    road.display();
                    glutPostRedisplay(); // Inform GLUT that the display has changed
                    glutTimerFunc(time_step,update,0);//Call update after each 25 millisecond
                    return;
                }

                // Simulation End
            }
        }
    }
    // glutPostRedisplay(); // Inform GLUT that the display has changed
    // glutTimerFunc(time_step,update,0);//Call update after each 25 millisecond
}

int main(int argc, char **argv)
{
    // ----------------- Config File Reading ----------------- 
    string line;
    ifstream myfile ("./config/config.ini");
    string curr = ""; //Current header operation
    int def_speed=1;
    int def_acc=1;
    vinfo veh;
    veh.maxspeed = def_speed;
    veh.acc = def_acc;
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
                            veh.maxspeed = def_speed;
                        }
                        else if (key == "Default_Acceleration"){
                            def_acc = val;
                            veh.acc = def_acc;
                        }
                    }
                    else if (curr == "[Vehicles]"){
                        if (key == "Vehicle_Type"){
                            if (flag == 1){
                                vlist.push_back(veh);
                                veh.maxspeed = def_speed;
                                veh.acc = def_acc;
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
                        sim_cmd.push_back(line);
                    }
                    else{cout << "No headers given yet" << endl;}
                }   
            }
        }
        myfile.close();
    }
    else{cout << "Unable to open file" << endl;}

    cout << "Sim commands: " << sim_cmd.size() << endl;
    // -----------------  OpenGL Code -----------------
    roadLength = road.length;
    roadWidth = road.width;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Traffic Simulator");
        initRendering();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(handleResize);

    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // glutIgnoreKeyRepeat(1);
    // glutSpecialUpFunc(pressKey);        

    // Add a timer for the update(...) function
    glutTimerFunc(time_step, update, 0);
    glutMainLoop();
    // cout << "Testing..." << endl;
    // using namespace std::this_thread; // sleep_for, sleep_until
    // using namespace std::chrono; // nanoseconds, system_clock, seconds
    // sleep_for(seconds(5));
    return 0;
}

// To Compile
// g++ simgl.cpp -lGL -lGLU -lglut
