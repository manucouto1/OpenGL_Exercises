#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

int mouseClicked = 0;

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

// Primera articulación
void figura(T_rotXYZ rot){
    glutWireSphere(0.5f,100,100); // Primera articulación
    glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rot.y, .0f, 1.0f, 0.0f);
    glRotatef(rot.z, .0f, 0.0f, 1.0f);
    
    glTranslatef(.0f,-1.0f, 0.0f); // Movemos el muslo y luego rotamos
    glutWireCube(1);
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);

    // Primera articulación
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    figura(rotate1);

    glTranslatef(.0f,-1.0f, 0.0f); // Movemos la segunda articulación
    
    // Segunda articulación
    glColor3f(0.0f, 1.0f, 1.0f); //cyan
    figura(rotate2);

    glFlush(); 
    glutSwapBuffers();
};

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    
    glOrtho(-6, 6, -6, 6, -6, 6);

    glMatrixMode(GL_MODELVIEW);
};

void mouseEv(int button, int state, int x, int y){
    mouseClicked = (button==GLUT_LEFT_BUTTON)?0:1;
}

// Si pulsamos el raton derecho movemos la segunda articulación
// Para volver a mover la primera tenemos que clicar el boton izquierdo
void keyboard(unsigned char key, int x, int y) {
    
    if(mouseClicked){
        switch(key) {
            case 'q':
                rotate2.x+=1.0f;
                break;
            case 'a':
                rotate2.x-=1.0f;
                break;
            case 'w':
                rotate2.y+=1.0f;
                break;
            case 's':
                rotate2.y-=1.0f;
                break;
            case 'e':
                rotate2.z+=1.0f;
                break;
            case 'd':
                rotate2.z-=1.0f;
                break;
        }
    } else {
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
        }
    }
}

void idle(){
    display();
}

void TimerFunction(){
    display();
    glutTimerFunc(45, TimerFunction, 1);
}

void init() {
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

int main( int argc, char **argv){
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(WIDTH, HEIGTH); 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);
    glutCreateWindow("Articulacion");
    init();
    glPushMatrix();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseEv);
    glutTimerFunc(1000, TimerFunction,0); 
    glutMainLoop();
    return 0;
}