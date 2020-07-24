#pragma once
#include "core.h"
#include "Object/Scene.h"

class Game {
public:
	enum class eState {
		INIT,
		TITLE,
		START_GAME,
		GAME,
		GAME_OVER
	};

public:
	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddPoints(int points) { m_score += points; }
	void SetState(eState state) { m_state = state; }

protected:
	eState m_state{ eState::TITLE };
	int m_lives{ 3 };
	int m_score{ 0 };

	nc::Scene m_scene;

	float m_frameTime;
	float m_spawntimer{ 0 };

	static const int WIDTH;
	static const int HEIGHT;
};

