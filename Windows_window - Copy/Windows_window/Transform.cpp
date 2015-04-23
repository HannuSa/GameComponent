#include "Transform.h"
#include <conio.h>

Transform::Transform()
{
	key_code = 0;
}


Transform::~Transform()
{
}

void Transform::Update()
{
	if (kbhit())
	{
		key_code = getch();

		switch (key_code)
		{
		case 0:
			break;
		case 1:
			break;
		default:
			break;
		}
	}
}