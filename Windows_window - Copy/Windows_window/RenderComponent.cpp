#include "RenderComponent.h"


RenderComponent::RenderComponent(std::vector<unsigned char> _image, unsigned int _width, unsigned int _height) :Component(RENDER_COMP)
{
	image = _image;
	width = _width;
	height = _height;
}


RenderComponent::~RenderComponent()
{
}
