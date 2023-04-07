#include "player.hpp"
#include <string>
using namespace std;
using namespace ariel;

int Player::_count = 1;


Player::Player():_name("Player_" + std::to_string(_count)),_pdeck(),_cards_won(){
    ++_count;
}
Player::Player(const string &name):_name(name),_pdeck(),_cards_won(){
}

std::string Player::getPlayerName() const{
    return _name;
}
void Player::setName(const std::string& name){
    Player::_name=name;
}
int Player::stacksize() const{
    return _pdeck.size();
}
int Player::cardesTaken() const{
    return _cards_won.size();
}
void Player::addCard(const Card &card){
    _pdeck.push_back(card);
}
void Player::addCardsWon(const std::vector<Card>& cards){
    _cards_won.insert(_cards_won.end(), cards.begin(), cards.end());
}
ariel::Card Player::drawCard(){
    ariel::Card card = _pdeck.back();
    _pdeck.pop_back();
    return card;
}