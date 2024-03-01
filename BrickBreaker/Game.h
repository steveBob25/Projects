#pragma once

#include <GameDev2D.h>
#include "Constants.h"


namespace GameDev2D
{
	class Game
	{
	public:
		Game();
		~Game();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		//Input event methods
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		void OnMouseMovedEvent(float mouseX, float mouseY);

		void Reset();

		void CheckBallCollision(float delta);

	private:
		//Member variables GO HERE 
		Vector2 m_BallPosition;
		Vector2 m_BallVelocity;
		float m_BallRadius;
		bool m_IsPaused;

		LineSegment m_ScreenEdges[NUM_EDGES];

		std::vector<AABB> m_AABBs;
	};
}
