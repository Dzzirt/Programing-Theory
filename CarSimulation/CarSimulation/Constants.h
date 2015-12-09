#pragma once

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const float CarAcceleration = 0.05f;
const float MaxCarSpeed = 10.f;
const sf::Vector2f StartCarPos = sf::Vector2f(50, 376);
const sf::Vector2f RearWheelPos = sf::Vector2f(62, 99);
const sf::Vector2f FrontWheelPos = sf::Vector2f(253, 99);
const unsigned int WindowWidth = 800U;
const unsigned int WindowHeight = 600U;
