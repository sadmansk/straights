#include "ComputerPlayer.h"

std::pair<const Card*, std::string> ComputerPlayer::autoPlay(std::vector<const Card*> played_cards){
    const std::vector<const Card*> plays = legalMoves(played_cards);
    if(plays.size() == 0){
        const Card* discarded = *hand_.begin();
        discardCard( *hand_.begin(), played_cards );
        return {discarded, "discarded"};
    }

    const Card* played = *hand_.begin();
    playCard( *hand_.begin(), played_cards );
    return {played, "played"};
}

GameState ComputerPlayer::getTurnState() const {
    return COMPUTER_PLAYER_TURN;
}
