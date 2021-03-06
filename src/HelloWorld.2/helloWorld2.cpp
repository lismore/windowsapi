#include <windows.h>

const char g_class_name[] = "myHelloWorld2WindowClass";

// declare the WndProc function
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/** 
 * @brief  Main Function - displays a resizable window
 * @note   
 * @param  hThisInstance: 
 * @param  hPrevInstance: 
 * @param  lpCmdLine: 
 * @param  nCmdShow: 
 * @retval 
 */
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
	   HWND hwnd;
	   MSG Msg;

	   //create a structure describing the window
	   wc.cbSize        = sizeof(WNDCLASSEX);
	   wc.style         = 0;
	   wc.lpfnWndProc   = WndProc;       // N.B. here we specify the name of our function
	   wc.cbClsExtra    = 0;
	   wc.cbWndExtra    = 0;
	   wc.hInstance     = hThisInstance;
	   wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	   wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	   wc.lpszMenuName  = NULL;
	   wc.lpszClassName = g_class_name;
	   wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	   // call RegisterClassEx. This is called "registering the window class".
	   // this tells the operating system we are here and want a window
	   if (!RegisterClassEx(&wc))
	   {
	      MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	      return 0;
	   }

	   // the operating system says we can have a window. Now we create it using CreateWindowEx.
	   // The parameters here define the appearance of the window: what the border looks like,the title, etc.
	   hwnd = CreateWindowEx(
	      WS_EX_CLIENTEDGE,                         // what the border looks like
	      g_class_name,
	      "Hello World 2",                 // text appearing in top bar
	      WS_OVERLAPPEDWINDOW,
	      CW_USEDEFAULT, CW_USEDEFAULT, 840, 820,   // window xpos, ypos, width, height
	      NULL, NULL, hThisInstance, NULL);

	   if (hwnd == NULL)
	   {
	      MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
	      return 0;
	   }

	   ShowWindow(hwnd, nCmdShow);
	   UpdateWindow(hwnd);

	   /* the Message Loop. This while loop is perpetually going round and round at the "base" of the program, it constantly picks up messages from the keyboard,
          mouse and other devices, and calling the WndProc function
	   */  
	   while ( GetMessage(&Msg, NULL, 0, 0) > 0 )
	   {
	      TranslateMessage(&Msg);
	      DispatchMessage(&Msg);
	   }
	   return Msg.wParam;
}

/** 
 * @brief  Display function - displays a string
 * @note   
 * @param  hwnd: 
 * @param  s: 
 * @retval None
 */
void disp(HWND hwnd, char* s)
{  
	HFONT hfont, hOldfont;
   	HDC hdc;

	hfont = (HFONT) GetStockObject(ANSI_VAR_FONT);    	// obtain a standard font
	hdc = GetDC(hwnd);                       			// point to the "device context" for this window
	hOldfont = (HFONT) SelectObject(hdc, hfont);      	// select font into the device context
	if (hOldfont)  										// if succesful
	{
		TextOut(hdc, 10, 50, s, strlen(s));
		SelectObject(hdc, hOldfont);         			// put the previous font back into dc
	}
	else MessageBox(hwnd, "could not select the font", "Error!", MB_ICONEXCLAMATION | MB_OK);

	ReleaseDC(hwnd, hdc);                   			// tidy up
}

/** 
 * @brief  WindowsProcedure - call back function 
 * @note   
 * @param  hwnd: 
 * @param  msg: 
 * @param  wParam: 
 * @param  lParam: 
 * @retval 
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch(msg)
   {
   case WM_SIZE:   
     disp(hwnd, "hello world 2");
     return 0;
   case WM_LBUTTONDOWN:
     MessageBox(hwnd, "hello again", "Hello World 2", MB_OK);
     return 0;       
   case WM_CLOSE:
      DestroyWindow(hwnd);
     return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
   }
}   