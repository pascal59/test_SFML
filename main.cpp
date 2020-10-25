#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Car.hpp"

using namespace std;
using namespace sf;

const Vector2u WINDOW_SIZE(800, 600);

int main()
{
	// Fenêtre
	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "TP Camera");

	// Frames Per Second (FPS)
	app.setFramerateLimit(60); // limite la fenêtre à 60 images par seconde

	// Fond d'écran
	Texture backgroundImage, carImage, player_forwardImage;
	Sprite backgroundSprite, carSprite, player_forwardSprite;

	if (!backgroundImage.loadFromFile("../img/background.png") ||
		!carImage.loadFromFile("../img/car.png") ||
		!player_forwardImage.loadFromFile("../img/Player_forward.png"))
	{
		cerr << "Erreur pendant le chargement des images" << endl;
		return EXIT_FAILURE; // On ferme le programme
	}
	backgroundSprite.setTexture(backgroundImage);
	carSprite.setTexture(carImage);
	carSprite.setPosition(sf::Vector2f(20, 34));
	carSprite.setScale(sf::Vector2f(0.5, 0.5));

	sf::IntRect rect;

	rect.top = 0;
	rect.left = 0;

	rect.width = 102;
	rect.height = 115;

	constexpr int shift_x = 50;
	constexpr int shift_y = 10;

	player_forwardSprite.setTexture(player_forwardImage);
	player_forwardSprite.setTextureRect(rect);
	player_forwardSprite.setPosition(sf::Vector2f(790 - shift_x, 1215 - shift_y));
	player_forwardSprite.setScale(sf::Vector2f(0.3f, 0.3f));

	Car car(790, 1215, 0, 0);
	Runner runner(790 - shift_x, 1215 - shift_y, 0, 0, rect, shift_x, shift_y);

	Vector2f center(car.getX(), car.getY());
	player_forwardSprite.setPosition(sf::Vector2f(car.getX() - shift_x, car.getY() - shift_y));

	Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);
	//	Vector2f halfSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
	View view(center, halfSize);
	app.setView(view);
	
	while (app.isOpen()) // Boucle principale
	{
		Event event;
		while (app.pollEvent(event)) // Boucle des évènements de la partie pause
		{
			if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == Event::Closed)
			{
				app.close();
			}
		}

		car.move();
		runner.move();
		view.setCenter(car.getX(), car.getY());

		app.setView(view);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			car.turnLeft();
			carSprite.setRotation(car.getAngle());
			runner.turnLeft();
			player_forwardSprite.setRotation(car.getAngle());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			car.turnRight();
			carSprite.setRotation(car.getAngle());
			runner.turnRight();
			player_forwardSprite.setRotation(car.getAngle());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			car.speedUp();
			runner.speedUp();
		}
		else
		{
			car.speedDown();
			runner.speedDown();
		}

		// Affichages
		app.clear();
		app.draw(backgroundSprite);

		carSprite.setPosition(car.getX(), car.getY());
		player_forwardSprite.setPosition(runner.getX(), runner.getY());
		player_forwardSprite.setTextureRect(rect);
		app.draw(carSprite);
		app.draw(player_forwardSprite);

		app.display();
	}

	return EXIT_SUCCESS;
}
