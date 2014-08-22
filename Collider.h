#ifndef COLLIDER_H
#define COLLIDER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class Collider
{
private:

	/*
		previousWidth/Height act as a restore point so that we
		can temporarily modify the width/height values without
		having to worry about losing the original values.
	*/
	long previousWidth;
	long previousHeight;

	RECT* pBoundingBox;

public:

	/*
		Returns the stored bounding box to the caller.

		Make sure that the caller's current X and Y have been stored
		before making this call or the returned bounding box may be
		inaccurate.
	*/
	const RECT getBoundingBox();

	/*
		First time initialization function that sets up a bounding box
		based on the passed values.
	*/
	void Initialize(long xPosition, long yPosition,
					long widthOfObject, long heightOfObject);

	/*
		A general 'Update' function that allows for the bounding box to be
		updated as the composing object moves.
	*/
	void UpdateCollider(long x, long y);


	//Self-explanatory setters
	void setBoxWidth(long BBWidth);
	void setBoxHeight(long BBHeight);

	/*
		Allows for the width of the bounding box to be modified by a
		coefficient value.

		Note, the coefficient is always applied to the original width value,
		and not to a previously modified width value.
	*/
	void modifyBoxWidth(float widthCoefficient);

	/*
		Allows for the height of the bounding box to be modified by a 
		coefficient value. 

		Note, the coefficient is always applied to the original height value,
		and not to a previously modified height value.
	*/
	void modifyBoxHeight(float heightCoefficient);

	/*
		Return the bounding box it's original width/height dimensions
		after a call to modifyBoundingBoxHeight/Width().
	*/
	void ResetBoxHeight();

	Collider();
	~Collider();
};

#endif