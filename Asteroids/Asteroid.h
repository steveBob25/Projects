#pragma once
#include <GameDev2D.h>
#include "Collision.h"
#include "Shield.h"

using namespace GameDev2D;

class Asteroid
{
public:

	Asteroid();
	~Asteroid();

	void OnUpdate(float delta);

	void OnRender(BatchRenderer& batchRenderer);

	void destroyAsteroid();

	bool getIsAlive();	

	Collision& getCollider();

	int Probability(int num);

	Vector2 GetPosition();

private:
	std::vector<Vector2> m_points;
	float m_Angle;
	Vector2 m_Position;
	Vector2 m_Velocity;
	Collision m_Collider;
	bool m_isAlive;
	//int m_asteroidsDestroyed = 0;

};

