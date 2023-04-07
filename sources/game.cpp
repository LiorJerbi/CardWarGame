#include "game.hpp"
#include <random>
#include <algorithm>
#include <iostream>
using namespace ariel;
    

Game::Game(Player& pl1,Player& pl2):_lst_turn(""),_table(),_p1(pl1),_p2(pl2){
    if(&pl1 != &pl2 && pl1.getPlayerName() != pl2.getPlayerName()){
    Game::makeDeck();
    std::cout << _p1.stacksize() << " Player 1 stacksize " << _p2.stacksize() << " Player 2 stacksize" << std::endl;
    }
    else{
        std::cout << "Can't start a game with only 1 Player Or With Players with the same name. Try again!" << std::endl;
    }
}

void Game::makeDeck(){
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            ariel::Suit suit = static_cast<ariel::Suit>(i);
            ariel::Rank rank = static_cast<ariel::Rank>(j);
            Card card(suit, rank);
            _deck.push_back(card);
        }
    }
    //Shuffle & Split the deck between the players.
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_deck.begin(),_deck.end(), g);
    int s=_deck.size();
    for(int i = 0; i < s/2; i++){
        _p1.addCard(_deck[static_cast<std::vector<Card>::size_type>(i)]);
    }
    for(int i = s/2; i < s; i++){
        _p2.addCard(_deck[static_cast<std::vector<Card>::size_type>(i)]);
    }
}


void Game::playTurn(){
    // std::cout << _p2.stacksize() << "stacksize" << std::endl;
    if(_p1.stacksize()==0||_p2.stacksize()==0){
        std::cout << "Error. Not enough cards to play turn!" << std::endl;
        return;
    }
    _lst_turn = "";
    _table.clear();
    while(_p1.stacksize() > 0 && _p2.stacksize() > 0){
        Card c1 = _p1.drawCard();
        Card c2 = _p2.drawCard();
        _table.push_back(c1);
        _table.push_back(c2);
        _lst_turn += _p1.getPlayerName() + " played " + c1.printCard() + " " + _p2.getPlayerName() + " played " + c2.printCard() + ". ";
        if(c1.getIntRank() != c2.getIntRank()){
            if(c1.getIntRank() > c2.getIntRank()){
                _lst_turn += _p1.getPlayerName() + " Wins.";        //Player 1 Wins.
                _p1.addCardsWon(_table);
            }
            else{
                _lst_turn += _p2.getPlayerName() + " Wins.";        //Player 2 Wins.
                _p2.addCardsWon(_table);
            }
            _game_log += _lst_turn + "\n";
            return;
        }
        else{
            _lst_turn +=" Draw.";
            if(_p1.stacksize() > 0 && _p2.stacksize() > 0){     //Put 2 Cards upsidedown.
                _table.push_back(_p1.drawCard());
                _table.push_back(_p2.drawCard());
            }
            if((_p1.stacksize() == 0 || _p2.stacksize() == 0) && _table.size() > 0){  //If there is a draw and the cards of the players ended.
                //resplit the table cards between the players. 
                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(_table.begin(),_table.end(), g);       
                int s=_table.size();
                for(int i = 0; i < s/2; i++){
                    _p1.addCard(_table[static_cast<std::vector<Card>::size_type>(i)]);
                }
                for(int i = s/2; i < s; i++){
                    _p2.addCard(_table[static_cast<std::vector<Card>::size_type>(i)]);
                }
                _table.clear();             
            }
        }
    }
}
void Game::printLastTurn(){
    std::cout << _lst_turn << std::endl;
}

void Game::playAll(){
    while(_p1.stacksize() > 0 && _p2.stacksize() > 0){
        Game::playTurn();
    }
}
void Game::printWiner(){
    if(_p1.cardesTaken() > _p2.cardesTaken()){std::cout << _p1.getPlayerName() << std::endl;}
    else if(_p1.cardesTaken() < _p2.cardesTaken()){std::cout << _p2.getPlayerName() << std::endl;}
    else{std::cout << "Draw!" << std::endl;}
}
void Game::printLog(){
    std::cout << _game_log << std::endl;
}
void Game::printStats(){
    return;
}
