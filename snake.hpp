#ifndef Snake_HPP
#define Snake_HPP
#define wlk_RIGHT 2
#define wlk_TOP 3
#define wlk_BOTTOM 0
#define wlk_LEFT 1
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include    <vector>
#define _EMPTY 0
#define _SNAKE 1
#define _FOOD 2
#define partSize 60
#define acceleration 0.98
class Snake{
    public:
        Snake();
        void setWalkingDirection(int tmp);
        void setWalking(bool tmp);
        void keyEvent(sf::Event event);
        void animate();
        void afficher(sf::RenderWindow * _window);
        void avance(sf::Vector2i nextPosition);
        void mange(sf::Vector2i nextPosition);
        bool isASnake();
        void lose();
        void changeEtatPart(sf::Vector2i position,int etat);
        void generateFood();
        void reinit();
    private:
        int walkingDirection;
        bool walking;
        int walkingStage;
        char ** part;
        std::vector<sf::Vector2i> corps;
        sf::Clock walkingTimer;
        sf::Vector2i foodPosition;
        sf::Vector2i taille;
        sf::RectangleShape partCorps;
        sf::CircleShape partFood;
        sf::Font font;
        sf::Text text;
        sf::Text text2;
        int lastWalkingDirection;
        int vitesse;
        bool loose;
};



#endif // Snake_HPP

