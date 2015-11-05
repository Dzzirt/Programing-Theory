#pragma once
#include <SFML/Graphics.hpp>


const int ArrowWidth = 150;
const int ArrowhHeight = 400;
const int ArrowMarg = 10;
const int MaxImgSize = 24377174;

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const float WindowWidth = 800.f;
const float WindowHeight = 600.f;

enum State {
	PREVIOUS,
	NEXT
};