#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <vector>
#include <string>
#include "Texture.h"

using namespace std;

class TextureManager
{
public:
	//size_t currentTexture;
	vector<Texture> list;

	TextureManager();
	~TextureManager();

	void	Init();

	size_t	numTextures();

	Texture	getTexture(string name);
	Texture	getTexture(GLuint id);
	int		addTexture(char* filename);
	void	removeTexture(size_t i);
	void	removeAllTextures();
};

#endif