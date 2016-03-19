#pragma once

class IGraphicsRenderer
{
public:
	virtual ~IGraphicsRenderer() { }

	virtual void AddRenderable(IRendereable *renderable) = 0;

	virtual void RemoveRenderable(IRendereable *renderable) = 0;

	virtual void RenderAll() = 0;
};