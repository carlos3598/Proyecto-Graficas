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
#include <stdio.h>
#include "imageloader.h"
#include "Drug.h"
#include "Juan.h"
#include "Hand.h"
using namespace std;

//Apuntadores a las lista

char msg[20];
Drug drugs[10][6];
Juan juan;
Hand hand;
int direction;
bool pause;

//__FILE__ is a preprocessor macro that expands to full path to the current file.
string fullPath = __FILE__;
const int TEXTURE_COUNT=3;

int state=0;
static GLuint texName[TEXTURE_COUNT];

//le borramos el exceso para solo obtener el Path padre
void getParentPath()
{
    for (int i = (int)fullPath.length()-1; i>=0 && fullPath[i] != '/'; i--) {
        fullPath.erase(i,1);
    }
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //Filtros de ampliacion y redución con cálculo mas cercano no es tan bueno pero es rápido
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    //Filtros de ampliacion y redución con cálculo lineal es mejo pero son más calculos
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}

void initRendering()
{
    //Declaración del objeto Image
    Image* image;
    GLuint i=0;
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(TEXTURE_COUNT, texName); //Make room for our texture
    
    
    char  ruta[200];
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Inicio.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Instrucciones.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    sprintf(ruta,"%s%s", fullPath.c_str() , "Texturas/fondo_Salir.bmp");
    image = loadBMP(ruta);loadTexture(image,i++);
    
    
    delete image;
}


void init()
{
    pause = false;
    
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
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (state < 3) {
        
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
    }else{
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 6; j++) {
                drugs[i][j].draw();
            }
        }
        
        juan.draw();
        hand.draw();
    }

    
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
    gluLookAt(0, 0, 1.1, 0, 0, 0, 0, 1, 0);
}

void changeState(int change){
    if (change > 0) {
        state++;
    }else{
        state--;
    }
    
    if (state >2) {
        state = 2;
    }
    
    if (state < 0) {
        state = 0;
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
        case GLUT_KEY_UP:
            if (state != 3) {
                changeState(-1);
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if (state != 3) {
                changeState(+1);
            }
            glutPostRedisplay();
            break;
        case 13:
            if (state == 0) {
                state = 3;
                glutPostRedisplay();
            }
            if (state == 2) {
                exit(-1);
            }
            break;
        //Letter 'p' or 'P'
        case 80:
        case 112:
            pause = !pause;
            glutPostRedisplay();
            break;
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
    }
    glutTimerFunc(100, mytimer, 1);
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH| GLUT_DOUBLE );
    getParentPath();
    glutCreateWindow("Proyecto Graficas");
    init();
    initRendering();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(reshape);
    glutSpecialFunc(JuanMovement);
    glutTimerFunc(100, mytimer, 1);
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





