#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 400
#define HEIGTH 400
#define ORIGIN_X 100
#define ORIGIN_Y 100

#define ZBuffer 1
#define Wire 1

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}



void display()
{
    glClear((ZBuffer) ? GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT : GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    /* White Triangle
    glBegin(GL_POLYGON);
      glVertex3f(0.0f , .0f ,-1.0f ); //V1
      glVertex3f(2.0f , .0f , -1.0f ); //V2
      glVertex3f(1.0f , 2.0f , -1.0f ); //V3
    glEnd();
     */
    /* EXE Coordinates*/
    glBegin(GL_LINES);
        glVertex3f(-4.0f , .0f , .0f ); //V1
        glVertex3f(4.0f , .0f , .0f ); //V1
        glVertex3f(.0f , -4.0f , .0f ); //V1
        glVertex3f(.0f , 4.0f , .0f ); //V1
        glVertex3f(.0f , .0f , -20.0f ); //V1
        glVertex3f(.0f , .0f , 20.0f ); //V1
    glEnd();

    glRotatef(20.0f, .0f, .0f, 1.0f);
    glTranslatef(.20f, 0.0f, 0.0f);
    glScalef(1.0f, 2.0f, 1.0f);
    glRotatef(45.0f, .0f, .0f, 1.0f);

    glBegin(GL_LINES);
        glVertex3f(-4.0f , .0f , .0f ); //V1
        glVertex3f(4.0f , .0f , .0f ); //V1
        glVertex3f(.0f , -4.0f , .0f ); //V1
        glVertex3f(.0f , 4.0f , .0f ); //V1
        glVertex3f(.0f , .0f , -20.0f ); //V1
        glVertex3f(.0f , .0f , 20.0f ); //V1
    glEnd();
    // glColor3f( 1.0f, 0.0f, 0.0f);
    // (Wire)? glutWireTeapot(0.25f): glutSolidTeapot(0.25f);
    glColor3f( .0f, 1.0f, 0.0f);
    (Wire)? glutWireCube(0.25f): glutSolidCube(0.25f);
    // glColor3f( .0f, .0f, 1.0f);
    // (Wire)? glutWireSphere(.5f,40.0f,40.0f): glutSolidSphere(.5f,40.0f,40.0f);
    // glColor3f( 1.0f, .0f, 1.0f);
    // (Wire)? glutWireCone(.5f,2.0f,40.0f,40.0f): glutSolidCone(.5f,2.0f,40.0f,40.0f);
    // glColor3f( .0f, 1.0f, 1.0f);
    // (Wire)? glutWireTorus(.1f, .75f, 40.0f, 40.0f): glutSolidTorus(.1f, .75f, 40.0f, 40.0f);

    /*glBegin(GL_POLYGON);
        glColor3f( 1.0f, 0.0f, 0.0f);
        glVertex3f(.0f , .0f ,-1.0f ); //V1
        glVertex3f(2.0f , .0f , -1.0f ); //V2
        glVertex3f(2.0f , 2.0f , -1.0f ); //V3
        glVertex3f(.0f , 2.0f , -1.0f ); //V4
        glColor3f( 0.0f, 1.0f, 0.0f);
        glVertex3f(.0f , 2.0f , -2.0f ); //V4
        glVertex3f(2.0f , 2.0f , -2.0f ); //V3
        glVertex3f(2.0f , .0f , -2.0f ); //V2
        glVertex3f(.0f , .0f , -2.0f ); //V1
    glEnd();*/

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(5.0f); // Increse the point size to see the points easier
    /* Red Dots */
    glBegin(GL_POINTS);
      glVertex3f(.0f, .5f, -1.0f); //Point inside the triangle
      glVertex3f(2.25f, 1.75f, -2.0f); //Point outside the triangle
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 3.0, -1.0, 3.0, -20.0, 20.0); 
    glMatrixMode(GL_MODELVIEW);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); 
    glutInitDisplayMode((ZBuffer) ? GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH : GLUT_DOUBLE |GLUT_RGB); 
    glutInitWindowSize(WIDTH, HEIGTH);  
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y); 
    glutCreateWindow("Hola Mundo"); 
    init();
    glutDisplayFunc(display); 
    if (ZBuffer) { glEnable(GL_DEPTH_TEST); }
    glutReshapeFunc(reshape); 
    glutMainLoop(); 
    
    return 0;
}
