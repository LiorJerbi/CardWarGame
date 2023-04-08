#pragma once
#include <string>
#include <vector>
#include "card.hpp"
namespace ariel{
    struct PlayerStats {
        int wins = 0;
        int draws = 0;
        };
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
        const PlayerStats& getStats() const;
        void updateStats(int did_win=0, int did_draw=0);
        std::string cardsWonRepr() const;

    private:
        std::string _name;
        std::vector <ariel::Card> _pdeck;
        std::vector <ariel::Card> _cards_won;
        static int getCount();
        PlayerStats _stats;
    };
}
