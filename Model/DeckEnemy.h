#ifndef DECKENEMY_H
#define DECKENEMY_H

#include <vector>
#include "Card.h"

class DeckEnemy{
private:
    std::vector<Card> cards;

public:
    void addCard(const Card& card);
    void shuffle();
    Card drawCard();
    const std::vector<Card>& getCard() const;
    bool isEmpty() const;
    size_t size() const;
    void clear(); // Vide le deck
};

#endif // DECK_H
