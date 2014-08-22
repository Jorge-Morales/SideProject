#ifndef IAI_H
#define IAI_H

#include "Entity.h"

/*
	TODO: Discuss what variables should be contained within the class.
*/
class IAI : public Entity
{
protected:

	/*
		Because the AI will have 'spawning' specific animations, we need to know when
		they're done so that the AI can continue on with normal actions.
	*/
	bool spawningAnimationOver;

public:

	/*
		Determines when an AI is ready to be removed from play.

		Because this can differ depending on the AI, we leave this as a
		virtual function so that children can determine what criteria 
		merits their removal.
	*/
	virtual bool removeFromPlay() = 0;

	/*
		Registers the AI object in the event system.

		Call this function ONCE when the AI is ready to be displayed to
		the screen. This allows us to keep the event system quick and small
		by only registering listeners when they're needed.
	*/
	virtual void RegisterWithES() = 0;

	virtual ~IAI(){}
};

#endif