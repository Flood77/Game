#include "Player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename) {
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::Load(stream);

		std::string line1;
		//std::getline(stream, line1);
		stream >> line1;
		m_thrust = stof(line1);

		//std::getline(stream, line2);
		stream >> line1;
		m_rotationRate = stof(line1);

		stream.close();
	}

	return success;
}

void Player::Update(float dt) {
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate) {
		m_fireTimer = 0;
		Projectile* actor = new Projectile;
		actor->Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\projectile.txt");
		actor->GetTransform().position = m_transform.position;
		actor->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(actor);
	}

	//position
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);
	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;
	m_transform.position = m_transform.position + (m_velocity * dt);

	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * nc::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * nc::DegreesToRadians(360.0f);

	m_transform.position = nc::Clamp(m_transform.position, { 0,0 }, {800, 600});

	if (force.LengthSqr() > 0) {
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::yellow, 1, 1, 10);
	}

	m_transform.Update();
}

void Player::OnCollision(Actor* actor){
	if (actor->GetType() == eType::ENEMY) {
		m_scene->GetGame()->SetState(Game::eState::GAME_OVER);
	}
}
