#pragma once
#include "Framework/Game.h"
#include "Render/Text.h"
class SpaceWars : public Sc::Game {
public:
	enum eState {
		Tittle,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};
public:
	virtual bool Init() override;
	virtual void Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw(Sc::Render& render) override;
	void SetState(eState state) { m_state = state; }
private:
	std::shared_ptr<Sc::Font> m_font;
	std::unique_ptr<Sc::Text> m_scoreText;
	std::unique_ptr<Sc::Text> m_tittleText;
	std::unique_ptr<Sc::Text> m_Lives;
	std::unique_ptr<Sc::Text> m_gameOverText;
	eState m_state = eState::Tittle;
	float m_spawnTimer = 0;
	float m_spawnTime = 2.0f;
	float m_stateTimer = 0;

};
