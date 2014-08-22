#ifndef BACKGROUNDMAN_H
#define BACKGROUNDMAN_H

#include "IBackground.h"
#include "Event.h"
#include <queue>

/*
	Created by Garhett Bambrick

	BackgroundManager manages the background.
	 - Manages the background layers
	 - Determines when encounters start
	 - Backgrounds are added via level creation code
*/
class BackgroundManager
{
private:
	
	// This vector holds the locations at which each encounter should begin
	std::queue<float> encounterStartPos;

	// Because we will be having layered backgrounds, we hold these in a vector
	std::vector<IBackground*> backgrounds;

	// The number of layers currently being used
	int totalLayers;

	// The layer that the play area is being rendered
	int playAreaLayer;

public:

	/*
		Retrieve static address of the BackgroundManager.

		Should only be called within GlobalEnvironment.
	*/
	static BackgroundManager& getInstance()
	{
		static BackgroundManager* pInstance = NULL;

		if (!pInstance)
		{
			pInstance = new BackgroundManager();
		}

		return (*pInstance);
	}

	/*
		Tells the backgrounds to update

		Only call this in the Update cycle of Game. DO NOT call this in the Render cycle.
	*/
	void Update();

	/*
		AddBackground adds another background to the vector of backgrounds so that it
		can be rendered and updated properly.
	*/
	void AddBackground(IBackground* newBG);

	/*
		SetEncounterPositions takes a vector of floats from the level creation code,
		sorts them in ascending order, and puts them into a queue. This ensures that
		the encounters start in the right order.
	*/
	void SetEncounterPositions(std::vector<float> encounterPos);

	/*
		Only call this in the Render cycle of Game. DO NOT call this in the Update cycle.
	*/
	void Render();

	/*
		Self-explanatory Getter and Setter functions
	*/
	int getNumLayers();
	int getPlayAreaLayerNum();

	void SetNumLayers(int);
	void SetPlayAreaLayerNum(int);

	// Tors
	BackgroundManager();
	~BackgroundManager();
};

#endif