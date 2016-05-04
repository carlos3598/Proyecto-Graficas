//
//  PlaySound.cpp
//  Proyecto Graficas
//
//  Created by Balbina Santana on 5/3/16.
//  Copyright © 2016 Carlos Salazar. All rights reserved.
//

#include "PlaySound.h"

PlaySound::PlaySound(){
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(8);
    path = this->getAssetsPath();
    
    char backgroundMusicPath[300];
    sprintf(backgroundMusicPath,"%s%s", path.c_str() , "megaman8bit.wav");
    backgroundMusic = Mix_LoadWAV(backgroundMusicPath);
    
    char spaceBarSoundPath[300];
    sprintf(spaceBarSoundPath,"%s%s", path.c_str() , "pew.wav");
    spaceBarSound = Mix_LoadWAV(spaceBarSoundPath);
    
    char crashSoundPath[300];
    sprintf(crashSoundPath,"%s%s", path.c_str() , "Explosion.wav");
    crashSound = Mix_LoadWAV(crashSoundPath);
    
}

void PlaySound::playBackgroundMusic(){
    Mix_PlayChannel(1, backgroundMusic, 0);
}

void PlaySound::playSpaceBarSound(){
    Mix_PlayChannel(2, spaceBarSound, 0);
}

void PlaySound::playCrashSound(){
    Mix_PlayChannel(3, crashSound, 0);
}



string PlaySound::getAssetsPath(){
    if (path.length()) {
        return path;
    }
    // remove "PlaySound" from path
    for (int i = (int)soundFilePath.length()-1; i>=0 && soundFilePath[i] != '/'; i--) {
        soundFilePath.erase(i,1);
    }
    path = soundFilePath;
    return path;
}