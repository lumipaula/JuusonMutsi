#include "ivideo.h"

VideoBuffer::VideoBuffer(int width,int height) :
    m_width(width),
    m_height(height),
    m_info(new RenderInfo[m_width*m_height]){

}

VideoBuffer::~VideoBuffer(){
    if(m_info)
        delete[] m_info;
}