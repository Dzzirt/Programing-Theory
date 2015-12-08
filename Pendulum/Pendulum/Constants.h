#pragma once


const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const unsigned int WinWidth = 800;
const unsigned int WinHeight = 600;

const float StartAngle = 30.f;
const float PendulumDeltaSpeed = 0.01f;
const float CogwheelDeltaSpeed = 0.5f;

const sf::Vector2f LeftCogwheelPos = sf::Vector2f(100, 200);
const sf::Vector2f RightCogwheelPos = sf::Vector2f(257, 246);
const sf::Vector2f PendulumPos = sf::Vector2f(550, 200);