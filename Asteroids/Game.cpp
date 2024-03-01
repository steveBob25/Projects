#include "Game.h"
#include "Constants.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Collision.h"
#include "Shield.h"
#include "Ship.h"



namespace GameDev2D
{
	Game::Game() :
		m_asteroids(),
		m_ship(this),
		m_Bullets{},
		m_shield(),
		m_number(0)

	{
		for (int i = 0; i < c_ammoCount; i++)
		{
			m_Bullets[i] = new Bullet();
		}

	}

	Game::~Game()
	{
		for (int i = 0; i < c_ammoCount; i++)
		{
			if (m_Bullets[i] != nullptr)
			{
				delete m_Bullets[i];
				m_Bullets[i] = nullptr;
			}
		}

	}

	void Game::OnUpdate(float delta)
	{
		float gameTimer = 0;

		gameTimer += delta;
		
		m_ship.OnUpdate(delta);


		for (int i = 0; i < 20; i++)
		{
			m_asteroids[i].OnUpdate(delta);
		}

		for (int i = 0; i < c_ammoCount; i++)
		{
			m_Bullets[i]->OnUpdate(delta);
		}
		
		
		for (int i = 0; i < 20; i++)
		{
			if (m_asteroids[i].getIsAlive())
			{
				for (int j = 0; j < c_ammoCount; j++)
				{
					if (m_asteroids[i].getCollider().CheckCollision(m_Bullets[j]->getCollider()))
					{
						m_Bullets[j]->Deactivate();
						m_asteroids[i].destroyAsteroid();
						m_number = m_asteroids[i].Probability(m_number);
						if (m_number == 7)
						{
							CreateShield(m_asteroids[i].GetPosition());
						}

					}


				}

				if (m_asteroids[i].getCollider().CheckCollision(m_ship.getCollider()))
				{
				
					m_ship.respawn();
				}

			}

		}

	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();

		m_ship.OnRender(batchRenderer);

		m_shield.OnRender(batchRenderer);

		for (int i = 0; i < 20; i++)
		{
			m_asteroids[i].OnRender(batchRenderer);
		}

		for (int i = 0; i < c_ammoCount; i++)
		{
			m_Bullets[i]->OnRender(batchRenderer);
		}

		batchRenderer.EndScene();
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		m_ship.OnKeyEvent(keyCode, keyState);	
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{
		
	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{

	}
	void Game::ShootBullet(const Vector2& position, const Vector2& speed)
	{
		Bullet* bullet = GetBullet();
		if (bullet != nullptr)
		{
			bullet->Activate(position, speed);
		}

	}

	void Game::CreateShield(const Vector2& position)
	{
		m_shield.ActivateDrop(m_Position, m_number);
	}

	
	Bullet* Game::GetBullet()
	{
		for (int i = 0; i < c_ammoCount; i++)
		{
			if (m_Bullets[i]->isActive() == false)
			{
				return m_Bullets[i];
			}
		}

	
		return nullptr;
	}
}