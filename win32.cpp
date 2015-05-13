#include "win32.h"



win32::win32(char *title_ ) 
{
	m_title = title_;
	m_className  = "win32class";
	Render = NULL;
	Update = NULL;
}


win32::~win32(void)
{
}


bool win32::RegisterWindow(HINSTANCE _instance)
{

	//bFullScreen ? width = 1600.0f, height = 1200.0f, x = y = 0 : width = 800.0f, height = 600.0f, x = y = 100;   
	if (bFullScreen)
	{
		 m_width = 1600, m_height = 1200, m_xPos = m_yPos= 0 ;
	}
	else
	{
		 m_width = 1600, m_height= 1200, m_xPos = m_yPos= 0; 
	}
	

	ZeroMemory(&(m_window), sizeof(m_window));	//Clear the memory for m_window object
	m_window.cbSize = sizeof(WNDCLASSEX);				//Sets the size equal to the size of the structure
	m_window.hbrBackground = (HBRUSH)COLOR_3DLIGHT;
	m_window.style = CS_HREDRAW | CS_VREDRAW;			//Enables horizontal and vertical redraw
	bShowCursor ? m_window.hCursor = LoadCursor(NULL, IDC_ARROW),ShowCursor(true):NULL, ShowCursor(false);	//decides wether to sho cursor or not
	m_window.lpszClassName = m_className;				//Sets the name of the class
	m_window.lpfnWndProc = win32::WindProc;
	m_handle = NULL;
	m_window.lpszMenuName = NULL;
	m_instance = m_window.hInstance = _instance;
	HRESULT result = RegisterClassEx(&m_window);
	if (FAILED(result))
		return false;
	else
	return true;

}


bool win32::CreateWin32Window(HINSTANCE instance_, int xPos_, int yPos_, int width_, int height_)
{
	//First register the window, if it returns true, then we return 
	if(RegisterWindow(instance_))
	{
	//If width and height is given, then use that and return 
		if(width_ & height_)
		{
			m_width= width_;
			m_height = height_;
			m_handle = CreateWindowEx(NULL, m_className, m_title,
				 WS_OVERLAPPEDWINDOW, xPos_, yPos_, width_, height_,
				NULL, NULL, m_instance, NULL);
			return true;
		}
	//If width and height is not given , then get the current system resolution and return 
	//Now get the current resolution (including taskbar and titlebar)
		width_  = GetSystemMetrics(SM_CXSCREEN);
		height_ = GetSystemMetrics(SM_CYSCREEN);
		
		
		m_width= width_;
		m_height = height_;
		m_handle = CreateWindowEx(NULL, m_className, m_title,
									 WS_POPUP, xPos_, yPos_,
									 width_, height_,NULL,
									 NULL, m_instance, NULL);
		return true;
	}
	else
		return false;
	

	
}

LRESULT win32::WindProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
				PostQuitMessage(0);
			
		}
		
			break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			
		} break;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);

}

void win32::get_Run()
{
	ShowWindow(m_handle,1);
	
	MSG msg;


		while(GetMessage( &msg, NULL, 0, 0 ))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			
		}
	
}

void win32::peek_Run()
{
	ShowWindow(m_handle,1);

	MSG msg;

	while (1)
	{
		while(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			PostQuitMessage(0);
			break;
		} 
		else
		{

		}

	}


}

void win32::SetPosition(int _x, int _y)
{
	m_xPos = _x, m_yPos = _y;
}

void win32::ShowMessage(char* text,char* caption)
{
	MessageBox(NULL,text,caption,MB_ICONEXCLAMATION | MB_OK);
}


