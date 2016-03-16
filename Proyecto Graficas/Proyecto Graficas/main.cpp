//
//  main.cpp
//  Proyecto Graficas
//
//  Created by Carlos Salazar on 3/15/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
//Apuntadores a las lista

char msg[20];


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
    
    
}


void dibuja()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //First row
    double fRow = 7.0;
    while (fRow != -8) {
        glPushMatrix();
        glScalef(0.25, 0.25, 0.15);
        glTranslated(fRow, 6, 0);
        glutSolidCube(1);
        glPopMatrix();
        fRow = fRow - 1.5;
    }
    
    //Second row
    double sRow = 7.0;
    while (sRow != -8) {
        glPushMatrix();
        glScalef(0.25, 0.25, 0.15);
        glTranslated(sRow, 4.5, 0);
        glutSolidCube(1);
        glPopMatrix();
        sRow = sRow - 1.5;
    }
    
    //Third row
    double tRow = 7.0;
    while (tRow != -8) {
        glPushMatrix();
        glScalef(0.25, 0.25, 0.15);
        glTranslated(tRow, 3, 0);
        glutSolidCube(1);
        glPopMatrix();
        tRow = tRow - 1.5;
    }
    
    //Fourth row
    double fourRow = 7.0;
    while (fourRow != -8) {
        glPushMatrix();
        glScalef(0.25, 0.25, 0.15);
        glTranslated(fourRow, 1.5, 0);
        glutSolidCube(1);
        glPopMatrix();
        fourRow = fourRow - 1.5;
    }
    
    //Main Character
    glPushMatrix();
    glScalef(0.15, 0.15, 0.15);
    glTranslated(0, -12, 0);
    glutSolidSphere(1, 20, 20);
    
    glPushMatrix();
    glScalef(0.3, 0.4, 0.4);
    glTranslated(2, 2, 0);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    
    glPopMatrix();
    
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

void mytimer(int i){
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
    glutTimerFunc(100, mytimer, 1);
    glutMainLoop();
    return 0;
}