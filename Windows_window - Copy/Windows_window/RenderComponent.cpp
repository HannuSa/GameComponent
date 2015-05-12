#include "RenderComponent.h"


RenderComponent::RenderComponent(std::vector<unsigned char> _image, unsigned int _width, unsigned int _height, unsigned int _buffer) :Component(RENDER_COMP)
{
	image = _image;
	width = _width;
	height = _height;
	buffer = _buffer;
}


RenderComponent::~RenderComponent()
{
}
