#if !defined(RENDERER_MANAGER_HPP)
#define RENDERER_MANAGER_HPP

class RendererManager
{
private:
    RendererManager();
public:
    static RendererManager& getInstance() {
        static RendererManager instance;
        return instance;
    }
};


#endif // RENDERER_MANAGER_HPP
