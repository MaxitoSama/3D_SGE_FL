#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#include "ImGui\imgui.h"
#include "ImGui\imgui_impl_sdl.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

struct ShapeSize {
	float sizeX;
	float sizeY;
	float sizeZ;
};

struct Rotation {
	float	angle;
	vec3	axis;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool CleanUp();

	void CreateMenu();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	char title[128];
	int fps;

	update_status Status;
	
};
