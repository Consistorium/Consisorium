#pragma once
class IGraphicsRenderer
{
public:
	virtual ~IGraphicsRenderer() { }

	virtual void DrawDescriptions() = 0;
};