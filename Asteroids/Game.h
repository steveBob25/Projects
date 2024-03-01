#pragma once
#include <GameDev2D.h>
#include "Ship.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Bullet.h"
#include "Shield.h"


namespace GameDev2D
{
	class Game
	{
	public:
		Game();
		~Game();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		void OnMouseMovedEvent(float mouseX, float mouseY);
		void ShootBullet(const Vector2& position, const Vector2& speed);
		void CreateShield(const Vector2& position);

	private:
		Ship m_ship;
		Asteroid m_asteroids[20];
		Vector2 m_Position;
		Bullet* m_Bullets[c_ammoCount];
		Bullet* GetBullet();
		Shield m_shield;
		int m_number = 0;
	};
}
