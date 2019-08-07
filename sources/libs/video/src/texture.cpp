#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



Texture::Texture(const std::string &filename){
    int n;
    m_data = (unsigned int*)stbi_load(filename.c_str(), &m_width, &m_height, &n, 4);
}

Texture::Texture(int width,int height) :
    m_width(width),
    m_height(height),
    m_data(new unsigned int[width*height]){

}

Texture::~Texture(){
    if(m_data)
        delete[] m_data;
}