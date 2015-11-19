#pragma once
#include <SFML/Graphics.hpp>


const int ArrowWidth = 80;
const int ArrowhHeight = 250;
const int ArrowMarg = 10;
const int MaxImgSize = 24377174;

const int ZoomButtonsWidth = 60;
const int ZoomButtonsHeight = 40;
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const float WindowWidth = 800.f;
const float WindowHeight = 600.f;

const float MaxZoom = 8.f;
const float MinZoom = 1 / 8.f;

enum State {
	PREVIOUS,
	NEXT
};