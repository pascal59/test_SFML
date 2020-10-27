#include "Runner.hpp"

Runner::Runner(sf::IntRect &rect, int shift_x, int shift_y, Car &car) : shift_x_(shift_x), shift_y_(shift_y), rect_(rect), car_(car) {}

void Runner::speedUp()
{
    if (clock.getElapsedTime().asSeconds() > 0.08) {
        rect_.left = rect_.left + 102;

        if (rect_.left >= 1020)
        {
            rect_.left = 204;
        }
        clock.restart();
    }
}

void Runner::speedDown() {
    rect_.top = 0;
    rect_.left = 0;
}

float Runner::getX() const {
    float angle = static_cast<float>(car_.getAngle() * M_PI / 180.0f);
    
    float dx = static_cast<float>(cos(M_PI + angle) * shift_x_ + sin(M_PI + angle) * shift_y_);
    return car_.getX() + dx;
}

float Runner::getY() const {
    float angle = static_cast<float>(car_.getAngle() * M_PI / 180.0f);
    
    auto dy = static_cast<float>(sin(M_PI + angle) * shift_x_ + cos(M_PI + angle) * shift_y_);
    return car_.getY() + dy;
}