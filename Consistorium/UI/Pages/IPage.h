#pragma once

class IPage
{
private:
	virtual void Init() = 0;
public:
	virtual void Run() = 0;
};