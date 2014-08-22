#ifndef TWODR_H
#define TWODR_H

#include "Math.h"
#include <d3d9.h>
#include <string>

class Vector2;

class TwoDRenderer
{
private:

	bool animate;
	Vector2 posVector;
	IDirect3DTexture9* texture;	
	float scaleX;
	float scaleY;
	unsigned int frameW;
	unsigned int frameH;
	unsigned int numCol;   
	unsigned int curFrame;	
	unsigned int startFrame;	
	unsigned int endFrame;	
	unsigned int delay;
	unsigned int ST;			
	int direction;
	float rotation;

	/*
		gets called in Update if the animate flag is set to true.

		Increments the currentFrame value by the direction value, and loops around
		if the currentFrame exceeds the endFrame value.
	*/
	void Animate();

public:

	/*
		Update handles any logic needed for the rendering process before calling
		the render function to draw to the screen.
	*/
	void Update();

	/*
		It renders.

		I don't really know what you were expecting.
	*/
	void Render();

	/*
		This should only be called when a large number of variables need to be
		changed to accomodate switching to a different set of animations within
		the same sprite sheet.
	*/
	void Initialize(unsigned int frameWidth, unsigned int frameHeight,
		unsigned int startFrame,
		unsigned int endFrame, unsigned int delay);

	/*
		Set all variables needed to draw a static image or a specific portion of a
		spritesheet.
	*/
	void Initialize(float scaleX, float scaleY, unsigned int frameWidth, 
				    unsigned int frameHeight, unsigned int numCol,  
					unsigned int startFrame, unsigned int endFrame, 
					unsigned int delay, int dir, 
					float rot, float newX, float newY,
					std::string textureToUse);

	// Self-explanatory getters
	const Vector2 getPos();
	const float getAdjustedWidth();
	const float getAdjustedHeight();
	const unsigned int getCurrentFrame();
	const unsigned int getEndFrame();
	const float getRotation();
	const float getScaleX();
	const float getScaleY();
	const RECT getBoundingBox();

	// Modify the specified values
	void modifyX(float deltaX);
	void modifyY(float deltaY);
	void modifyScaleX(float deltaSX);
	void modifyScaleY(float deltaSY);

	/*
		Rotation is stored in radians.

		Don't be that guy that passes this function degrees; people will hate
		you, and you'll waste time figuring out what happened.
	*/
	void modifyRotation(float deltaRot);

	// Self explanatory setters
	void setX(float newX);
	void setY(float newY); 
	void setScaleX(float newSX);
	void setScaleY(float newSY);
	void setFrameWidth(float newFW);
	void setFrameHeight(float newFH);
	void setDelay(unsigned int newDel);
	void setAnimateFlag(bool newAnimate);
	void setCurrentFrame(unsigned int newCurrentFrame);

	/*
		Rotation is stored in radians.

		Don't be that guy that passes this function degrees; people will hate
		you, and you'll waste time figuring out what happened.
	*/
	void setRot(int newRot);

	/* 
		For easy loading of a new texture

				----CAUTION----
		This does not update the rest of the information used by the renderer.
		If you need to change many attributes to get the new texture working, use Initialize
	*/
	void setNewTexture(std::string);

	TwoDRenderer();

	~TwoDRenderer();
};

#endif