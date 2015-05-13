#pragma once
#include <Windows.h>
#include <WindowsX.h>


typedef  bool (*t_void_func)();
typedef  bool (*t_float_func)(float);

class win32
{

	
public:
	//Bool flags for setting the properties
	bool bShowCursor;
	bool bFullScreen;
	bool bPopupWindow;
	

	//Public Interface
	
//	bool RegisterWindow( HINSTANCE instance, int _width = 800, int _height = 600, char* _class_name = "Win32Class");
	bool CreateWin32Window(HINSTANCE instance_, int xPos, int yPos, int width_, int height_);
	void peek_Run();	//Run using peekmessage() to be used in gaming
	void get_Run();		//Run using getmessage() to be used generally but not in gaming
	void SetTitle( char* text ) { m_title = text; }
	void SetPosition(int _x, int _y);
	void SetRender_func(t_void_func) ;
	void SetUpdate_func(t_float_func);
	void ShowMessage(char* text, char* caption);
	HWND GetHandle()		{ return m_handle; }
	int GetWidth()		{ return m_width;  }
	int GetHeight()		{ return m_height; }
	HINSTANCE GetInstance()	{return m_instance;}
	
	win32(char *title_ );
	~win32(void);


protected:
	static LRESULT CALLBACK WindProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );


private:
	WNDCLASSEX m_window;	//Structure to hold m_windows prperties
	char* m_title;		//Text on title bar
	char* m_className;	//Name of the class used in CreateWindowEX
	int m_width,m_height;	//m_windows width and height
	int m_xPos,m_yPos;			//m_windows  position on screen
	HWND m_handle;	//Handle to the m_window that will be returned
	HINSTANCE m_instance;		//Holds the current instance of the m_window
	t_void_func Render;		//Function pointer which will point to render function from outside
	t_float_func Update;		//Function pointer which will call to Update function from outside

	bool RegisterWindow(HINSTANCE);	//Called by CreateWindow

};


#define message(msg,caption) MessageBox(NULL,(char*)msg,(char*)caption,MB_ICONEXCLAMATION | MB_OK)