#include "../sources/card.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace ariel;
    
std::string Card::getStringSuit() const{
    switch(_suit){
        case Suit::Clubs:
            return "Clubs";
        case Suit::Diamonds:
            return "Diamonds";
        case Suit::Hearts:
            return "Hearts";
        case Suit::Spades:
            return "Spades";
    }
}

std::string Card::getStringRank() const{    
    switch(_rank){
        case Rank::Ace:
            return "Ace";
        case Rank::Two:
            return "2";
        case Rank::Three:
            return "3";
        case Rank::Four:
            return "4";
        case Rank::Five:
            return "5";
        case Rank::Six:
            return "6";
        case Rank::Seven:
            return "7";
        case Rank::Eight:
            return "8";
        case Rank::Nine:
            return "9";
        case Rank::Ten:
            return "10";
        case Rank::Jack:
            return "Jack";
        case Rank::Queen:
            return "Queen";
        case Rank::King:
            return "King";
    }
}

Card::Card(){
    srand(time(nullptr));

    int suitInt = rand() % 4;
    _suit = static_cast<Suit>(suitInt); //Generates a random number from 0 to 3 to choose suit.
    int rankInt = (rand() % 13) + 1;
    _rank = static_cast<Rank>(rankInt); //Generates a random number from 1 to 13 to choose rank.
}
Card::Card(Suit suit, Rank rank){
    _suit=suit;
    _rank=rank;
}

//Getters & Setters:

std::string Card::getSuit() const{
    return Card::getStringSuit();
}
std::string Card::getRank() const{
    return Card::getStringRank();
}
Rank Card::getIntRank() const{
    return _rank;
}

void Card::setSuit(Suit suit){
    _suit=suit;
}
void Card::setRank(Rank rank){
    _rank=rank;
}

//Method that return repr of the card:
std::string Card::printCard(){ std::cout << getRank() << " of " << getSuit();}


