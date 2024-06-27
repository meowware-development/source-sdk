#pragma once

class ConsoleCommand {
public:
	ConsoleCommand* m_pNext;
	bool m_bRegistered;
	const char* m_pszName;
	const char* m_pszHelpString;
	int	m_nFlags;
};

// TODO: Fill the struct
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