#pragma once
#include "../enums/sourcedefs.hpp"

enum VGuiPanel {
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

// In-game panels are cropped to the current engine viewport size
enum PaintMode {
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2), // software cursor, if appropriate
};

class EngineVGui {
public:
	virtual					~EngineVGui(void) { }
	virtual VPANEL	GetPanel(VGuiPanel type) = 0;
	virtual bool			IsGameUIVisible() = 0;
};