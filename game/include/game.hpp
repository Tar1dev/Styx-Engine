#include <core/Application.hpp>
#include <graphics/Renderer.hpp>
#include <iostream>

class Game : public Styx::Application
{
private:
	Styx::Renderer& renderer = Styx::Renderer::getInstance();
	Styx::Texture2D box;
public:
	Game() {};

	void init() override {
		box = Styx::Texture2D();
		box.loadFromFile(std::string(RESSOURCES_DIR) + "/textures/container.jpg");
	}

	void update(float dt) override {
		std::cout << dt << std::endl;
	}

	void draw() override {
		renderer.drawTexture(box, glm::vec2(0, 0));
	}
};
