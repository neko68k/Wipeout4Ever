#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int v6 = 0;
	int v60 = 0;
	int v61 = 0;

	long dword_4AF0B0 = 0;
	long dword_49DF80 = 1500;
	long dword_48F7FC = 1;
	short word_A6496A = -1;
	WNDCLASS WndClass;
	HMODULE hModule;
	bool windowInitFlag;
	HWND hWnd = FindWindowA("PSYGWO2", 0);
	HWND v5 = hWnd;
	RECT Rect;
	if( hWnd!=0 ){
		HWND lastWnd = GetLastActivePopup(hWnd);
		BringWindowToTop(hWnd);
		if(lastWnd!=hWnd)
			BringWindowToTop(lastWnd);		
	}else{
		//WO_GetRootDirectoryRegKey();
		//sub_45F110();

		DWORD baseAddr = 0;
		DWORD sysColor = GetSysColor(15);
		HBRUSH hbr = CreateSolidBrush(sysColor);
		WndClass.style = 3;
		WndClass.lpfnWndProc = (WNDPROC)WndProc;//sub_45B220;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hInstance = hInstance;
		WndClass.hIcon = LoadIconA(hInstance, "AppIcon");
		WndClass.hCursor = LoadCursorA(0, IDC_ARROW);
		WndClass.hbrBackground = hbr;
		WndClass.lpszMenuName = "AppMenu";
		WndClass.lpszClassName = "PSYGWO2";
		hModule = GetModuleHandleA(0);
	}

	if ( RegisterClassA(&WndClass) )
    {
      HWND  desktopWindow = GetDesktopWindow();
      GetWindowRect(desktopWindow, &Rect);
      int x = (Rect.right - Rect.left - 500) / 2;
      int y = (Rect.bottom - Rect.top - 360) / 2;
      hWnd = CreateWindowExA(
               0x40000u,
               "PSYGWO2",
               "Wipeout XL",
               0x80C80000u,
               x,
               y,
               500,
               360,
               0,
               0,
               hInstance,
               0);
      if ( hWnd )
      {
        WO_DDrawInit();
        SetWindowPos(hWnd, 0, x, y, 500, 360, 0x14u);
        windowInitFlag = 1;
      }
      else
      {
        WO_StupidDDrawErrorMsg("CreateWindowEx failed");
        windowInitFlag = 0;
      }
    }
    else
    {
      windowInitFlag = 0;
    }
    if ( !windowInitFlag )
      return 0;

	HBITMAP h = LoadBitmapA(hInstance, (LPCSTR)113);
    HBITMAP dword_4C7BD8 = LoadBitmapA(hInstance, (LPCSTR)0x72);
    dword_48F81C = WO_ConfigLoad();
    WO_CreateConfigPopup();
    ShowWindow(hWnd, 1);
    UpdateWindow(hWnd);
    WO_GameStateStruct = (int)&unk_917920;
    byte_917926 = 1;
    WO_CD_Init();
    WO_CD_DRM();
    sub_42D830(&unk_4C7AB0);
    word_4C7AB8 = 0;
    word_4C7ABA = 0;
    word_4C7ABC = 320;
    byte_4C7AB4 = 0;
    word_4C7ABE = 0;
    word_4C7AC0 = 0;
    byte_4C7AB5 = 0;
    word_4C7AC2 = 240;
    word_4C7AC4 = 320;
    byte_4C7AB6 = 0;
    word_4C7AC6 = 240;







	return 0;
}