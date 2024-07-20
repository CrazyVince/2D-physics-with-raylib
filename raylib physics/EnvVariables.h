#include "raylib.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define TARGET_FPS 240.0f

#define PHYSICS_TIME_STEP 1.0f / TARGET_FPS
#define PHYSICS_VELOSITY_ITERATIONS 6
#define PHYSICS_POSITION_ITERATIONS 2

#define CAMERA_SPEED 10.0f
#define CAMERA_ZOOM_SPEED 10.0f

#define CREATE_NOTHING_MODE 0
#define CREATE_STATIC_OBJECT_MODE 1
#define CREATE_DYNAMIC_OBJECT_MODE 2

static float deltaTime;

static Camera2D camera;

static b2Vec2 createObjectCorner1;
static b2Vec2 createObjectCorner2;