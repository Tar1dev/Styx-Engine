#include <game.hpp>
#include <graphics/Texture2D.hpp>
#include <iostream>

Styx::Texture2D box;
Styx::Texture2D smile;
Styx::Renderer& renderer = Styx::Renderer::getInstance();

void initGame() {
    box = Styx::Texture2D();
    box.loadFromFile(std::string(RESSOURCES_DIR) + "/textures/container.jpg");

    smile = Styx::Texture2D();
    smile.loadFromFile(std::string(RESSOURCES_DIR) + "/textures/awesomeface.png");
}

void updateGame(float dt) {
    renderer.drawTexture(box, glm::vec2(0, 0));
    renderer.drawTexture(box, glm::vec2(400, 0));
    renderer.drawTexture(smile, glm::vec2(0, 400));
}

void closeGame() {

}