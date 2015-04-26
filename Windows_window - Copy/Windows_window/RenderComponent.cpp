#include "RenderComponent.h"


RenderComponent::RenderComponent(std::vector<unsigned char> _image) :Component(RENDER_COMP)
{
	image = _image;
}


RenderComponent::~RenderComponent()
{
}
