//-----------------------------------------------------------------------------
//  TD IHM
//  application.cpp
//-----------------------------------------------------------------------------

#include "application.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;


int alea(int _min, int _max){

    return rand()%(_max-_min+1)+_min;
}

Application::Application()
{

   ContextSettings settings;
   settings.antialiasingLevel=8;
    _window = new RenderWindow(VideoMode(largeur, hauteur), "TD2 IHM (SFML)",Style::Fullscreen,settings);


}

void Application::run()
{
    sf::Clock FPSController;
	while (_window->isOpen())
	{
		processEvents();
		update();

		render();

        while(FPSController.getElapsedTime().asMilliseconds()<16);
        FPSController.restart();

	}
}


void Application::processEvents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
        if (event.type == sf::Event::KeyPressed)
            switch(event.key.code)
            {
                case Keyboard::Escape :
                    _window->close();
                break;
                default:
                    break;
            }
        game.keyEvent(event);
	}




}

void Application::update()
{
    game.animate();
}

void Application::render()
{
	_window->clear();
	game.afficher(_window);
	_window->display();

}

