//
//  PlaySound.h
//  Proyecto Graficas
//
//  Created by Balbina Santana on 5/3/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#ifndef PlaySound_h
#define PlaySound_h

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
using namespace std;


#endif /* PlaySound_h */

class PlaySound {
    
    string path = "";
    string soundFilePath = __FILE__;
    Mix_Music *music;
    Mix_Chunk *backgroundMusic;
    Mix_Chunk *spaceBarSound;
    Mix_Chunk *crashSound;
    
public:
    
    PlaySound();
    void playSpaceBarSound();
    void playCrashSound();
    void playBackgroundMusic();
    string getAssetsPath();
    
};