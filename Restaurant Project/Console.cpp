#include "Console.h"
#include <windows.h>

void Console::Change_font()
{
	HANDLE console_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX font_info{};
	font_info.cbSize = sizeof font_info;
	font_info.dwFontSize.X = 10;
	font_info.dwFontSize.Y = 20;
	font_info.FontFamily = FF_DONTCARE;
	font_info.FontWeight = FW_REGULAR;
	SetCurrentConsoleFontEx(console_out, FALSE, &font_info);
}

void Console::Disable_cursor()
{
	HANDLE console_output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(console_output, &cursor_info);
	cursor_info.bVisible = false;
	SetConsoleCursorInfo(console_output, &cursor_info);
}

void Console::Disable_x_button()
{
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}