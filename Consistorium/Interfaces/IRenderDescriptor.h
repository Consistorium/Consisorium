#pragma once
class IRenderDescriptor
{
public:
	virtual ~IRenderDescriptor() { }

	virtual void DrawDescriptions() = 0;
};

//TODO:DELETE