#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <limits.h>

#include "lib/my_movement.h"
#include "lib/my_objects.h"

GLUquadric* qobj;

// Constantes
#define ORIGIN_X 50
#define ORIGIN_Y 50

#define ORTO_W (GLdouble) 22.0f
#define ORTO_H (GLdouble) 22.0f
#define ORTO_Z (GLdouble) 22.0f

#define PUSHED 1
#define NOT_PUSHED 0

#define YELLOW 0
#define RED 1
#define GREEN 2
#define BLUE 3

#define FAST 4.0f
#define NORMAL 2.5f
#define SLOW 1.0f


// Variables globales 
int speed=2.5;
int clicked_buton = 0;
int last_positionX = 0;
int last_positionY = 0;
int hazPerspectiva = 0;

int invert_rot = 0;
int stop = 0;
int active_color = 0;

int key_a[UCHAR_MAX];

GLint WIDTH =  400;
GLint HEIGTH = 400;

T_rotXYZ rotate0 = INIT_ROTATE;
T_rotXYZ rotate1 = INIT_ROTATE;
T_rotXYZ rotate2 = INIT_ROTATE;
T_rotXYZ rotate3 = INIT_ROTATE;

void cabina(float brazo){
    
    glColor3f(1.0f,1.0f,1.0f);

    glTranslatef(brazo, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 6.0f);

    // Invertimos rotación para no marear a pasajeros
    myRotateZ(INVERT_ROT(rotate1).z);

    glPushMatrix();
        glScalef(3.0f,1.0f,3.0f);
        glutSolidCube(2);
    glPopMatrix();

    // Configuración del color pasajeros
    switch (active_color){
        case YELLOW: 
            glColor3f(1.0f,1.0f,0.0f);
        break;
        case RED:
            glColor3f(1.0f,0.0f,0.0f);
        break;
        case GREEN:
            glColor3f(0.0f,1.0f,0.0f);
        break;
        case BLUE:
            glColor3f(0.0f,0.0f,1.0f);
        break;
    }

    glTranslatef(0.0f, 1.75f, 0.0f);

    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 2.0f);
    glutSolidCube(1.75f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, 0.0f, -2.0f);
    glutSolidCube(1.75f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, -2.0f);
    glutSolidCube(1.75f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 2.0f);
    glutSolidCube(1.75f);
    glPopMatrix();

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f,0.0f,1.0f);


    myRotateXYZ(rotate0);

    // Base de la atracción
    glTranslatef(1.0f,-TR_HEIGTH(16.0f)/2 - 2.0f,1.0f);
    myCylinder(8, 2);

    // Estructura    
    myTriangle(16.0f, TR_HEIGTH(16.0f), 2.0f);
    glTranslatef(0.0f,TR_HEIGTH(16.0f), 0.0f);

    // Brazo
    myRotateZ(rotate1.z);
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.0f);
        glTranslatef(TR_HEIGTH(16.0f)/2 - 1.0f, 0.0f, 0.0f);
        glScalef(TR_HEIGTH(16.0f)/2 -1.0f, 1.0f, 1.0f);
        glutSolidCube(2);
    glPopMatrix();

    // Cabina
    cabina(TR_HEIGTH(16.0f)-1.0f);

    glFlush(); 
    glutSwapBuffers();
};

// Camviar modo de proyección
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva){
        gluPerspective(60.0f, (GLfloat)w/(GLfloat)h, 0.2f, 100);
    } else {       
        glOrtho(-ORTO_W, ORTO_W, -ORTO_H, ORTO_H, -ORTO_Z, 3*ORTO_Z);
    }

    //Reposicionamos cámara para ver correctamente
    gluLookAt(0.0f,0.0f, 2.5*ORTO_Z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);

    WIDTH = w;
    HEIGTH = h;
};

void idle(){
    display();
}

// P y O para cambiar de entre perspectiva y ortogonal
// Q y A Para mover atracción en eje Y
// R para invertir la rotación
// S para Parar la atracción
void keyboard(unsigned char key, int x, int y) {
    
    switch(key) {
        case 'p':
            hazPerspectiva = 1;
            reshape(WIDTH,HEIGTH);

            break;
        case 'o':
            hazPerspectiva = 0;
            reshape(WIDTH,HEIGTH);

            break;
        case 'q':
            rotate0.y -= speed;
            break;
        case 'a':
            rotate0.y += speed;
            break;
        
        case 'r':
            invert_rot = (invert_rot)?0:1;
            break;
        case 's':
            stop = 1;
            break;
    }
}

// Configuración de menu para seleccionar velocidad de rotación y colores de pasajeros
void menu (int value){
    switch (value)
    {
        case 1:
            speed = (float) FAST;
        break;
        case 2:
            speed = (float) NORMAL;
        break;
        case 3:
            speed = (float) SLOW;
        break;
        case 4:
            active_color = YELLOW;
        break;
        case 5:
            active_color = RED;
        break;
        case 6:
            active_color = GREEN;
        break;
        case 7:
            active_color = BLUE;
        break;
    }

}

void createMenu(){
    int typeSpeed = glutCreateMenu(menu);
    glutAddMenuEntry("Fast",1);
    glutAddMenuEntry("Normal",2);
    glutAddMenuEntry("Slow",3);

    int typeColor = glutCreateMenu(menu);
    glutAddMenuEntry("Yellow",4);
    glutAddMenuEntry("Red",5);
    glutAddMenuEntry("Green",6);
    glutAddMenuEntry("Blue",7);
    
    glutCreateMenu(menu);
    glutAddSubMenu("Speed", typeSpeed);
    glutAddSubMenu("Color", typeColor);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

void TimerFunction(){

    display();
    
    if(stop && (((int) (rotate1.z-270)%360)==0)){
        printf("Stop");
    } else {
        glutTimerFunc(50/speed, TimerFunction, 1);
        rotate1.z += (invert_rot)?-speed:speed;
    }
    
    
}

void motion_func (int x, int y) {

    if( clicked_buton == GLUT_LEFT_BUTTON){

        if(key_a[GLUT_ACTIVE_SHIFT]==PUSHED){
            
            if (x > last_positionX + 1){
                rotate0.y+=speed;
            } else if (x < last_positionX - 1){
                rotate0.y-=speed;
            }
        } else {
            if(y > last_positionY + 1){
                rotate0.x += speed;
            } else if(y < last_positionY-1) {
                rotate0.x -= speed;
            }
        }
    }
    
    last_positionX = x;
    last_positionY = y;
}

void mouse_func(int but, int state, int x, int y){
    clicked_buton = but;
}

void specialkeyUp(int key, int x, int y){
    int mod = glutGetModifiers();

    if(GLUT_ACTIVE_SHIFT == mod) {
        key_a[GLUT_ACTIVE_SHIFT]=NOT_PUSHED;
    } 
}

void specialkeyDown(int key, int x, int y){
    int mod = glutGetModifiers();

    if(key == 112||(mod==GLUT_ACTIVE_SHIFT)) {
        key_a[GLUT_ACTIVE_SHIFT]=PUSHED;
    } 
}

void myInit() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(WIDTH, HEIGTH); 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);
    glutCreateWindow("Examen");
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    WIDTH = 400;
    HEIGTH = 400;
}

int main( int argc, char **argv){
    glutInit(&argc, argv); 
    myInit();
    createMenu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutKeyboardFunc(keyboard);
    glutSpecialUpFunc(specialkeyUp);
    glutSpecialFunc(specialkeyDown);
    
    glutTimerFunc(1000, TimerFunction,0);
    glutMainLoop();
    gluDeleteQuadric(qobj);
    return 0;
}