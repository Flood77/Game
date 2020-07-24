#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace nc {
	void Scene::Startup() {
		//nothing
	}

	void Scene::Shutdown() {
		for (Actor* actor : m_actors) {
			delete actor;
		}
		m_actors.clear();
	}
	void Scene::Update(float dt) {
		//check actor collisions
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				float distance = Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= (actors[i]->GetRadius() + actors[j]->GetRadius())) {
					actors[i]->OnCollision(actors[j]);
					actors[j]->OnCollision(actors[i]);
				}
			}
		}

		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			if ((*iter)->IsDestroy()) {
				delete* iter;
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		for (Actor*& a : m_actors) {
			a->Update(dt);
		}
	}
	void Scene::Draw(Core::Graphics& graphics) {
		for (Actor*& a : m_actors) {
			a->Draw(graphics);
		}
	}
	void Scene::AddActor(Actor* actor) {
		actor->SetScene(this);
		m_actors.push_back(actor);
	}
	void Scene::RemoveActor(Actor* actor) {
		auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end()) {
			delete* iter;
			m_actors.erase(iter);
		}
	}
}