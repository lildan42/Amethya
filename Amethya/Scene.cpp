#include "Scene.h"

namespace Scenes {
	Scene::Scene(std::string name) : name(name) {}

	std::string Scene::getName() {
		return this->name;
	}

	void Scene::draw(sf::RenderWindow& window) {
		//TODO
	}
}