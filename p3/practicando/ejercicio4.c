#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WIDTH 500
#define HEIGTH 500
#define ORIGIN_X 50
#define ORIGIN_Y 50

#define CABEZA 0.75f
#define ROTULA 0.5f
#define HUESO 1.0f
#define BODY 2.0f

#define S_NONE 1.0f //Scalate none
#define M_SPEED 10 //Velocidad manual

int solid = 0;
float speed = 0.5f;
int lastPosition = 0.0f;
int entryState = GLUT_LEFT;

int clicked_buton = 0;

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

//función para la rotación natural
float myTransferRotation(float x){
    float alpha = fmod(x, 90);
    float gamma  = fmod(x, 180);
    return abs((alpha == gamma)? alpha: (90 - alpha));
}

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

void extremidad(T_rotXYZ rot1, T_rotXYZ rot2, T_scale escale1a, T_scale escale1b, T_scale escale2a, T_scale escale2b,void (*func_rot1)(T_rotXYZ), void (*func_rot2)(T_rotXYZ)){
    
    float yCorrect = myPCorrect(2*ROTULA, HUESO, escale1a.y, escale1b.y);
    float yCorrect2 = myPCorrect(2*ROTULA, HUESO, escale2a.y, escale2b.y);

    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    articula(rot1, escale1a, escale1b, func_rot1); // Primera articulación

    glTranslatef(.0f, -yCorrect, 0.0f); // Desplazamos la segunda estructura
    
    glColor3f(0.0f, 1.0f, 1.0f); //cyan
    articula(rot2, escale2a, escale2b, func_rot1); // Segunda articulación

    glTranslatef(.0f, -yCorrect2, 0.0f); // Desplazamos la segunda estructura
    
    glPushMatrix();
        func_rot1( (struct T_rot){myTransferRotation(rot2.x), rot2.y, rot2.z} );
        glTranslatef(.0f, .0f, 0.5f);
        glScalef(escale1b.x*2, 1.0f, 3.0f);
        myCube(0.50);
    glPopMatrix();
}

void cabeza(){
    glPushMatrix();
        glTranslatef(0.0f, 0.75f, 0.0f);
        mySphere(CABEZA);
    glPopMatrix();
}

void brazos(){
    T_scale s_artic = {x: 0.75f, y:0.75f, z:0.75f};
    T_scale s_hueso = {x: 0.75f, y:1.25f, z:0.75f};

    float xCorrect = myPCorrect(BODY, 2*ROTULA, S_NONE, s_artic.x);
    
    glPushMatrix();
        glTranslatef(-xCorrect, 0.0f, 0.0f);
        extremidad(
            rotate1,
            rotate1,
            s_artic, s_hueso, s_artic, s_hueso, myRotateZZZ,myRotateZZZ
        );
    glPopMatrix();

    glPushMatrix();
        glTranslatef( xCorrect, 0.0f, 0.0f);
        extremidad(
            rotate2, rotate2,
            s_artic, s_hueso, s_artic, s_hueso, myRotateZZZ,myRotateZZZ
        );
    glPopMatrix();
}

void tronco(){
    glPushMatrix(); 
        glScalef(1.0f,1.5f,1.f);   
        glTranslatef(0.f,-1.f,0.f);
        myCube(BODY);
    glPopMatrix();
}

void piernas(){
    glTranslatef(0.0f, -3.5f, 0.0f);

    T_scale s_artic = {x: 1.0f, y:1.0f, z:1.0f};
    T_scale s_hueso = {x: 1.0f, y:1.5f, z:1.0f};

    float zeta1 = myTransferRotation(rotate1.x);
    float zeta2 = myTransferRotation(rotate2.x);

    // myRotateY(rotate1.y);

    glPushMatrix();
        glTranslatef(-0.5f, 0.0f, 0.0f);
        extremidad(
            (struct T_rot){x:-zeta1, y: 0.0f, z: 0.0f},
            (struct T_rot){x: zeta1, y: 0.0f, z: 0.0f},
            s_artic, s_hueso, s_artic, s_hueso, myRotateXXX, myRotateMinusXXX
        );
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5f, 0.0f, 0.0f);
        extremidad(
            (struct T_rot){x:-zeta2, y: 0.0f, z: 0.0f},
            (struct T_rot){x: zeta2, y: 0.0f, z: 0.0f},
            s_artic, s_hueso, s_artic, s_hueso, myRotateXXX, myRotateMinusXXX
        );
    glPopMatrix();
}

void motion_func (int x, int y) {
    
    switch (clicked_buton)
    {
        case GLUT_LEFT_BUTTON:
            if(y > lastPosition){
                rotate1.x+=speed;
            } else {
                rotate1.x-=speed;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(y > lastPosition){
                rotate2.x+=speed;
            } else {
                rotate2.x-=speed;
            }
            break;
    }
    
    lastPosition = y;
}

void entry_func(int state){
    entryState = state;
}

void mouse_func(int but, int state, int x, int y){
    clicked_buton = but;
}

// Movemos pierna1 Q-A
// Movemos Pierna2 W-S
// Movemos Brazo1  E-D
// Movemos Brazo2  R-F
void keyboard(unsigned char key, int x, int y) {
    
    switch(key) {
        case 'q':
            rotate1.x+=speed*M_SPEED;
            break;
        case 'a':
            rotate1.x-=speed*M_SPEED;
            break;
        case 'w':
            rotate2.x+=speed*M_SPEED;
            break;
        case 's':
            rotate2.x-=speed*M_SPEED;
            break;
        case 'e':
            rotate1.z+=speed*M_SPEED;
            break;
        case 'd':
            rotate1.z-=speed*M_SPEED;
            break;
        case 'r':
            rotate2.z+=speed*M_SPEED;
            break;
        case 'f':
            rotate2.z-=speed*M_SPEED;
            break;
    }
}

void menu(int value);

void menu (int value){
    switch (value)
    {
        case 1:
            solid = 0;
            break;
        case 2:
            solid = 1;
            break;
        case 3:
            speed = 0.25f;
            break;
        case 4:
            speed = 0.5f;
            break;
        case 5:
            speed = 1.0f;
            break;
    }

}

void createMenu(){
    int typeFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Wire",1);
    glutAddMenuEntry("Solid",2);

    int speedMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Low", 3);
    glutAddMenuEntry("Normal", 4);
    glutAddMenuEntry("High",5);

    glutCreateMenu(menu);
    glutAddSubMenu("Speed", speedMenu);
    glutAddSubMenu("Type", typeFigure);

    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3f(1.0f,0.0f,1.0f);
    glTranslatef(0.0f, 4.0f, 0.0f);

    cabeza();
    brazos();
    tronco();
    piernas();

    glFlush(); 
    glutSwapBuffers();

    if(entryState == GLUT_LEFT){
        rotate1.x = fmod(speed + rotate1.x, 180.0f);
        rotate2.x = abs(rotate1.x - 90);
    }
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
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion_func);
    glutEntryFunc(entry_func);
    glutMouseFunc(mouse_func);
    glutMainLoop();
    return 0;
}