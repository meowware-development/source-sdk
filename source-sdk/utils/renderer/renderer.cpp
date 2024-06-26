#include "renderer.hpp"

#include "../../sdk/interfaces/interfaces.hpp"

#define WIN32_LEAN_AND_mEAN
#include <Windows.h>

#undef CreateFont

void utils::renderer::fonts::AddFont(Font& font)
{
	if (!font.handle)
		font.handle = sdk::interfaces::surface->CreateFont();

	sdk::interfaces::surface->SetFontGlyphSet(font.handle, font.windowsFontName, font.tall, font.weight, font.blur, font.scanlines, font.flags);
}

void utils::renderer::fonts::Initialize()
{
	tahoma13 = Font{
		"Tahoma",
		13, 1000, 0, 0,
		EFontFlags::FONTFLAG_DROPSHADOW | EFontFlags::FONTFLAG_ANTIALIAS
	};

	AddFont(tahoma13);
}

void utils::renderer::Initialize()
{
	sdk::interfaces::surface->GetScreenSize(screenWidth, screenHeight);

	fonts::Initialize();
}

void utils::renderer::FilledRectangle(float x, float y, float width, float height, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	sdk::interfaces::surface->DrawFilledRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height));
}

void utils::renderer::Rectangle(float x, float y, float width, float height, Color color)
{
	sdk::interfaces::surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	// This calls DrawFilledRect 4 times :dislike:
	sdk::interfaces::surface->DrawOutlinedRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>(x + width), static_cast<int>(y + height));
}

void utils::renderer::Text(float x, float y, const fonts::Font& font, Color color, std::string_view text)
{
	// Using WinAPI seems like the easiest solution.
	// There was the codecvt library that did utf8 -> utf16 but it got deprecated in c++17 (and it had poor performance also)
	// And MSVC suggested to switch to MultiByteToWideChar, so whatever.
	wchar_t wstr[128];
	if (MultiByteToWideChar(CP_UTF8, 0, text.data(), -1, wstr, 128) > 0) {
		sdk::interfaces::surface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
		sdk::interfaces::surface->DrawSetTextFont(font.handle);
		sdk::interfaces::surface->DrawSetTextPos(static_cast<int>(x), static_cast<int>(y));
		sdk::interfaces::surface->DrawPrintText(wstr, wcslen(wstr));
	}
}

void utils::renderer::TextWSTR(float x, float y, const fonts::Font& font, Color color, std::wstring wstr)
{
	sdk::interfaces::surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	sdk::interfaces::surface->DrawSetTextFont(font.handle);
	sdk::interfaces::surface->DrawSetTextPos(static_cast<int>(x), static_cast<int>(y));
	sdk::interfaces::surface->DrawPrintText(wstr.data(), wstr.length());
}

Vector2 utils::renderer::GetTextSize(const fonts::Font& font, std::string text)
{
	wchar_t wstr[128];
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wstr, 128) > 0) {
		int wide, tall;

		sdk::interfaces::surface->GetTextSize(font.handle, wstr, wide, tall);

		return Vector2{ static_cast<float>(wide), static_cast<float>(tall) };
	}

	return Vector2();
}

Vector2 utils::renderer::GetTextSizeWSTR(const fonts::Font& font, std::wstring wstr)
{
	int wide, tall;

	sdk::interfaces::surface->GetTextSize(font.handle, wstr.data(), wide, tall);

	return Vector2{ static_cast<float>(wide), static_cast<float>(tall) };
}