#pragma once

#include <string_view>
#include <format>
#include "../../sdk/valve/interfaces/surface.hpp"

namespace utils::renderer {
	namespace fonts {
		inline unsigned long tahoma13;
		inline unsigned long tahoma13outline;
		inline unsigned long tahoma14;

		void AddFont(HFont& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0);

		void Initialize();
	}

	void FilledRectangle(float x, float y, float width, float height, Color color);
	void Rectangle(float x, float y, float width, float height, Color color);

	void Text(float x, float y, const HFont& font, Color color, std::string text);
	void TextWSTR(float x, float y, const HFont& font, Color color, std::wstring wstr);

	Vector2 GetTextSize(const HFont& font, std::string text);
	Vector2 GetTextSizeWSTR(const HFont& font, std::wstring wstr);

	inline int screenWidth = 0;
	inline int screenHeight = 0;

	void Initialize();
}