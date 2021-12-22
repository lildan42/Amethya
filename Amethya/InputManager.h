#pragma once

#include "pch.h"

namespace Input {
	static constexpr size_t BUTTON_COUNT = 105;

	enum class ButtonState {
		RELEASED,
		RELEASE_STARTED,
		PRESSED,
		HELD
	};

	struct InputMapping {
		int button;
		ButtonState state;
	};

	class InputManager {
	private:
		std::map<std::string, InputMapping> inputMap;

		std::array<bool, BUTTON_COUNT> isPressed;
		std::array<ButtonState, BUTTON_COUNT> buttonStates;

		InputManager();

	public:
		InputManager(const InputManager&) = delete;
		void operator =(const InputManager&) = delete;

		void setButtonPressed(int button, bool pressed);
		void updateButtonStates();

		bool isInputActive(std::string input);

		static InputManager& getInstance();
	};
}