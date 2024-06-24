#pragma once
#include <d3dx9.h>

class Color
{
public:
	// constructors
	Color() = default;

	Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}


	Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetColor(int _r, int _g, int _b, int _a = 0)
	{
		m_Color[0] = (unsigned char)_r;
		m_Color[1] = (unsigned char)_g;
		m_Color[2] = (unsigned char)_b;
		m_Color[3] = (unsigned char)_a;
	}

	void GetColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = m_Color[0];
		_g = m_Color[1];
		_b = m_Color[2];
		_a = m_Color[3];
	}

	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int*)this);
	}

	inline int r() const { return m_Color[0]; }
	inline int g() const { return m_Color[1]; }
	inline int b() const { return m_Color[2]; }
	inline int a() const { return m_Color[3]; }

	D3DCOLOR D3DColor()
	{
		return D3DCOLOR_RGBA(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	}

	unsigned char& operator[](int index)
	{
		return m_Color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return m_Color[index];
	}

	bool operator == (const Color& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const Color& rhs) const
	{
		return !(operator==(rhs));
	}

	Color& operator=(const Color& rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

private:
	unsigned char m_Color[4] = { 255, 255, 255, 255 };
};