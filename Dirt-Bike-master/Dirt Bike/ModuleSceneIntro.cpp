#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Init()
{
	ImGui_ImplSdl_Init(App->window->window);
	return true;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("music/Song_1.ogg");
	

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	ImGui_ImplSdl_Shutdown();

	return true;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
	ImGui_ImplSdl_NewFrame(App->window->window);
	return UPDATE_CONTINUE;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Color plane_color(200, 100, 100);
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	ImGui::Text("Press button");
	if(ImGui::Button("Close"))
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	ImGui::Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateRoad()
{
	ShapeSize Road[17] = { { 12, 1, 28 * 2 },{ 12, 1, 156 },{ 12, 1, 24 },{ 12, 1, 24 },{ 12, 1, 24 },
	{ 12,1,71 },{ 12, 1, 24 },{ 12, 1, 24 },{ 12, 1, 24 },{ 12, 1, 100 },{ 12, 1, 24 },{ 12, 1, 100 },
	{ 12, 1, 24 },{ 12, 1, 184.8f },{ 12, 1, 14 },{ 12, 1, 14 },{ 12, 1, 14 } };

	vec3 RoadPos[17] = { { -15, 0.99f, 15 },{ -35, 1, 50 },{ -27.6f, 0.99f, 133.6f },{ -10.0f, 1, 141 },
	{ 7.7f, 0.99f, 133.6f },{ 15.1f, 1, 92.5f },{ 22.55f, 0.99f, 51.4f },{ 40.0f, 1, 44.1f },{ 57.9f, 0.99f, 51.4f },
	{ 65, 1, 107.0f },{ 57.9f, 0.99f,162.4f },{ 2, 1, 169.5f },{ -53.9f, 0.99f, 162.4f },{ -61, 1, 64.2f },{ -57.0f, 0.99f, -30.2f },
	{ -38.8f, 0.99f, -30.2f },{ -47.8f, 0.99f, -34.0f } };

	Rotation RoadRot[17] = { { -45,{ 0,1,0 } },{0,{0,1,0}}, { 45,{ 0,1,0 } }, { 90,{ 0,1,0 } },{ -45,{ 0,1,0 } },
	{ 0,{ 0,1,0 }},{ -45,{ 0,1,0 } },{ 90,{ 0,1,0 } },{ 45,{ 0,1,0 } },{ 0,{ 0,1,0 }},{ -45,{ 0,1,0 } },{ 90,{ 0,1,0 } },
		{ 45,{ 0,1,0 } },{ 0,{ 0,1,0 }},{ -45,{ 0,1,0 } },{ 45,{ 0,1,0 } },{ 90,{ 0,1,0 } } };

	for (int i = 0; i < 17; i++)
	{
		RoadCubes.PushBack(new Cube(Road[i].sizeX, Road[i].sizeY, Road[i].sizeZ));
		RoadCubes[i]->SetPos(RoadPos[i].x, RoadPos[i].y, RoadPos[i].z);
		RoadCubes[i]->SetRotation(RoadRot[i].angle, RoadRot[i].axis);
		bodyRoadCubes.PushBack(App->physics->AddBody(*(RoadCubes[i]), 0.0f));
	}

	ShapeSize barriers[35] = { { 1, 5, 52 },{ 1, 5, 44 },{ 1, 5, 87 },{ 1, 5, 49 },{ 1, 5, 153 },
	{ 1, 5, 16 },{ 1, 5, 30 },{ 1, 5, 25 },{ 1, 5, 16 },{ 1, 5, 30 },{ 1, 5, 15 },{ 1, 5, 68 },
	{ 1, 5, 64 },{ 1, 5, 15 },{ 1, 5, 28 },{ 1, 5, 15 },{ 1, 5, 24 },{ 1, 5, 16 },{ 1, 5, 27.5f },
	{ 1, 5, 92 },{ 1, 5, 101 },{ 1, 5, 27 },{ 1, 5, 15 },{ 1, 5, 104 },{ 1, 5, 93 },{ 1, 5, 28 },
	{ 1, 5, 15 },{ 1, 5, 184.8f },{ 1, 5, 176.8f },{ 1, 5, 18 },{ 1, 5, 6 },{ 1, 5, 16 },{ 1, 5, 6 },
	{ 1, 5, 18 },{ 1, 5, 5.5 } };

	vec3 barriersPos[35] = { { -10, 0.99f, 19 },{ -13, 0.99f, 3.5f },{ -28.5f, 1, 80.2f },{ -28.5f, 1, -5.5f },
	{ -41.5f, 1, 51.8f },{ -23.f, 1, 129 },{ -31.f, 1, 138.f },{ -10.0f, 1, 147 },{ -10.0f, 1, 134.5f },
	{ 11.f, 0.99f, 136.f },{ 3.5f, 0.99f, 129.f },{ 8.7f, 0.99f, 89.5f },{ 21.7f, 0.99f, 93.5f },{ 27.f, 0.99f, 56.f },
	{ 18.f, 0.99f, 47.f },{ 40.5f, 1, 50.5f },{ 40.0f, 1, 37.5f },{ 53.f, 0.99f, 55.6f },{ 62.5f, 0.99f, 48.f },
	{ 58.5f, 1, 107.0f },{ 70.5f, 1, 107.0f },{ 61.9f, 0.99f, 166.4f },{ 53.4f, 0.99f, 157.8f },{ 1, 1, 175.5f },
	{ 2, 1, 163.f },{ -57.9f, 0.99f, 166.4f },{ -49.3f, 0.99f, 157.9f },{ -67.5, 1, 64.2f },{ -54.5, 1, 64.6f },
	{ -61.0f, 0.99f, -34.2f },{ -52.4f, 0.99f, -25.7f },{ -47.8f, 0.99f, -40.0f },{ -47.7f, 0.99f, -27.7f },
	{ -33.6f, 0.99f, -33.5f },{ -43.25f, 0.99f, -26.05f } };

	Rotation barriersRot[35] = { {-45, { 0,1,0 }},{-45, { 0,1,0 }},{0,{0,1,0}},{0,{0,1,0}},{0,{0,1,0}},{45, { 0,1,0 }},
	{45, { 0,1,0 }},{90, { 0,1,0 }},{90, { 0,1,0 }},{-45, { 0,1,0 }},{-45, { 0,1,0 }},{0,{0,1,0}},{0,{0,1,0}},{-45, { 0,1,0 }},
	{-45, { 0,1,0 }},{90, { 0,1,0 }},{90, { 0,1,0 }},{45, { 0,1,0 }},{45, { 0,1,0 }},{0,{0,1,0}},{0,{0,1,0}},{-45, { 0,1,0 }},
	{-45, { 0,1,0 }},{90, { 0,1,0 }},{90, { 0,1,0 }},{45, { 0,1,0 }},{45, { 0,1,0 }},{0,{0,1,0}},{0,{0,1,0}},{-45, { 0,1,0 }},
	{-45, { 0,1,0 }},{90, { 0,1,0 }},{90, { 0,1,0 }},{45, { 0,1,0 }},{45, { 0,1,0 }} };

	for (int i = 0; i < 35; i++)
	{
		barrierCubes.PushBack(new Cube(barriers[i].sizeX, barriers[i].sizeY, barriers[i].sizeZ));
		barrierCubes[i]->SetPos(barriersPos[i].x, barriersPos[i].y, barriersPos[i].z);
		barrierCubes[i]->SetRotation(barriersRot[i].angle, barriersRot[i].axis);
		barrierCubes[i]->color = Blue;
		bodybarrierCubes.PushBack(App->physics->AddBody(*(barrierCubes[i]), 0.0f));

	}

	ShapeSize cyl[5] = { { 2.0f, 12 ,0},{ 3.0f, 12 ,0},{ 2.0f, 12 ,0},{ 3.0f, 12 ,0},{ 2.0f, 12 ,0} };
	vec3 cylPos[5] = { { 15.1f, 1, 105 },{ 15.1f, 0, 92.5f },{ 15.1f, 1, 80 },{ 15.1f, 0, 115 },{ 15.1f, 1, 70 } };
	
	for (int i = 0; i < 5; i++)
	{
		cylinders.PushBack(new Cylinder(cyl[i].sizeX, cyl[i].sizeY));
		cylinders[i]->SetPos(cylPos[i].x, cylPos[i].y, cylPos[i].z);
		cylinders[i]->color = Red;
		bodycylinders.PushBack(App->physics->AddBody(*(cylinders[i]), 0.0f));
	}

	ShapeSize jumpsshape[6] = { { 12, 1, 10 },{ 12, 1, 10 },{ 12, 1, 10 },
	{ 10, 1, 10 },{ 20, 1, 10 },{ 10, 1, 10 }};

	vec3 jumpsPos[6] = { { -35, 1, 70 },{ -35, 2.8f, 80 },{ -35, 1, 90 },
	{ 20, 1, 169.5f },{ 2, 2.8f, 169.5f },{ -14, 1, 169.5f } };

	Rotation jumpRot[6] = { { -20,{ 1,0,0 } },{ 0,{ 0,1,0 } },{ 20,{ 1,0,0 } },{ -20,{ 0,0,1 } },
	{ 0,{ 0,1,0 } },{ 20,{ 0,0,1 } }};

	for (int i = 0; i < 6; i++)
	{
		Jumps.PushBack(new Cube(jumpsshape[i].sizeX, jumpsshape[i].sizeY, jumpsshape[i].sizeZ));
		Jumps[i]->SetPos(jumpsPos[i].x, jumpsPos[i].y, jumpsPos[i].z);
		Jumps[i]->SetRotation(jumpRot[i].angle, jumpRot[i].axis);
		bodyJumps.PushBack(App->physics->AddBody(*(Jumps[i]), 0.0f));
	}

}

