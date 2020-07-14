#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include <iostream>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 300;

nc::Color color{ 0, 1, 1 };
nc::Transform transform{ { 400.0f, 300.0f }, 4, 0 };

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

nc::Actor player;
nc::Actor enemy;
nc::Shape currentShape;

bool Update(float dt){ // delta time (60fps) (1 / 60 = 0.016)
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	t = t + dt * 5.0f;

	frametime = dt;
	roundTime += dt;
	if (roundTime >= 5.0f) gameOver = true;

	if (gameOver) dt = dt * 0.25f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x, y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x,y };
	//nc::Vector2 direction = target - position;
	//direction.Normalize();

	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, player.GetTransform().angle);
	player.GetTransform().position = player.GetTransform().position + direction;

	//rotate
	if (Core::Input::IsPressed('A')) { player.GetTransform().angle = player.GetTransform().angle - (dt * nc::DegreesToRadians(360.0f)); }
	if (Core::Input::IsPressed('D')) { player.GetTransform().angle = player.GetTransform().angle + (dt * nc::DegreesToRadians(360.0f)); }

	transform.position = nc::Clamp(player.GetTransform().position, { 0,0 }, { 800,600 });

	//move
	/*if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) position += nc::Vector2::left * speed * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) position += nc::Vector2::right * speed * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) position += nc::Vector2::up * speed * dt;
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) position += nc::Vector2::down * speed * dt;*/

	if (Core::Input::IsPressed('1')) { player.Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\player_ship.txt"); }
	if (Core::Input::IsPressed('2')) { player.Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\player_square.txt"); }

	return quit;
}

void Draw(Core::Graphics& graphics){
	
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f;

	//nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	//graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 100, 100 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main(){
	player.Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\player_ship.txt");
	enemy.Load("C:\\Users\\Sarcasm\\C++\\CSC196\\Build\\enemy.txt");
	DWORD ticks = GetTickCount(); //how many ticks in a second
	std::cout << ticks / 1000/ 60 / 60 << std::endl;
	prevTime = GetTickCount();
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 15);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
