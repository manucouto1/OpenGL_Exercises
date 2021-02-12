#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

typedef struct coord {
    GLfloat x;
    GLfloat y;
} t_coord;



t_coord cosineTriang(float alfa, int h){
    t_coord coord ;
    coord.y = cosf(alfa) * h;
    coord.x = sinf(alfa) * h;
    return  coord;
}

void init()
{
    glClearColor(0,0,0,0);/*Fijar el color por defecto a negro en el formato (RGBA)*/
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
        glVertex3f(-6.0f , .0f , .0f ); //X
        glVertex3f( 6.0f , .0f , .0f ); //X
        glVertex3f(.0f , -6.0f , .0f ); //Y
        glVertex3f(.0f , 6.0f , .0f ); //Y
        glVertex3f(.0f , .0f , -6.0f ); //Z
        glVertex3f(.0f , .0f , 6.0f ); //Z
    glEnd();

    // t_coord coord = cosineTriang(20.0f, 5.0f);

    // printf(" Eje x %f eje y %f \n", coord.x, coord.y);

    // glBegin(GL_LINES);
    //     glVertex3f(.0f , .0f , .0f ); //X
    //     glVertex3f(coord.x , coord.y, .0f ); //X
    // glEnd();
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); /*Borrado del FrameBuffer*/ 
    glMatrixMode(GL_MODELVIEW); /* Activar las modificaciones en los objetos del mundo*/
    glLoadIdentity();/* Cargar la identidad en la matrix de modeficaciones del mundo*/
    drawXY();

    
    glRotatef(20.0f, .0f, .0f, 1.0f);
    glTranslatef(5.0f, 0.0f, 0.0f);

    glScalef(1.0f, 2.0f, 1.0f);
    glRotatef(45.0f, .0f, .0f, 1.0f);
    
    
    
    glBegin(GL_QUADS);       //cara frontal
        glVertex3f(-1.0f, -1.0f,  1.0f); 
        glVertex3f( 1.0f, -1.0f,  1.0f); 
        glVertex3f( 1.0f,  1.0f,  1.0f); 
        glVertex3f(-1.0f,  1.0f,  1.0f); 
    glEnd();
    
    
    glFlush(); /*Forzar el renderizado*/
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);/*Activar las modificaciones en la camara*/
    glLoadIdentity(); /*Cargar la identidad en la matrix de proyección*/
    glOrtho(-10, 10, -10, 10, -10, 10);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); /*Cargar el teclado y el ráton*/
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /*inicializar el Frame Buffer*/
    glutInitWindowSize(WIDTH, HEIGTH); /*Tamaño de la ventana*/ 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); /*Posición del extremo superior-izquierdo de la ventana*/
    glutCreateWindow("Hola Mundo"); /* Crear la ventana*/
    init();
    
    glutDisplayFunc(display); /*Activar la funcion de pintado*/
    glutReshapeFunc(reshape); /*Activar la funcion de escalado*/
    glutMainLoop(); /*Arrancar el bucle de OpenGL*/

    return 0;
}
