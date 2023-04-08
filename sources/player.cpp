#include "player.hpp"
#include <string>
using namespace std;
using namespace ariel;

int Player::getCount(){
    static int count=0;
    return count++;
}


Player::Player():_name("Player_" + std::to_string(Player::getCount())),_pdeck(),_cards_won(),_stats(){
}
Player::Player(const string &name):_name(name),_pdeck(),_cards_won(),_stats(){
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
const PlayerStats& Player::getStats() const{
    return _stats;
}
void Player::updateStats(int did_win, int did_draw){
    if(did_win!=0){
        _stats.wins++;
    }
    if(did_draw!=0){
        _stats.draws++;
    }
}
std::string Player::cardsWonRepr() const{
    std::string result = "";
    for (int i = 0; i < _cards_won.size(); i++) {
        result += _cards_won[static_cast<std::vector<Card>::size_type>(i)].printCard();
        if (i != _cards_won.size() - 1) {
            if ((i+1)%4==0) {
                result += ",\n";
            } else {
                result += ", ";
            }
        }
    }
    return result;
}