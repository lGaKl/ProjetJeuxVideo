#include "Deck.h"
#include <stdexcept>

void Deck::addCard(const Card& card){cards.push_back(card);}

Card Deck::drawCard(){
    if(cards.empty()){
        throw std::runtime_error("The deck is empty !");
    }
    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

bool Deck::isEmpty() const{return cards.empty();}
