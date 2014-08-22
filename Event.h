#ifndef EVENT_H
#define EVENT_H

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

/*
	A listing of all events in the game.

	Use this namespace when determining what type of event was received by a listener.
		- Example: pEvent->Event_Type == Event_Listings::PLAYER_ATTACK
*/
namespace Event_Listings
{
	const unsigned int PLAYER_MOVE = 0;
	const unsigned int START_ENCOUNTER = 1;
	const unsigned int END_ENCOUNTER = 2;
	const unsigned int PLAYER_INPUT = 3;
	const unsigned int PLAYER_ATTACK = 4;
	const unsigned int AI_ATTACK = 5;
	const unsigned int CREATE_TEMPOBJ = 6;
	const unsigned int QUIT_GAME = 7;
	const unsigned int START_GAME = 8;
	const unsigned int START_NEXT_LEVEL = 9;
	const unsigned int GOTO_MENU = 10;
	const unsigned int GOTO_CREDITS = 11;
	const unsigned int MOUSE_CLICK = 12;
	const unsigned int END_LEVEL = 13;
	const unsigned int SCORE_EVENT = 14;

	const unsigned int MAX = SCORE_EVENT;
}

// TempObject creation
enum TempObjectID
{
	FLOATING_DAMAGE = 150,
	FLOATING_HAND = 151
};

// EVENTS
class Event
{
public:

	/* 
		Value used by listeners to determine what type of event they've
		received.

		Should not be used for any other purpose.
	*/
	unsigned int Event_Type;

	
	/* 
		Determines whether or not an event should continue to be distributed to
		other listeners in the Event System
	*/
	bool handledErase;

	Event()
	{
		handledErase = false;
	}

};

class Start_Encounter_Event : public Event
{
public:

	Start_Encounter_Event()
	{
		Event_Type = Event_Listings::START_ENCOUNTER;
	}
};

class End_Encounter_Event : public Event
{
public:

	End_Encounter_Event()
	{
		Event_Type = Event_Listings::END_ENCOUNTER;
	}
};

class Player_Move_Event : public Event
{
public:

	float amountMoved;

	Player_Move_Event(float amtMoved)
	{
		Event_Type = Event_Listings::PLAYER_MOVE;
		amountMoved = amtMoved;
	}
}; 

class Player_Input_Event : public Event
{
public:

	bool up;
	bool left;
	bool right;
	bool down;

	bool attack;
	bool jump;
	bool prevWeap;
	bool nextWeap;

	Player_Input_Event()
	{
		Event_Type = Event_Listings::PLAYER_INPUT;

		up = left = right = down = attack = jump = prevWeap = nextWeap = false;
	}
};

/*
	Player and AI damage events are seperated by default. This is partly for
	convenience (being that AI won't be attacking each other with the currently
	planned system), but is mostly due to time constraints.

	Don't do this at home kids.

	TODO: Either merge these into one class and let the AI hurt each other, or
			create an additional class that is a 'general damage' Event for special
			attacks.
*/
class Player_Attack_Event : public Event
{
public:

	RECT damageBox;
	int damage;
	unsigned int depth;

	Player_Attack_Event()
	{
		damageBox = { 0, 0, 0, 0 };
		damage = depth = 0;
		Event_Type = Event_Listings::PLAYER_ATTACK;
	}

};

class AI_Attack_Event : public Event
{
public:

	RECT damageBox;
	int damage;
	unsigned int depth;

	AI_Attack_Event()
	{
		damageBox = { 0, 0, 0, 0 };
		damage = depth = 0;
		Event_Type = Event_Listings::AI_ATTACK;
	}
};

class Quit_Game_Event : public Event
{
public:

	Quit_Game_Event()
	{
		Event_Type = Event_Listings::QUIT_GAME;
	}
};

class Start_Game_Event : public Event
{
public:

	unsigned int level;

	Start_Game_Event()
	{
		level = 0;
		Event_Type = Event_Listings::START_GAME;
	}

};

class Next_Level_Event : public Event
{
public:

	Next_Level_Event()
	{
		Event_Type = Event_Listings::START_NEXT_LEVEL;
	}

};

class Goto_Menu_Event : public Event
{
public:

	Goto_Menu_Event()
	{
		Event_Type = Event_Listings::GOTO_MENU;
	}
};

class Goto_Credit_Event : public Event
{
public:

	Goto_Credit_Event()
	{
		Event_Type = Event_Listings::GOTO_CREDITS;
	}
};

class Mouse_Click_Event : public Event
{
public:

	RECT clickArea;

	Mouse_Click_Event()
	{
		clickArea = { 0, 0, 0, 0 };
		Event_Type = Event_Listings::MOUSE_CLICK;
	}
};

class Score_Event : public Event
{
public:

	int scoreChange;

	Score_Event()
	{
		scoreChange = 0;
		Event_Type = Event_Listings::SCORE_EVENT;
	}
};

class Create_TempObj_Event : public Event
{
public:

	int ID;
	float x, y;

	Create_TempObj_Event()
	{
		ID = x = y = 0;
		Event_Type = Event_Listings::CREATE_TEMPOBJ;
	}
};

#endif