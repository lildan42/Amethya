#include "pch.h"
#include "TimerManager.h"
#include "Event.h"
#include "ResourceManager.h"

int main()
{
	Events::Event<int, int&> evt;

	evt.subscribeHandler([](int a, int& b) {
		std::cout << (a + b) << std::endl;
	});

	evt.subscribeHandler([](int a, int& b) {
		std::cout << "LETTER: " << (char)('a' + b) << std::endl;
	});

	Timer::Timer& timerRef = Timer::TimerManager::getInstance().addTimer(Timer::Timer(1.5f, [&evt](int repeatTime) {
		std::cout << repeatTime << std::endl;
		evt.invoke(4000, repeatTime);

	}, 0));

	float dt = 1.0f / 60.0f;

	rapidjson::Document doc = Resources::ResourceManager::parseJsonFile("test.json");
	
	if(doc.IsObject())
		for (auto it = doc.MemberBegin(); it != doc.MemberEnd(); it++) {
			std::cout << it->name.GetString() << std::endl;
		}

	sf::RenderWindow window(sf::VideoMode(800, 600), "Amethya");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		auto start = std::chrono::steady_clock::now();

		sf::Event windowEvent;

		while (window.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color('b', 'o', 'b'));
		window.display();

		auto end = std::chrono::steady_clock::now();
		dt = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e9f;

		Timer::TimerManager::getInstance().updateTimers(dt);
	}
}