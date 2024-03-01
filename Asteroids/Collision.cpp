//#include "stdafx.h"
#include "Collision.h"

GameDev2D::Collision::Collision(Vector2& position, float radius) : 
	m_Position(position),
	m_Radius(radius)
{
}

GameDev2D::Collision::Collision(Vector2& position) :
	m_Position(position)
{
}

void GameDev2D::Collision::OnRender(BatchRenderer& batchRenderer)
{
	batchRenderer.RenderCircle(m_Position, m_Radius, ColorList::Clear, ColorList::Red, 2.0f);
}

bool GameDev2D::Collision::CheckCollision(const Collision& hitbox)
{
	float distanceSquared = m_Position.DistanceSquared(hitbox.m_Position);
	float radiusSquared = (m_Radius + hitbox.m_Radius) * (m_Radius + hitbox.m_Radius);
	return distanceSquared <= radiusSquared;
}

void GameDev2D::Collision::setRadius(float newRadius)
{
	m_Radius = newRadius;
}
