#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>


GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 1;

float xRef = 0.0;
float yRef = 0.0;
float zRef = 0.0;
float x = 0.0;
float y = 4.0;
float z = 12.0;
float r, g, b = 1.0;


void display(void);
void reshape(int x, int y);
void idle(void);
void keyPressed(int key, int x, int y);
float randomFloat(float a, float b);


void idle(void) {
    
    //xRotated += 0.01;
    yRotated += 0.4;
    //zRotated += 0.01;
    display();
}

float randomFloat(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

//Moves the camera along axis based on the key pressed
void keyPressed(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        xRef -= 0.5;
    }
    if (key == GLUT_KEY_RIGHT) {
        xRef += 0.5;
    }
    if (key == GLUT_KEY_UP) {
        z -= 0.5;
    }
    if (key == GLUT_KEY_DOWN) {
        z += 0.5;
    }
    if (key == 32) {
        r = randomFloat(0.0, 1.0);
        g = randomFloat(0.0, 1.0);
        b = randomFloat(0.0, 1.0);
    }
   
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1500, 1500);
    glutCreateWindow("Solar System Model");
    xRotated = yRotated = zRotated = 30.0;
    xRotated = 43;
    yRotated = 50;
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyPressed);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(x, y, z, xRef, yRef, zRef, 0.0, 1.0, 0.0);
    
    //Earth
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 1.0);
    glColor3f(r, g, b);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glScalef(1.0,1.0,1.0);
    glutWireSphere(radius,20,20);
    glPopMatrix();
    
    //Sun
    glPushMatrix();
    glTranslatef(8.0, 0.0, 3.0);
    glColor3f(1.0, 1.0, 0.0);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glScalef(1.0,1.0,1.0);
    glutSolidSphere(radius + 0.5, 20, 20);
    glPopMatrix();
    
    //Mars
    glPushMatrix();
    glTranslatef(8.0, 0.0, -2.0);
    glColor3f(r, g, b);
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glutWireSphere(radius, 20, 20);
    glPopMatrix();
    
    //Moon
    glRotatef(yRotated * 2, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(-2.0, 0.0, 3.0);
    glColor3f(r, g, b);
    glScalef(1.0, 1.0, 1.0);
    glutWireSphere(radius, 20, 20);
    glPopMatrix();
    
    glFlush();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLdouble)x / (GLdouble)y, 0.3, 21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}
