#pragma once
#include "memory"
#include "Render/Renderer.h"
namespace Sc {
	class Game {
	public:
		Game() = default;
		virtual ~Game() = default;
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(Render& render) = 0;
		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }
		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }
	protected:
		std::unique_ptr<class Scene> m_scene;
		int m_score = 0;
		int m_lives = 0;
	};
}
