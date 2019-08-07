#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include <stdio.h>
#include <string.h>

#include "ivideo.h"


class Display : public IVideo{
private:

	//Clean me

	std::string title;
	uint32_t width, height;
	SDL_Window *handle;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *windowSurface;
	TTF_Font *font;
	SDL_Surface *textSurface;
	SDL_Texture *textTexture;
	uint32_t fontSize;
	SDL_Color textColor = {100,100,100};

	uint32_t *framebuffer;


	std::mutex bufferLock;
public:

	void loadWindow(const std::string &t,int w,int h);
	void loadFont(const std::string &t,uint32_t s);
	void setFontColor(uint8_t r,uint8_t g, uint8_t b);
	uint32_t getFontSize();
	void setFramebuffer(uint32_t *fb,uint32_t _width, uint32_t _height);
	void clear();
	void render();
	void refresh();
	void drawText(uint32_t startY, uint32_t startX, const char *text);
	void quit();

	void setVideoBuffer(std::unique_ptr<VideoBuffer> buffer) override;
    void notifyRenderer() override;
    void renderLoop() override;

};

bool initSDL();


#endif // DISPLAY_MANAGER_H