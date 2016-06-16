#include "stdafx.h"
#include "windowHandler.h"

std::queue<WindowHandler::Event> WindowHandler::m_EventQueue;

WindowHandler::~WindowHandler ()
{

}

WindowHandler::WindowHandler ()
{
}

void WindowHandler::ModifyWindow (int id)
{
	Event mEvent;
	mEvent.id = id;

	m_EventQueue.push (mEvent);
}

void WindowHandler::ProcessEvent (Window& window, Event mEvent)
{
	if (mEvent.id == 0)
	{
		glfwDestroyWindow(window.m_WindowContext);
	}
}

void WindowHandler::Update (Window& window)
{
	if (!m_EventQueue.empty ())
		while (!m_EventQueue.empty ())
		{
			Event mEvent = m_EventQueue.front ();
			m_EventQueue.pop ();
			ProcessEvent (window, mEvent);
		}
}