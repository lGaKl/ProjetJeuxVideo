#include "GameView.h"
#include <iostream>

GameView::GameView() : window(sf::VideoMode(800,600), "Projet C++"){
    if(!font.loadFromFile("Assets/font.ttf")){
        throw std::runtime_error("Impossible to load font !");
    }
}

void GameView::render(const Player& player){
    window.clear(sf::Color::Black);

    window.display();
}

bool GameView::isWindowOpen() const{return window.isOpen();}
