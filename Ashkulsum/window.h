#ifndef WINDOW_H
#define WINDOW_H

#include "oglEngine.h"
#include "pvwUpdater.h"
#include "camera.h"
#include "trackBall.h"
#include "timer.h"
#include <string>

class Window
{
public:
	~Window ();

	struct WindowSize 
	{
		int m_XOrigin;
		int m_YOrigin;
		int m_XSize;
		int m_YSize;
	};

	Window (std::string title, int xOrigin, int yOrigin, int xSize, int ySize);

	void Destroy ();
	void SetWindowSize (int xSize, int ySize);
	void SwapBuffers ();	

public:
	std::shared_ptr<OpenGLEngine> m_Engine;
	std::shared_ptr<ProgramFactory> m_Factory;
	std::shared_ptr<Camera> m_Camera;
	BufferUpdater m_Updater;
	PVWUpdater m_PVWUpdater;
	TrackBall m_TrackBall;
	Timer m_Timer;
	int m_WindowContext;
	WindowSize m_WindowSize;
	std::string m_Title;
};
#endif