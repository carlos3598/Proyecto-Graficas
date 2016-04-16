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
}

void Drawable::draw(GLuint texName) {
    GLUquadricObj *qobj;

    glBindTexture(GL_TEXTURE_2D, texName);
    glPushMatrix();
        qobj = gluNewQuadric();
        glTranslated(x, y, 0);
        glScalef(scaleX, scaleY, 0.1);
        gluQuadricDrawStyle(qobj, GLU_POINT); /* smooth shaded */
        gluSphere(qobj, 0.75, 25, 20);
        glutSolidSphere(1.0,10,10);
    glPopMatrix();
}

float Drawable::getX() {
    return x;
}

float Drawable::getY() {
    return y;
}

void Drawable::setX(float x) {
    this -> x = x;
}

void Drawable::setY(float y) {
    this -> y = y;
}