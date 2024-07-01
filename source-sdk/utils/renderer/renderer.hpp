#pragma once

#include <string_view>
#include <string>
#include <format>

#include "../../sdk/valve/datatypes/color.hpp"
#include "../../sdk/math/vector.hpp"

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

		void AddFont(Font& font) noexcept;

		void Initialize() noexcept;
	}

	void FilledRectangle(int x, int y, int width, int height, Color color) noexcept;
	void Rectangle(int x, int y, int width, int height, Color color) noexcept;

	void Text(int x, int y, const fonts::Font& font, Color color, std::string_view text) noexcept;
	void TextWSTR(int x, int y, const fonts::Font& font, Color color, std::wstring wstr) noexcept;

	struct Size {
		int width, height;
	};

	Size GetTextSize(const fonts::Font& font, std::string text) noexcept;
	Size GetTextSizeWSTR(const fonts::Font& font, std::wstring wstr) noexcept;

	inline int screenWidth = 0;
	inline int screenHeight = 0;

	void Initialize() noexcept;
}