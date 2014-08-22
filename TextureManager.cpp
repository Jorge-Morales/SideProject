#include "TextureManager.h"
#include "GlobalEnvironment.h"

#include <fstream>
#include <sstream>
#include <string>

IDirect3DTexture9* TextureManager::LoadTexture(std::string filename, D3DCOLOR transparencyKey)
{
	IDirect3DTexture9* texture = NULL;

	/*
		This is used to retrieve the details of the loaded texture.

		Our code doesn't actually use this, but DirectX requires it so
		we can't get rid of it.
	*/
	D3DXIMAGE_INFO info;

	D3DXGetImageInfoFromFile(filename.c_str(), &info);

		// -------- This is the old method of a loading an image --------
	//D3DXCreateTextureFromFileEx(
	//	gEnv->getD3DManager()->getD3DDevice(),	// Direct3D device obj
	//	filename.c_str(),		// Filename of bitmap
	//	info.Width,				// Bitmap image width
	//	info.Height,			// Bitmap image height
	//	1,						// Mip-map levels (1 for no chain)
	//	D3DPOOL_DEFAULT,		// The type of surface (standard)
	//	D3DFMT_UNKNOWN,			// Surface format (default)
	//	D3DPOOL_DEFAULT,		// Memory class for textures
	//	D3DX_DEFAULT,			// Image filter
	//	D3DX_DEFAULT,			// Mip filter
	//	transparencyKey,		// Color key for transparency (Alpha)
	//	&info,					// Bitmap file info (loaded from file earlier)
	//	NULL,					// Color palette
	//	&texture);				// Dest texture

	if (FAILED(D3DXCreateTextureFromFileEx(gEnv->getD3DManager()->getD3DDevice(), 
										   filename.c_str(), 0, 0, 1, 0,
										   D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
										   D3DX_FILTER_NONE, D3DX_DEFAULT,
										   0xFFFF00FF, &info, NULL, &texture)))
	{
		// MessageBox is a good tool, but it'd be great if we could setup an error log to output to
		MessageBox(NULL, "Failed to create texture", "Unable to make texture from file", MB_OK);
	}

	return texture;
}

IDirect3DTexture9& TextureManager::retrieveTexture(std::string textureToRetrieve)
{
	IDirect3DTexture9* texture = NULL;

	if(TextureListing[textureToRetrieve])
	{
		texture = TextureListing[textureToRetrieve];
	}
	else
	{
		// TODO: Output to error log
		MessageBox(NULL, "Failed to find texture", "Unable to find desired texture in TextureListing", MB_OK);
	}

	return (*texture);
}

TextureManager::TextureManager()
{
	std::ifstream textureFile("textureListing.txt");

	std::string fileInput = "";
	std::string fileName = "";

	// The alpha channel of the image being loaded (can be NULL)
	std::string alphaR = "";
	std::string alphaG = "";
	std::string alphaB = "";

	// Read in each line of the texture textfile
	// WARNING: This code is somewhat fragile in that it requires the text file to be tab delimited
	while (getline(textureFile, fileInput))
	{
		std::istringstream buffer(fileInput);
		buffer >> fileName >> alphaR >> alphaG >> alphaB;

		// Make sure we don't leak any memory by removing an existing texture
		if (TextureListing[fileName] != NULL)
		{
			LPDIRECT3DTEXTURE9 temp = static_cast<LPDIRECT3DTEXTURE9>(TextureListing[fileName]);
			temp->Release();
		}

		// Insert a texture into the TextureListing map
		if (alphaR == "NULL" && alphaG == "NULL" && alphaB == "NULL")
		{
			TextureListing[fileName] = LoadTexture(fileName, NULL);
		}
		else
		{
			TextureListing[fileName] = LoadTexture(fileName, D3DCOLOR_XRGB(atoi(alphaR.c_str()), atoi(alphaG.c_str()), atoi(alphaB.c_str())));
		}
	
		if (textureFile.eof())
		{
			break;
		}
	}

	textureFile.close();
}

TextureManager::~TextureManager()
{
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator tlIt;
	LPDIRECT3DTEXTURE9 temp = NULL;

	for (tlIt = TextureListing.begin(); tlIt != TextureListing.end(); ++tlIt)
	{
		/*
			We need to static_cast here because tlIt technically points to a IDirect3DTexture9 which
			doesn't define Release(). Because LPDIRECT3DTEXTURE9 inherits from it, we can cheese the
			system and handle the memory that way.
		*/
		temp = static_cast<LPDIRECT3DTEXTURE9>(tlIt->second);

		temp->Release();
	}

	// Empty the map now that all memory has been handled
	TextureListing.erase(TextureListing.begin(), TextureListing.end());
}