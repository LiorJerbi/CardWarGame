#pragma once
#include <string>
namespace ariel{
//Enums represents Suits and Ranks.
enum class Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};
enum class Rank {
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};
class Card{
public:

    //Constructors & Destructor:
    Card();
    Card(Suit suit, Rank rank);
    //Getters & Setters:

    std::string getSuit() const;
    std::string getRank() const;
    Rank getIntRank() const;

    void setSuit(Suit suit);
    void setRank(Rank rank);

    //Method to show the card:

    std::string printCard() const;


private:
    Suit _suit;
    Rank _rank;
    std::string getStringSuit() const;
    std::string getStringRank() const;

};

}
