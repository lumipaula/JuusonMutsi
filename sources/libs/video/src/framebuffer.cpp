#include "framebuffer.h"


Framebuffer::Framebuffer(int width_,int height_):
        width(width_),
        height(height_),
        data(new unsigned int[width*height]){
}

void Framebuffer::setPixel(int x,int y,unsigned int color){
    data[y*width+x] = color;
}

void Framebuffer::drawTexture(const Texture &tex, int x,int y){
    //Don't go over borders
    int y0 = std::min(height,y+tex.m_height);
    int x0 = std::min(width,x+tex.m_width);
    for(int i=y; i<y0; i++){
        for(int j=x; j<x0; j++){
            
        }
    }
}