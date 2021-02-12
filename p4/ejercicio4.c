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
#define CUERPO 2.0f

#define S_NONE 1.0f

// Variables globales 
int shift_clicked = 0;
int selected = 1;
int solid = 0;
int  auto_rotate = 0;
float speed = 0.5f;
int clicked_buton = 0;
float lastPosition = 0.0f;


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

T_rotXYZ brazoI = {
    x : 0.0f,
    y : 0.0f,
    z : 0.0f,
};

T_rotXYZ brazoD = {
    x : 0.0f,
    y : 0.0f,
    z : 0.0f,
};

T_rotXYZ piernaI = {
    x : 0.0f,
    y : 0.0f,
    z : 0.0f,
};

T_rotXYZ piernaD = {
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

    T_scale s_artic = {x: 0.50, y:0.50f, z:0.50f};
    T_scale s_hueso = {x: 0.50f, y:1.50f, z:0.50f};

    float xCorrect = myPCorrect(CUERPO, 2*ROTULA, S_NONE, s_artic.x);

    glPushMatrix();
        glTranslatef(-xCorrect, 0.0f, 0.0f);
        extremidad(brazoI, brazoI, s_artic, s_hueso, s_artic, s_hueso, myRotateXYZ, myRotateXYZ);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xCorrect, 0.0f, 0.0f);
        extremidad(brazoD, brazoD, s_artic, s_hueso, s_artic, s_hueso, myRotateXYZ, myRotateXYZ);
    glPopMatrix();

    glPushMatrix();
        glScalef(1.0f, 1.5f, 1.0f);
        glTranslatef(0.0f, -1.0f, 0.0f);
        myCube(CUERPO);
    glPopMatrix();

    glTranslatef(0.0f, -3.25f, 0.0f);

    glPushMatrix();
        glTranslatef(-0.5, 0.0f, 0.0f);
        extremidad(piernaI, piernaI, s_artic, s_hueso, s_artic, s_hueso, myRotateXYZ, myRotateXYZ);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5, 0.0f, 0.0f);
        extremidad(piernaD, piernaD, s_artic, s_hueso, s_artic, s_hueso, myRotateXYZ, myRotateXYZ);
    glPopMatrix();


    glFlush(); 
    // glutSwapBuffers();
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

void keyboard_especial(int z, int x, int y) {
    int modifiers = glutGetModifiers();
    printf("%d %d %d %d %d \n",modifiers, z,x,y, GLUT_ACTIVE_SHIFT);
    shift_clicked = (112 == z && (GLUT_ACTIVE_SHIFT));

}
void keyboard(unsigned char key, int x, int y) {
    
    switch(key) {
        case '1':
            selected = 1;
            break;
        case '2':
            selected = 2;
            break;
        case '3':
            selected = 3;
            break;
        case '4':
            selected = 4;
            break;
        case 'q':
            switch (selected)
                {
                case 1:
                    brazoI.x += speed;
                    break;
                case 2:
                    brazoD.x += speed;
                    break;
                case 3:
                    piernaI.x += speed;
                    break;
                case 4:
                    piernaD.x += speed;
                    break;
                }
            break;
        break;
        case 'a':
            switch (selected)
                {
                case 1:
                    brazoI.x -= speed;
                    break;
                case 2:
                    brazoD.x -= speed;
                    break;
                case 3:
                    piernaI.x -= speed;
                    break;
                case 4:
                    piernaD.x -= speed;
                    break;
                }
            break;
        case 'w':
            switch (selected)
                {
                case 1:
                    brazoI.y += speed;
                    break;
                case 2:
                    brazoD.y += speed;
                    break;
                case 3:
                    piernaI.y += speed;
                    break;
                case 4:
                    piernaD.y += speed;
                    break;
                }
            break;
        break;
        case 's':
            switch (selected)
                    {
                    case 1:
                        brazoI.y -= speed;
                        break;
                    case 2:
                        brazoD.y -= speed;
                        break;
                    case 3:
                        piernaI.y -= speed;
                        break;
                    case 4:
                        piernaD.y -= speed;
                        break;
                    }
                break;
            break;
        case 'e':
        switch (selected)
                {
                case 1:
                    brazoI.z += speed;
                    break;
                case 2:
                    brazoD.z += speed;
                    break;
                case 3:
                    piernaI.z += speed;
                    break;
                case 4:
                    piernaD.z += speed;
                    break;
                }
            break;
        break;
        case 'd':
        switch (selected)
                {
                case 1:
                    brazoI.z -= speed;
                    break;
                case 2:
                    brazoD.z -= speed;
                    break;
                case 3:
                    piernaI.z -= speed;
                    break;
                case 4:
                    piernaD.z -= speed;
                    break;
                }
            break;
        break;

        
    }
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
        case 3:
            auto_rotate = (auto_rotate)?0:1;
        case 4:
            speed = 0.25f;
            break;
        case 5:
            speed = 0.50f;
            break;
        case 6:
            speed = 1.0f;
            break;
    }

}

void createMenu(){
    int typeFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Wire",1);
    glutAddMenuEntry("Solid",2);

    int activateAutoMovement = glutCreateMenu(menu);
    glutAddMenuEntry("On/Off",3);

    int selectSpeed = glutCreateMenu(menu);
    glutAddMenuEntry("Slow",4);
    glutAddMenuEntry("Normal",5);
    glutAddMenuEntry("Fast",6);

    glutCreateMenu(menu);
    glutAddSubMenu("Type", typeFigure);
    glutAddSubMenu("Auto", activateAutoMovement);
    glutAddSubMenu("Speed", selectSpeed);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

void TimerFunction(){
    if(auto_rotate){
        piernaI.x+=speed;
        piernaD.x+=speed;
        piernaI.y+=speed;
        piernaD.y+=speed;
        piernaI.z+=speed;
        piernaD.z+=speed;
    }
    display();
    glutTimerFunc(1, TimerFunction, 1);
}

// Por defecto movemos pierna derecha con raton
// CON SHIFT movemos izquierda
void motion_func (int x, int y) {
    
        if (clicked_buton == GLUT_LEFT_BUTTON){
            if(y > lastPosition){
                if (shift_clicked){
                    piernaI.x+=speed;
                } else {
                    piernaD.x+=speed;
                }
                
                
            } else {
                if (shift_clicked){
                    piernaI.x-=speed;
                } else {
                    piernaD.x-=speed;
                }
                
            }
        }
            
    lastPosition = y;
}


void mouse_func(int but, int state, int x, int y){
    clicked_buton = but;
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_especial);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutTimerFunc(1000, TimerFunction,0);
    glutMainLoop();
    return 0;
}