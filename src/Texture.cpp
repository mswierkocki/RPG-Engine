
#include <vector>

#include "Texture.h"
#include "SOIL.h"
#include "error.h"


Texture::Texture(std::string filename)
{
	if(filename != "")
	{
		if(!Load(filename)) error("Error loading texture image!");
	}
	else
	{
		file="";
		texID = 0;
		width = 0;
		height = 0;
		channels = 0;
	}
}

bool Texture::Load(std::string filename)
{
	file = _strdup(filename.c_str());

	if(filename == "")
	{
		texID = 0;
		width = 0;
		height = 0;
		channels = 0;
		return false;
	}

	unsigned char* data = SOIL_load_image(file, (int*)&width, (int*)&height, (int*)&channels, SOIL_LOAD_AUTO);

	if(!data) return false;

	texID = SOIL_create_OGL_texture(data, width, height, channels, 0, SOIL_FLAG_INVERT_Y | SOIL_FLAG_POWER_OF_TWO);

	SOIL_free_image_data(data);

	return true;
}
