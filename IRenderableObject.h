#ifndef RENDERABLEOBJECT
#define RENDERABLEOBJECT

/*
	Interface that anything that has to render should inherit from.

	The Render function is called within the Game::Render loop and must
	be present within an object to be eligible for rendering.
*/
class IRenderableObject
{
public:

	/*
		Function in which rendering should be done.

		>>> SHOULD NOT CONTAIN ANY LOGIC <<<

		Called as often as the computer can iterate through the main game loop.
	*/
	virtual void Render() = 0;
};

#endif