#include "Display.h"






void Display::
quit(){
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(handle);

}


void Display::
loadWindow(const std::string & t,int w,int h){
	title = t;
	width = w;
	height = h;
	handle = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (handle == NULL){
		return;
	}
	renderer = SDL_CreateRenderer(handle,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	if (renderer == NULL){
		SDL_DestroyWindow(handle);
		return;
	}

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		width,
		height
	);

	if (texture == NULL){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(handle);
		return;
	}

}

void Display::
loadFont(const std::string &t, uint32_t s){
	font = TTF_OpenFont(t.c_str(), 32);
	fontSize = s;
}

void Display::
setFramebuffer(uint32_t *fb,uint32_t _width, uint32_t _height){
	bufferLock.lock();
	framebuffer = fb;
	bufferLock.unlock();
	width = _width;
	height = _height;
}

void Display::
setFontColor(uint8_t r,uint8_t g, uint8_t b){
	textColor = {r,g,b};
}

uint32_t Display::
getFontSize(){
	return fontSize;
}

void Display::
clear(){
	SDL_RenderClear(renderer);
}

void Display::
render(){

	SDL_Surface *surf;
	SDL_Surface *surfScaled;
	SDL_Texture *tex;

	uint32_t amask,rmask,gmask,bmask;
	amask = 0xFF000000;
	rmask = 0x00FF0000;
	gmask = 0x0000FF00;
	bmask = 0x000000FF;

	bufferLock.lock();
	

	
	surf = SDL_CreateRGBSurfaceFrom((void*)framebuffer, width, height, 32, 4*width,
                                             rmask, gmask, bmask, amask);

	
	bufferLock.unlock();

	surfScaled = SDL_CreateRGBSurface(0,1920,1080,32,rmask,gmask,bmask,amask);

	SDL_BlitScaled(surf,NULL,surfScaled,NULL);

	tex = SDL_CreateTextureFromSurface(renderer,surf);	

	SDL_RenderCopy(renderer, tex, NULL, NULL);
	

	SDL_FreeSurface(surf);
	SDL_FreeSurface(surfScaled);
	SDL_DestroyTexture(tex);
}

void Display::
refresh(){
	SDL_RenderPresent(renderer);
}


void Display::
drawText(uint32_t startY, uint32_t startX, const char *text){
	SDL_Rect drect;
	drect.x = startX;
	drect.y = startY;
	drect.w = strlen(text) * fontSize;
	drect.h = fontSize;
	textSurface = TTF_RenderText_Blended(font, text ,textColor);
	textTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, &drect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

}



bool initSDL(){
	SDL_Init( SDL_INIT_EVERYTHING );
	TTF_Init();

}

void setVideoBuffer(std::unique_ptr<VideoBuffer> buffer){

}

void notifyRenderer(){

}

void renderLoop(){
	
}





