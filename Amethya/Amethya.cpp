#include "pch.h"
#include "TimerManager.h"
#include "Event.h"

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

	while (true) {
		auto start = std::chrono::steady_clock::now();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		auto end = std::chrono::steady_clock::now();
		dt = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1e9f;

		Timer::TimerManager::getInstance().updateTimers(dt);
	}
}