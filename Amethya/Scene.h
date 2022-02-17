#pragma once

#include "pch.h"
#include "GameObject.h"

namespace Scenes {
	class Scene {
	private:
		std::string name;
		std::vector<GameObjects::GameObject> gameObjects;

	public:
		Scene(std::string name);

		virtual void onEnter() = 0;
		virtual void update(float dt) = 0;
		virtual void lateUpdate(float dt) = 0;
		virtual void onExit() = 0;

		std::string getName();

		void draw(sf::RenderWindow& window);
	};
}