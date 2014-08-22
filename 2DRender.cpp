#include "2DRender.h"
#include "GlobalEnvironment.h"

void TwoDRenderer::Render()
{
	D3DXVECTOR2 scale(scaleX, scaleY);

	D3DXVECTOR2 center((float)(frameW * scaleX) / 2.0f, (float)(frameH * scaleY) / 2.0f);

	D3DXVECTOR2 trans(posVector.x, posVector.y);

	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &center, rotation, &trans);

	gEnv->getD3DManager()->getSpriteObject()->SetTransform(&mat);

	RECT rect;
	rect.left = (curFrame % numCol) * frameW;
	rect.right = rect.left + frameW;
	rect.top = (curFrame / numCol) * frameH;
	rect.bottom = rect.top + frameH;

	gEnv->getD3DManager()->getSpriteObject()->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void TwoDRenderer::Animate()
{
	if ((int)GetTickCount() > ST + delay)
	{
		ST = GetTickCount();

		curFrame += direction;

		if (curFrame > endFrame)
			curFrame = startFrame;

		if (curFrame < startFrame)
			curFrame = startFrame;
	}
}

void TwoDRenderer::Update()
{
	if (animate)
	{
		Animate();
	}
}

void TwoDRenderer::Initialize(float scaleX, float scaleY, unsigned int frameWidth,
							  unsigned int frameHeight, unsigned int numberOfColumns,
							  unsigned int startFrame, unsigned int endFrame, unsigned int delay,
							  int animationDirection, float radianRotation,
							  float newX, float newY, std::string textureToUse)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	frameW = frameWidth;
	frameH = frameHeight;
	numCol = numberOfColumns;
	this->startFrame = startFrame;
	this->endFrame = endFrame; 
	this->delay = delay;
	ST = GetTickCount();
	direction = animationDirection;
	rotation = radianRotation;

	curFrame = startFrame;

	posVector.x = newX;
	posVector.y = newY;

	texture = (&gEnv->getTextureManager()->retrieveTexture(textureToUse));
}

void TwoDRenderer::Initialize(unsigned int newFrameWidth, unsigned int newFrameHeight,
	 unsigned int newStartFrame,
	unsigned int newEndFrame, unsigned int newDelay)
{
	frameW = newFrameWidth;
	frameH = newFrameHeight;
	startFrame = newStartFrame;
	endFrame = newEndFrame;
	delay = newDelay;
}

/*
	Self-explanatory getters 
*/
const Vector2 TwoDRenderer::getPos()
{
	return posVector;
}

/*
	Returns the active frame width

	frameW * scaleX
*/
const float TwoDRenderer::getAdjustedWidth()
{
	return frameW * scaleX;
}

/*
	Returns the active frame height
	
	frameH * scaleY
*/
const float TwoDRenderer::getAdjustedHeight()
{
	return frameH * scaleY;
}
const unsigned int TwoDRenderer::getCurrentFrame()
{
	return curFrame;
}
const unsigned int TwoDRenderer::getEndFrame()
{
	return endFrame;
}

/*
	Value returned is in radians. 
	
	If you want degrees for some reason, you'll need to convert it yourself.
*/
const float TwoDRenderer::getRotation()
{
	return rotation;
}
const float TwoDRenderer::getScaleX()
{
	return scaleX;
}
const float TwoDRenderer::getScaleY()
{
	return scaleY;
}
const RECT TwoDRenderer::getBoundingBox()
{
	RECT boundingBox;

	boundingBox.left = posVector.x;
	boundingBox.right = posVector.x + getAdjustedWidth();
	boundingBox.top = posVector.y;
	boundingBox.bottom = posVector.y + getAdjustedHeight();

	return boundingBox;
}
void TwoDRenderer::setCurrentFrame(unsigned int newCurrentFrame)
{
	curFrame = newCurrentFrame;
}

/*
	Modifies existing values by the amount passed.

	If you need to decrement a value, just pass a negative value.
*/
void TwoDRenderer::modifyX(float deltaX)
{
	posVector.x += (deltaX);
}
void TwoDRenderer::modifyY(float deltaY)
{
	posVector.y += (deltaY);
}
void TwoDRenderer::modifyScaleX(float deltaSX)
{
	scaleX += deltaSX;
}
void TwoDRenderer::modifyScaleY(float deltaSY)
{
	scaleY += deltaSY;
}
void TwoDRenderer::modifyRotation(float deltaRot)
{
	rotation += deltaRot;
}

// Setters
void TwoDRenderer::setX(float newX)
{
	posVector.x = newX;
}
void TwoDRenderer::setY(float newY)
{
	posVector.y = newY;
}
void TwoDRenderer::setScaleX(float newSX)
{
	scaleX = newSX;
}
void TwoDRenderer::setScaleY(float newSY)
{
	scaleY = newSY;
}
void TwoDRenderer::setDelay(unsigned int newDel)
{
	delay = newDel;
}
void TwoDRenderer::setRot(int newRot)
{
	rotation = newRot;
}
void TwoDRenderer::setAnimateFlag(bool newAnimate)
{
	animate = newAnimate;
}

TwoDRenderer::TwoDRenderer()
{
	scaleX = 1.0f;
	scaleY = 1.0f;
	frameW = 100.0f;
	frameH = 100.0f;
	numCol = 1;
	curFrame = 0;
	startFrame = 0;
	endFrame = 0;
	delay = 0;
	ST = GetTickCount();
	direction = 1;
	rotation = 0;
	animate = false;
	texture = NULL;
}

TwoDRenderer::~TwoDRenderer()
{
	/*
		No memory to manage as the texture is handled by the TextureManager
	*/
}