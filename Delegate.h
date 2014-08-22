#ifndef DELEGATE_H
#define DELEGATE_H

#include "Event.h"

/*
	A variation of Sergey Ryazanov's "Impossibly Fast C++ Delegates"
		Original documentation can be found at: http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates

	Delegate acts as a wrapper for an object's member function, and allows us to invoke
	that member function on a whim without the calling code ever knowing about the object
	itself.
*/
class Delegate
{
public:
    Delegate()
        : object_ptr(0)
        , stub_ptr(0)
		, ID(0)
    {}

	// ID number of object to be registered
	unsigned int ID;

    template <class T, void (T::*TMethod)(Event*)>
    static Delegate makeDelegateFromFunction(T* object_ptr, unsigned int ID_NUM)
    {
		// Create a new Delegate object to return to callee
        Delegate d;

		// New Delegate "d" now has a pointer to the object that called it
        d.object_ptr = object_ptr;

		// New Delegate "d" now has a pointer to a member function of the callee
        d.stub_ptr = &invokeFunction<T, TMethod>;

		// Assign appropriate ID number
		d.ID = ID_NUM;

        return d;
    }

	// Overload the () operator to allow for easy access in STL containers
    void operator()(Event* Event) const
    {
        return (*stub_ptr)(object_ptr, Event);
    }

private:
    typedef void (*stub_type)(void* object_ptr, Event*);

    void* object_ptr;

    stub_type stub_ptr;

    template <class T, void (T::*TMethod)(Event*)>
    static void invokeFunction(void* object_ptr, Event* Event)
    {
		// Cast the void* "back" to a pointer of the object type
        T* p = static_cast<T*>(object_ptr);

		// Invoke the function
        return (p->*TMethod)(Event); 
    }
};

#endif