#pragma once

struct string_t
{
	bool operator!() const { return (pszValue == 0); }
	bool operator==(const string_t& rhs) const { return (pszValue == rhs.pszValue); }
	bool operator!=(const string_t& rhs) const { return (pszValue != rhs.pszValue); }
	bool operator<(const string_t& rhs) const { return ((void*)pszValue < (void*)rhs.pszValue); }

	const char* ToCStr() const { return (pszValue) ? pszValue : ""; }

	const char* pszValue;
};