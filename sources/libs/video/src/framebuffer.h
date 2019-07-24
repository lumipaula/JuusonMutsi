#pragma once

#include <stdint.h>

struct Framebuffer{
    uint32_t *data;
    uint32_t width,height;

    Framebuffer(uint32_t width_,uint32_t height_);
    void setPixel(uint32_t x,uint32_t y,uint32_t color);
    uint32_t getPixel(uint32_t x,uint32_t y){
        return data[y*width+x];
    }
};