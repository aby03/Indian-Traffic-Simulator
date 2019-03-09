#include <iostream>
#include <stdlib.h>

// the GLUT and OpenGL libraries have to be linked correctly
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

// Rotate X
double rX=0;
// Rotate Y
double rY=0;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

float carx=-1.5f;

// float deltaAngle = 0.0f;
// float deltaMove = 0;

// void computePos(float deltaMove) {

//     x += deltaMove * lx * 0.1f;
//     z += deltaMove * lz * 0.1f;
// }

// void computeDir(float deltaAngle) {

//     angle += deltaAngle;
//     lx = sin(angle);
//     lz = -cos(angle);
// }
// void pressKey(int key, int xx, int yy) {

//     switch (key) {
//         case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
//         case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
//         case GLUT_KEY_UP : deltaMove = 0.5f; break;
//         case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
//     }
// }

// void releaseKey(int key, int x, int y) {

//     switch (key) {
//         case GLUT_KEY_LEFT :
//         case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
//         case GLUT_KEY_UP :
//         case GLUT_KEY_DOWN : deltaMove = 0;break;
//     }
// }


void drawCar()
{
    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0f, 0.0f, 0.0f);
    glVertex3f(0.2, -0.1, 0);
    glVertex3f(0.2, 0.1, 0);
    glVertex3f(-0.2, 0.1, 0);
    glVertex3f(-0.2, -0.1, 0);
    glEnd();
}

void drawCube()
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

    gluLookAt(  x, 0.0f, z,
               x+lx, 0.0f,  z+lz,
               0.0f, 1.0f,  0.0f);

    // glTranslatef(0.0, 0.0, -5.0);
    // Add an ambient light
    GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add a positioned light
    // GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0};
    // GLfloat lightPos0[] = {4.0, 0.0, 8.0, 1.0};
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);


    // Rotate when user changes rX and rY
    // glRotatef( rX, 1.0, 0.0, 0.0 );
    // glRotatef( rY, 0.0, 1.0, 0.0 );

    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(2, -0.6, 0);
    glVertex3f(2, 0.6, 0);
    glVertex3f(-2, 0.6, 0);
    glVertex3f(-2, -0.6, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(carx, 0.3f, 0.1f);
    drawCar();
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
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void update(int value){
    carx += 0.01f;
    glutPostRedisplay(); // Inform GLUT that the display has changed
    glutTimerFunc(25,update,0);//Call update after each 25 millisecond
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Traffic Simulator");
        initRendering();

    glutDisplayFunc(drawCube);
    glutReshapeFunc(handleResize);

    glutIdleFunc(drawCube);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // glutIgnoreKeyRepeat(1);
    // glutSpecialUpFunc(pressKey);        

    // Add a timer for the update(...) function
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
