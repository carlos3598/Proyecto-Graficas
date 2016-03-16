//
//  Drawable.h
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Drawable {
    
public:
    void draw();
    Drawable();
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);

private:
    float x;
    float y;
    int texture;
    
};