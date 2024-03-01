//#include "stdafx.h"
#include "Asteroid.h"
#include "Constants.h"
#include <GameDev2D.h>




using namespace GameDev2D;

Asteroid::Asteroid() :
	m_Angle(Math::DegreesToRadians(90.0f)),
	m_Position(0.0f, 0.0f),
	m_points(),
	m_Collider(m_Position),
	m_isAlive(true)
{
	float largestRadius = 0;

	float randomAngle(Math::RandomFloat(0.0f, 2.0f)*M_PI );
	float randomSpeed(Math::RandomFloat(0.0f, 75.0f));

	m_Velocity = Vector2(cos(randomAngle), sin(randomAngle) * randomSpeed);


	int sides(Math::RandomInt(8, 12));

	float m_radiansPerSide{ 2.0f * (float)M_PI / (int)sides };

	for (int i = 0; i < sides; i++)
	{

		float angle = i * m_radiansPerSide;

		float radius = Math::RandomFloat(21.2f, 53.9f);
		if (radius > largestRadius)
		{
			largestRadius = radius;
		}
		Vector2 point = Vector2(cos(angle), sin(angle)) * radius;

		m_points.push_back(point);


	}
	m_points.push_back(m_points[0]);
	m_Collider.setRadius(largestRadius);

	float speed = Math::RandomFloat(c_asteroidMinSpeed, c_asteroidMaxSpeed);

	m_Angle = Math::RandomFloat(0.0f, 2.0f * M_PI);

	m_Velocity = Vector2(cos(m_Angle), sin(m_Angle)) * speed;

	int edge = Math::RandomInt(0, 3);
	if(edge == 0) // Left
	{
		m_Position.x = Math::RandomFloat(0.0f, 100.0f);
		m_Position.y = Math::RandomFloat(0.0f, GetScreenHeight());
	}
	else if (edge == 1) // Right
	{
		m_Position.x = Math::RandomFloat(GetScreenWidth() - 100.0f, GetScreenWidth());
		m_Position.y = Math::RandomFloat(0.0f, GetScreenHeight());
	}
	else if (edge == 2) // down
	{
		m_Position.x = Math::RandomFloat(0.0f, GetScreenWidth());
		m_Position.y = Math::RandomFloat(0.0f, 100.0f);
	}
	else if (edge == 3) // up
	{
		m_Position.x = Math::RandomFloat(0.0f, GetScreenWidth());
		m_Position.y = Math::RandomFloat(GetScreenHeight() - 100.0f, GetScreenHeight());
	}



}

Asteroid::~Asteroid()
{
}

void Asteroid::OnUpdate(float delta)
{

	if (m_isAlive == true)
	{
		if (m_Position.x > GetScreenWidth() + 20)
		{
			m_Position.x = -20;
		}
		if (m_Position.y > GetScreenHeight() + 20)
		{
			m_Position.y = -20;
		}
		if (m_Position.x < -21)
		{
			m_Position.x = GetScreenWidth() + 20;
		}
		if (m_Position.y < -21)
		{
			m_Position.y = GetScreenHeight() + 20;
		}

		m_Angle += Math::RandomFloat(c_angularAsteroidAccelMin, c_angularAsteroidAccelMax * M_PI) * delta;
		Vector2 displacement = m_Velocity * delta;
		m_Position += displacement;


	}

}

void Asteroid::OnRender(BatchRenderer& batchRenderer)
{
	if (m_isAlive == true)
	{
		batchRenderer.RenderLineStrip(m_points, ColorList::LightGray, 2.0f, m_Position, m_Angle);
		//m_Collider.OnRender(batchRenderer);
	}
}

void Asteroid::destroyAsteroid()
{


	m_isAlive = false;

}

bool Asteroid::getIsAlive()
{
	return m_isAlive;
}

Collision& Asteroid::getCollider()
{
	return m_Collider;
}

int Asteroid::Probability(int num)
{
	return num = (Math::RandomInt(1, 7));
}

Vector2 Asteroid::GetPosition()
{
	return m_Position;
}

