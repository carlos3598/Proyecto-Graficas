//
//  Drug.h
//  Proyecto Graficas
//
//  Created by Balbina Santana on 3/16/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#pragma once

#include "Drawable.h"

class Drug: public Drawable {
 
public:
    Drug();
    void move(int direction);
};

