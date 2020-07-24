#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Actors/Player.h" 
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>

const int Game::WIDTH = 800;
const int Game::HEIGHT = 800;

void Game::Startup(){
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown(){
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt){
	m_frameTime = dt;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	switch (m_state) {
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE)) {
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		Player* player = new Player;
		player->Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\player.txt");
		m_scene.AddActor(player);

		for (int i = 0; i < 4; i++) {
			Enemy* actor = new Enemy;
			actor->Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\enemy.txt");
			actor->SetTarget(player);
			actor->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
			m_scene.AddActor(actor);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
		m_spawntimer += dt;
		if (m_spawntimer >= 3.0f) {
			m_spawntimer = 0.0f;

			Enemy* actor = new Enemy;
			actor->Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\enemy.txt");
			actor->SetTarget(m_scene.GetActor<Player>());
			actor->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
			m_scene.AddActor(actor);
		}

		m_scene.Update(dt);
		break;
	case Game::eState::GAME_OVER:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::yellow };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{ x, y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics){
	graphics.SetColor(nc::Color{ 1, 1, 255 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "VECTOROIDS");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 40, std::to_string(m_score).c_str());
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
}
