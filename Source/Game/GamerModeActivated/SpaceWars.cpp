#include "SpaceWars.h"
#include "Audio/AudioSystem.h"
#include "Render/Text.h"
#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Render/Renderer.h"
#include "Framework/Scene.h"
#include "Render/ModelManager.h"
#include "Framework/Actor.h"
#include "Input/InputSystem.h"
#include "Framework/Emiter.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"


bool SpaceWars::Init(){
	//text
	m_font = std::make_shared<Sc::Font>("Lato-Regular.ttf", 24);

	m_scoreText = std::make_unique<Sc::Text>(m_font);
	m_scoreText->Create(Sc::g_render, std::to_string(m_score), Sc::Color{ 1, 0, 1, 1 });

	m_tittleText = std::make_unique<Sc::Text>(m_font);
	m_tittleText->Create(Sc::g_render, "SPACE WARS", Sc::Color{ 1, 0, 1, 1 });

	m_gameOverText = std::make_unique<Sc::Text>(m_font);
	m_gameOverText->Create(Sc::g_render, "GAME OVER", Sc::Color{ 1, 0, 1, 1 });

	m_Lives = std::make_unique<Sc::Text>(m_font);
	m_Lives->Create(Sc::g_render, std::to_string(m_lives), Sc::Color{1, 0, 1, 1});

	//audio
	Audi::g_audioSystem.AddAudio("laser", "Laser_Shoot.wav");
	Audi::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	Audi::g_audioSystem.AddAudio("hit", "Hit_Hurt.wav");
	Audi::g_audioSystem.AddAudio("ship", "ship.wav");
	Audi::g_audioSystem.AddAudio("theme_song","tiktake_HYo40FNpd.wav");

	//Scene
	m_scene = std::make_unique<Sc::Scene>();
	return true;

}

void SpaceWars::Shutdown(){
}

void SpaceWars::Update(float dt) {
	switch (m_state)
	{
	case SpaceWars::Tittle:
		if (I::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case SpaceWars::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceWars::StartLevel: {
		std::unique_ptr<Player> player = std::make_unique<Player>(5.0f, MaUt::Pi, 100.0f, T::Transform{ {400, 300}, 0, 6}, Sc::g_manager.Get("CoolS.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9);
		m_scene->Add(std::move(player));
	}
							  m_state = eState::Game;
							  break;
	case SpaceWars::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(R::randomf(75.0f, 150.0f), MaUt::Pi, T::Transform{ {R::randomf(800), R::randomf(600)}, R::randomf(0), R::randomf(6)}, Sc::g_manager.Get("CoolS.txt"));
				enemy->m_tag = "Enemy";
				enemy->m_game = this;
				m_scene->Add(std::move(enemy));
			}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		m_scene->RemoveAll();
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceWars::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case SpaceWars::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::Tittle;
		}
		break;
	default:
		break;
	}
	m_scoreText->Create(Sc::g_render, std::to_string(m_score), {1,0,1,1});
	m_Lives->Create(Sc::g_render, std::to_string(m_lives), {1,0,1,1});
	m_scene->Update(dt);
	Audi::g_audioSystem.PlayOneShot("theme_song", true);
}

void SpaceWars::Draw(Sc::Render& render){
	if (m_state == eState::Tittle) {
		m_tittleText->Draw(render, 340, 290);
	}
	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(render, 340, 290);
	}
	m_scoreText->Draw(render, 40, 40);
	m_Lives->Draw(render, 750, 40);
	m_scene->Draw(render);
}
