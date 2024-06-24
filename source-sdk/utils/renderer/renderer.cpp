#include "renderer.hpp"

#include "../../sdk/interfaces/interfaces.hpp"

#define WIN32_LEAN_AND_mEAN
#include <Windows.h>

#undef CreateFont

void utils::renderer::fonts::AddFont(HFont& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax)
{
	// Creates a new handle and returns it as a HFont (unsigned long)
	font = sdk::interfaces::surface->CreateFont();

	// Basically set the font options
	sdk::interfaces::surface->SetFontGlyphSet(font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMax, nRangeMax);
}

void utils::renderer::fonts::Initialize()
{
	AddFont(tahoma13, "Tahoma", 14, 500, 0, 0, EFontFlags::FONTFLAG_DROPSHADOW | EFontFlags::FONTFLAG_ANTIALIAS);
}

void utils::renderer::Initialize()
{
	sdk::interfaces::surface->GetScreenSize(screenWidth, screenHeight);

	fonts::Initialize();
}

void utils::renderer::FilledRectangle(float x, float y, float width, float height, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color);
	sdk::interfaces::surface->DrawFilledRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height));
}

void utils::renderer::Rectangle(float x, float y, float width, float height, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color);
	// This calls DrawFilledRect 4 times :dislike:
	sdk::interfaces::surface->DrawOutlinedRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height));
}

void utils::renderer::Line(float x1, float y1, float x2, float y2, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color);
	sdk::interfaces::surface->DrawLine(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
}

void utils::renderer::Circle(float x, float y, float radius, int segments, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color);
	sdk::interfaces::surface->DrawOutlinedCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(radius), segments);
}

void utils::renderer::Gradient(float x, float y, float width, float height, Color colorOne, Color colorTwo, bool horizontal)
{
	sdk::interfaces::surface->DrawSetColor(colorOne);
	sdk::interfaces::surface->DrawFilledRectFade(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height), 255, 0, horizontal);

	sdk::interfaces::surface->DrawSetColor(colorTwo);
	sdk::interfaces::surface->DrawFilledRectFade(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height), 0, 255, horizontal);
}

void utils::renderer::Text(float x, float y, const HFont& font, Color color, std::string text)
{
	// Using WinAPI seems like the easiest solution.
	// There was the codecvt library that did utf8 -> utf16 but it got deprecated in c++17 (and it had poor performance also)
	// And MSVC suggested to switch to MultiByteToWideChar, so whatever.
	wchar_t wstr[128];
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wstr, 128) > 0) {
		sdk::interfaces::surface->DrawSetTextColor(color);
		sdk::interfaces::surface->DrawSetTextFont(font);
		sdk::interfaces::surface->DrawSetTextPos(static_cast<int>(x), static_cast<int>(y));
		sdk::interfaces::surface->DrawPrintText(wstr, wcslen(wstr));
	}
}

void utils::renderer::TextWSTR(float x, float y, const HFont& font, Color color, std::wstring wstr)
{
	sdk::interfaces::surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	sdk::interfaces::surface->DrawSetTextFont(font);
	sdk::interfaces::surface->DrawSetTextPos(static_cast<int>(x), static_cast<int>(y));
	sdk::interfaces::surface->DrawPrintText(wstr.data(), wstr.length());
}

Vector2 utils::renderer::GetTextSize(const HFont& font, std::string text)
{
	wchar_t wstr[128];
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wstr, 128) > 0) {
		int wide, tall;

		sdk::interfaces::surface->GetTextSize(font, wstr, wide, tall);

		return Vector2{ static_cast<float>(wide), static_cast<float>(tall) };
	}

	return Vector2();
}

Vector2 utils::renderer::GetTextSizeWSTR(const HFont& font, std::wstring wstr)
{
	int wide, tall;

	sdk::interfaces::surface->GetTextSize(font, wstr.data(), wide, tall);

	return Vector2{ static_cast<float>(wide), static_cast<float>(tall) };
}