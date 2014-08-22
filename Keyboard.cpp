#include "Keyboard.h"
#include "GlobalEnvironment.h"

void Keyboard::ProcessInput(const unsigned int mask)
{
	/*
		Process the received bit-mask and send any applicable events

		PLAYER RELATED INPUT
		1 = Move up
		2 = Move left
		4 = Move down
		8 = Move right
		16 = Jump
		32 = Attack
		64 = Prev. weapon
		128 = Next weapon
	*/
	if (mask > 0)
	{
		// Check first 8 bits
		int maskTest = mask << 23;

		if (maskTest > 0)
		{
			Player_Input_Event* pTemp = new Player_Input_Event();

			pTemp->up		= (mask & 1);
			pTemp->left		= (mask & 2);
			pTemp->down		= (mask & 4);
			pTemp->right	= (mask & 8); 
			pTemp->jump		= (mask & 16);
			pTemp->attack	= (mask & 32);		
			pTemp->prevWeap	= (mask & 64);	 
			pTemp->nextWeap = (mask & 128);

			gEnv->getEventDispatcher()->DispatchEvent(pTemp);
		}

		// Check for values past the first 8 bits
		maskTest = mask >> 8 & 0xFFFFFFFF;
		
		if (maskTest > 0)
		{

		}
	}
}

Keyboard::Keyboard()
{

}