#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck{
private:
    std::vector<Card> cards;

public:
    void addCard(const Card& card);
    Card drawCard();
    bool isEmpty() const;
};

#endif // DECK_H
