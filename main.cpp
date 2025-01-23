#include <core/EngineFacade.hpp>

int main(int argc, char const *argv[])
{
    EngineFacade engine;

    engine.initialize();
    engine.run();
    engine.shutdown();
    return 0;
}
