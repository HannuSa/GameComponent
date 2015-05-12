#pragma once
#include "Component.h"
#include "lodepng.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent(std::vector<unsigned char> _image, unsigned int _width, unsigned int _height, unsigned int _buffer);
	~RenderComponent();

	std::vector<unsigned char> image;
	unsigned int width, height, buffer;
};

