#include "HumanPlayer.h"
#include <sstream>

std::string HumanPlayer::printHand() const{
    std::stringstream ss;
    ss << "Your Hand:";

    std::set<const Card*>::iterator card;
    for(card = hand_.begin(); card != hand_.end(); ++card){
        ss << " " << **card;
    }
    ss << std::endl;
    return ss.str();
}

std::string HumanPlayer::printMoves(const std::vector<const Card*> played_cards) const{
    std::stringstream ss;
    ss << "Legal Plays:";

    const std::vector<const Card*> legalPlays = legalMoves(played_cards);

    for(int i = 0; i < legalPlays.size(); i++){
        ss << " " << *legalPlays[i];
    }
    ss << std::endl;
    return ss.str();
}
