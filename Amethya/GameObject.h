#pragma once

#include "pch.h"

namespace GameObjects {
	class GameObject {
	public:
		void update(float dt);
		void lateUpdate(float dt);
		void draw(sf::RenderWindow& window);
	};
}