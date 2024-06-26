#pragma once
#include "consolecommand.hpp"

struct ConsoleCommand {
	ConsoleCommand* m_pNext;
	bool m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int	m_nFlags;
};

// TODO: Fill the struct
struct Cvar : public ConsoleCommand {

};