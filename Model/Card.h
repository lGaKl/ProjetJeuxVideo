#ifndef CARD_H_
#define CARD_H_

#include <string>

class Card {
private:
    std::string name;
    std::string description;
    std::string type;

public:
    Card(const std::string& name, const std::string& description, const std::string& type);
    std::string getName() const;
    std::string getDescription() const;
    std::string getType() const;
};

#endif // CARD_H_
