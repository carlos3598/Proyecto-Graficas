//
//  Drug.cpp
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#include "Drug.h"

Drug::Drug() {
    scaleX = 0.15;
    scaleY = 0.15;
    scaleZ = 0.1;
    
}

void Drug::move(int direction){
    setX(getX() + 0.05 * direction);
}