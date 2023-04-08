#pragma once
#include <string>
#include <vector>
#include "card.hpp"
namespace ariel{
    //Struct to hold each player Stats.
    struct PlayerStats {
        int wins = 0;
        int draws = 0;
        };
    class Player{
    public:

    //Constructors
    Player();
    Player(const std::string &name);

    //Getters & Setters
    int stacksize() const;
    int cardesTaken() const;
    std::string getPlayerName() const;
    void setName(const std::string& name);
    const PlayerStats& getStats() const;
    void updateStats(int did_win=0, int did_draw=0);   

    //Method to control the deck & cards won deck.
    void addCard(const ariel::Card &card);
    ariel::Card drawCard();
    void addCardsWon(const std::vector<ariel::Card>& cards);
    std::string cardsWonRepr() const;

    private:
        std::string _name;
        std::vector <ariel::Card> _pdeck;
        std::vector <ariel::Card> _cards_won;
        static int getCount();
        PlayerStats _stats;
    };
}
