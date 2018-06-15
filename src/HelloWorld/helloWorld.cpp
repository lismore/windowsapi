#include <windows.h>

/** 
 * @brief  Main Function - displays a message box
 * @note   
 * @param  hThisInstance: 
 * @param  hPrevInstance: 
 * @param  lpCmdLine: 
 * @param  nCmdShow: 
 * @retval 
 */
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, "Yes, I am awesome", "A minimal Hello World Windows Program", MB_OK);
    return 0;
}