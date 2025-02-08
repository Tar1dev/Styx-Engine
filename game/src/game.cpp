#include <game.hpp>
#include <graphics/Texture2D.hpp>
#include <iostream>

Texture2D box;
Texture2D smile;
RendererManager& renderer = RendererManager::getInstance();

void initGame() {
    box = Texture2D();
    box.loadFromFile(std::string(RESSOURCES_DIR) + "/textures/container.jpg");

    smile = Texture2D();
    smile.loadFromFile(std::string(RESSOURCES_DIR) + "/textures/awesomeface.png");
}

void updateGame(float dt) {
    renderer.drawTexture(box, glm::vec2(0, 0));
    renderer.drawTexture(smile, glm::vec2(400, 0));
}

void closeGame() {

}