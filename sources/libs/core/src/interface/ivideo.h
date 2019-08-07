#pragma once

#include <mutex>
#include <condition_variable>

enum RenderType{
    TERRAIN,
    ENTITY,
    OBJECT,
    EFFECT
};


struct RenderInfo{
    RenderType m_type;
    int m_modelID;
    int m_x,m_y;
    //Action??
};

//Not really the video buffer perse but merely the information needed to render the game excluding UI 
class VideoBuffer{
private:
    int m_width,m_height;
    RenderInfo *m_info;

public:
    VideoBuffer(int width,int height);
    ~VideoBuffer();

    void addRenderObject();

};

class IVideo{
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
public:
    IVideo(){}
    ~IVideo(){}

    virtual void setVideoBuffer(std::unique_ptr<VideoBuffer> buffer){}
    virtual void notifyRenderer(){}
    virtual void renderLoop(){}

};