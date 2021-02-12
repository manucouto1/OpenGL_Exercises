#ifndef MOV_HEADERS
#define MOV_HEADERS
    
    #include <GL/gl.h>

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

    #define INIT_ROTATE (struct T_rot){ x : 0.0f, y : 0.0f, z : 0.0f};
    #define INIT_SCALE (struct T_scale){ x : 0.0f, y : 0.0f, z : 0.0f};
    #define INVERT_ROT(rot) (struct T_rot) {x: -rot.x, y: -rot.y, z: -rot.z}

    void myRotateX(float x);
    void myRotateY(float y);
    void myRotateZ(float z);
    void myRotateXYZ(T_rotXYZ direccion);

#endif