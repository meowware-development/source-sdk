#pragma once

// Our color implementation differs a bit; this is the same as the game's

struct EngineColor {
	// constructors
	EngineColor()
	{
		*((int*)this) = 0;
	}

	EngineColor(int _r, int _g, int _b)
	{
		SetEngineColor(_r, _g, _b, 255);
	}

	EngineColor(int _r, int _g, int _b, int _a)
	{
		SetEngineColor(_r, _g, _b, _a);
	}

	// Set the EngineColor
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void SetEngineColor(int _r, int _g, int _b, int _a = 0)
	{
		_EngineColor[0] = (unsigned char)_r;
		_EngineColor[1] = (unsigned char)_g;
		_EngineColor[2] = (unsigned char)_b;
		_EngineColor[3] = (unsigned char)_a;
	}

	void GetEngineColor(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _EngineColor[0];
		_g = _EngineColor[1];
		_b = _EngineColor[2];
		_a = _EngineColor[3];
	}

	void SetRawEngineColor(int EngineColor32)
	{
		*((int*)this) = EngineColor32;
	}

	int GetRawEngineColor() const
	{
		return *((int*)this);
	}

	inline int r() const { return _EngineColor[0]; }
	inline int g() const { return _EngineColor[1]; }
	inline int b() const { return _EngineColor[2]; }
	inline int a() const { return _EngineColor[3]; }

	unsigned char& operator[](int index)
	{
		return _EngineColor[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _EngineColor[index];
	}

	bool operator == (const EngineColor& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const EngineColor& rhs) const
	{
		return !(operator==(rhs));
	}

	EngineColor& operator=(const EngineColor& rhs)
	{
		SetRawEngineColor(rhs.GetRawEngineColor());
		return *this;
	}

private:
	unsigned char _EngineColor[4];
};