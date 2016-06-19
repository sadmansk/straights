#include "ComputerPlayer.h"

void ComputerPlayer::autoPlay(std::vector<const Card*> played_cards){
    const std::vector<const Card*> plays = legalMoves(played_cards);
    if(plays.size() == 0){
        return discardCard( *hand_.begin(), played_cards );
    }

    return playCard(*hand_.begin(), played_cards);
}

GameState ComputerPlayer::getTurnState() const {
    return COMPUTER_PLAYER_TURN;
}
