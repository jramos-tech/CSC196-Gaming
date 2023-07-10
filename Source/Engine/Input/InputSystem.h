#pragma once
#include <SDL2-2.28.0/include/SDL.h>
#include <vector>
#include <Core/Vector2.h>
using namespace std;
namespace I
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;
		bool Initialize();
		void Shutdown();
		void Update();
		bool GetKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }
		const V::Vector2& GetMousePosition() const { return m_mousePosition; }
		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }
	private:
		vector<uint8_t> m_keyboardState;
		vector<uint8_t> m_prevKeyboardState;
		V::Vector2 m_mousePosition;
		array<uint8_t, 3> m_mouseButtonState;
		array<uint8_t, 3> m_prevMouseButtonState;
	};
}