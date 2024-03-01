#pragma once
#include <GameDev2D.h>


namespace GameDev2D
{
	class Collision
	{
	public:
		Collision(Vector2& position, float radius);
		Collision(Vector2& position);

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);
		bool CheckCollision(const Collision& hitbox);
		void setRadius(float newRadius);


	private:
		Vector2& m_Position;
		float m_Radius;
	};


}
