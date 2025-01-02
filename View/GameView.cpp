#include "GameView.h"
#include <iostream>

GameView::GameView() : window(sf::VideoMode(800,600), "Projet C++"){

}

void GameView::render(const Player& player){
    window.clear(sf::Color::Black);

    window.display();
}

bool GameView::isWindowOpen() const{return window.isOpen();}
