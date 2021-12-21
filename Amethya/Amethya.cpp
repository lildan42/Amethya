#include "Amethya.h"
#include "TimerManager.h"

Amethya::Amethya() : dt(FPS_DEFAULT), start(std::chrono::steady_clock::now()) { }

void Amethya::init() {
	this->window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_TITLE);
	this->window.setFramerateLimit(FPS_LIMIT);
}

Amethya& Amethya::getInstance() {
	static Amethya instance;
	return instance;
}

bool Amethya::isWindowOpen() {
	return this->window.isOpen();
}

float Amethya::getDeltaTime() {
	return this->dt;
}

void Amethya::pollEvents() {
	sf::Event evt;

	while (this->window.pollEvent(evt)) {
		switch (evt.type) {
		case sf::Event::Closed:
			this->window.close();
			break;

		default:
			break;
		}
	}
}

void Amethya::update(float dt) {
	this->start = std::chrono::steady_clock::now();
}

void Amethya::draw() {
	this->window.clear(BACKGROUND);
	this->window.display();

	auto end = std::chrono::steady_clock::now();
	this->dt = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - this->start).count() * NANOS_TO_SECONDS;

	Timer::TimerManager::getInstance().updateTimers(this->dt);
}

int main()
{
	Timer::TimerManager::getInstance().addTimer(Timer::Timer(1.0f, [](int repeatTime) {
		std::cout << "Time: " << repeatTime << std::endl;
	}));

	Amethya& game = Amethya::getInstance();
	game.init();

	while (game.isWindowOpen()) {
		game.pollEvents();
		game.update(game.getDeltaTime());
		game.draw();
	}
}