//
//  Drawable.cpp
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#include "Drawable.h"

Drawable::Drawable() {
    
    x = 0;
    y = 0;
    texture = -1;
}

void Drawable::draw() {
    glPushMatrix();
        glScalef(0.3, 0.3, 0.1);
        glTranslated(x, y, 0);
        glutSolidCube(1);
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