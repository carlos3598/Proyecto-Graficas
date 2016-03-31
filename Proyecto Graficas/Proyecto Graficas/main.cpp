//
//  main.cpp
//  Proyecto Graficas
//
//  Created by Carlos Salazar on 3/15/16.
//  Authors: Balbina Santana A00812215
//           Carlos Salazar A00809015
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "Drug.h"
#include "Juan.h"
#include "Hand.h"
//Apuntadores a las lista

char msg[20];
Drug drugs[10][6];
Juan juan;
Hand hand;
int direction;


void init()
{
    glClearColor(0, 0.19, 0.4, 1);
    // Para que las paredes se vean sólidas (no transparentes)
    glEnable(GL_DEPTH_TEST);
    //Habilitar el arreglo de vértices
    glEnableClientState(GL_VERTEX_ARRAY);
    //glVertexPointer(3, GL_FLOAT, 0, vertices);
    
    //Habilitar el arreglo de colores
    glEnableClientState(GL_COLOR_ARRAY);
    //glColorPointer(3, GL_FLOAT,0, colores);
    
    sprintf(msg,"%s","Mensaje");
    //habilitar mezcla de transparencia
    glEnable(GL_BLEND);
    //cambiar el modo de mezcla
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            drugs[i][j].setX(i * 0.25 - 1.15);
            drugs[i][j].setY(j * 0.25 + 0.5);
        }
    }
    
    juan.setX(0);
    juan.setY(-1.7);
    
    hand.setX(0);
    hand.setY(-1.5);
    
    direction = 1;
    
}


void dibuja()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            drugs[i][j].draw();
        }
    }
    
    juan.draw();
    hand.draw();
    
    glutSwapBuffers();
}

void reshape(int ancho, int alto)
{
    // Ventana
    glViewport(0, 0, ancho, alto);
    // Sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2,1,12 ); //izq, der, abajo, arriba, cerca, lejos
    //glFrustum(-2, 2, -2, 2, 1, 12);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
}

void menu(unsigned char theKey, int mouseX, int mouseY)
{
    switch (theKey)
    {
        case 'p':
        case 'P':
            break;
        case 'b':
        case 'B':
            break;
        case 'D':
        case 'd':
            break;
        case 'E':
        case 'e':
            exit(-1);
            //terminate the program
        default:
            break;		      // do nothing
    }
}

void JuanMovement(int tecla, int x, int y)
{
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            juan.setX(juan.getX() + 0.1);
            hand.setX(hand.getX() + 0.1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT :
            juan.setX(juan.getX() - 0.1);
            hand.setX(hand.getX() - 0.1);
            glutPostRedisplay();
            break;
    }
}

void mytimer(int i){
    bool crash = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            if(drugs[i][j].getX() > 2 || drugs[i][j].getX() < -2){
                crash = true;
                direction *= -1;
                break;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            drugs[i][j].move(direction);
        }
    }
    glutTimerFunc(100, mytimer, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    glutCreateWindow("Proyecto Graficas");
    init();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(reshape);
    glutSpecialFunc(JuanMovement);
    glutKeyboardFunc(menu);
    glutTimerFunc(100, mytimer, 1);
    glutMainLoop();
    return 0;
}