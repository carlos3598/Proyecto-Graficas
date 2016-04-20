//
//  Drawable.cpp
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#include "Drawable.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "imageloader.h"
#include "Drug.h"
#include "Juan.h"
#include "Hand.h"

Drawable::Drawable() {
    
    x = 0;
    y = 0;
    texture = -1;
    scaleX = 1.0;
    scaleY = 1.0;
    crash = false;
}

void Drawable::draw(GLuint texName) {
    if (!crash) {
        //glBindTexture(GL_TEXTURE_2D, texName);
        
        glPushMatrix();
        
        
        glTranslated(x, y, 0);
        glScalef(scaleX, scaleY, scaleZ);
//        GLUquadricObj *qobj;
//        qobj = gluNewQuadric();
//        gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
//        gluSphere(qobj, 0.75, 25, 20);
        
     //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_SGIS);//X
     //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_SGIS);//Y
        
        
        //Se selecciona la Textura
        glBindTexture(GL_TEXTURE_2D, texName);
        glColor3ub(0, 0, 0);

        glutSolidCube(1.2);

        glColor3ub(255, 255, 255);

        //Frente del cubo
        glBegin(GL_QUADS);
        //glNormal3f( 0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.6f, -.6f,  0.7f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f( .6f, -.6f,  0.7f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f( .6f,  .6f,  0.7f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.6f,  .6f,  0.7f);
        glEnd();
        
        
        
        glPopMatrix();
    }
}
bool Drawable::getCrash(){
    return crash;
}

float Drawable::getX() {
    return x;
}

float Drawable::getY() {
    return y;
}
void Drawable::setCrash(bool crash){
    this->crash = crash;
}
void Drawable::setX(float x) {
    this -> x = x;
}
void Drawable::setY(float y) {
    this -> y = y;
}