#include "my_objects.h"

void myTriangle(GLdouble side, GLdouble h, GLdouble depth){
    GLdouble pos = side / 2;
    GLdouble prof = depth / 2;
    
    glBegin(GL_TRIANGLES);
    // Front
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( 0.0f, h, prof);
        glVertex3f(-pos, 0.0f, prof);
        glVertex3f(pos, 0.0f, prof);
    // Back
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(0.0f, h, -prof);
        glVertex3f(-pos, 0.0f, -prof);
        glVertex3f(pos, 0.0f, -prof);
    glEnd();
    
    glBegin(GL_QUADS);
    // Right
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(0.0f, h, prof);
        glVertex3f(0.0f, h, -prof);
        glVertex3f(pos, 0.0f, -prof);
        glVertex3f(pos, 0.0f, prof);
    // Left
        glColor3f(1.0f, 1.0f, 0.0f);     // majenta
        glVertex3f( 0.0f, h, prof);
        glVertex3f( 0.0f, h, -prof);
        glVertex3f(-pos, 0.0f, -prof);
        glVertex3f(-pos, 0.0f, prof);
    // Bottom
        glColor3f(0.0f, 1.0f, 1.0f);     // majenta
        glVertex3f( pos, 0.0f,  -prof);
        glVertex3f( pos, 0.0f,  prof);
        glVertex3f(-pos, 0.0f, prof);
        glVertex3f(-pos, 0.0f, -prof);
    glEnd();
}

void myCylinder(GLdouble radius, GLdouble depth){
    glPushMatrix();
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
            qobj = gluNewQuadric();
            gluQuadricNormals(qobj, GLU_SMOOTH);
            gluCylinder(qobj, radius, radius, depth, 100, 150);
        glEnd();
    glPopMatrix();
}

void myPyramid(GLdouble side, GLdouble h){
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
        // Front
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( 0.0f, h, 0.0f);
        glVertex3f(-side, 0.0f, side);
        glVertex3f(side, 0.0f, side);
    
        // Right
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(0.0f, h, 0.0f);
        glVertex3f(side, 0.0f, side);
        glVertex3f(side, 0.0f, -side);
    
        // Back
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(0.0f, h, 0.0f);
        glVertex3f(side, 0.0f, -side);
        glVertex3f(-side, 0.0f, -side);
    
        // Left
        glColor3f(1.0f,0.0f,1.0f);       // Red
        glVertex3f( 0.0f, h, 0.0f);
        glVertex3f(-side, 0.0f,-side);
        glVertex3f(-side, 0.0f, side);
   glEnd();   
   glBegin(GL_QUADS);
        glColor3f(1.0f,1.0f,0.0f); 
        glVertex3f(-side, 0.0f,-side);
        glVertex3f(-side, 0.0f, side);
        glVertex3f(side, 0.0f, side);
      glVertex3f(side, 0.0f, -side);
   glEnd();
}

void myCircle(float radius, int lines, int depth){
    float i;
    float ang = 0.0f;

    lines = (lines<=360)?lines:360;

    for (i = 0; i <360; i += (360/lines)){
        ang = i * M_PI / 180.0f;
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
            glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
            glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth); 
            glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth);
            glVertex3f(0.0, 0.0, -depth);
        glEnd();
    }
    glBegin(GL_LINES);
    for (i = 0; i <360; i += (360/lines)){
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
        glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth); 
    }
    glEnd();
}

void myPolygone(float radius, int sides, int depth){
    float i;
    float ang = 0.0f;
    float incr = (sides<=360)?(360/sides):1;

    glColor3f( 1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (i = 0; i <360; i = i + incr){
        ang = i * M_PI / 180.0f;
        glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0); 
    }
    glEnd();

    for (i = 0; i <360; i = i + incr){
        glBegin(GL_QUADS);
            ang = i * M_PI / 180.0f;
            glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0);
            glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth);
            ang = (i+incr) * M_PI / 180.0f;
            glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth);
            glVertex3f(cos(ang)*radius, sin(ang)*radius, 0.0);
        glEnd();
    }

    glBegin(GL_POLYGON);
    for (i = i; i >=0; i = i - incr){
        ang = i * M_PI / 180.0f;
        glVertex3f(cos(ang)*radius, sin(ang)*radius, -depth); 
    }
    glEnd();
}
