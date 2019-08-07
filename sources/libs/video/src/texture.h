#pragma once

#include <string>

struct Texture{

    int m_width,m_height;
    unsigned int *m_data;

    Texture(const std::string &filename);
    Texture(int width,int height);
    ~Texture();
};