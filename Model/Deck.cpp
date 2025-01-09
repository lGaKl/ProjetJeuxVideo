#include "Deck.h"
#include <stdexcept>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

//The Deck class represents a deck of cards in the game.
//You can add cards, shuffle them, draw cards, and more.
void Deck::addCard(const Card& card){cards.push_back(card);}

void Deck::shuffle() {
    // Use std::chrono to get a "time" as a different seed for each call
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);   // Mersenne Twister based random number generator


    // Display the cards before shuffling
    std::cout << "Before shuffling: " << std::endl;
    for (const auto& card : cards) {
        std::cout << card.getName() << " ";
    }
    std::cout << std::endl;

    // Shuffle the cards using std::shuffle
    std::shuffle(cards.begin(), cards.end(), rng);

     // Display the cards after shuffling
    std::cout << "After shuffling: " << std::endl;
    for (const auto& card : cards) {
        std::cout << card.getName() << " ";
    }
    std::cout << std::endl;
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

const std::vector<Card>& Deck::getCard() const {
    return cards;
}

void Deck::clear() {
    cards.clear();
}
