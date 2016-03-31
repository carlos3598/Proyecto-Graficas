//
//  Drug.cpp
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#include "Drug.h"

Drug::Drug() {
    scaleX = 0.2;
    scaleY = 0.2;
    
}

void Drug::move(int direction){
    setX(getX() + 0.1 * direction);
}