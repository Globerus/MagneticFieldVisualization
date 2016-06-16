#include "stdafx.h"
#include "window.h"

Window::Window (std::string title, int xOrigin, int yOrigin, int xSize, int ySize)
	:	m_Camera (std::make_shared<Camera> (true)),
		m_Updater ([this](std::shared_ptr<Buffer> const& buffer) { m_Engine->Update (buffer);}),
		m_PVWUpdater (m_Camera, m_Updater),
		m_TrackBall (xSize, ySize, m_Camera)
{
	int argc = 1;
	char *argv[1] = {(char*)""};
	glutInit(&argc, argv);

	unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;

	glutInitDisplayMode (displayMode);
	glutInitContextVersion (3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize (xSize, ySize); 
	glutInitWindowPosition (0, 0);

	int m_WindowContext = glutCreateWindow ("");

	glload::LoadFunctions();
	if(!glload::IsVersionGEQ(3, 3))
	{
		printf("Your OpenGL version is %i, %i. You must have at least OpenGL 3.3.\n",
			glload::GetMajorVersion(), glload::GetMinorVersion());
	}
	
	m_Engine = std::make_shared<OpenGLEngine> ();
	m_Factory = std::make_shared<OGLProgramFactory> ();

	m_WindowSize.m_XOrigin = xOrigin;
	m_WindowSize.m_YOrigin = yOrigin;
	m_WindowSize.m_XSize = xSize;
	m_WindowSize.m_YSize = ySize;
	m_Title = title;
}

Window::~Window ()
{
}

void Window::SetWindowSize (int xSize, int ySize)
{
	m_WindowSize.m_XSize = xSize;
	m_WindowSize.m_YSize = ySize;
}

void Window::SwapBuffers ()
{
	glutSwapBuffers ();
}

void Window::Destroy ()
{
	glutDestroyWindow(m_WindowContext);
}