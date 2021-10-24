
//  main.cpp
//  Inside a box
//
//  Created by Masood Aweaz on 14/10/21.
//




#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <unistd.h>
#include <cmath>
#include <math.h>
#include <ctime>

#include <iostream>
using namespace std;

#define PI 3.14

void timerCallBack();
void handleKeyboard(unsigned char , int , int );
void handleKeyboardSpecial(int, int, int);
void initLight();
void setMaterial(GLfloat , GLfloat , GLfloat ,
                 GLfloat , GLfloat , GLfloat ,
                 GLfloat , GLfloat , GLfloat ,
                 int );
void create_scene();
void coloredCuboid();
void draw_cylinder(GLfloat,GLfloat ,GLubyte ,GLubyte ,GLubyte );
void display();
void tetrahedron();
void hexagonalprism();

float thetha = 0;
float camx, camz;
GLuint ind = 0; //Gets the index of all the objects
float theta = 0, phi = 0;
float camx = 0, camy = 0, camz = 3;
float zoom = 3;
float cuaxisx = 0, cuaxisy = 0, cuaxisz = 0; //Required For rotation for cylinder (index : 2)
float cutransx = 0.6, cutransy = 0, cutransz = 0; //Required For translation for cylinder (index : 2)
float hpaxisx = 0, hpaxisy = 0, hpaxisz = 0; //Required For rotation for hexagonal prism (index : 1)
float hptransx = 1.8, hptransy = -0.25, hptransz = 0; //Required For translation for hexagonal prism  (index : 1)
float thaxisx = 0, thaxisy = 0, thaxisz = 0; //Required For rotation for Tetrahedron (index : 3)
float thtransx = -0.6, thtransy = -0.25, thtransz = 0; //Required For translation for Tetrahedron (index : 3)
int mulcu = 1; //Multiplier for cylinder (index : 2)
int mulhp = 1; //Multiplier for hexagonal prism (index : 1)
int multh = 1; //Multiplier for TTetrahedron (index : 3)
float prev_mx =0, curr_mx = 0;
float prev_my = 0, curr_my = 0;


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
    theta = theta + 1;
//    float rad = theta * PI/100;
//    camx = cos(rad);
//    camz = sin(rad);
    
    srand((unsigned)time(NULL));
    
    if(ind!=2){
        cutransx = cutransx + mulcu*((double)rand()/(RAND_MAX))/60;
        cutransy = cutransy + mulcu*((double)rand()/(RAND_MAX))/60;
        cutransz = cutransz + mulcu*((double)rand()/(RAND_MAX))/60;
        double distcu = pow(cutransx, 2.0f) + pow(cutransy, 2.0f) + pow(cutransz, 2.0f);
        
        if(distcu>=9){
            if(mulcu==1)
                mulcu = -1;
            else
                mulcu = 1;
        }
    }
    
    if(ind!=1){
        hptransx = hptransx + mulhp*((double)rand()/(RAND_MAX))/50;
        hptransy = hptransy + mulhp*((double)rand()/(RAND_MAX))/50;
        hptransz = hptransz + mulhp*((double)rand()/(RAND_MAX))/50;
        double disthp = pow(hptransx, 2.0f) + pow(hptransy, 2.0f) + pow(hptransz, 2.0f);
        if(disthp>=9){
            if(mulhp==1)
                mulhp = -1;
            else
                mulhp = 1;
        }
    }
    
    if(ind!=3){
        thtransx = thtransx + multh*((double)rand()/(RAND_MAX))/50;
        thtransy = thtransy + multh*((double)rand()/(RAND_MAX))/50;
        thtransz = thtransz + multh*((double)rand()/(RAND_MAX))/50;
        double distth = pow(thtransx, 2.0f) + pow(thtransy, 2.0f) + pow(thtransz, 2.0f);
        if(distth>=9){
            if(multh==1)
                multh = -1;
            else
                multh = 1;
        }
    }
    usleep(3*10000);
    glutPostRedisplay();
}

