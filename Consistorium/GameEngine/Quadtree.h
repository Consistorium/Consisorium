#pragma once

#include <vector>
#include "IRenderable.h"

struct XY {
	XY(float _x, float _y) : x(_x), y(_y) {}
	float x, y;
};

struct AABB {
	int halfDiag;
	AABB(XY _center, XY _halfDimension) : center(_center), halfDimension(_halfDimension), halfDiag(0)
	{
		halfDiag = std::sqrt(std::pow(halfDimension.x, 2) + std::pow(halfDimension.y, 2));
	}

	bool containsPoint(GameEngine::IRenderable* item) {
		XY p(item->getPosition().x * 50, item->getPosition().y * 50);
		return ((p.x > center.x - halfDimension.x && p.x <= center.x + halfDimension.x) &&
			(p.y > center.y - halfDimension.y && p.y <= center.y + halfDimension.y));
	}

	float getHalfDiag() {
		return halfDiag;
	}

	bool intersectsAABB(AABB& other) {
		float x1 = other.center.x;
		float y1 = other.center.y;
		float x2 = center.x;
		float y2 = center.y;
		float d = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

		if (d >= getHalfDiag() + other.getHalfDiag())
		{
			return false;
		}
		return true;
		/*float biggerHalfWidth = std::max(other.halfDimension.x, halfDimension.x);
		float biggerHalfHeight = std::max(other.halfDimension.y, halfDimension.y);
		float smallerHalfWidth = std::min(other.halfDimension.x, halfDimension.x);
		float smallerHalfHeight = std::min(other.halfDimension.y, halfDimension.y);
		
		XY smallerAABBCenter = other.halfDimension.x == biggerHalfWidth && other.halfDimension.y == biggerHalfHeight ? other.center : center;
		XY biggerAABBCenter = center.x == smallerAABBCenter.x && center.y == smallerAABBCenter.y ? other.center : center;

		float biggerWidth = biggerHalfWidth * 2;
		float biggerHeight = biggerHalfHeight * 2;

		return (biggerAABBCenter.x - biggerWidth <= smallerAABBCenter.x && biggerAABBCenter.x + biggerWidth >= smallerAABBCenter.x) &&
			(biggerAABBCenter.y - biggerHeight <= smallerAABBCenter.y && biggerAABBCenter.y + biggerHeight >= smallerAABBCenter.y);*/
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