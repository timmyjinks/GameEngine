#include "Pickup.h"
#include "Player.h"

void Pickup::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		dynamic_cast<Player*>(actor)->SetFireModifier(0.5f);
		m_destroyed = true;
	}
}
