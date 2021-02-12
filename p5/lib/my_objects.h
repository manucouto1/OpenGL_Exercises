#ifndef OBJ_HEADERS
#define OBJ_HEADERS

    #include <GL/glu.h>
    #include <GL/gl.h>
    #include <math.h>

    #define TR_HEIGTH(s) (GLdouble) s / 2 * sqrt(3)

    GLUquadric* qobj;

    void myTriangle(GLdouble side, GLdouble h, GLdouble depth);
    void myCylinder(GLdouble radius, GLdouble depth);
    void myPyramid(GLdouble side, GLdouble h);
    void myCircle(float radius, int lines, int depth);
    void myPolygone(float radius, int sides, int depth);

#endif

/*
GL_POINTS : para que todos los vértices indicados entre ambas funciones se dibujen por separado a modo de puntos "libres".
GL_LINES : cada dos vértices definidos, se traza automáticamente una línea que los une.
GL_POLYGON : se unen todos los vértices formando un polígono.
GL_QUADS : cada 4 vértices se unen para formar un cuadrilátero.
GL_TRIANGLES : cada 3 vértices se unen para formar un triángulo.
GL_TRIANGLE_STRIP : crea un triángulo con los 3 primeros vértices entonces sucesivamente crea un nuevo triángulo unido al anterior usando los dos últimos vértices que se han definido y el actual.
GL_QUAD_STRIP : igual que el anterior pero con cuadriláteros.

void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
void glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
void glutSolidCube(GLdouble size); 
void glutWireCube(GLdouble size);
void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks); 
void glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings); 
void glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);
void glutSolidDodecahedron(void); 
void glutWireDodecahedron(void);
void glutSolidOctahedron(void); 
void glutWireOctahedron(void);
void glutSolidTetrahedron(void); 
void glutWireTetrahedron(void);
void glutSolidIcosahedron(void); 
void glutWireIcosahedron(void);
void glutSolidTeapot(GLdouble size); 
void glutWireTeapot(GLdouble size);
*/