/*
 * Screen.h
 *
 *  Created on: 31-Dec-2019
 *      Author: KIIT
 */

#include<SDL.h>
#include<string.h>
#include<iostream>
using namespace std;

#ifndef SCREEN_H_
#define SCREEN_H_

namespace cbh {

class Screen {
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;
public:
	Screen();
	bool init();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	bool processEvents();
	bool close();
	void boxBlur();
};

} /* namespace cbh */

#endif /* SCREEN_H_ */
