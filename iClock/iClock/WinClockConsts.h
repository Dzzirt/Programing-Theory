#pragma once


const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const unsigned int WindowWidth = 600;
const unsigned int WindowHeight = 600;

const float MinLineWidth = 4.f;
const float MinLineHeight = 250.f;

const float SecLineWidth = 2.f;
const float SecLineHeight = 270.f;

const float HourLineWidth = 6.f;
const float HourLineHeight = 180.f;

const int LabelsCount = 12;
const int LabelStepInDegree = 30;
const float LabelWidth = 4.f;
const float LabelHeight = 40.f;

const float HourStepInHalfDay = 30.f;
const float MinStepInHour = 6.f;
const float MinStepInHalfDay = 0.5f;
const float SecStepInDegree = 6.f;
const float SecStepInMin = 0.1f;
const float SecStepInHalfDay = 0.008f;

const float MainCircleRadius = 300.f;
const size_t MainCirclePointCount = 100;

const float MiddleCircleRadius = 10.f;
const size_t MiddleCirclePointCount = 50;
