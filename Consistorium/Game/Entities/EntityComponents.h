#pragma once

typedef struct EntityComponents
{
	GameEngine::RenderComponent* renderComponent;
	GameEngine::AnimationComponent* animationComponent;
	b2Body* body;
} EntityComponents;