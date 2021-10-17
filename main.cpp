//
//  main.cpp
//  Inside a box
//
//  Created by Masood Aweaz on 14/10/21.
//

/*#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
*/

/*#define GL_SILENCE_DEPRECATION
#include <random>
#include <GL/glut.h>
#include <cstdlib>
#define PI 3.14
#include <unistd.h>
#include <stdio.h>
#include <iostream>

void shapes()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        //glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(quadratic,0.1f,0.1f,3.0f,32,32);
    
}

int main(int argc,char* argv[])
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(640, 640);
    
    glutInitWindowPosition(10, 10);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    
    glutCreateWindow("Inside a box");
    
    glClearColor(1,1,1,0);
    
    glutDisplayFunc(shapes);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 720);
    
    glutMainLoop();
    
}
*/

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <unistd.h>
#include <cmath>

#define PI 3.14

void timerCallBack();
void initLight();
void setMaterial(GLfloat , GLfloat , GLfloat ,
                 GLfloat , GLfloat , GLfloat ,
                 GLfloat , GLfloat , GLfloat ,
                 int );
void scene();
void coloredCuboid();

float thetha = 0;
float camx, camz;

int main(int argc, char **argv){
    //Initialise GLUT
    glutInit(&argc, argv);

    //Setup the window
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Assignment");
    
    //Enable the stage
    glEnable(GL_DEPTH_TEST);
    
    initLight();
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(1, 1, 1, 0);

    glutDisplayFunc(scene);
    
    glutIdleFunc(timerCallBack);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glOrtho(-3, 3, -3, 3, -3, 4);
    gluPerspective(40, 1, 0.5, 1000);

    glutMainLoop();
}


void timerCallBack(){
    thetha++;
    float rad = thetha * PI/100;
    camx = cos(rad);
    camz = sin(rad);
    usleep(3*10000);
    glutPostRedisplay();
}

void initLight(){
    float ambient[] = {0.3, 0.3, 0.3, 1};
    float diffuse[] = {0.6, 0.6, 0.6, 1};
    float specular[] = {0.8, 0.8, 0.8, 1};
    float position[] = {-2, 0.5, 4, 1};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
}

void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
                 GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
                 GLfloat specularR, GLfloat specularG, GLfloat specularB,
                 int shine){
    
    float ambient[] = {ambientR, ambientG, ambientB};
    float diffuse[] = {diffuseR, diffuseG, diffuseB};
    float specular[] = {specularR, specularG, specularB};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shine);

}

void coloredCube(){
    
    glColor3f((GLfloat)184/255, (GLfloat)115/255, (GLfloat)51/255);
    //Front Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1.0);
        glVertex3f(-1, 1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(-1, -1, 1);
    glEnd();
    
//    glColor3f(0, 1, 1);
    //Right Face
    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0, 0);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, -1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);
    glEnd();
    
//    glColor3f(1, 0, 1);
    //Back Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(-1, 1, -1);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
    glEnd();
    
//    glColor3f(1, 0.5, 0.2);
    //Left Face
    glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(-1, 1, -1);
        glVertex3f(-1, 1, 1);
        glVertex3f(-1, -1, 1);
        glVertex3f(-1, -1, -1);
    glEnd();
    
//    glColor3f(0.2, 0.5, 0);
    //Top Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(-1, 1, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(1, 1, 1);
        glVertex3f(-1, 1, 1);
    glEnd();
    
//    glColor3f(1, 0.9, 0);
    //Bottom Face
    glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);
        glVertex3f(-1, -1, 1);
    glEnd();
//    glutSolidCube(0.5);
}
void coloredCuboid(){
    
    glColor3f((GLfloat)184/255, (GLfloat)115/255, (GLfloat)51/255);
    //Front Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1.0);
        glVertex3f(-0.5, 0.25, 0.25);
        glVertex3f(0.5, 0.25, 0.25);
        glVertex3f(0.5, -0.25, 0.25);
        glVertex3f(-0.5, -0.25, 0.25);
    glEnd();
    
//    glColor3f(0, 1, 1);
    //Right Face
    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0, 0);
        glVertex3f(0.5, 0.25, 0.25);
        glVertex3f(0.5, 0.25, -0.25);
        glVertex3f(0.5, -0.25, -0.25);
        glVertex3f(0.5, -0.25, 0.25);
    glEnd();
    
//    glColor3f(1, 0, 1);
    //Back Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(0.5, 0.25, -0.25);
        glVertex3f(-0.5, 0.25, -0.25);
        glVertex3f(-0.5, -0.25, -0.25);
        glVertex3f(0.5, -0.25, -0.25);
    glEnd();
    
//    glColor3f(1, 0.5, 0.2);
    //Left Face
    glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(-0.5, 0.25, -0.25);
        glVertex3f(-0.5, 0.25, 0.25);
        glVertex3f(-0.5, -0.25, 0.25);
        glVertex3f(-0.5, -0.25, -0.25);
    glEnd();
    
//    glColor3f(0.2, 0.5, 0);
    //Top Face
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(-0.5, 0.25, -0.25);
        glVertex3f(0.5, 0.25, -0.25);
        glVertex3f(0.5, 0.25, 0.25);
        glVertex3f(-0.5, 0.25, 0.25);
    glEnd();
    
//    glColor3f(1, 0.9, 0);
    //Bottom Face
    glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(-0.5, -0.25, -0.25);
        glVertex3f(0.5, -0.25, -0.25);
        glVertex3f(0.5, -0.25, 0.25);
        glVertex3f(-0.5, -0.25, 0.25);
    glEnd();
//    glutSolidCube(0.5);
}
void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

void scene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera Adjusments
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5*camx, 2.5, 5*camz, 0, 0, 0, 0, 1, 0);
//    glRotatef(thetha, 0, 1, 0);
    //--------------------
    
    //ambient : r,g,b diffuse: r, g, b specular: r, g, b  shininess(0-128) 0 is rough
    
    setMaterial(0.2, 0.2, 0.2, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, 60);
    glPushMatrix();
        glRotatef(thetha, 1, 0, 0);
        //coloredCuboid();
        draw_cylinder(0.3, 1.0, 255, 160, 100);
    glPopMatrix();

    glFlush();
}
