#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Math\Math.h"
#include <fstream>

bool Projectile::Load(const std::string& filename) {
	bool success = false;
	
	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::Load(stream);

		std::string line;
		//std::getline(stream, line);
		stream >> line;
		m_thrust = stof(line);

		stream.close();
	}
	return success;
}

void Projectile::Update(float dt) {
	m_lifetime -= dt;
	m_destroy = (m_lifetime <= 0);

	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
	nc::Vector2 velocity = direction * m_thrust;
	m_transform.position = m_transform.position + velocity * dt;

	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 10, 1, nc::Color::white, 0.5f, 1, 10);

	//if(m_transform.position.x > 800 || m_transform.position.x < 0) m_destroy = true;

	m_transform.Update();
}

void Projectile::OnCollision(Actor* actor) {
	if (actor->GetType() == eType::ENEMY) {
		m_destroy = true;
	}
}