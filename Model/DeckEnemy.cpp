#include "DeckEnemy.h"
#include <stdexcept>
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
void DeckEnemy::addCard(const Card& card){cards.push_back(card);}

void DeckEnemy::shuffle() {
    // Utiliser std::chrono pour obtenir un "temps" comme graine différente à chaque appel
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);  // Générateur de nombres aléatoires basé sur Mersenne Twister

    // Afficher les cartes avant le mélange
    std::cout << "Avant le mélange : " << std::endl;
    for (const auto& card : cards) {
        std::cout << card.getName() << " ";
    }
    std::cout << std::endl;

    // Mélanger les cartes avec std::shuffle
    std::shuffle(cards.begin(), cards.end(), rng);

    // Afficher les cartes après le mélange
    std::cout << "Après le mélange : " << std::endl;
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
    return cards;  // Retourner une référence constante vers le vecteur de cartes
}
