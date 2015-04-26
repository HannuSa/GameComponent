#pragma once
#include "Component.h"
#include "lodepng.h"

class RenderComponent :
	public Component
{
public:
	RenderComponent(std::vector<unsigned char> _image);
	~RenderComponent();

	std::vector<unsigned char> image;
};