void handleKeyboard(unsigned char key, int x, int y){
    
    switch(key){
        case '-': zoom++;
            break;
        case '=': zoom--;
            break;
        default:
            break;
    }
    
    //For Rotation
    if(ind == 1){
        //First hexagonal prism
        //Do rotation
        switch(key){
            case 'x': hpaxisx!=1?hpaxisx=1:hpaxisx=0;
                break;
            case 'y': hpaxisy!=1?hpaxisy=1:hpaxisy=0;
                break;
            case 'z': hpaxisz!=1?hpaxisz=1:hpaxisz=0;;
                break;
        }
    }
    
    if(ind == 2){
        //First hexagonal prism
        //Do rotation
        switch(key){
            case 'x': cuaxisx!=1?cuaxisx=1:cuaxisx=0;
                break;
            case 'y': cuaxisy!=1?cuaxisy=1:cuaxisy=0;
                break;
            case 'z': cuaxisz!=1?cuaxisz=1:cuaxisz=0;;
                break;
        }
    }
    
    if(ind == 3){
        //First hexagonal Prism
        //Do rotation
        switch(key){
            case 'x': thaxisx!=1?thaxisx=1:thaxisx=0;
                break;
            case 'y': thaxisy!=1?thaxisy=1:thaxisy=0;
                break;
            case 'z': thaxisz!=1?thaxisz=1:thaxisz=0;;
                break;
        }
    }
    //Rotation Done
    glutPostRedisplay();
}

void handleKeyboardSpecial(int key, int x, int y){
    if(ind == 1){
        switch(key){
            case GLUT_KEY_UP: hptransy = hptransy + mulhp*0.2;
                break;
            case GLUT_KEY_DOWN: hptransy = hptransy - mulhp*0.2;
                break;
            case GLUT_KEY_LEFT: hptransx = hptransx - mulhp*0.2;
                break;
            case GLUT_KEY_RIGHT: hptransx = hptransx + mulhp*0.2;
                break;
            default:
                break;
        }
        double disthp = pow(hptransx, 2.0f) + pow(hptransy, 2.0f) + pow(hptransz, 2.0f);
        if(disthp>=9){
            if(mulhp==1)
                mulhp = -1;
            else
                mulhp = 1;
        }
    }
    if(ind == 2){
        switch(key){
            case GLUT_KEY_UP: cutransy = cutransy + mulcu*0.2;
                break;
            case GLUT_KEY_DOWN: cutransy = cutransy - mulcu*0.2;
                break;
            case GLUT_KEY_LEFT: cutransx = cutransx - mulcu*0.2;
                break;
            case GLUT_KEY_RIGHT: cutransx = cutransx + mulcu*0.2;
                break;
            default:
                break;
        }
        double distcu = pow(cutransx, 2.0f) + pow(cutransy, 2.0f) + pow(cutransz, 2.0f);
        
        if(distcu>=9){
            if(mulcu==1)
                mulcu = -1;
            else
                mulcu = 1;
        }
    }
    if(ind == 3){
        switch(key){
            case GLUT_KEY_UP: thtransy = thtransy + multh*0.2;
                break;
            case GLUT_KEY_DOWN: thtransy = thtransy - multh*0.2;
                break;
            case GLUT_KEY_LEFT: thtransx = thtransx - multh*0.2;
                break;
            case GLUT_KEY_RIGHT: thtransx = thtransx + multh*0.2;
                break;
            default:
                break;
        }
        double distth = pow(thtransx, 2.0f) + pow(thtransy, 2.0f) + pow(thtransz, 2.0f);
        if(distth>=9){
            if(multh==1)
                multh = -1;
            else
                multh = 1;
        }
    }
}

void handleMouseMotion(int x, int y){
    
    float rad_theta = theta * PI / 180;
    float rad_phi = phi * PI / 180;
    float radius = 3;
    curr_mx = x;
    curr_my = y;


    float eyeZ = radius * cos(rad_theta) * cos(rad_phi);
    float eyeX = radius * sin(rad_theta) * cos(rad_phi);
    float eyeY = radius * sin(rad_phi);
    float dtheta = (curr_mx - prev_mx) / 50;
    float dphi = (curr_my - prev_my) / 50;

    theta -= dtheta;
    phi -= dphi;
    camx = eyeX;
    camy = eyeY;
    camz = eyeZ;

    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        prev_mx = curr_mx = x;
        prev_my = curr_my = y;
    }
    
    if(state != GLUT_DOWN)
        return;
    float window_height = glutGet(GLUT_WINDOW_HEIGHT);

