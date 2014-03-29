#include "snake.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "snake.hpp"
#include "application.hpp"
using namespace sf;
using namespace std;


Snake::Snake()
{
    walkingDirection=lastWalkingDirection=-1;
    walking = loose = false;
    if(!font.loadFromFile("Unionform.ttf"))
        cout << "Erreur lors de la lecture d'un fichier" << endl;

    text.setFont(font);
    text2.setFont(font);
    text.setColor(sf::Color(100,0,50));
    text2.setColor(sf::Color(125,0,150));

    text.setCharacterSize(75);
    text.setString("Game Over");
    text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
    text.setPosition(largeur/2,hauteur/2 - 80);

    text2.setCharacterSize(40);
    text2.setString("Appuyer sur ESPACE pour rejouer");
    text2.setOrigin(text2.getGlobalBounds().width/2,text2.getGlobalBounds().height/2);
    text2.setPosition(largeur/2,hauteur/2 + text.getGlobalBounds().height + 40 );

    vitesse = 300;

    srand(time(0));

    taille.x = largeur/partSize;
    taille.y = hauteur/partSize;

    part = new char*[taille.x];


    partCorps.setFillColor(sf::Color::White);
    partCorps.setSize(Vector2f(partSize,partSize));
    partFood.setFillColor(sf::Color::Red);
    partFood.setRadius(partSize/4);

    partFood.setOrigin(-partSize/4,-partSize/4);

    for(int i=0;i<taille.x;i++)
        part[i] = new char[taille.y];

    for(int i=0;i<taille.x;i++)
        for(int j=0;j<taille.y;j++)
            part[i][j]=_EMPTY;
    Vector2i tmp =Vector2i(alea(0,taille.x-1),alea(0,taille.y-1));
    corps.push_back(tmp);
    changeEtatPart(corps[0],_SNAKE);

    generateFood();
}

void Snake::reinit(){
    walkingDirection=lastWalkingDirection=-1;
    walking = false;

    vitesse = 300;

    for(int i=0;i<taille.x;i++)
        for(int j=0;j<taille.y;j++)
            part[i][j]=_EMPTY;
    Vector2i tmp =Vector2i(alea(0,taille.x-1),alea(0,taille.y-1));

    while(corps.size()>0) corps.pop_back();

    corps.push_back(tmp);
    changeEtatPart(corps[0],_SNAKE);

    generateFood();
}

void Snake::keyEvent(Event event)
{

        if (event.type == sf::Event::KeyPressed){
            switch(event.key.code)
            {
                case Keyboard::Up :
                    if( lastWalkingDirection!=wlk_BOTTOM && !loose){
                    walkingDirection=wlk_TOP;
                    walking = true;
                    }
                break;
                case Keyboard::Down :
                     if( lastWalkingDirection!=wlk_TOP && !loose){
                    walkingDirection=wlk_BOTTOM;
                    walking = true;
                     }
                break;
                case Keyboard::Left :
                     if( lastWalkingDirection!=wlk_RIGHT && !loose){
                    walkingDirection=wlk_LEFT;
                    walking = true;
                     }
                break;
                case Keyboard::Right :
                     if( lastWalkingDirection!=wlk_LEFT && !loose){
                    walkingDirection=wlk_RIGHT;
                    walking = true;
                     }
                break;
                 case Keyboard::Space :
                     if(loose){
                        reinit();
                        loose = false;
                     }
                break;
                default:
                break;
            }

        }
}

void Snake::animate()
{
    if(walking&&walkingTimer.getElapsedTime().asMilliseconds()>vitesse){
            lastWalkingDirection = walkingDirection;
            walkingTimer.restart();
            Vector2i nextPosition = corps[0];
        switch(walkingDirection){
            case wlk_BOTTOM:
                nextPosition.y ++;
            break;
            case wlk_TOP:
                nextPosition.y --;
            break;
            case wlk_RIGHT:
                nextPosition.x ++;
            break;
            case wlk_LEFT:
                nextPosition.x --;
            break;

        }
        if(nextPosition.x<0
           ||nextPosition.x>=taille.x
           || nextPosition.y<0
           ||nextPosition.y>=taille.y)
            lose();
        else
         switch(part[nextPosition.x][nextPosition.y])
         {
                case _EMPTY :
                    avance(nextPosition);
                break;
                case _FOOD :
                    mange(nextPosition);
                break;
                case _SNAKE :
                    lose();
                break;
                default:
                    lose();
                break;
         }
    }

}

void Snake::afficher(sf::RenderWindow * _window){
    int colorByQuad = 200/corps.size();
    for(int i=0;i<corps.size();i++){
        partCorps.setFillColor(Color(10,255-(i*colorByQuad),10));
        partCorps.setPosition(Vector2f(corps[i].x*partSize,corps[i].y*partSize));
        _window->draw(partCorps);
    }
    _window->draw(partFood);
    if(loose){
            RectangleShape tmp;
    tmp.setFillColor(Color(50,0,0,127));
    tmp.setPosition(0,0);
    tmp.setSize(Vector2f(largeur,hauteur));
        _window->draw(tmp);
        _window->draw(text);
        _window->draw(text2);
    }
}

void Snake::setWalkingDirection(int tmp)
{
        walkingDirection = tmp;
}

void Snake::setWalking(bool tmp)
{
    if(!tmp)
    walking=tmp;

}

void Snake::lose()
{
    loose = true;

}

void Snake::avance(Vector2i nextPosition){
    changeEtatPart(corps[corps.size()-1],_EMPTY);
    corps[corps.size()-1]=nextPosition;
    for(int i=0;i<corps.size()-1;i++)
        swap(corps[i],corps[corps.size()-1]);
    changeEtatPart(corps[0],_SNAKE);
}

void Snake::mange(Vector2i nextPosition){

    corps.push_back(nextPosition);

    for(int i=0;i<corps.size()-1;i++)
        swap(corps[i],corps[corps.size()-1]);
    changeEtatPart(corps[0],_SNAKE);
    generateFood();

    vitesse*=acceleration;
    cout << vitesse << endl;
}

void Snake::changeEtatPart(sf::Vector2i position,int etat){
    part[position.x][position.y] = etat;
}

void Snake::generateFood(){
    foodPosition = Vector2i(alea(0,taille.x-1),alea(0,taille.y-1));

    while(part[foodPosition.x][foodPosition.y]!=_EMPTY)
        foodPosition = Vector2i(alea(0,taille.x-1),alea(0,taille.y-1));

    changeEtatPart(foodPosition,_FOOD);

    partFood.setPosition(Vector2f(foodPosition.x*partSize,foodPosition.y*partSize));
}
