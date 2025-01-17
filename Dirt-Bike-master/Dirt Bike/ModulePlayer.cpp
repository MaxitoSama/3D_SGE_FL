#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(1, 1, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 1000.0f;
	car.suspensionStiffness = 20.88f;
	car.suspensionCompression = 12.0f;
	car.suspensionDamping = 20;
	car.maxSuspensionTravelCm = 700.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.8f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.6f;
	float suspensionRestLength = 1.1f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 2;
	car.wheels = new Wheel[2];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.9f*wheel_width, connection_height, half_length*1.1f - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.9 * wheel_width, connection_height, - half_length*1.1f + wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = false;
	car.wheels[1].drive = true;
	car.wheels[1].brake = true;
	car.wheels[1].steering = false;

	//// REAR-LEFT ------------------------
	//car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	//car.wheels[2].direction = direction;
	//car.wheels[2].axis = axis;
	//car.wheels[2].suspensionRestLength = suspensionRestLength;
	//car.wheels[2].radius = wheel_radius;
	//car.wheels[2].width = wheel_width;
	//car.wheels[2].front = false;
	//car.wheels[2].drive = false;
	//car.wheels[2].brake = true;
	//car.wheels[2].steering = false;

	//// REAR-RIGHT ------------------------
	//car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	//car.wheels[3].direction = direction;
	//car.wheels[3].axis = axis;
	//car.wheels[3].suspensionRestLength = suspensionRestLength;
	//car.wheels[3].radius = wheel_radius;
	//car.wheels[3].width = wheel_width;
	//car.wheels[3].front = false;
	//car.wheels[3].drive = false;
	//car.wheels[3].brake = true;
	//car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 4, 0);

	init_matrix = mat4x4(
		0.5253220f, 0, 0.8509035f, 0,
		0, 1, 0, 0,
		-0.8509035f, 0, 0.5253220f, 0,
		0, 0, 0, 1);

	vehicle->SetTransform(init_matrix.M);

	//vehicle->SetTransform(rotation_m.M);
	race_time.Start();
	race_time.Stop();
	laps = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	float posx = vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX();
	float posz = vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION*2.0f;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh()>0) 
		{
			brake = BRAKE_POWER;
		}	
		else
		{
			acceleration = -MAX_ACCELERATION;
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		vehicle->vehicle->getRigidBody()->setLinearVelocity({ 0,0,0 });
		vehicle->SetPos(0, 5, 0);
		vehicle->SetTransform(init_matrix.M);
		race_time.Start();
		race_time.Stop();
		start_race = false;
		laps = 0;
	}

	if (posx <= -29 && posx >= -41 && posz <= 50 && posz>=49)
	{
		if (!start_race)
		{
			start_race = true;
			race_time.Start();
			laps = 1;
			App->audio->PlayFx(1);
		}
		else
		{
			if (checkpoint)
			{
				laps++;
				checkpoint = false;
			}
			if (laps == 4)
			{
				laps = 0;
				race_time.Stop();
			}
		}
	}
	
	if (posx <= -55 && posx >= -67 && posz <= 64 && posz >= 60)
	{
		checkpoint = true;
	}


	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	Player_camera();

	
	LOG("x=%.1f", posx);
	LOG("z=%.1f", posz);

	return UPDATE_CONTINUE;
}


void ModulePlayer::Player_camera()
{
	car_pos = vehicle->vehicle->getChassisWorldTransform();
	car_origin = { car_pos.getOrigin().getX(),car_pos.getOrigin().getY(),car_pos.getOrigin().getZ() };
	car_dir = { car_pos.getBasis().getColumn(2).getX(),car_pos.getBasis().getColumn(2).getY(),car_pos.getBasis().getColumn(2).getZ()};

	cam_new_pos = car_origin - 5 * car_dir;

	App->camera->Position.x = cam_new_pos.x;
	App->camera->Position.y = cam_new_pos.y;
	App->camera->Position.z = cam_new_pos.z;

	App->camera->Position.y = car_origin.y + 5;
}


