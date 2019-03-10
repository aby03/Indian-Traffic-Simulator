#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>


//Units used
float ux = 0.1f;
float uy = 0.1f;
float uz = 0.1f;

// //Units with gap
// float gx = 0.1f;
// float gy = 0.15f;

// angle of rotation for the camera direction
float angleX=0.0;
float angleY=0.0;


// Camera coordinates
float x=0.0f, y=0.0f, z=5.0f;
// actual vector representing the camera's direction
float lx=0.0f, ly=0.0f, lz=-1.0f;
// XZ position of the camera
float r=5.0f, rz=5.0f;

int roadLength = 21;
int roadWidth = 6;



void drawCar(int carl, int carw)
{
	float carX = carl*ux/2.0;
	float carY = carw*uy/2.0;
	float carZ = 0.1f;

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

    glPopMatrix;
}

void renderScene()
{

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

    float initX = -((roadLength+1.0)/2)*ux;
    float initY = ((roadWidth-1.0)/2)*uy;

    //Translate to position (0,0) on road
	glTranslatef(initX, initY, 0.1f);    

    glPushMatrix();
    glTranslatef(3*ux, 0, 0); //Translate to that car's coordinates!
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
			angleX -= 0.05f;
			x = r*sin(angleX);
			z = rz*cos(angleX);
			break;
		case GLUT_KEY_RIGHT :
			angleX += 0.05f;
			x = r*sin(angleX);
			z = rz*cos(angleX);
			break;
        case GLUT_KEY_UP :
			angleY += 0.05f;
			y = r*sin(angleY);
			z = rz*cos(angleY);
			break;
        case GLUT_KEY_DOWN :
			angleY -= 0.05f;
			y = r*sin(angleY);
			z = rz*cos(angleY);
			break;
    }
}

// void update(int value){
//     // carx += 0.01f;
//     rX += 1.0f;
//     rY += 1.0f;
//     // if (rX > 360){
//     // 	rX = 0;
//     // }
//     glutPostRedisplay(); // Inform GLUT that the display has changed
//     glutTimerFunc(25,update,0);//Call update after each 25 millisecond
// }


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
    // glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
