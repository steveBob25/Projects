#pragma once
#include <GameDev2D.h>
#include "Collision.h"



namespace GameDev2D
{

	class Game;

	class Ship
	{
	public:


		Ship(Game* game);

		~Ship();

		void OnUpdate(float delta);

		void OnRender(BatchRenderer& batchRenderer);

		void OnKeyEvent(KeyCode keyCode, KeyState keyState);

		Collision& getCollider();

		void respawn();

		Vector2 getShipPosition();

	private:
		std::vector<Vector2> m_Points;
		float m_Angle;
		Vector2 m_Position;
		Vector2 m_speed = Vector2::Zero;
		Game* m_Game;
		Collision m_Collider;

	};

}

