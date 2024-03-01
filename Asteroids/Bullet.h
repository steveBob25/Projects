#pragma once
#include <GameDev2D.h>
#include<vector>
#include "Collision.h"

using namespace GameDev2D;

class Bullet
{
public:
	Bullet();
	void OnUpdate(float delta);
	void OnRender(BatchRenderer& batchRenderer);
	Vector2 GetPosition();

	void Activate(const Vector2 position, const Vector2& speed);
	bool isActive();
	Collision& getCollider();
	void Deactivate();


private:
	std::vector<Vector2> m_BulletPoints;
	Vector2 m_BulletPosition;
	Vector2 m_BulletSpeed;
	bool m_isBulletActive;
	float m_time = 0;
	float m_deactivateTime = 0.0f;
	Collision m_Collider;

};

