#include "Game.h"
#include "Constants.h"


namespace GameDev2D
{
	Game::Game() :
		m_BallPosition(GetHalfScreenWidth(), GetHalfScreenHeight()),
		m_BallVelocity(Vector2::Zero),
		m_BallRadius(BALL_RADIUS + BALL_OUTLINE),
		m_IsPaused(true),
		m_ScreenEdges{},
		m_AABBs{}
	{
		Vector2 screen(GetScreenWidth(), GetScreenHeight());

		m_ScreenEdges[0] = LineSegment(Vector2(0.0f, 0.0f), Vector2(0.0f, screen.y));           //Left
		m_ScreenEdges[1] = LineSegment(Vector2(screen.x, 0.0f), Vector2(screen.x, screen.y));   //Right
		m_ScreenEdges[2] = LineSegment(Vector2(0.0f, screen.y), Vector2(screen.x, screen.y));   //Top
		m_ScreenEdges[3] = LineSegment(Vector2(0.0f, 0.0f), Vector2(screen.x, 0.0f));           //Bottom

		//m_AABBs.push_back(AABB(Vector2(220.0f, 500.0f), Vector2(380.0f, 580.0f)));
		//m_AABBs.push_back(AABB(Vector2(560.0f, 500.0f), Vector2(720.0f, 580.0f)));
		m_AABBs.push_back(AABB(Vector2(900.0f, 500.0f), Vector2(1060.0f, 580.0f)));

		Reset();
	}

	Game::~Game()
	{

	}

	void Game::OnUpdate(float delta)
	{
		if (m_IsPaused)
			return;

		CheckBallCollision(delta);
	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();

		Color ballOutline = ColorList::Black;
		Color ballFill = ColorList::ForestGreen;
		ballFill.a = 0.6f;

		batchRenderer.RenderCircle(m_BallPosition, BALL_RADIUS - BALL_OUTLINE, ballFill, ballOutline, BALL_OUTLINE);

		for (AABB& aabb : m_AABBs)
		{
			batchRenderer.RenderQuad(aabb.Center(), aabb.GetDimensions(), Vector2(0.5f, 0.5f), ColorList::DarkGreen);
		}

		batchRenderer.EndScene();
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		if (keyState == KeyState::Down)
		{
			if (keyCode == KeyCode::R)
			{
				Reset();
			}
			else if (keyCode == KeyCode::Space)
			{
				m_IsPaused = !m_IsPaused;
			}
		}
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{
		
	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{

	}

	void Game::Reset()
	{
		m_BallPosition = Vector2(GetHalfScreenWidth(), GetHalfScreenHeight());

		float speed = 800.0f;
		float degrees = Math::RandomFloat(60.0f, 120.0f);
		float radians = Math::DegreesToRadians(degrees);
		m_BallVelocity = Vector2(cos(radians), sin(radians)) * speed;

		m_IsPaused = true;
	}

	void Game::CheckBallCollision(float delta)
	{

		Vector2 position = m_BallPosition;
		Vector2 velocity = m_BallVelocity;

		Vector2 normals[NUM_EDGES] = { Vector2::Right, Vector2::Left, Vector2::Down, Vector2::Up };

		Vector2 displacementRemaining = m_BallVelocity * delta;

		bool collision = false;
		int numPasses = 0;
		LineSegment* ignoreEdge = nullptr;
		AABB* ignoreAABB = nullptr;

		do
		{
			numPasses++;
			collision = false;

			Vector2 start = position;
			Vector2 end = start + displacementRemaining;

			for (int i = 0; i < NUM_EDGES; i++)
			{
				//Ensure you don't check collision with the same edge twice
				if (&m_ScreenEdges[i] != ignoreEdge)
				{
					LineSegment path(start, end);
					Vector2 intersectionPoint;

					if (path.DoesIntersect(m_ScreenEdges[i], intersectionPoint) == true)
					{
						collision = true;

						//r = d - 2(d*n)n;
						velocity = velocity - 2.0f * (velocity.DotProduct(normals[i])) * normals[i];

						float distanceRemaining = (end - intersectionPoint).Length();
						displacementRemaining = velocity.Normalized() * distanceRemaining;

						position = intersectionPoint;

						//Ignore the edge we just collided with to ensure to 
						//we don't collide with it again on the next pass
						ignoreEdge = &m_ScreenEdges[i];

						break;
					}
				}
			}


			for (int i = 0; i < m_AABBs.size(); i++)
			{
				//Ensure you don't check collision with the same edge twice
				if (&m_AABBs[i] != ignoreAABB)
				{
					LineSegment path(start, end);
					Vector2 intersectionPoint;
					Vector2 collisionNormal;

					if(m_AABBs[i].DoesIntersectWithCircle(path, m_BallRadius, intersectionPoint, collisionNormal) == true)
					{
						collision = true;

						//r = d - 2(d*n)n;
						velocity = velocity - 2.0f * (velocity.DotProduct(collisionNormal)) * collisionNormal;

						float distanceRemaining = (end - intersectionPoint).Length();
						displacementRemaining = velocity.Normalized() * distanceRemaining;

						position = intersectionPoint;

						//Ignore the aabb we just collided with to ensure to 
						//we don't collide with it again on the next pass
						ignoreAABB = &m_AABBs[i];

						break;
					}
				}
			}



			if (collision == false)
			{
				position = start + displacementRemaining;
			}
		} while (collision && numPasses < NUM_PASSES);

		m_BallPosition = position;
		m_BallVelocity = velocity;
	}
}