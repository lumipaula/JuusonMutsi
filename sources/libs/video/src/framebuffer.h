#pragma once

#include <stdint.h>
#include "texture.h"


struct Framebuffer{
    unsigned int *data;
    int width,height;

    Framebuffer(int width_,int height_);
    void setPixel(int x,int y,unsigned int color);
    int getPixel(int x,int y){
        return data[y*width+x];
    }

    void drawTexture(const Texture &tex, int x, int y);

};