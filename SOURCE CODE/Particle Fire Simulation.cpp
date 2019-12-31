//============================================================================
// Name        : Particle.cpp
// Author      : CHANDRA BHANU
// Version     :
// Copyright   : All Rights Reserved
// Description : Particle Fire Simulator
//============================================================================

#include <iostream>
#include <string.h>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "Screen.h"
#include "Swarm.h"
using namespace cbh;

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Screen screen;

	if(!screen.init()){
		cout<<"error in initialization of screen !";
	}

	Swarm swarm;

	//loop stops when quit event occurs i.e, window is closed
	while(true){
		//update particles

		//Draw particles

		int elapsed = SDL_GetTicks(); // returns number of milliseconds passed


		swarm.update(elapsed); // particle animation

		// range of sin() = [ -1 , 1 ]
		unsigned char red = (unsigned char)( ( 1 + sin(elapsed*0.0001 ) ) * 128 ); // hue for red
		unsigned char green = (unsigned char)( ( 1 + sin(elapsed*0.0002 ) ) * 128 ); // hue for green
		unsigned char blue = (unsigned char)( ( 1 + sin(elapsed*0.0003 ) ) * 128 ); // hue for blue

		const Particle * const pParticles = swarm.getParticles();
		for(int i=0; i<Swarm::NPARTICLES; i++){
			Particle particle = pParticles[i];

			int x = ( particle.m_x + 1 ) * Screen::SCREEN_WIDTH/2;
			int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT / 2;

			screen.setPixel(x, y, red, green, blue);
		}


		screen.boxBlur();
		//Draw the screen
		screen.update();

		//Check for messages / Events
		if(screen.processEvents()==false){
			break;
		}
	}

	screen.close();

	return 0;



}
