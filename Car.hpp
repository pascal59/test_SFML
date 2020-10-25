#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>

class Car
{
public:
	Car(float x, float y, float angle, float speed);

	float getX() const;
	float getY() const;
	float getAngle() const;

	void move();

	void move(float dx, float dy);

	void turnLeft();
	void turnRight();
	void speedUp();
	void speedDown();

private:
	float _x, _y;
	float _angle;
	float _speed;
};

class Runner : public Car
{
private:
	sf::Clock clock;
	sf::IntRect &rect;
	int shift_x;
	int shift_y;

public:
	Runner(float x, float y, float angle, float speed,
		   sf::IntRect &rect, int shift_x, int shift_y);

	void speedUp();
	void speedDown();


	void turnLeft();

};