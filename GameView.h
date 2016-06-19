#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include "Observer.h"
#include "GameController.h"
#include "Game.h"

// View class
class GameView : public Observer {
public:
    GameView(GameController*, Game*);
    virtual ~GameView();
    virtual void update();              // Observer pattern: concrete update method
    virtual void start();

private:
	// Observer Pattern: to access model accessors without having to downcast subject
	Game *game_;
	
	// Strategy Pattern member (plus signal handlers)
	GameController *controller_;
};

#endif // GAME_VIEW_H_
