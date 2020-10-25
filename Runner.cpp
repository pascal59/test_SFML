#include "Car.hpp"

Runner::Runner(float x, float y, float angle, float speed,
               sf::IntRect &rect, int shift_x, int shift_y) : 
               shift_x(shift_x), shift_y(shift_y), rect(rect), Car(x, y, angle, speed){}

void Runner::speedUp() {
    Car::speedUp();
    if (clock.getElapsedTime().asSeconds() > 0.08)
    {
        rect.left = rect.left + 102;

        if (rect.left >= 1020)
        {
            //rect.top = 270;
            rect.left = 204;
        }
        else if (rect.top > 200 && rect.left > 190)
        {
            rect.top = 180;
            rect.left = 0;
        }
        clock.restart();
    }
    else
    {
    }
}

void Runner::speedDown()
{
    Car::speedDown();
    rect.top = 0;
    rect.left = 0;
}

void Runner::turnLeft()
{

    Car::turnLeft();
    Car::move(static_cast<float>((cos(Car::getAngle()* M_PI / 180.0)+
    cos(1.f * M_PI / 180.0))*shift_x)/100,
              static_cast<float>((sin(Car::getAngle()* M_PI / 180.0)-
    sin(1.f * M_PI / 180.0))*shift_x)/100);
}
