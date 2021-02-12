#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 100
#define ORIGIN_Y 100

GLint ancho=400;
GLint alto=400;

struct T_rot {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} typedef T_rotXYZ;

T_rotXYZ rotate1 = {
    x : 0.0f,
    y : 0.0f,
    z : 0.0f,
};

T_rotXYZ rotate2 = {
    x : 0.0f,
    y : 0.0f,
    z : 0.0f,
};

int hazPerspectiva = 0;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(hazPerspectiva)
        gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 20.0f);
    else       
        glOrtho(-4,4, -4, 4, 1, 10);

    glMatrixMode(GL_MODELVIEW);
 
    ancho = width;
    alto = height;
}

void drawCube(void)
{
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glBegin(GL_QUADS);       //cara frontal
    glVertex3f(-1.0f, -1.0f,  1.0f); 
    glVertex3f( 1.0f, -1.0f,  1.0f); 
    glVertex3f( 1.0f,  1.0f,  1.0f); 
    glVertex3f(-1.0f,  1.0f,  1.0f); 
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glBegin(GL_QUADS);       //cara trasera
    glVertex3f( 1.0f, -1.0f, -1.0f); 
    glVertex3f(-1.0f, -1.0f, -1.0f); 
    glVertex3f(-1.0f,  1.0f, -1.0f); 
    glVertex3f( 1.0f,  1.0f, -1.0f); 
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glBegin(GL_QUADS);       //cara lateral izq
    glVertex3f(-1.0f,-1.0f, -1.0f); 
    glVertex3f(-1.0f,-1.0f,  1.0f); 
    glVertex3f(-1.0f, 1.0f,  1.0f); 
    glVertex3f(-1.0f, 1.0f, -1.0f); 
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glBegin(GL_QUADS);       //cara lateral dcha
    glVertex3f(1.0f, -1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glEnd(); 
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glBegin(GL_QUADS);       //cara arriba
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
 
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glBegin(GL_QUADS);       //cara abajo
    glVertex3f( 1.0f,-1.0f, -1.0f);
    glVertex3f( 1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f,  1.0f);
    glVertex3f(-1.0f,-1.0f, -1.0f);
    glEnd();
}

void drawXY(){
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
        glVertex3f(-4.0f , .0f , .0f ); //X
        glVertex3f(4.0f , .0f , .0f ); //X
        glVertex3f(.0f , -4.0f , .0f ); //Y
        glVertex3f(.0f , 4.0f , .0f ); //Y
        glVertex3f(.0f , .0f , -4.0f ); //Z
        glVertex3f(.0f , .0f , 4.0f ); //Z
    glEnd();
}

void display()
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotate1.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate1.y, 0.0f, 1.0f, 0.0f); 
    glRotatef(rotate1.z, 0.0f, 1.0f, 0.0f); 

    glScalef(1.0f, 2.0f, 1.0f);
    drawCube();
    
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    drawXY();

    glLoadIdentity();
 
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotate2.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate2.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotate2.z, 0.0f, 0.0f, 1.0f);

    glTranslatef(3.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireSphere(0.5f, 8, 8);
 
    glFlush();
    glutSwapBuffers();
}

void init()
{
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    ancho = 400;
    alto = 400;
}
 

void idle()
{
    display();
}
 
// Si pulsamos el raton derecho movemos la segunda articulación
// Para volver a mover la primera tenemos que clicar el boton izquierdo
void keyboard(unsigned char key, int x, int y) {
    
        switch(key) {
            case 'q':
                rotate1.x+=1.0f;
                break;
            case 'a':
                rotate1.x-=1.0f;
                break;
            case 'w':
                rotate1.y+=1.0f;
                break;
            case 's':
                rotate1.y-=1.0f;
                break;
            case 'e':
                rotate1.z+=1.0f;
                break;
            case 'd':
                rotate1.z-=1.0f;
                break;
            case 'r':
                rotate2.x+=1.0f;
                break;
            case 'f':
                rotate2.x-=1.0f;
                break;
            case 't':
                rotate2.y+=1.0f;
                break;
            case 'g':
                rotate2.y-=1.0f;
                break;
            case 'y':
                rotate2.z+=1.0f;
                break;
            case 'h':
                rotate2.z-=1.0f;
                break;
        }
}

void TimerFunction(){
    display();
    glutTimerFunc(45, TimerFunction, 1);
}
 
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Cubo");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000, TimerFunction,0); 
    glutMainLoop();
    return 0;
}