//#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() :
	m_BulletPosition(Vector2::Zero),
	m_BulletSpeed(Vector2::Zero),
	m_isBulletActive(false),
	m_BulletPoints{ {0,-10}, {10,0}, {0,10}, {-10,0}, {0,-10} },
	m_Collider(m_BulletPosition, 10.0f)
{
}

void Bullet::OnUpdate(float delta)
{

	if (m_isBulletActive)
	{
		m_time += delta;

		m_BulletPosition += m_BulletSpeed * delta;

		if (m_time >= m_deactivateTime)
		{
			m_isBulletActive = false;
		}

		if (m_BulletPosition.x > GetScreenWidth() + 20)
		{
			m_BulletPosition.x = -20;
		}
		if (m_BulletPosition.y > GetScreenHeight() + 20)
		{
			m_BulletPosition.y = -20;
		}
		if (m_BulletPosition.x < -21)
		{
			m_BulletPosition.x = GetScreenWidth() + 20;
		}
		if (m_BulletPosition.y < -21)
		{
			m_BulletPosition.y = GetScreenHeight() + 20;
		}

	}




}

void Bullet::OnRender(BatchRenderer& batchRenderer)
{
	if (m_isBulletActive)
	{
		batchRenderer.RenderLineStrip(m_BulletPoints, ColorList::White, 2.0f, m_BulletPosition, 0);
		//m_Collider.OnRender(batchRenderer);
	}
}

Vector2 Bullet::GetPosition()
{
	return m_BulletPosition;
}

void Bullet::Activate(const Vector2 position, const Vector2& speed)
{
	m_deactivateTime = m_time + 2.0f;
	m_isBulletActive = true;
	m_BulletPosition = position;
	m_BulletSpeed = speed;
}

bool Bullet::isActive()
{
	return m_isBulletActive;
}

Collision& Bullet::getCollider()
{
	return m_Collider;
}

void Bullet::Deactivate()
{
	m_isBulletActive = false;
}
