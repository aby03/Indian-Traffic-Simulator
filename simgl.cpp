#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

//Units used
float ux = 0.1f;
float uy = 0.1f;
float uz = 0.1f;

// //Units with gap
// float gx = 0.1f;
// float gy = 0.15f;

// angle of rotation for the camera direction
float angle1=0.0;
float angle2=0.0;


// Camera coordinates
float x=0.0f, y=0.0f, z=5.0f;
// actual vector representing the camera's direction
float lx=0.0f, ly=0.0f, lz=-1.0f;
// Spherical position of the camera
float r=5.0f;

int roadLength = 21;
int roadWidth = 6;



void drawCar(int carl, int carw)
{
	float carX = carl*ux/2.0;
	float carY = carw*uy/2.0;
	float carZ = 0.1f;

	//To create gaps in between adjacent cars
	carX -= 0.03f;
	carY -= 0.03f; 

	glPushMatrix();

	float initcarX = - ((carl-1.0)/2) * ux;
	float initcarY = - ((carw-1.0)/2) * uy;

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
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(-carX, -carY, carZ);
    glVertex3f(-carX, carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, -carY, carZ);
    glVertex3f(-carX, -carY, carZ);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 2*carZ);
    glVertex3f(carX, carY, carZ);
    glVertex3f(carX, -carY, carZ);
    glEnd();
    //

    //Wheel
    

    glPopMatrix;
}

void renderScene(){
    cout << "Rendering..." << endl;
    // if (deltaMove)
    //     computePos(deltaMove);
    // if (deltaAngle)
    //     computeDir(deltaAngle);

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

    glPushMatrix();
    glTranslatef(2*ux, 0, 0); //Translate to that car's coordinates!
    drawCar(3,2);
    glPopMatrix();

    // glPushMatrix();
    // glTranslatef(ux, -2*uy, 0); //Translate to that car's coordinates!
    // drawCar(2,1);
    // glPopMatrix();

    glPushMatrix();
    glTranslatef(5*ux, -4*uy, 0); //Translate to that car's coordinates!
    drawCar(2,2);
    glPopMatrix();

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

void update(int value){
	//doSomething
    glutPostRedisplay(); // Inform GLUT that the display has changed
    glutTimerFunc(1000,update,0);//Call update after each 25 millisecond
}


int main(int argc, char **argv)
{
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
    glutTimerFunc(1000, update, 0);
    cout << "TEST" << endl;
    glutMainLoop();
    return 0;
}

// To Compile
// g++ simgl.cpp -lGL -lGLU -lglut