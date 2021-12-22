#include "InputManager.h"

namespace Input {
	InputManager::InputManager() : isPressed(), buttonStates() {
		this->isPressed.fill(false);
		this->buttonStates.fill(ButtonState::RELEASED);

		this->inputMap.emplace("Jump", InputMapping{sf::Keyboard::Space, ButtonState::PRESSED});
	}

	void InputManager::setButtonPressed(int button, bool pressed) {
		this->isPressed[button] = pressed;
	}

	void InputManager::updateButtonStates() {
		for (size_t i = 0; i < BUTTON_COUNT; i++) {
			switch (this->buttonStates[i]) {
			case ButtonState::RELEASED:
				if (this->isPressed[i])
					this->buttonStates[i] = ButtonState::PRESSED;

				break;

			case ButtonState::RELEASE_STARTED:
				this->buttonStates[i] = this->isPressed[i] ? ButtonState::PRESSED : ButtonState::RELEASED;
				break;

			case ButtonState::PRESSED:
				this->buttonStates[i] = this->isPressed[i] ? ButtonState::HELD : ButtonState::RELEASE_STARTED;
				break;

			case ButtonState::HELD:
				if (!this->isPressed[i])
					this->buttonStates[i] = ButtonState::RELEASE_STARTED;

				break;
			}
		}
	}

	bool InputManager::isInputActive(std::string input) {
		return this->buttonStates[this->inputMap[input].button] == this->inputMap[input].state;
	}

	InputManager& InputManager::getInstance() {
		static InputManager instance;
		return instance;
	}
}