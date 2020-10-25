#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Car.hpp"
#include "Runner.hpp"

using namespace std;
using namespace sf;


int main() {
	// Fenêtre
	const Vector2u WINDOW_SIZE(800, 600);
	
	RenderWindow app(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y, 32), "My Camera");

	// Frames Per Second (FPS)
	app.setFramerateLimit(60); // limite la fenêtre à 60 images par seconde

	// Fond d'écran
	Texture backgroundImage, carImage, runnerImage;
	Sprite backgroundSprite, carSprite, runnerSprite;

	if (!backgroundImage.loadFromFile("../img/background.png") ||
		!carImage.loadFromFile("../img/car.png") ||
		!runnerImage.loadFromFile("../img/runner.png")) {
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

	runnerSprite.setTexture(runnerImage);
	runnerSprite.setTextureRect(rect);
	runnerSprite.setScale(sf::Vector2f(0.3f, 0.3f));

	Car car(790, 1215, 0, 0);
	Runner runner(rect, shift_x, shift_y, car);

	Vector2f center(car.getX(), car.getY());

	Vector2f halfSize(WINDOW_SIZE.x / 2.f, WINDOW_SIZE.y / 2.f);

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
		view.setCenter(car.getX(), car.getY());

		app.setView(view);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{
			car.turnLeft();
			carSprite.setRotation(car.getAngle());
			runnerSprite.setRotation(car.getAngle());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			car.turnRight();
			carSprite.setRotation(car.getAngle());
			runnerSprite.setRotation(car.getAngle());
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
		runnerSprite.setPosition(runner.getX(), runner.getY());
		runnerSprite.setTextureRect(rect);
		app.draw(carSprite);
		app.draw(runnerSprite);

		app.display();
	}

	return EXIT_SUCCESS;
}
