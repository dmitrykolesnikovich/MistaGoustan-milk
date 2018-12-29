#include "Physics.h"

#include <vector>

#include "../components/BoxCollider.h"
#include "../components/Velocity.h"
#include "../core/Actor.h"

void Physics::onActorAdded(Actor& actor)
{
	BoxCollider* collider = actor.getComponent<BoxCollider>();
	Velocity* velocity = actor.getComponent<Velocity>();

	// The actor is fully dynamic (moves and collides)
	if (collider != nullptr && velocity != nullptr)
	{
		std::unique_ptr<DynamicNode> dynamic(new DynamicNode(actor));

		if (first_ == nullptr) 
		{
			first_ = dynamic.get();
			last_ = dynamic.get();
		}
		else if (last_ != nullptr)
		{
			last_->next = dynamic.get();

			dynamic->previous = last_;
			dynamic->next = nullptr;

			last_ = dynamic.get();
		}

		dynamicActors_.insert(std::make_pair(actor.id(), std::move(dynamic)));
	}
	// Actor only collides
	else if (collider != nullptr)
	{
		collidableActors_.insert(std::make_pair(actor.id(), collider));
	}
	// Actor only moves
	else if (velocity != nullptr)
	{
		movableActors_.insert(std::make_pair(actor.id(), velocity));
	}
}

void Physics::onActorDestroyed(Actor& actor)
{
	auto dynamicFound = dynamicActors_.find(actor.id());

	if (dynamicFound != dynamicActors_.end())
	{
		auto physicsObject = dynamicFound->second.get();

		if (physicsObject->previous != nullptr)
			physicsObject->previous->next = physicsObject->next;

		if (physicsObject->next != nullptr)
			physicsObject->next->previous = physicsObject->previous;

		if (physicsObject == first_)
			first_ = physicsObject->next;

		if (physicsObject == last_)
			last_ = physicsObject->previous;

		dynamicActors_.erase(actor.id());

		return;
	}

	auto movableFound = movableActors_.find(actor.id());

	if (movableFound != movableActors_.end()) 
	{
		movableActors_.erase(actor.id());
		return;
	}

	auto collidableFound = collidableActors_.find(actor.id());

	if (collidableFound != collidableActors_.end())
	{
		collidableActors_.erase(actor.id());
		return;
	}
}

void Physics::update()
{
	// Move objects
	for (auto& it : movableActors_) 
	{
		Actor& actor = it.second->actor();
		actor.position(actor.position() + it.second->value());
	}

	DynamicNode* current = first_;

	while (current != nullptr) 
	{
		Velocity* velocity = current->actor.getComponent<Velocity>();
		velocity->actor().position(velocity->actor().position() + velocity->value());

		BoxCollider* collider = current->actor.getComponent<BoxCollider>();	
		collider->updateBBox();

		// Check against static collidable actors
		for (auto& it : collidableActors_) 
		{
			if (collider->overlaps(it.second->rect()))
			{
				// There is an overlap
				Vector2d pos = current->actor.position();

				current->actor.position(pos.x - velocity->value().x, pos.y);
				collider->updateBBox();

				// If there is still an overlap after removing x overlap, then there is a y overlap.
				if (collider->overlaps(it.second->rect())) 
				{
					current->actor.position(pos.x, pos.y - velocity->value().y);
					collider->updateBBox();
				}
			}
		}

		current = current->next;
	}
}
