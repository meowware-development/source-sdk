#pragma once
#include <iostream>
#include <cstdarg>
#include <array>
#include <utility>
#include "appsystem.hpp"
#include "../../../utils/constants/const.hpp"
#include "../../../utils/memory/memory.hpp"

struct Cvar;
struct ConsoleCommand;
struct EngineColor;

class CvarManager;

using CvarChangeCallback = void(__stdcall*)(CvarManager*, const char* old, float oldValue);

class CvarManager : public AppSystem {
public:
	virtual int AllocateDLLIdentifier() = 0;
	virtual void RegisterConCommand(ConsoleCommand* commandBase) = 0;
	virtual void UnregisterConCommand(ConsoleCommand* commandBase) = 0;
	virtual void UnregisterConCommands(int id) = 0;
	virtual const char* GetCommandLineValue(const char* name) = 0;

	// Try to find the cvar pointer by name
	virtual ConsoleCommand* FindCommandBase(const char* name) = 0;
	virtual const ConsoleCommand* FindCommandBase(const char* name) const = 0;
	virtual Cvar* FindVar(const char* name) = 0;
	virtual const Cvar* FindVar(const char* name) const = 0;
	virtual void* FindCommand(const char* name) = 0;
	virtual const void* FindCommand(const char* name) const = 0;

	// Get first ConsoleCommand to allow iteration
	virtual ConsoleCommand* GetCommands(void) = 0;
	virtual const ConsoleCommand* GetCommands(void) const = 0;

	// Install a global change callback (to be called when any Cvar changes) 
	virtual void InstallGlobalChangeCallback(CvarChangeCallback callback) = 0;
	virtual void RemoveGlobalChangeCallback(CvarChangeCallback callback) = 0;
	virtual void CallGlobalChangeCallbacks(Cvar* var, const char* pOldString, float flOldValue) = 0;

	// Install a console printer
	virtual void InstallConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const EngineColor& clr, const char* pFormat, ...) = 0;
	virtual void ConsolePrintf(const char* pFormat, ...) = 0;
	virtual void ConsoleDPrintf(const char* pFormat, ...) = 0;

	// Reverts cvars which contain a specific flag
	virtual void RevertFlaggedCvars(int nFlag) = 0;

	// Method allowing the engine ICvarQuery interface to take over
	// A little hacky, owing to the fact the engine is loaded
	// well after ICVar, so we can't use the standard connect pattern
	virtual void InstallCVarQuery(void* pQuery) = 0;

	virtual bool IsMaterialThreadSetAllowed() const = 0;
	virtual void QueueMaterialThreadSetValue(Cvar* pCvar, const char* pValue) = 0;
	virtual void QueueMaterialThreadSetValue(Cvar* pCvar, int nValue) = 0;
	virtual void QueueMaterialThreadSetValue(Cvar* pCvar, float flValue) = 0;
	virtual bool HasQueuedMaterialThreadCvarSets() const = 0;
	virtual int	ProcessQueuedMaterialThreadCvarSets() = 0;
};