#pragma once
#include <string>
#include <vector>
#include "card.hpp"
namespace ariel{
}
class Player{
public:

    Player();
    Player(const std::string &name);

    int stacksize() const;
    int cardesTaken() const;
    std::string getPlayerName() const;
    void setName(const std::string& name);
    void addCard(const ariel::Card &card);
    ariel::Card drawCard();
    void addCardsWon(const std::vector<ariel::Card>& cards);

private:
    std::string _name;
    std::vector <ariel::Card> _pdeck;
    std::vector <ariel::Card> _cards_won;
    static int _count;
};
