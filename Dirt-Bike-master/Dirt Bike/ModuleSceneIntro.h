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

	void CreateRoad();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	p2List<PhysBody3D*> Constraints;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	Cube* first_cube;
	PhysBody3D* ramp_1;

	Cube* second_cube;
	PhysBody3D* ramp_2;

	Cube* rect_1;
	PhysBody3D* body_rect_1;
	
	Cube* rect_2;
	PhysBody3D* body_rect_2;
	
	p2DynArray<Cube*> RoadCubes;
	p2DynArray<PhysBody3D*> bodyRoadCubes;
	
	p2DynArray<Cube*> barrierCubes;
	p2DynArray<PhysBody3D*> bodybarrierCubes;

	p2DynArray<Cylinder*> cylinders;
	p2DynArray<PhysBody3D*> bodycylinders;

	p2DynArray<Cube*> Jumps;
	p2DynArray<PhysBody3D*> bodyJumps;

	Cube* finish_1;
	PhysBody3D* bfinish_1;

	Cube* finish_2;
	PhysBody3D* bfinish_2;

	Cube* finish_3;
	PhysBody3D* bfinish_3;

	Cylinder* column_1;
	PhysBody3D* bcolumn_1;

	Cube* rotwall_1;
	PhysBody3D* brotwall_1;

	Cylinder* column_2;
	PhysBody3D* bcolumn_2;

	Cube* rotwall_2;
	PhysBody3D* brotwall_2;

	Cylinder* column_3;
	PhysBody3D* bcolumn_3;

	Cube* rotwall_3;
	PhysBody3D* brotwall_3;
};
