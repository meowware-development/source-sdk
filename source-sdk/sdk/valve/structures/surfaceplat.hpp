#pragma once
#include <Windows.h>

struct VPanel;

struct SurfacePlat
{
public:
	HWND    hwnd;
	HDC     hdc;
	HDC     hwndDC;
	HDC	  textureDC;
	HGLRC   hglrc;
	HRGN    clipRgn;
	HBITMAP bitmap;
	int     bitmapSize[2];
	int     restoreInfo[4];
	bool    isFullscreen;
	bool	disabled;
	int     fullscreenInfo[3];
	VPanel* embeddedPanel;
	bool    isToolbar;
	HICON   notifyIcon;
	unsigned int notifyPanel;
	unsigned long lastKeyFocusIndex;
};