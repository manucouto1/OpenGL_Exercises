#include "my_movement.h"

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

