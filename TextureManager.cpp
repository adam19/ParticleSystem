#include "TextureManager.h"

#include <iostream>

using namespace std;

TextureManager::TextureManager()
{
	list.clear();
}

TextureManager::~TextureManager()
{
	list.clear();
}

void	TextureManager::Init()
{
	ilInit();
	iluInit();
	ilutInit();

	ilutRenderer(ILUT_OPENGL);

	if (!addTexture("wall.jpg"))
		cout << "Could not find default texture!\n";
}

size_t	inline TextureManager::numTextures()
{
	return list.size();
}

Texture	TextureManager::getTexture(string name)
{
	Texture tex = list[0];

	for(size_t i=0; i<list.size(); ++i)
	{
		if(list[i].filename == name)
		{
			tex = list[i];
		}
	}

	return tex;
}

Texture	TextureManager::getTexture(GLuint id)
{
	Texture tex = list[0];

	for(size_t i=0; i<list.size(); ++i)
	{
		if(list[i].id == id)
		{
			tex = list[i];
		}
	}

	return tex;
}

int		TextureManager::addTexture(char* filename)
{
	if(!filename)
		return false;

	Texture temp;

	temp.filename = string(filename);

	BuildTexture(filename, temp);

	list.push_back(temp);

	return true;
}

void	inline TextureManager::removeTexture(size_t i)
{
	if(i < list.size())
		list.erase(list.begin()+i);
}

void	inline TextureManager::removeAllTextures()
{
	list.clear();
}