/*
 * Screen.cpp
 *
 * Author: CHANDRA BHANU
 */

#include "Screen.h"

namespace cbh {

	Screen::Screen():m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL){

	}
	bool Screen::init(){
		const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

		//initialize SDL
		if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
			return false;
		}

		//cout<<"SDL Init success !";

		// Creating a window in SDL
		m_window = SDL_CreateWindow("Particle Fire Explosion",
							SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		//checking if window created or not
		if(m_window == NULL){
			SDL_Quit();
			return false;
		}


		//the texture will be rendered by renderer.
		m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_PRESENTVSYNC );
		m_texture = SDL_CreateTexture( m_renderer, SDL_PIXELFORMAT_RGBA8888 ,
				SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT );

		//checking for failures and quitting
		if(m_renderer == NULL){
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		if(m_texture == NULL){
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}


		//memory for holding pixel color's RGB values
		m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
		m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

		//set the color of all pixels to white
		memset( m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32) );// 0xFF-white, 0-black
		memset( m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32) );

		return true;

	}

	void Screen::boxBlur(){

		//swap both buffers
		Uint32 *temp=m_buffer1;
		m_buffer1=m_buffer2;
		m_buffer2=temp;

		for(int y=0; y<SCREEN_HEIGHT; y++){
			for(int x=0; x<SCREEN_WIDTH; x++){

				/*BOX_BLUR
				 * 0 0 0
				 * 0 1 0
				 * 0 0 0
				 * set central pixel to be the average of pixels around it
				 * */

				int redTotal=0, greenTotal=0, blueTotal=0;

				//loop to get total RGB of surrounding pixels
				for(int row=-1; row<=1; row++){
					for(int col=-1; col<=1; col++){
						int currentX = x+col;
						int currentY = y+row;

						if(currentX>=0 && currentX<SCREEN_WIDTH && currentY>=0 &&currentY<SCREEN_HEIGHT){
							Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + x];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				//averaging the RGB values
				Uint8 red = redTotal/9;
				Uint8 green = greenTotal/9;
				Uint8 blue = blueTotal/9;

				setPixel(x, y, red, green, blue);

			}
		}
	}

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){

		//check for window overflow
		if(x<0 || x>= SCREEN_WIDTH || y<0 || y>= SCREEN_HEIGHT){
			return;
		}

		Uint32 color =0;
		color+=red;
		color<<=8;
		color+=green;
		color<<=8;
		color+=blue;
		color<<=8;
		color+=0xff; // opacity

		m_buffer1[ (y*SCREEN_WIDTH) + x ] = color;

	}

	void Screen::update(){
		//update the texture each time screen refreshes
		SDL_UpdateTexture( m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32) );
		SDL_RenderClear(m_renderer); // clear old renderer
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); // copy the updated texture to renderer
		SDL_RenderPresent(m_renderer);//now render the updated texture

	}

	bool Screen::processEvents(){

		SDL_Event event; // event is object of SDL_EVENT class

		//check for events and if quit event is encountered then set quit = true which will end the game loop
		while(SDL_PollEvent(&event)){
			if( event.type == SDL_QUIT ){
				return false;
			}
		}

		return true;
	}
	bool Screen::close(){
			delete[] m_buffer1;
			delete[] m_buffer2;
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyTexture(m_texture);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return true;
	}

} /* namespace cbh */
