#pragma once

#include <vector>

#include "IRenderable.h"

struct XY {
	XY(float _x, float _y) : x(_x), y(_y) {}
	float x, y;
};

struct AABB {
	AABB(XY _center, XY _halfDimension) : center(_center), halfDimension(_halfDimension) {}

	bool containsPoint(GameEngine::IRenderable* item) {
		XY p(item->getPosition().x * 50, item->getPosition().y * 50);
		return ((p.x > center.x - halfDimension.x && p.x <= center.x + halfDimension.x) &&
			(p.y > center.y - halfDimension.y && p.y <= center.y + halfDimension.y));
	}

	bool intersectsAABB(AABB& other) {
		float newWidth = other.halfDimension.x * 2;
		float newHeight = other.halfDimension.x * 2;
		return ((other.center.x - newWidth < center.x) && (other.center.x + newWidth > center.x)) ||
			((other.center.y - newHeight < center.y) && (other.center.y + newHeight > center.y));
	}

	XY center;
	XY halfDimension;
};

class Quadtree {
public:
	Quadtree(XY, XY);

	Quadtree(XY, XY, int);

	bool insert(GameEngine::IRenderable*);

	bool remove(GameEngine::IRenderable*);

	void subdivide();

	void queryRange(std::vector<GameEngine::IRenderable*>&, AABB&);

	void clear();

	bool getCollision(std::vector<GameEngine::IRenderable*>);

	AABB boundary;

	int nodeCapacity;

	Quadtree *NW;
	Quadtree *NE;
	Quadtree *SW;
	Quadtree *SE;

	std::vector<GameEngine::IRenderable*> points;
};