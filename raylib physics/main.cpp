#include <iostream>
#include <list>
#include <string>

#include "raylib.h"
#include "box2d/box2d.h"
#include "BoxEntity.h"
#include "Conversions.h"

#include "EnvVariables.h"

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "physics test");
	SetTargetFPS((int)TARGET_FPS);

	camera.offset = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	camera.rotation = 0;
	camera.zoom = 10;

	Texture2D cubeTexture = LoadTexture("resources/textures/physics_cube.png");

	b2World world = b2World(b2Vec2{ 0.0f, 10.0f });
	std::list<BoxEntity> objects;

	int createObjectMode = CREATE_NOTHING_MODE;

	b2Vec2 createObjectCorner1;
	b2Vec2 createObjectCorner2;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		deltaTime = GetFrameTime();

		world.Step(PHYSICS_TIME_STEP, PHYSICS_VELOSITY_ITERATIONS, PHYSICS_POSITION_ITERATIONS);

		//camera controls
		if (IsKeyDown(KEY_RIGHT))
		{
			camera.target.x += CAMERA_SPEED * deltaTime;
		}
		if (IsKeyDown(KEY_LEFT))
		{
			camera.target.x -= CAMERA_SPEED * deltaTime;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			camera.target.y += CAMERA_SPEED * deltaTime;
		}
		if (IsKeyDown(KEY_UP))
		{
			camera.target.y -= CAMERA_SPEED * deltaTime;
		}
		if (IsKeyDown(KEY_I))
		{
			camera.zoom += CAMERA_ZOOM_SPEED * deltaTime;
		}
		if (IsKeyDown(KEY_O))
		{
			camera.zoom -= CAMERA_ZOOM_SPEED * deltaTime;
		}

		//create objects controls
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && createObjectMode != CREATE_NOTHING_MODE)
		{
			createObjectCorner1 = ConvertScreenToWorld(GetMousePosition(), &camera);
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && createObjectMode != CREATE_NOTHING_MODE)
		{
			createObjectCorner2 = ConvertScreenToWorld(GetMousePosition(), &camera);

			b2Vec2 size = {};
			b2Vec2 position = {};
			b2BodyType type;

			if (createObjectCorner2.x > createObjectCorner1.x)
			{
				size.Set(createObjectCorner2.x - createObjectCorner1.x, 0.0f);
				position.Set(createObjectCorner1.x + size.x / 2, 0.0f);
			}
			else
			{
				size.Set(createObjectCorner1.x - createObjectCorner2.x, 0.0f);
				position.Set(createObjectCorner2.x + size.x / 2, 0.0f);
			}

			if (createObjectCorner2.y > createObjectCorner1.y)
			{
				size.Set(size.x, createObjectCorner2.y - createObjectCorner1.y);
				position.Set(position.x, createObjectCorner1.y + size.y / 2);
			}
			else
			{
				size.Set(size.x, createObjectCorner1.y - createObjectCorner2.y);
				position.Set(position.x, createObjectCorner2.y + size.y / 2);
			}

			if (createObjectMode == CREATE_STATIC_OBJECT_MODE) type = b2_staticBody;
			else type = b2_dynamicBody;

			CreateBoxEntity(type, position, size, 0.0f, 0.3f, &cubeTexture, &world, &objects);
		}

		if (IsKeyPressed(KEY_U))
		{
			createObjectMode++;
			if (createObjectMode > CREATE_DYNAMIC_OBJECT_MODE) createObjectMode = CREATE_NOTHING_MODE;
		}


		BeginMode2D(camera);

		for (auto e : objects)
		{
			DrawBoxEntity(&e);
		}

		EndMode2D();

		int fps = GetFPS();
		std::string fpsText = "fps: ";
		fpsText.append(std::to_string(fps));
		DrawText(fpsText.c_str(), 0, 0, 20, LIGHTGRAY);
		DrawText("current create mode: ", 0, SCREEN_HEIGHT - 20, 20, LIGHTGRAY);

		std::string createObjectModeText;
		Color createObjectModeTextColor;

		if (createObjectMode == CREATE_NOTHING_MODE)
		{
			createObjectModeText = "DISABLED";
			createObjectModeTextColor = RED;
		}
		if (createObjectMode == CREATE_STATIC_OBJECT_MODE)
		{
			createObjectModeText = "STATIC";
			createObjectModeTextColor = BLUE;
		}
		if(createObjectMode == CREATE_DYNAMIC_OBJECT_MODE)
		{
			createObjectModeText = "DYNAMIC";
			createObjectModeTextColor = GREEN;
		}
		DrawText(createObjectModeText.c_str(), 230, SCREEN_HEIGHT - 20, 20, createObjectModeTextColor);

		EndDrawing();
	}

	return 0;
}