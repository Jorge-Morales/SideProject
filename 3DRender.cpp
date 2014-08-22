#include "3DRender.h"
#include "GlobalEnvironment.h"

void ThreeDRenderer::calcDrawRect()
{
	drawDest->left = position.x;
	drawDest->right = drawDest->left + textureW;
	drawDest->top = position.y;
	drawDest->bottom = drawDest->top + textureH;

	drawDest->top = 0;
	drawDest->bottom = 512;
	drawDest->left = 0;
	drawDest->right = 512;
}

void ThreeDRenderer::Render()
{
	float X;
	float Y;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matScaling;
	D3DXMATRIX matTransform;

	//Get coordinates
	X = drawDest->left - (float)(gEnv->getD3DManager()->getDPP().BackBufferWidth) / 2;
	Y = -drawDest->top + (float)(gEnv->getD3DManager()->getDPP().BackBufferHeight) / 2;

	//Setup translation and scaling matrices
	D3DXMatrixScaling(&matScaling, (float)(drawDest->right - drawDest->left),
					 (float)(drawDest->bottom - drawDest->top), 1.0f);
	D3DXMatrixTranslation(&matTranslation, X, Y, 0.0f);
	matTransform = matScaling * matTranslation;

	//Check if quad is rotated
	if (rotation)
	{
		D3DXMATRIX matRotate;

		//Create rotation matrix about the z-axis
		D3DXMatrixRotationZ(&matRotate, rotation);

		//Multiply matrices together
		matTransform *= matRotate;
	}

	// The a quad at the desired position with this object's texture
	gEnv->getD3DManager()->getD3DDevice()->SetTransform(D3DTS_WORLD, &matTransform);
	gEnv->getD3DManager()->getD3DDevice()->SetTexture(0, texture);
	gEnv->getD3DManager()->getD3DDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2);
}

void ThreeDRenderer::Update(float xPos, float yPos, float zPos)
{
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;

	calcDrawRect();
}

void ThreeDRenderer::Initialize(float xPos, float yPos, float zPos, float _scaleX, float _scaleY, float _rotation, std::string textureFile)
{
	// Positional data
	position.x = xPos;
	position.y = yPos;
	position.z = zPos;

	// Scale of object
	scale.x = _scaleX;
	scale.y = _scaleY;

	rotation = _rotation;

	// Retrieve a reference to the desired texture
	texture = (&gEnv->getTextureManager()->retrieveTexture(textureFile));

	// Find out the dimensions of the texture so that
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(textureFile.c_str(), &info);
	textureW = info.Width * scale.x;
	textureH = info.Height * scale.y;

	drawDest = new RECT();

	calcDrawRect();
}

// Modify the scaling factor of the drawn image
void ThreeDRenderer::modifyScaling(float _scaleX, float _scaleY)
{
	scale.x = _scaleX;
	scale.y = _scaleY;

	calcDrawRect();
}

ThreeDRenderer::ThreeDRenderer()
{
	textureH = 0.0f;
	textureW = 0.0f;
	texture = NULL;
	drawDest = NULL;
}

ThreeDRenderer::~ThreeDRenderer()
{
	// The texture pointer is managed elsewhere, but we need to deallocate the drawing rect
	delete drawDest;
}