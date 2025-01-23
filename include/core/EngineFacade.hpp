#if !defined(ENGINE_FACADE_HPP)
#define ENGINE_FACADE_HPP

#include "WindowManager.hpp"

class EngineFacade
{
public:
    bool initialize();
    void run();
    void shutdown();
};


#endif // ENGINE_FACADE_HPP

