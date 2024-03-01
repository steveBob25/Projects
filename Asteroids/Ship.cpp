//#include "stdafx.h"
#include "Ship.h"
#include "Constants.h"
#include "Game.h"

namespace GameDev2D
{

	Ship::Ship(Game* game) :
		m_Points{ {20.0f,0.0f}, {-10.0f,10.0f}, {0.0f,0.0f},{-10.0f,-10.0f},{20.0f,0.0f} },
		m_Angle(Math::DegreesToRadians(90.0f)),
		m_Position(GetHalfScreenWidth(), GetHalfScreenHeight()),
		m_Game(game),
		m_Collider(m_Position, c_ShipSize/2)
	{
	}

	Ship::~Ship()
	{
	}



	void Ship::OnUpdate(float delta)
	{

		//  Left Key


		if (IsKeyDown(KeyCode::A) == true)
		{
			m_Angle += c_angularAccel * delta;

		}

		//  Right Key

		if (IsKeyDown(KeyCode::D) == true)
		{

			m_Angle -= c_angularAccel * delta;

		}


		Vector2 acceleration;
		Vector2 displacement;

		//  Up Key

		if (IsKeyDown(KeyCode::W) == true)
		{
			acceleration = Vector2(cos(m_Angle), sin(m_Angle)) * c_acceleration;

			m_speed += acceleration * delta;

			displacement = m_speed * delta;

			m_Position += displacement;

			if (m_speed.Length() > c_maxSpeed)
			{
				m_speed = m_speed.Normalized() * c_maxSpeed;
			}
		}



		displacement = m_speed * delta;
		m_Position += displacement;



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

	}

	void Ship::OnRender(BatchRenderer& batchRenderer)
	{

		batchRenderer.RenderLineStrip(m_Points, ColorList::White, 2.0f, m_Position, m_Angle);
		//m_Collider.OnRender(batchRenderer);

	}

	void Ship::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{

		if (keyState == KeyState::Down)
		{
			if (keyCode == KeyCode::Space)
			{
				float location = c_ShipSize * 0.5f;
				Vector2 direction(cos(m_Angle), sin(m_Angle));
				Vector2 position = m_Position + direction * location;
				Vector2 velocity = direction * c_bulletSpeed;
				m_Game->ShootBullet(position, velocity);
			}
		}

	}

	Collision& Ship::getCollider()
	{
		return m_Collider;
	}

	void Ship::respawn()
	{
		m_Position = Vector2(Math::RandomFloat(0.0f, GetScreenWidth()), Math::RandomFloat(0.0f, GetScreenHeight()));
	}

	Vector2 Ship::getShipPosition()
	{
		return m_Position;
	}

}