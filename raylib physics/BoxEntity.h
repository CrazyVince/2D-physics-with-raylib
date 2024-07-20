#include "box2d/box2d.h"
#include "raylib.h"

struct BoxEntity
{
	b2Vec2 size;
	Texture2D* texture;
	b2Body* physicsBody;
};

void CreateBoxEntity(b2BodyType type, b2Vec2 position, b2Vec2 size, float rotation, float friction, Texture2D* texture, b2World* world, std::list<BoxEntity>* objectsList);
void DrawBoxEntity(BoxEntity* boxEntity);