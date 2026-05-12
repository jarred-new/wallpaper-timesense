#include "stdafx.h"

#pragma comment(lib, "User32.lib")

#define TIMER_ID 1
#define TIMER_LOADER 2

std::wstring GetAppDir() {
	wchar_t szPath[MAX_PATH];
	// Get the full path of the current .exe
	GetModuleFileNameW(NULL, szPath, MAX_PATH);

	std::wstring path(szPath);
	// Find the last backslash to remove the filename
	size_t lastSlash = path.find_last_of(L"\\/");
	return path.substr(0, lastSlash + 1);
}

void ChangeWallpaperBasedOnTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	int hour = st.wHour;
	std::wstring imagePath;

	if (hour >= 5 && hour < 12)
		imagePath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\morning.jpg");
	else if (hour >= 12 && hour < 17)
		imagePath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\afternoon.jpg");
	else if (hour >= 17 && hour < 20)
		imagePath = _T("C:\\Program Files (x86)\\Jarred\\WallpaperTimeSense\\time\\night.jpg");

	SystemParametersInfoW(
		SPI_SETDESKWALLPAPER,
		0,
		(PVOID)imagePath.c_str(),
		SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, TIMER_ID, 60000, NULL); // Check every 60 seconds
		SetTimer(hwnd, TIMER_LOADER, 1000, NULL); // Check every 60 seconds
		ChangeWallpaperBasedOnTime();          // Run immediately
		return 0;

	case WM_TIMER:
		if (wParam == TIMER_ID)
			ChangeWallpaperBasedOnTime();
		if (wParam == TIMER_LOADER) {
			ShowWindow(hwnd, SW_HIDE);
			KillTimer(hwnd, TIMER_LOADER);
		}
		return 0;

	case WM_DESTROY:
		KillTimer(hwnd, TIMER_ID);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
	const wchar_t CLASS_NAME[] = L"WallpaperTimeSense";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Preparing WallpaperTimeSense - by Jarred",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}