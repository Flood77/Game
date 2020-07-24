#pragma once
#include "Object/Actor.h"
#include "Math/Math.h"

class Player : public nc::Actor {
public:
	Player() {}
	virtual ~Player() {}

	virtual eType GetType() { return eType::PLAYER; }


	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor);

protected:
	float m_thrust{ 0.0f };
	float m_rotationRate{ 360.0f };
	float m_fireRate{ 0.2f };
	float m_fireTimer{ 0.0f };

	nc::Vector2 m_velocity;

};