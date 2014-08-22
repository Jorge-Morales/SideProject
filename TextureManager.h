#ifndef TEXMAN_H
#define TEXMAN_H

#include <map>
#include <d3d9.h>

/*
	The TextureManager acts as the one-stop-shop for all textures used 
	in the project. 

	As part of the program startup sequence, the TextureManager will 
	read in all files listed in textureListing.txt and create a single
	instance of each texture. The textures are released and deallocated
	as part of this manager's destructor.

	This allows us to only load one copy of each texture, regardless of
	the number of objects that end up requiring the texture. Additionally,
	this allows us to front-load some of the loading time to limit slowdowns
	during gameplay.
*/
class TextureManager
{
private:

	/*
		All textures are stored in this map, and can be retrieved by 
		using their texture name (E.G. "texture.png") as a key
	*/
	std::map<std::string, IDirect3DTexture9*> TextureListing;

	IDirect3DTexture9* LoadTexture(std::string textureName, D3DCOLOR transparencyKey);

public:

	~TextureManager();
	TextureManager();

	static TextureManager& getInstance()
	{
		static TextureManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new TextureManager();
		}

		return (*pInstance);
	}

	IDirect3DTexture9& retrieveTexture(std::string textureToRetrieve);
};
#endif