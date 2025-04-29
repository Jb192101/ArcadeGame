#include "SpaceShipModel.h"
# define M_PI           3.14159265358979323846

SpaceShipModel::SpaceShipModel(Vector2D pos) {
	this->position = pos;
	this->velocity.setX(0.0f);
	this->velocity.setY(0.0f);
}

void SpaceShipModel::Update(float deltaTime, int w, int h) {
    if (thrusting) {
        Vector2D thrustDirection = Vector2D(1, 0).rotated(rotation);
        velocity += thrustDirection * thrustPower * deltaTime;

        // Ограничение максимальной скорости
        float maxSpeed = 0.5f;
        if (velocity.length() > maxSpeed) {
            velocity = velocity.normalized() * maxSpeed;
        }
    }

    position += velocity * deltaTime;

    // Зацикливание позиции при выходе за границы
    //if (position.x < 0) position.x += 1;
    //if (position.x > 1) position.x -= 1;
    //if (position.y < 0) position.y += 1;
    //if (position.y > 1) position.y -= 1;

    if (invincibilityTime > 0) {
        invincibilityTime -= deltaTime;
    }
}

void SpaceShipModel::rotate(float angle) {
    rotation += angle;
}

void SpaceShipModel::setThrusting(bool isThrusting) {
    thrusting = isThrusting;
}

BulletModel SpaceShipModel::shoot() {
    Vector2D bulletDirection = Vector2D(1, 0).rotated(rotation);
    Vector2D bulletPosition = position + bulletDirection * 0.02f;
    Vector2D bulletVelocity = velocity + bulletDirection * 0.5f;
    return BulletModel(bulletPosition, bulletVelocity, 2.0f); // Время жизни 2 секунды
}

bool SpaceShipModel::isInvincible() const {
    return invincibilityTime > 0;
}