//      GLbyte color[4];
//      GLfloat depth;
//
//      glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
//      glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &ind);
    printf("Clicked on pixel stencil index %u\n",ind);
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

    //Draw the tube
    //glColor3ub(R-40,G-40,B-40);
    glColor3f(1, 0.7, 0);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = 2*radius * cos(angle);
            y = 2*radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    //Draw the circle on top of cylinder
    //glColor3ub(R,G,B);
    glColor3f(1, 0, 0.2);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = 2*radius * cos(angle);
            y = 2*radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
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


void tetrahedron() {
  // Draw the tetrahedron.  It is a four sided figure, so when defining it
  // with a triangle strip we have to repeat the last two vertices.
  glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
    glColor3f(0, 1, 0); glVertex3f(1, 0, 1);
    glColor3f(0, 0, 1); glVertex3f(0, 0, -1.4);
    glColor3f(1, 1, 1); glVertex3f(0, 2, 0);
    glColor3f(1, 0, 0); glVertex3f(-1, 0, 1);
  glEnd();

  glFlush();
}

void hexagonalPrism()
{
    float x[] = { 0.866f, 0.0f, -0.866f, -0.866f,  0.0f,  0.866f };
    float y[] = { 0.5f,   1.0f,  0.5f,   -0.5f,   -1.0f, -0.5f };

    glBegin(GL_QUADS);
    for (int i1 = 0; i1 < 6; ++i1)
    {
        glColor4f(
          i1 < 2 || i1 > 4 ? 1.0f : 0.0f,
          i1 > 0 && i1 < 5 ? 1.0f : 0.0f,
          i1 > 2 ? 1.0f : 0.0f,
          1.0f
        );

        int i2 = (i1 + 1) % 6;
        glVertex3f(x[i1], 0.0f, y[i1]);
        glVertex3f(x[i2], 0.0f, y[i2]);
        glVertex3f(x[i2], 1.0f, y[i2]);
        glVertex3f(x[i1], 1.0f, y[i1]);
    }
    glEnd();

    glColor4f( 1, 1, 1, 1 );

    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; ++i)
        glVertex3f(x[i], 0.0f, y[i]);
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; ++i)
        glVertex3f(x[i], 1.0f, y[i]);
    glEnd();
}

void display(){
    //to display the note when an object is selected and cosidered to be under the control of user
    unsigned char str[] = "The Object Selected is Paused now you can play with it";
    int w;
    w = glutBitmapLength(GLUT_BITMAP_8_BY_13, str);

    glRasterPos3f(0, 0, 0.);
    glColor3f(1., 0., 0.);
    int leng = 54;
    for (int i = 0; i < leng; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    }
    usleep(10*1000);
}

void create_scene(){
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    
    //Camera Adjusments
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(zoom*camx, zoom*camy, zoom*camz, 0, 0, 0, 0, 1, 0);
   
    //ambient : r,g,b diffuse: r, g, b specular: r, g, b  shininess(0-128) 0 is rough
    setMaterial(0.5, 0.5, 0.5, 0.6, 0.6, 0.6, 0.8, 0.8, 0.8, 128);
    
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glPushMatrix();
        if(hpaxisx!=0 || hpaxisy!=0 || hpaxisz!=0)
            glRotatef(theta, hpaxisx, hpaxisy, hpaxisz);
        glTranslatef(hptransx, hptransy, hptransz);
//        glScalef(10.0f, 10.0f, 10.0f);
        glStencilFunc(GL_ALWAYS, 1, -1);
        hexagonalPrism();
    glPopMatrix();

    glPushMatrix();
        if(cuaxisx!=0 || cuaxisy!=0 || cuaxisz!=0)
            glRotatef(theta, cuaxisx, cuaxisy, cuaxisz);
        glTranslatef(cutransx, cutransy, cutransz);
//        glScalef(10.0f, 10.0f, 10.0f);
        glStencilFunc(GL_ALWAYS, 2, -1);
        draw_cylinder(0.3, 1.0, 255, 160, 100);
    glPopMatrix();
    
    glPushMatrix();
        if(thaxisx!=0 || thaxisy!=0 || thaxisz!=0)
            glRotatef(theta, thaxisx, thaxisy, thaxisz);
        glTranslatef(thtransx, thtransy, thtransz);
//        glScalef(10.0f, 10.0f, 10.0f);
        glStencilFunc(GL_ALWAYS, 3, -1);
        tetrahedron();
    glPopMatrix();

    glPushMatrix();
            if(ind!=0){
                display();
            }
        glPopMatrix();
    glFlush();
}
