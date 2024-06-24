#pragma once

#include <string_view>
#include <format>
#include "../../sdk/valve/interfaces/isurface.hpp"

namespace utils::renderer {
	namespace fonts {
		inline unsigned long tahoma13;

		void AddFont(HFont& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0);

		void Initialize();
	}

	void FilledRectangle(float x, float y, float width, float height, Color color);
	void Rectangle(float x, float y, float width, float height, Color color);
	void Line(float x1, float y1, float x2, float y2, Color color);
	void Circle(float x, float y, float radius, int segments, Color color);
	void Gradient(float x, float y, float width, float height, Color colorOne, Color colorTwo, bool horizontal = true);

	void Text(float x, float y, const HFont& font, Color color, std::string text);
	void TextWSTR(float x, float y, const HFont& font, Color color, std::wstring wstr);

	Vector2 GetTextSize(const HFont& font, std::string text);
	Vector2 GetTextSizeWSTR(const HFont& font, std::wstring wstr);

	inline int screenWidth = 0;
	inline int screenHeight = 0;

	void Initialize();
}