#include "Pickup.h"
#include "Player.h"

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player") {
		m_destroyed = true;
	}
}
