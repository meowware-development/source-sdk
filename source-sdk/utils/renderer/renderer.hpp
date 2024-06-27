#pragma once

#include <string_view>
#include <format>
#include "../../sdk/valve/interfaces/surface.hpp"

namespace utils::renderer {
	namespace fonts {
		struct Font {
			const char* windowsFontName = "";
			int tall = 0;
			int weight = 0;
			int blur = 0;
			int scanlines = 0;
			int flags = 0;

			unsigned long handle = 0;
		};

		inline Font tahoma13;
		inline Font tahoma13outline;
		inline Font tahoma14;

		void AddFont(Font& font);

		void Initialize();
	}

	void FilledRectangle(float x, float y, float width, float height, Color color);
	void Rectangle(float x, float y, float width, float height, Color color);

	void Text(float x, float y, const fonts::Font& font, Color color, std::string_view text);
	void TextWSTR(float x, float y, const fonts::Font& font, Color color, std::wstring wstr);

	Vector2 GetTextSize(const fonts::Font& font, std::string text);
	Vector2 GetTextSizeWSTR(const fonts::Font& font, std::wstring wstr);

	inline int screenWidth = 0;
	inline int screenHeight = 0;

	void Initialize();
}