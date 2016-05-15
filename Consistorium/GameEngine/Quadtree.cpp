#include <cassert>
#include "Quadtree.h"

Quadtree::Quadtree(XY _center, XY _halfDimension)
	: boundary(_center, _halfDimension), nodeCapacity(4)
{
	NW = NE = SW = SE = nullptr;
	points.reserve(nodeCapacity);
}

Quadtree::Quadtree(XY _center, XY _halfDimension, int _nodeCapacity)
	: boundary(_center, _halfDimension), nodeCapacity(_nodeCapacity)
{
	NW = NE = SW = SE = nullptr;
	points.reserve(nodeCapacity);
}

bool Quadtree::remove(GameEngine::IRenderable* toRemove)
{
	// doesnt work
	if (NW == nullptr) { return false; }
	for (int i = 0; i < NW->points.size(); i++)
	{
		if (NW->points[i] == toRemove)
		{
			NW->points[i] == nullptr;
			delete toRemove;
			return true;
		}
	}
	for (int i = 0; i < NE->points.size(); i++)
	{
		if (NE->points[i] == toRemove)
		{
			NE->points[i] == nullptr;
			delete toRemove;
			return true;
		}
	}
	for (int i = 0; i < SE->points.size(); i++)
	{
		if (SE->points[i] == toRemove)
		{
			SE->points[i] == nullptr;
			delete toRemove;
			return true;
		}
	}
	for (int i = 0; i < SW->points.size(); i++)
	{
		if (SW->points[i] == toRemove)
		{
			SW->points[i] == nullptr;
			delete toRemove;
			return true;
		}
	}

	if (NW->remove(toRemove)) return true;
	if (NE->remove(toRemove)) return true;
	if (SW->remove(toRemove)) return true;
	if (SE->remove(toRemove)) return true;

	return false;
}

bool Quadtree::insert(GameEngine::IRenderable * a) {
	if (!boundary.containsPoint(a))
		return false;

	if (points.size() < nodeCapacity) {
		points.push_back(a);
		return true;
	}

	if (NW == nullptr) subdivide();

	if (NW->insert(a)) return true;
	if (NE->insert(a)) return true;
	if (SW->insert(a)) return true;
	if (SE->insert(a)) return true;

	assert(false);
	return false; // should never happen
}

void Quadtree::subdivide() {
	XY center = boundary.center;
	XY newDim(boundary.halfDimension.x / 2, boundary.halfDimension.y / 2);

	NW = new Quadtree(XY(center.x - newDim.x, center.y - newDim.y), newDim);
	NE = new Quadtree(XY(center.x + newDim.x, center.y - newDim.y), newDim);
	SW = new Quadtree(XY(center.x - newDim.x, center.y + newDim.y), newDim);
	SE = new Quadtree(XY(center.x + newDim.x, center.y + newDim.y), newDim);
}

void Quadtree::queryRange(std::vector<GameEngine::IRenderable*>& list, AABB& range) {
	if (!boundary.intersectsAABB(range)) return; // list is empty

	for (int i = 0; i < points.size(); ++i)
		if (range.containsPoint(points[i]))
			list.push_back(points[i]);

	if (SE == nullptr) return;
	NW->queryRange(list, range);
	NE->queryRange(list, range);
	SW->queryRange(list, range);
	SE->queryRange(list, range);
}

// scan the tree and remove all node/Item*
void Quadtree::clear() {
	if (this == nullptr) return;
	points.clear();

	NW->clear();
	delete NW;
	NW = nullptr;
	NE->clear();
	delete NE;
	NE = nullptr;
	SW->clear();
	delete SW;
	SW = nullptr;
	SE->clear();
	delete SE;
	SE = nullptr;
}