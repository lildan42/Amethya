#include "Amethya.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

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

		case sf::Event::KeyPressed:
			if (evt.key.code != sf::Keyboard::Unknown)
				Input::InputManager::getInstance().setButtonPressed(evt.key.code, true);

			break;

		case sf::Event::KeyReleased:
			if (evt.key.code != sf::Keyboard::Unknown)
				Input::InputManager::getInstance().setButtonPressed(evt.key.code, false);

			break;

		default:
			break;
		}
	}

	Input::InputManager::getInstance().updateButtonStates();
}

void Amethya::update(float dt) {
	this->start = std::chrono::steady_clock::now();
}

void Amethya::draw() {
	this->window.clear();

	sf::Sprite& sprite0 = Resources::ResourceManager::getInstance().getSprite("platforms", 1);

	for (float i = 0; i < (float)this->WIDTH * (float)this->HEIGHT / 32.0f; i += 32.0f) {
		sprite0.setPosition(sf::Vector2f(fmodf(i, this->WIDTH), 32.0f * floorf(i / this->WIDTH)));
		this->window.draw(sprite0);
	}

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

	Input::InputManager::getInstance().subscribeOnPressButtonHandler([](int key) {
		if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
			std::cout << (char)('A' + key);
		}
	});

	while (game.isWindowOpen()) {
		game.pollEvents();
		game.update(game.getDeltaTime());
		game.draw();

		if (Input::InputManager::getInstance().isInputActive("Jump")) {
			std::cout << "JUMPED!" << std::endl;
		}
	}
}