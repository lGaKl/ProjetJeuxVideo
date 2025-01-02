#include "Deck.h"
#include <stdexcept>
#include <random>
#include <algorithm>
void Deck::addCard(const Card& card){cards.push_back(card);}

void Deck::shuffle() {
        // Créer un générateur de nombres aléatoires basé sur l'horloge
        std::random_device rd;
        std::default_random_engine rng(rd()); // g est le générateur

        // Mélanger les cartes avec std::shuffle
        std::shuffle(cards.begin(), cards.end(), rng);
    }

Card Deck::drawCard(){
    if(cards.empty()){
        throw std::runtime_error("The deck is empty !");
    }
    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

bool Deck::isEmpty() const{return cards.empty();}

 size_t Deck::size() const {
        return cards.size();
    }
