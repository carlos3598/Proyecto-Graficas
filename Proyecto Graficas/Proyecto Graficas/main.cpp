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
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include "imageloader.h"
#include "Drug.h"
#include "Juan.h"
#include "Hand.h"
#include "PlaySound.h"
#include "SOIL.h"

using namespace std;



//Apuntadores a las lista

char msg[20];
Drug drugs[10][6];
Juan juan;
Hand hand;
int direction;
bool pause;
bool hasFired = false;
int score;
double posBackground;
double posCharacterY;
bool gameover = false;
int width = 640;
int height = 480;

//__FILE__ is a preprocessor macro that expands to full path to the current file.
string fullPath = __FILE__;
const int TEXTURE_COUNT = 18; //17

int state;
static GLuint texName[TEXTURE_COUNT];

PlaySound playSound;

void sound (int value){

    if (!pause) {
        playSound.playBackgroundMusic();
    }
    glutTimerFunc(40000,sound,0);
}

//le borramos el exceso para solo obtener el Path padre
void getParentPath()
{
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}

void drawText(float x, float y, std::string text, void* font, int r, int g, int b) {
    glColor3ub(r, g, b);
//    glRasterPos2f(x, y);
    glRasterPos3f(x, y, -1.0f);
    
    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

std::string toString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void initRendering()
{
    //Declaración del objeto Image
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    
    
    char  ruta[200];
    
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/welcome.bmp");
    texName[0] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/historia.bmp");
    texName[1] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Inicio.bmp");
    texName[2] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Instrucciones.bmp");
    texName[3] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Salir.bmp");
    texName[4] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/instrucciones_regresar.bmp");
    texName[5] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/instrucciones_iniciar.bmp");
    texName[6] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/maryjane.bmp");
    texName[7] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/molly.bmp");
    texName[8] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/shroom.bmp");
    texName[9] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/coke.bmp");
    texName[10] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/meth.bmp");
    texName[11] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/heroine.bmp");
    texName[12] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/hand.bmp");
    texName[13] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/juanito.bmp");
    texName[14] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/gameover.bmp");
    texName[15] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/gameover_exit.bmp");
    texName[16] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Pausa.bmp");
    texName[17] = SOIL_load_OGL_texture
    (
     ruta,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
}

//Initialize all the paramenters.
void init()
{
    pause = true;
    score = 0;
    posBackground = 0.1;
    posCharacterY = -1.4;
    gameover = false;
    
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
            drugs[i][j] = Drug();
            drugs[i][j].setX(i * 0.28 - 1.15);
            drugs[i][j].setY(j * 0.35);
        }
    }
    
    
    juan = Juan();
    juan.setX(0);
    juan.setY(posCharacterY);
    
    hand = Hand();
    hand.setX(0);
    hand.setY(posCharacterY);
    
    direction = 1;
    
}

