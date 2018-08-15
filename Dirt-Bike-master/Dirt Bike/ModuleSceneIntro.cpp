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
	Status = UPDATE_CONTINUE;

	Color plane_color(200, 100, 100);
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	CreateMenu();

	return Status;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	ImGui::Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateMenu()
{
	//Window size
	ImGui::SetNextWindowSize({ 200,300 });

	//Creates a new Window
	ImGui::Begin("ImGui Test");

	//Create a windo inside a window
	ImGui::BeginChild("Child 1", { 100,100 }, true);
	
	//Text inside the child window
	ImGui::Text("Press button");

	//Remember to close the Child!!
	ImGui::EndChild();
	
	//Creates a Text
	ImGui::Text("Press button");
	
	//Creates a button with its function
	if (ImGui::Button("Close"))
	{
		Status	= UPDATE_STOP;
	}

	ImGui::End();

	//Creates the example window
	ImGui::SetNextWindowPos({ 300, 100 });
	ImGui::ShowTestWindow();

	//open a window with the cpu information
	ImGui::SetNextWindowPos({ 900, 100 });
	ImGui::ShowMetricsWindow(false);

}

