#include "Game.h"
#include "ComputerPlayer.h"
#include <cassert>

ComputerPlayer::ComputerPlayer(Player& p) : Player(p){}

std::pair<Card*, std::string> ComputerPlayer::autoPlay(std::vector<Card*> & played_cards){
    const std::vector<Card*> plays = legalMoves(played_cards);
    assert(hand_.size() != 0);
    if(plays.size() == 0){
        Card* discarded = *hand_.begin();
        discardCard( **hand_.begin(), played_cards );
        return {discarded, "discards"};
    }

    Card* played = plays[0];
    playCard( *played, played_cards );
    return {played, "plays"};
}

GameState ComputerPlayer::getTurnState() const {
    if (hand_.size() == 0) {
        return GameState::ROUND_ENDED;
    }
    return GameState::COMPUTER_PLAYER_TURN;
}
