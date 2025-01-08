#include "DeckEnemy.h"
#include <stdexcept>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
//The DeckEnemy class is similar to the Deck class but specifically represents the enemy's deck of cards in the game.
void DeckEnemy::addCard(const Card& card){cards.push_back(card);}

void DeckEnemy::shuffle() {
    // Use std::chrono to get a "time" as a different seed for each call
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);  // Mersenne Twister based random number generator

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


Card DeckEnemy::drawCard(){
    if(cards.empty()){
        throw std::runtime_error("The deck is empty !");
    }
    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

bool DeckEnemy::isEmpty() const{return cards.empty();}

 size_t DeckEnemy::size() const {
        return cards.size();
    }

const std::vector<Card>& DeckEnemy::getCard() const {
    return cards;
}

void DeckEnemy::clear() {
    cards.clear();
}
