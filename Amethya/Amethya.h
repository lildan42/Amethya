#pragma once

#include "pch.h"

class Amethya {
private:
	const sf::Color BACKGROUND = sf::Color(0xaa00ff);

	const unsigned int FPS_LIMIT = 60;
	const float FPS_DEFAULT = 1.0f / (float)FPS_LIMIT;

	const float NANOS_TO_SECONDS = 1e-9f;

	const std::string WINDOW_TITLE = "Amethya";

	std::chrono::steady_clock::time_point start;
	float dt;

	sf::RenderWindow window;

	Amethya();

public:
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

	Amethya(const Amethya&) = delete;
	void operator =(const Amethya&) = delete;

	static Amethya& getInstance();

	bool isWindowOpen();
	float getDeltaTime();

	void init();

	void pollEvents();
	void update(float dt);
	void draw();
};