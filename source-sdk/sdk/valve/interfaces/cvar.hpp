#pragma once
#include <iostream>
#include <cstdarg>
#include <array>
#include <utility>

#include "appsystem.hpp"
#include "../../../utils/constants/const.hpp"
#include "../../../utils/memory/memory.hpp"

class ConVar;
class ConsoleCommand;
class Color;

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
	virtual ConVar* FindVar(const char* name) = 0;
	virtual const ConVar* FindVar(const char* name) const = 0;
	virtual void* FindCommand(const char* name) = 0;
	virtual const void* FindCommand(const char* name) const = 0;

	// Get first ConsoleCommand to allow iteration
	virtual ConsoleCommand* GetCommands(void) = 0;
	virtual const ConsoleCommand* GetCommands(void) const = 0;

	// Install a global change callback (to be called when any Cvar changes) 
	virtual void InstallGlobalChangeCallback(CvarChangeCallback callback) = 0;
	virtual void RemoveGlobalChangeCallback(CvarChangeCallback callback) = 0;
	virtual void CallGlobalChangeCallbacks(ConVar* var, const char* pOldString, float flOldValue) = 0;

	// Install a console printer
	virtual void InstallConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void RemoveConsoleDisplayFunc(void* pDisplayFunc) = 0;
	virtual void ConsoleColorPrintf(const Color& clr, const char* pFormat, ...) = 0;
	virtual void ConsolePrintf(const char* pFormat, ...) = 0;
	virtual void ConsoleDPrintf(const char* pFormat, ...) = 0;

	// Reverts cvars which contain a specific flag
	virtual void RevertFlaggedCvars(int nFlag) = 0;

	// Method allowing the engine ICvarQuery interface to take over
	// A little hacky, owing to the fact the engine is loaded
	// well after ICVar, so we can't use the standard connect pattern
	virtual void InstallCVarQuery(void* pQuery) = 0;

	virtual bool IsMaterialThreadSetAllowed() const = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pCvar, const char* pValue) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pCvar, int nValue) = 0;
	virtual void QueueMaterialThreadSetValue(ConVar* pCvar, float flValue) = 0;
	virtual bool HasQueuedMaterialThreadCvarSets() const = 0;
	virtual int	ProcessQueuedMaterialThreadCvarSets() = 0;
};

class ConsoleCommand {
public:
	ConsoleCommand* m_pNext;
	bool m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int	m_nFlags;
};

class ConVar : public ConsoleCommand {
public:
	void SetString(const char* value) {
		return utils::memory::CallVirtualFunction<void>(this, 10, value);
	}

	void SetFloat(float value) {
		return utils::memory::CallVirtualFunction<void>(this, 11, value);
	}

	void SetInt(int value) {
		return utils::memory::CallVirtualFunction<void>(this, 12, value);
	}

	void SetBool(bool value) {
		return utils::memory::CallVirtualFunction<void>(this, 12, static_cast<int>(value));
	}

	float GetFloat() {
		uint32_t uXored = *reinterpret_cast<uint32_t*>(&m_fValue) ^ reinterpret_cast<std::uint32_t>(this);
		return *reinterpret_cast<float*>(&uXored);
	}

	int GetInt() {
		return m_nValue ^ reinterpret_cast<int>(this);
	}

	bool GetBool() {
		return static_cast<bool>(m_nValue ^ reinterpret_cast<int>(this));
	}

	const char* GetString() {
		char const* szValue = m_pszString;
		return szValue ? szValue : "";
	}

	ConVar* m_pParent;

	// Static data
	const char* m_pszDefaultValue;

	// Value
	// Dynamically allocated
	char* m_pszString;
	int							m_StringLength;

	// Values
	float						m_fValue;
	int							m_nValue;

	// Min/Max values
	bool						m_bHasMin;
	float						m_fMinVal;
	bool						m_bHasMax;
	float						m_fMaxVal;

	// Min/Max values for competitive.
	bool						m_bHasCompMin;
	float						m_fCompMinVal;
	bool						m_bHasCompMax;
	float						m_fCompMaxVal;

	bool						m_bCompetitiveRestrictions;
};