//It Draws all the figures and textu                                     res.
void dibuja()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Menu State
    if (state < 7) {
        
        //Habilitar el uso de texturas
        glEnable(GL_TEXTURE_2D);
        
        //Elegir la textura del Quads: state cambia con el timer
        glBindTexture(GL_TEXTURE_2D, texName[state]);
        
        glBegin(GL_QUADS);
        //Asignar la coordenada de textura 0,0 al vertice
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-2.0f, -2.0f, 0);
        //Asignar la coordenada de textura 1,0 al vertice
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(2.0f, -2.0f, 0);
        //Asignar la coordenada de textura 1,1 al vertice
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(2.0f, 2.0f, 0);
        //Asignar la coordenada de textura 0,1 al vertice
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-2.0f, 2.0f, 0);
        glEnd();
        
    }
    //Game State
    else if (state == 7){
        
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        glEnable(GL_TEXTURE_2D);
        
        glPushMatrix();
        glRotated(-10, 1, 0, 0);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 6; j++) {
                drugs[i][j].draw(texName[j + 7]);
            }
        }
        
        //Cube Lines
        glPushMatrix();
        glColor3ub(0, 100, 36);
        glTranslated(posBackground, 1, 0);
        glScaled(3, 2.3, 0.15);
        glutWireCube(1);
        //glColor3ub(255, 255, 255);
        glPopMatrix();
        
        glPopMatrix();
        
        glPushMatrix();
        glRotated(-5, 1, 0, 0);
        hand.draw(texName[13]);
        juan.draw(texName[14]);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        
        //Background
        glPushMatrix();
        glColor3ub(36, 36, 36);
        glutSolidCube(4);
        glPopMatrix();
        glColor3ub(255, 255, 255);
    
        drawText(-1, -1, toString(score), GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);
        drawText(-2, -1, "Puntaje:", GLUT_BITMAP_HELVETICA_18, 255, 255, 255);

    }
    //Gameove State
    else if (state == 8 || state == 9) {
        
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        //Habilitar el uso de texturas
        glEnable(GL_TEXTURE_2D);
        
        
        //Elegir la textura del Quads: state cambia con el timer
        glBindTexture(GL_TEXTURE_2D, texName[state + 7]);
        
        glBegin(GL_QUADS);
        //Asignar la coordenada de textura 0,0 al vertice
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-2.0f, -2.0f, -1.5f);
        //Asignar la coordenada de textura 1,0 al vertice
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(2.0f, -2.0f, -1.5f);
        //Asignar la coordenada de textura 1,1 al vertice
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(2.0f, 2.0f, -1.5f);
        //Asignar la coordenada de textura 0,1 al vertice
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-2.0f, 2.0f, -1.5f);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
        
        //Background
        glColor3ub(255, 255, 255);
        
        
        drawText(-1.1, -1.2, toString(score), GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);
        
    }
    else if(state == 17){
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        //Habilitar el uso de texturas
        glEnable(GL_TEXTURE_2D);
        
        
        //Elegir la textura del Quads: state cambia con el timer
        glBindTexture(GL_TEXTURE_2D, texName[17]);
        
        glBegin(GL_QUADS);
        //Asignar la coordenada de textura 0,0 al vertice
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-4.2f, -4.2f, -1.5f);
        //Asignar la coordenada de textura 1,0 al vertice
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(4.2f, -4.2f, -1.5f);
        //Asignar la coordenada de textura 1,1 al vertice
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(4.2f, 4.2f, -1.5f);
        //Asignar la coordenada de textura 0,1 al vertice
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-4.2f, 4.2f, -1.5f);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
        
        //Background
        glColor3ub(255, 255, 255);
        
        
        drawText(-2.2, -2.1, toString(score), GLUT_BITMAP_TIMES_ROMAN_24, 255, 255, 255);
        
    }
    
    
    
    glutSwapBuffers();
}

void reshape(int ancho, int alto)
{
    if (state < 7 || state == 8 || state == 9 || state == 17) {
        // Ventana
        glViewport(0, 0, ancho, alto);
        // Sistema de coordenadas
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-2, 2, -2, 2,1,12 ); //izq, der, abajo, arriba, cerca, lejos
        //glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 12);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
    }
    else{
        // Ventana
        glViewport(0, 0, ancho, alto);
        // Sistema de coordenadas
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-2, 2, -2, 2,1,12 ); //izq, der, abajo, arriba, cerca, lejos
        glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 12);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 1.25, 0, 0, 0, 0, 1, 0);
    }
}

void changeState(int change){
    if (change > 0) {
        state++;
    }else{
        state--;
    }
    
    if (state >4) {
        state = 4;
    }
    
    if (state < 2) {
        state = 2;
    }
}

