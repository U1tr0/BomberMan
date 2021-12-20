#include "BoxCollider.h"

sf::Vector2f BoxCollider::getPivotPosition()
{
	return position + sf::Vector2f(rect.width / 2, rect.height / 2);
}
