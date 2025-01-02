#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck{
private:
    std::vector<Card> cards;

public:
    void addCard(const Card& card);
    void shuffle();
    Card drawCard();
    bool isEmpty() const;
    size_t size() const;
};

#endif // DECK_H
