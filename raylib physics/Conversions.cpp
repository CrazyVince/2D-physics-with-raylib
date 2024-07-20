#include "raylib.h"
#include "box2d/box2d.h"
#include "EnvVariables.h"

b2Vec2 ConvertScreenToWorld(Vector2 input, Camera2D* camera)
{
	b2Vec2 output = {(input.x - camera->offset.x + (camera->target.x * camera->zoom)) / camera->zoom, (input.y - camera->offset.y + (camera->target.y * camera->zoom)) / camera->zoom};
	return output;
}