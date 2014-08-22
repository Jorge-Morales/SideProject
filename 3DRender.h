#ifndef THREEDR_H
#define THREEDR_H

#include <d3dx9math.h>
#include <string>

class ThreeDRenderer
{
private:

	D3DXVECTOR3 position;
	D3DXVECTOR2 scale;
	IDirect3DTexture9* texture;
	RECT* drawDest;

	unsigned int textureH;
	unsigned int textureW;

	void calcDrawRect();

public:

	float rotation;

	// Draw the object to the screen
	void Render();
	void Update(float xPos, float yPos, float zPos);

	// Default Initialization process that should be done in the composing object's constructor
	void Initialize(float xPos, float yPos, float zPos, float _scaleX, float _scaleY, float _rotation, std::string textureFile);

	// Modify the scaling factor of the drawn image
	void modifyScaling(float _scaleX, float _scaleY);

	ThreeDRenderer();
	~ThreeDRenderer();
};

#endif