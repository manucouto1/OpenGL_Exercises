#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Constantes
#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

#define ROTULA 0.5f
#define HUESO 1.0f

#define S_NONE 1.0f


// Variables globales 
float speed = 0.5f;

int solid = 0;
int lastPositionX = 0.0f;
int lastPositionY = 0.0f;

struct T_rot {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} typedef T_rotXYZ;

struct T_scale {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} typedef T_scale;

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

//función para rotar en el eje X
void myRotateX(float x){
    glRotatef(x, 1.0f, 0.0f, 0.0f);
}

//función para rotar en el eje Y
void myRotateY(float y){
    glRotatef(y, .0f, 1.0f, 0.0f);
}

//función para rotar en el eje Z
void myRotateZ(float z){
    glRotatef(z, .0f, 0.0f, 1.0f);
}

//función para rotar en los 3 ejes
void myRotateXYZ(T_rotXYZ direccion){
    if(direccion.x != 0.0f){
        myRotateX(direccion.x);
    }
    if(direccion.y != 0.0f){
        myRotateY(direccion.y);
    }
    if(direccion.z != 0.0f){
        myRotateZ(direccion.z);
    }
}

void myRotateXXX(T_rotXYZ direccion){
    myRotateX(direccion.x);
}

void myRotateMinusXXX(T_rotXYZ direccion){
    myRotateX(-direccion.x);
}

void myRotateYYY(T_rotXYZ direccion){
    myRotateY(direccion.y);
}

void myRotateMinusYYY(T_rotXYZ direccion){
    myRotateY(-direccion.y);
}

void myRotateZZZ(T_rotXYZ direccion){
    myRotateZ(direccion.z);
}
void myRotateMinusZZZ(T_rotXYZ direccion){
    myRotateZ(-direccion.z);
}

// Correje la posición en función del estirado en un eje determinado
float myPCorrect(float tam1, float tam2, float scale1, float scale2){
    return (tam1*scale1 + tam2*scale2)/(2.0f);
}

void mySphere(float rSize){
    if(solid){
        glutSolidSphere(rSize,10,10); 
    } else {
        glutWireSphere(rSize,10,10);  
    }
}

void myCube( float lSize){
    if(solid){
        glutSolidCube(lSize);
    } else {
        glutWireCube(lSize);
    }
}

// Extremidad
void articula(T_rotXYZ rot, T_scale scale_rotula, T_scale scale_hueso, void (*func_rot)(T_rotXYZ)){

    float yCorrect = myPCorrect(2*ROTULA, HUESO, scale_rotula.y, scale_hueso.y);

    glPushMatrix(); // Transformaciones especificas parte articulación Rotula
        glScalef(scale_rotula.x, scale_rotula.y, scale_rotula.z);
        mySphere(ROTULA);
    glPopMatrix();
    
    func_rot(rot);
    glTranslatef(0.0f,-yCorrect, 0.0f); // Colocamos el huso con posición corregida
    
    glPushMatrix(); // Transformaciones específicas parte articulada Hueso
        glScalef(scale_hueso.x, scale_hueso.y,scale_hueso.z);
        myCube(HUESO);
    glPopMatrix();

};

void extremidad(T_rotXYZ rot1, T_rotXYZ rot2, T_scale escale1a, T_scale escale1b, T_scale escale2a, T_scale escale2b, void (*func_rot1)(T_rotXYZ), void (*func_rot2)(T_rotXYZ)){
    
    float yCorrect = myPCorrect(2*ROTULA, HUESO, escale1a.y, escale1b.y);
    float yCorrect2 = myPCorrect(2*ROTULA, HUESO, escale2a.y, escale2b.y);

    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    articula(rot1, escale1a, escale1b, func_rot1); // Primera articulación

    glTranslatef(.0f, -yCorrect, 0.0f); // Desplazamos la segunda estructura
    
    glColor3f(0.0f, 1.0f, 1.0f); //cyan
    articula(rot2, escale2a, escale2b, func_rot2); // Segunda articulación

}


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f,0.0f,1.0f);
    glTranslatef(0.0f, 4.0f, 0.0f);

    T_scale s_artic = {x: 0.75f, y:0.75f, z:0.75f};
    T_scale s_hueso = {x: 0.75f, y:1.25f, z:0.75f};

    float xCorrect = myPCorrect(2.0f, 2*ROTULA, S_NONE, s_artic.x);

    glPushMatrix();
        glTranslatef(-xCorrect, 0.0f, 0.0f);
        extremidad(rotate1, rotate2, s_artic, s_hueso, s_artic, s_hueso, myRotateZZZ, myRotateZZZ);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xCorrect, 0.0f, 0.0f);
        extremidad(rotate1, rotate2, s_artic, s_hueso, s_artic, s_hueso, myRotateZZZ, myRotateZZZ);
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0f, 1.5f, 1.0f);
        glTranslatef(0.0f, -1.0f, 0.0f);
        myCube(2.0f);
    glPopMatrix();

    glTranslatef(0.0f, -3.5f, 0.0f);

    s_artic = (struct T_scale){x: 1.0f, y:1.0f, z:1.0f};
    s_hueso = (struct T_scale){x: 1.0f, y:1.5f, z:1.0f};

    glPushMatrix();
        glTranslatef(-0.5, 0.0f, 0.0f);
        extremidad(rotate1, rotate2, s_artic, s_hueso, s_artic, s_hueso, myRotateXXX, myRotateMinusXXX);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5, 0.0f, 0.0f);
        extremidad(rotate1, rotate2, s_artic, s_hueso, s_artic, s_hueso, myRotateXXX, myRotateMinusXXX);
    glPopMatrix();

    glFlush(); 
    glutSwapBuffers();
};

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 6, -6, 6, -6, 6);
    glMatrixMode(GL_MODELVIEW); 
};

void idle(){
    display();
}

void init() {
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
}

void motion_func (int x, int y) {

    if(x > lastPositionX){
        rotate1.z+=speed;
        rotate2.z+=speed;
    } else {
        rotate1.z-=speed;
        rotate2.z-=speed;
    }

    if(y > lastPositionY){
        rotate1.x+=speed;
        rotate2.x+=speed;
    } else {
        rotate1.x-=speed;
        rotate2.x-=speed;
    }

    lastPositionX = x;
    lastPositionY = y;
}

void menu (int value){
    switch (value)
    {
        case 1:
            solid = 0;
            break;
        case 2:
            solid = 1;
            break;
    }

}

void createMenu(){
    int typeFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Wire",1);
    glutAddMenuEntry("Solid",2);

    glutCreateMenu(menu);
    glutAddSubMenu("Type", typeFigure);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

int main( int argc, char **argv){
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(WIDTH, HEIGTH); 
    glutInitWindowPosition(ORIGIN_X, ORIGIN_Y);
    glutCreateWindow("Monigote");
    init();
    createMenu();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion_func);
    glutMainLoop();
    return 0;
}