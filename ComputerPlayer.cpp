#include "Game.h"
#include "ComputerPlayer.h"

std::pair<Card*, std::string> ComputerPlayer::autoPlay(std::vector<Card*> played_cards){
    const std::vector<Card*> plays = legalMoves(played_cards);
    if(plays.size() == 0){
        Card* discarded = *hand_.begin();
        discardCard( **hand_.begin(), played_cards );
        return {discarded, "discards"};
    }

    Card* played = *hand_.begin();
    playCard( **hand_.begin(), played_cards );
    return {played, "plays"};
}

GameState ComputerPlayer::getTurnState() const {
    return GameState::COMPUTER_PLAYER_TURN;
}
