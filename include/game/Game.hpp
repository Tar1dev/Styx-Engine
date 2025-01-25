#if !defined(GAME_HPP)
#define GAME_HPP

#include <core/EngineFacade.hpp>

class Game
{
private:

public:
    static Game& getInstance() {
        static Game game;
        return game;
    }
    void run();
};


#endif // GAME_HPP

