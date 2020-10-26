#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Car.hpp"

class Runner {
private:
	sf::Clock clock;
	sf::IntRect &rect_;
	Car    &car_;
	int shift_x_;
	int shift_y_;

public:
	Runner(sf::IntRect &rect, int shift_x, int shift_y, Car &car);

	void speedUp();
	void speedDown();

	float getX() const;
	float getY() const;

	void turnRight();
	void turnLeft();

	void move();
};