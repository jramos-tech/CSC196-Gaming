#include "InputSystem.h"
namespace I
{
	bool InputSystem::Initialize(){
		int numKeys;
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);
		m_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;
		return true;
	}
	void InputSystem::Shutdown(){

	}
	void InputSystem::Update(){
		SDL_Event event;
		SDL_PollEvent(&event);
		m_prevKeyboardState = m_keyboardState;
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

	}
}