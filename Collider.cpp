#include "Collider.h"
#pragma warning (disable : 4244)

const RECT Collider::getBoundingBox()
{
	if (pBoundingBox)
	{
		return (*pBoundingBox);
	}
	else
	{
		// Generate an empty RECT and return that instead
		RECT temp;
		temp.left = temp.right = temp.bottom = temp.top = 0;

		// TODO: Generate an appropriate error message
		return temp;
	}
}

void Collider::Initialize(long xPosition, long yPosition,
						  long widthOfObject, long heightOfObject)
{
	// Create a new RECT if one doesn't already exist
	if (!pBoundingBox)
	{
		pBoundingBox = new RECT();
	}

	// The store width/height values for calculations later
	previousWidth = widthOfObject;
	previousHeight = heightOfObject;

	pBoundingBox->left = xPosition;
	pBoundingBox->right = pBoundingBox->left + widthOfObject;
	pBoundingBox->top = yPosition;
	pBoundingBox->bottom = pBoundingBox->top + heightOfObject;
}

void Collider::UpdateCollider(long xPosition, long yPosition)
{
	// Update values if a bounding box exists
	if (pBoundingBox)
	{
		// Temporary values that store the width and height of the current box
		long tempWidth = pBoundingBox->right - pBoundingBox->left;
		long tempHeight = pBoundingBox->bottom - pBoundingBox->top;

		pBoundingBox->left = xPosition;
		pBoundingBox->top = yPosition;

		pBoundingBox->right = pBoundingBox->left + tempWidth;
		pBoundingBox->bottom = pBoundingBox->top + tempHeight;
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

void Collider::setBoxWidth(long BBWidth)
{
	// Make sure a bounding box exists before modifying values
	if (pBoundingBox)
	{
		previousWidth = BBWidth;
		pBoundingBox->right = pBoundingBox->left + BBWidth;
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

void Collider::setBoxHeight(long BBHeight)
{
	// Make sure a bounding box exists before modifying values
	if (pBoundingBox)
	{
		previousHeight = BBHeight;
		pBoundingBox->bottom = pBoundingBox->top + BBHeight;
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

void Collider::modifyBoxWidth(float widthCoefficient)
{
	// Make sure a bounding box exists before modifying values
	if (pBoundingBox)
	{
		pBoundingBox->right = pBoundingBox->left + (previousWidth * widthCoefficient);
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

void Collider::modifyBoxHeight(float heightCoefficient)
{
	// Make sure a bounding box exists before modifying values
	if (pBoundingBox)
	{
		pBoundingBox->bottom = pBoundingBox->top + (previousHeight * heightCoefficient);
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

void Collider::ResetBoxHeight()
{
	// Make sure a bounding box exists before modifying values
	if (pBoundingBox)
	{
		pBoundingBox->right = pBoundingBox->left + previousWidth;
		pBoundingBox->bottom = pBoundingBox->top + previousHeight;
	}
	else
	{
		// TODO: Generate an appropriate error message
	}
}

Collider::Collider()
{
	long previousWidth = 0;
	long previousHeight = 0;

	pBoundingBox = NULL;
}

Collider::~Collider()
{
	if (pBoundingBox)
	{
		delete pBoundingBox;
	}
}