#include "framebuffer.h"


Framebuffer::Framebuffer(uint32_t width_,uint32_t height_):
        width(width_),
        height(height_),
        data(new uint32_t[width*height]){
}

void Framebuffer::setPixel(uint32_t x,uint32_t y,uint32_t color){
    data[y*width+x] = color;
}