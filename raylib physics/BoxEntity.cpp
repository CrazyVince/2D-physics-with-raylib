#include <list>
#include <iostream>

#include "BoxEntity.h"
#include "Conversions.h"
#include "EnvVariables.h"

void CreateBoxEntity(b2BodyType type, b2Vec2 position, b2Vec2 size, float rotation, float friction, Texture2D* texture, b2World* world, std::list<BoxEntity>* objectsList)
{
	BoxEntity boxEntity = {};
	boxEntity.size = size;
	boxEntity.texture = texture;

	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.angle = rotation / 57.29578;

	boxEntity.physicsBody = world->CreateBody(&bodyDef);

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox(size.x / 2, size.y / 2);

	b2FixtureDef bodyFixture;
	bodyFixture.density = 1;
	bodyFixture.friction = friction;
	bodyFixture.shape = &bodyShape;

	boxEntity.physicsBody->CreateFixture(&bodyFixture);

	objectsList->push_back(boxEntity);
}

void DrawBoxEntity(BoxEntity* boxEntity)
{
	b2Vec2 position = boxEntity->physicsBody->GetPosition();
	float rotation = boxEntity->physicsBody->GetAngle() * 57.29578;

	Rectangle source = { 0, 0, boxEntity->texture->width, boxEntity->texture->height };
	Rectangle dest = { position.x, position.y, boxEntity->size.x, boxEntity->size.y };
	Vector2 origin = { boxEntity->size.x / 2, boxEntity->size.y / 2 };

	DrawTexturePro(*boxEntity->texture, source, dest, origin, rotation, WHITE);
}