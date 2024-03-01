#pragma once
#include <GameDev2D.h>

//ship


const float c_acceleration = 150.0f;
const float c_angularAccel = 6.0f;
const int c_maxSpeed = 200;
const int c_minSpeed = 30;
const GameDev2D::Vector2 VELOCITY(170.0f, 40.0f);
const float RADIUS = 25.0f;
const float OUTLINE = 4.0f;
const float c_ShipSize = 30.0f;


//asteroids

const float c_asteroidMaxSpeed = 150.0f;
const float c_asteroidMinSpeed = 75.0f;
const float c_angularAsteroidAccelMax = 2.0f;
const float c_angularAsteroidAccelMin = 0.1f;


//bullet 

const float c_bulletSpeed = 300.0f;
const int c_ammoCount = 20;

//Shield

const int c_shieldAmount = 3; 