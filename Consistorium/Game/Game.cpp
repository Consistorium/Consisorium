#include "Game.h"

Game::Game(SDL_Window* window)
	:Window(window),
	renderer_(window),
	gravity_(0.0f, -10.0f)
{	
}

Game::~Game()
{
}

void Game::Init()
{
	world_ = new b2World(gravity_);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world_->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 9.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	//The suggested iteration count for Box2D is 8 for velocity and 3 for position.
	timeStep_ = 1.0f / 60.0f;
	velocityIterations_ = 8;
	positionIterations_ = 3;
}

void Game::Run()
{
	Init();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 10.0f);
	b2Body* body = world_->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	Player player(body->GetPosition(), "mainCharacter.png");
	player.setBody(body);
	player.setBodyDef(bodyDef);

	double previousTicks = 0L;
	double currentTicks = 0L;
	double deltaTicks = 0.0;

	SDL_Event e;

	renderer_.AddRenderable(&player);

	while (true) {
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				handleKeyPress(e, &player, deltaTicks);
			}
		}

		world_->Step(timeStep_, velocityIterations_, positionIterations_);

		b2Vec2 position = player.getBody()->GetPosition();
		float32 angle = player.getBody()->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

		currentTicks = SDL_GetTicks();
		deltaTicks = currentTicks - previousTicks;
		if (deltaTicks == 0)
		{
			deltaTicks = 1;
		}
		deltaTicks /= 1000;

		renderer_.RenderAll();

		previousTicks = currentTicks;
	}
}

void handleKeyPress(SDL_Event e, Player* player, float deltaTicks) 
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LEFT:
		moveCharacter(player, deltaTicks, -1);
	case SDLK_RIGHT:
		moveCharacter(player, deltaTicks, 1);
		break;
	}
}

void moveCharacter(Player* player, float deltaTicks, int direction)
{
	b2Vec2 position = player->getPosition();
	position.Set(position.x + direction * player->getSpeed() * deltaTicks, position.y);
	player->setPosition(position);
}