//-----------------------------------------------------------------------------
//  TD IHM
//  application.h
//-----------------------------------------------------------------------------

#ifndef APPLICATION_H
#define APPLICATION_H
#define largeur 1920
#define hauteur 1080

#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#endif // SFML_STATIC
#include <SFML/Graphics.hpp>
#include "snake.hpp"

int alea(int _min, int _max);

class Application
{
    public:
        Application();
        void run();
    protected:
        void processEvents();
        void update();
        void render();
    private:
         sf::RenderWindow * _window;
        Snake game;
 };
#endif

