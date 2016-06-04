#include <queue>
#include "window.h"
#include "glfw3.h"

class WindowHandler
{
public:
	struct Event
	{
		int id;
	};

	WindowHandler ();
	~WindowHandler ();

	
	static void Update (Window& window);
	static void ModifyWindow (int id);
	static void ProcessEvent (Window& window, Event mEvent);

public:
	static std::queue<Event> m_EventQueue;

};