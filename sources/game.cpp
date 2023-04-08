#include "game.hpp"
#include <random>
#include <algorithm>
#include <iostream>
using namespace ariel;
    
//Constructor
Game::Game(Player& pl1,Player& pl2):_lst_turn(""),_table(),_p1(pl1),_p2(pl2),_turn_count(0){
    Game::makeDeck();
}
//Method that makes a new deck of 52 cards and splits them randomly between players.
void Game::makeDeck(){
    for (int i = 0; i < 4; i++) {   //Generate deck of 52 Cards of 4 Suits and 13 Ranks for each suit.
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
//Method to play turn of the game
void Game::playTurn(){
    if(_p1.getPlayerName() == _p2.getPlayerName()){     
        throw std::invalid_argument("Can't start a game with same player Or players with the same name!");
    }
    if(_p1.stacksize()==0||_p2.stacksize()==0){
        throw std::runtime_error("Error: Not enough cards to play turn!");
    }
    _lst_turn = "";
    _table.clear();
    while(_p1.stacksize() > 0 && _p2.stacksize() > 0){
        Card c1 = _p1.drawCard();
        Card c2 = _p2.drawCard();
        _table.push_back(c1);
        _table.push_back(c2);
        _lst_turn += _p1.getPlayerName() + " played " + c1.printCard() + " " + _p2.getPlayerName() + " played " + c2.printCard() + ". ";
        _turn_count++;
        if(c1.getIntRank() != c2.getIntRank()){
            if(c1.getIntRank() > c2.getIntRank()){
                _lst_turn += _p1.getPlayerName() + " Wins.";        //Player 1 Wins.
                _p1.addCardsWon(_table);
                _p1.updateStats(1,0);
            }
            else{
                _lst_turn += _p2.getPlayerName() + " Wins.";        //Player 2 Wins.
                _p2.addCardsWon(_table);
                _p2.updateStats(1,0);
            }
            _game_log += _lst_turn + "\n";
            return;
        }
        else{
            _lst_turn +=" Draw.";
            _p1.updateStats(0,1),_p2.updateStats(0,1);
            if(_p1.stacksize() > 0 && _p2.stacksize() > 0){     //Put 2 Cards upsidedown.
                _table.push_back(_p1.drawCard());
                _table.push_back(_p2.drawCard());
            }
            if((_p1.stacksize() == 0 || _p2.stacksize() == 0) && _table.size() > 0){  //If there is a draw and the cards of the players ended.
                //resplit the table cards between the players. 
                if(_table.size() == 2){
                    std::vector <ariel::Card> vc1,vc2;
                    vc1.push_back(_table.back());
                    _table.pop_back();
                    vc2.push_back(_table.back());
                    _table.pop_back();
                }
                else{
                    // std::cout << "ReShuffle War, Table size:" << _table.size() << "players stacks: " << _p1.stacksize() << _p2.stacksize() <<std::endl;
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
    else{throw std::logic_error("Draw!");}
}
void Game::printLog(){
    std::cout << _game_log;
}
void Game::printStats(){
    std::cout << "\n\n****** Players Stats ******" << std::endl;
    std::cout << "Player Name: " << _p1.getPlayerName() << std::endl;
    std::cout << "Turn's Won: " << _p1.getStats().wins << " Turn Win Rate: " << (static_cast<double>(_p1.getStats().wins)/_turn_count)*100 << "%" << std::endl;
    std::cout << "Draw's Count: " << _p1.getStats().draws << " Draw Rate: " << (static_cast<double>(_p1.getStats().draws)/_turn_count)*100 << "%" <<  std::endl;
    std::cout << "Cards Won: " << _p1.cardsWonRepr() << std::endl<< "Total: "<< _p1.cardesTaken() << std::endl;

    std::cout << "Player Name: " << _p2.getPlayerName() << std::endl;
    std::cout << "Turn's Won: " << _p2.getStats().wins << " Turn Win Rate: " << (static_cast<double>(_p2.getStats().wins)/_turn_count)*100 << "%" << std::endl;
    std::cout << "Draw's Count: " << _p2.getStats().draws << " Draw Rate: " << (static_cast<double>(_p2.getStats().draws)/_turn_count)*100 << "%" <<  std::endl;
    std::cout << "Cards Won: " << _p2.cardsWonRepr() << std::endl << "Total: "<< _p2.cardesTaken() << std::endl;
}
