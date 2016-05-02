#pragma once

#include <string>
#include <Box2D\Box2D.h>

struct EntityDescriptor
{
	std::string animation;
	std::string modelName;
	std::string entityName;
	b2Vec2 position;
	double width;
	double height;
	b2BodyType bodyType;

	const std::string EXCEPTION_COMMON_MESSAGE = "EntityDescriptorException: ";

	EntityDescriptor() {}

	EntityDescriptor& withAnimation(std::string value)
	{
		animation = value;
		return *this;
	}

	EntityDescriptor& withModelName(std::string value)
	{
		modelName = value;
		return *this;
	}

	EntityDescriptor& withEntityName(std::string value)
	{
		entityName = value;
		return *this;
	}

	EntityDescriptor& withPosition(b2Vec2 value)
	{
		position = value;
		return *this;
	}

	EntityDescriptor& withWidth(double value)
	{
		if (value < 0)
		{
			throw std::runtime_error(EXCEPTION_COMMON_MESSAGE + "Width cannot be less than 0.");
		}

		width = value;
		return *this;
	}

	EntityDescriptor& withHeight(double value)
	{
		if (value < 0)
		{
			throw std::runtime_error(EXCEPTION_COMMON_MESSAGE + "Height cannot be less than 0.");
		}

		height = value;
		return *this;
	}

	EntityDescriptor& withBodyType(b2BodyType value)
	{
		bodyType = value;
		return *this;
	}

	EntityDescriptor& create()
	{
		if (stateIsValid())
		{
			return *this;
		}

		throw std::runtime_error(EXCEPTION_COMMON_MESSAGE + "State is invalid.");
	}

	bool stateIsValid()
	{
		if (animation.length() <= 0)
		{
			return false;
		}

		if (modelName.length() <= 0)
		{
			return false;
		}

		if (entityName.length() <= 0)
		{
			return false;
		}

		if (width < 0)
		{
			return false;
		}

		if (height < 0)
		{
			return false;
		}

		return true;
	}
};