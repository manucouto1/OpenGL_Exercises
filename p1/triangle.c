#include <GL/glut.h>
#include <math.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

void init()
{
    glClearColor(0,0,0,0);/*Fijar el color por defecto a negro en el formato (RGBA)*/
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); /*Borrado del FrameBuffer*/ 
    glMatrixMode(GL_MODELVIEW); /* Activar las modificaciones en los objetos del mundo*/
    glLoadIdentity();/* Cargar la identidad en la matrix de modeficaciones del mundo*/

    /* Lo que haya que pintar ira aquí*/
    /* Triangulo Blanco */
  /*Círculo con lineas*/
int i;
float radius = 1.0f;
float ang = 0.0f;

glColor3f( 1.0f, 1.0f, 1.0f);
for (i = 0; i <360; i = i+3){
    ang = i * M_PI / 180.0f;
   glBegin(GL_LINES);
       glVertex3f(0.0, 0.0, -1.0);
       glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); //Hace falta #include <math.h> para usar las funciones de seno y coseno
   glEnd();
}
    glFlush(); /*Forzar el renderizado*/
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);/*Activar las modificaciones en la camara*/
    glLoadIdentity(); /*Cargar la identidad en la matrix de proyección*/
    glOrtho(0, 0, 0, 0, 0, 0);
}

void idle(){
    display();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); /*Cargar el teclado y el ráton*/
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); /*inicializar el Frame Buffer*/
    glutInitWindowSize(WIDTH, HEIGTH); /*Tamaño de la ventana*/ 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); /*Posición del extremo superior-izquierdo de la ventana*/
    glutCreateWindow("Hola Mundo"); /* Crear la ventana*/
    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display); /*Activar la funcion de pintado*/
    glutReshapeFunc(reshape); /*Activar la funcion de escalado*/
    glutMainLoop(); /*Arrancar el bucle de OpenGL*/

    return 0;
}