void JuanMovement(int tecla, int x, int y)
{
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            if (state == 5) {
                state = 6;
            }
            if (state == 7) {
                juan.setX(juan.getX() + 0.1);
                if (!hasFired) {
                    hand.setX(hand.getX() + 0.1);
                }
                if (juan.getX() > 1.8) {
                    juan.setX(1.8);
                    hand.setX(1.8);
                }
            }
            if (state == 8) {
                state = 9;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT :
            if (state == 6) {
                state = 5;
            }
            if (state == 7) {
                juan.setX(juan.getX() - 0.1);
                if (!hasFired) {
                    hand.setX(hand.getX() - 0.1);
                }
                if (juan.getX() < -1.8) {
                    juan.setX(-1.8);
                    hand.setX(-1.8);
                }
            }
            if (state == 9) {
                state = 8;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            if (state != 7 && state != 5 && state != 6 && state != 8 && state != 9) {
                changeState(-1);
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if (state != 7 && state != 5 && state != 6 && state != 8 && state != 9) {
                changeState(+1);
            }
            glutPostRedisplay();
            break;
        //Enter button.
        case 13:
            if (state == 2) {
                glutTimerFunc(0,sound,0);
                state = 7;
                reshape(width, height);
                pause = false;
            }
            else if (state == 3) {
                state = 5;
            }
            else if (state == 5) {
                state = 2;
            }
            else if (state == 4) {
                exit(-1);
            }
            else if (state == 6){
                glutTimerFunc(0,sound,0);
                state = 7;
                reshape(width, height);
                pause = false;
            }
            else if (state == 8) {
                init();
                glutPostRedisplay();
                pause = false;
                state = 7;
                reshape(width, height);
            }
            else if (state == 9) {
                exit(-1);
            }
            glutPostRedisplay();
            break;
        //Space Button
        case 32:
            hasFired = true;
            glutPostRedisplay();
            playSound.playSpaceBarSound();
            break;
        //Letter 'p' or 'P'.
        case 80:
        case 112:
            pause = !pause;
            if (state == 7) {
                state = 17;
            }
            else if (state == 17) {
                state = 7;
            }
            glutPostRedisplay();
            break;
        //Letter 'r' or 'R'.
        case 82:
        case 114:
            init();
            glutPostRedisplay();
            pause = false;
            break;
        //Esc button.
        case 27:
            exit(-1);
            break;
            
    }
}

void mytimer(int i){
    if (!pause) {
        bool crash = false;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 6; j++) {
                //Collides with walls.
                if(drugs[i][j].getX() > 1.8 || drugs[i][j].getX() < -1.8){
                    crash = true;
                    direction *= -1;
                    break;
                }
                //Collides with hand in X.
                if (hand.getX() > drugs[i][j].getX() - 0.25 && hand.getX() <  drugs[i][j].getX() + 0.25 ) {
                    //Collides with hand in Y.
                    if (hand.getY() > drugs[i][j].getY() -0.25 && hand.getY() < drugs[i][j].getY() + 0.25) {
                        if (!drugs[i][j].getCrash()) {
                            drugs[i][j].setCrash(true);
                            hasFired = false;
                            hand.setY(posCharacterY);
                            hand.setX(juan.getX());
                            
                            score += (j + 1) * 10;
                            playSound.playCrashSound();
                        }
                    }
                }
            }
        }
        
        if (!gameover) {
            if (score >= 50){
                gameover = true;
                state = 8;
                reshape(width, height);
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 6; j++) {
                drugs[i][j].move(direction);
            }
        }
        posBackground += 0.05 * direction;
        
        if (hasFired) {
            hand.setY(hand.getY() + 0.1);
        }
        if (hand.getY() > 2.5) {
            hasFired = false;
            hand.setY(posCharacterY);
            hand.setX(juan.getX());
        }
    }
    
    glutTimerFunc(100, mytimer, 1);
    glutPostRedisplay();
}

void history(int i){
    state = 2;
    glutTimerFunc(100, mytimer, 1);
    glutPostRedisplay();
}

void welcome(int i){
    state = 1;
    glutTimerFunc(10000, history, 1);
    glutPostRedisplay();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    getParentPath();
    glutCreateWindow("JUANTIDRUGS 2016");
    init();
    initRendering();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(reshape);
    glutSpecialFunc(JuanMovement);
    glutTimerFunc(5000, welcome, 1);
    glutMainLoop();
    return 0;
}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}





