#include <WinUser.h>
#include <string>
#include <string.h>
#include <processthreadsapi.h>
#include "Imgui/imgui.h"

#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace hotkeys
{
	int aimkey;
	int triggerkey;
	int backkey;
	int aimkeyyy;
	int aimkeyyyy;
	int airstuckey;
}

static int keystatus = 0;
static int keystatuss = 0;
static int keystatusssss = 0;
static int triggerstatus = 0;
static int realkeyy = 0;
static int keystatusss = 0;
static int keystatussss = 0;
static int realkeyyy = 0;
static int realkeyyyy = 0;
static int backtrackkey = 0;

bool GetKey(int key)
{
	triggerstatus = key;
	return true;
}
bool GetKeyy(int keyy)
{
	realkeyy = keyy;
	return true;
}
bool GetKeyyy(int keyyy)
{
	realkeyyy = keyyy;
	return true;
}
bool GetKeyyyy(int keyyyy)
{
	realkeyyyy = keyyyy;
	return true;
}
bool GetKeyyyyy(int keyyyyy)
{
	backtrackkey = keyyyyy;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 0;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}
void ChangeKeyyy(void* blank)
{
	keystatusss = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkeyyy = i;
				keystatusss = 0;
				return;
			}
		}
	}
}
void ChangeKeyyyy(void* blank)
{
	keystatussss = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkeyyyy = i;
				keystatussss = 0;
				return;
			}
		}
	}
}
void ChangeTrigger(void* blank)
{
	triggerstatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::triggerkey = i;
				triggerstatus = 0;
				return;
			}
		}
	}
}
void ChangeKeyyyyy(void* blank)
{
	keystatusssss = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::backkey = i;
				keystatusssss = 0;
				return;
			}
		}
	}
}


static const char* keyNamers[] =
{
	"Triggerbot Key",
	"Left Mouse Button",
	"Right Mouse Button",
	"Control-break processing",
	"Middle Mouse Button",
	"X1 mouse button",
	"X2 mouse button",
	"Undefined",
	"BACKSPACE key",
	"TAB key",
	"unknown",
	"unknown",
	"CLEAR key",
	"ENTER key",
	"unknown",
	"unknown",
	"SHIFT key",
	"CTRL key",
	"ALT key",
	"PAUSE key",
	"CAPS LOCK key",
	"IME Kana mode",
	"unknown",
	"IME Junja mode",
	"IME final mode",
	"IME Kanji mode",
	"IME Off",
	"ESC key",
	"IME convert",
	"IME nonconvert",
	"IME nonconvert",
	"IME accept",
	"SPACEBAR",
	"PAGE UP key",
	"PAGE DOWN key",
	"END key",
	"HOME key",
	"LEFT ARROW key",
	"UP ARROW key",
	"RIGHT ARROW key",
	"DOWN ARROW key",
	"SELECT key",
	"PRINT key",
	"EXECUTE key",
	"PRINT SCREEN key",
	"INS key",
	"DEL key",
	"HELP key",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"Left Windows key",
	"Right Windows key",
	"Applications key",
	"unknown",
	"Computer Sleep key",
	"Numeric keypad 0 key",
	"Numeric keypad 1 key",
	"Numeric keypad 2 key",
	"Numeric keypad 3 key",
	"Numeric keypad 4 key",
	"Numeric keypad 5 key",
	"Numeric keypad 6 key",
	"Numeric keypad 7 key",
	"Numeric keypad 8 key",
	"Numeric keypad 9 key",
	"Multiply key",
	"Add key",
	"Separator key",
	"Subtract key",
	"Decimal key",
	"Divide key",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"NUM LOCK key",
	"SCROLL LOCK key",
	"OEM NEC Equal",
	"OEM FJ masshou",
	"OEM FJ touroku",
	"OEM FJ loya",
	"OEM FJ roya",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"Left Shift",
	"Right Shfit",
	"Left Control",
	"Right Control",
	"Left ALT key",
	"Right ALT key"
};
static const char* keyNames[] =
{
	"Aimbot Key",
	"Left Mouse Button",
	"Right Mouse Button",
	"Control-break processing",
	"Middle Mouse Button",
	"X1 mouse button",
	"X2 mouse button",
	"Undefined",
	"BACKSPACE key",
	"TAB key",
	"unknown",
	"unknown",
	"CLEAR key",
	"ENTER key",
	"unknown",
	"unknown",
	"SHIFT key",
	"CTRL key",
	"ALT key",
	"PAUSE key",
	"CAPS LOCK key",
	"IME Kana mode",
	"unknown",
	"IME Junja mode",
	"IME final mode",
	"IME Kanji mode",
	"IME Off",
	"ESC key",
	"IME convert",
	"IME nonconvert",
	"IME nonconvert",
	"IME accept",
	"SPACEBAR",
	"PAGE UP key",
	"PAGE DOWN key",
	"END key",
	"HOME key",
	"LEFT ARROW key",
	"UP ARROW key",
	"RIGHT ARROW key",
	"DOWN ARROW key",
	"SELECT key",
	"PRINT key",
	"EXECUTE key",
	"PRINT SCREEN key",
	"INS key",
	"DEL key",
	"HELP key",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"Left Windows key",
	"Right Windows key",
	"Applications key",
	"unknown",
	"Computer Sleep key",
	"Numeric keypad 0 key",
	"Numeric keypad 1 key",
	"Numeric keypad 2 key",
	"Numeric keypad 3 key",
	"Numeric keypad 4 key",
	"Numeric keypad 5 key",
	"Numeric keypad 6 key",
	"Numeric keypad 7 key",
	"Numeric keypad 8 key",
	"Numeric keypad 9 key",
	"Multiply key",
	"Add key",
	"Separator key",
	"Subtract key",
	"Decimal key",
	"Divide key",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"NUM LOCK key",
	"SCROLL LOCK key",
	"OEM NEC Equal",
	"OEM FJ masshou",
	"OEM FJ touroku",
	"OEM FJ loya",
	"OEM FJ roya",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"Left Shift",
	"Right Shfit",
	"Left Control",
	"Right Control",
	"Left ALT key",
	"Right ALT key"
};
static const char* keyNiggers[] =
{
	"Menu Key",
	"Left Mouse Button",
	"Right Mouse Button",
	"Control-break processing",
	"Middle Mouse Button",
	"X1 mouse button",
	"X2 mouse button",
	"Undefined",
	"BACKSPACE key",
	"TAB key",
	"unknown",
	"unknown",
	"CLEAR key",
	"ENTER key",
	"unknown",
	"unknown",
	"SHIFT key",
	"CTRL key",
	"ALT key",
	"PAUSE key",
	"CAPS LOCK key",
	"IME Kana mode",
	"unknown",
	"IME Junja mode",
	"IME final mode",
	"IME Kanji mode",
	"IME Off",
	"ESC key",
	"IME convert",
	"IME nonconvert",
	"IME nonconvert",
	"IME accept",
	"SPACEBAR",
	"PAGE UP key",
	"PAGE DOWN key",
	"END key",
	"HOME key",
	"LEFT ARROW key",
	"UP ARROW key",
	"RIGHT ARROW key",
	"DOWN ARROW key",
	"SELECT key",
	"PRINT key",
	"EXECUTE key",
	"PRINT SCREEN key",
	"INS key",
	"DEL key",
	"HELP key",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m",
	"n",
	"o",
	"p",
	"q",
	"r",
	"s",
	"t",
	"u",
	"v",
	"w",
	"x",
	"y",
	"z",
	"Left Windows key",
	"Right Windows key",
	"Applications key",
	"unknown",
	"Computer Sleep key",
	"Numeric keypad 0 key",
	"Numeric keypad 1 key",
	"Numeric keypad 2 key",
	"Numeric keypad 3 key",
	"Numeric keypad 4 key",
	"Numeric keypad 5 key",
	"Numeric keypad 6 key",
	"Numeric keypad 7 key",
	"Numeric keypad 8 key",
	"Numeric keypad 9 key",
	"Multiply key",
	"Add key",
	"Separator key",
	"Subtract key",
	"Decimal key",
	"Divide key",
	"f1",
	"f2",
	"f3",
	"f4",
	"f5",
	"f6",
	"f7",
	"f8",
	"f9",
	"f10",
	"f11",
	"f12",
	"f13",
	"f14",
	"f15",
	"f16",
	"f17",
	"f18",
	"f19",
	"f20",
	"f21",
	"f22",
	"f23",
	"f24",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"NUM LOCK key",
	"SCROLL LOCK key",
	"OEM NEC Equal",
	"OEM FJ masshou",
	"OEM FJ touroku",
	"OEM FJ loya",
	"OEM FJ roya",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"unknown",
	"Left Shift",
	"Right Shfit",
	"Left Control",
	"Right Control",
	"Left ALT key",
	"Right ALT key"
};
static const char* keyNamess[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static const char* keyNamesss[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static const char* keyNamessss[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static const char* keyNamesssss[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

void NiggerButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNiggers))
		Items_ArrayGetter(keyNiggers, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}
void HotkeyButtonnn(int aimkeyyy, void* changekeyyy, int statusss)
{
	const char* preview_value = NULL;
	if (aimkeyyy >= 0 && aimkeyyy < IM_ARRAYSIZE(keyNamers))
		Items_ArrayGetter(keyNamers, aimkeyyy, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (statusss == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (statusss == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekeyyy, nullptr, 0, nullptr);
		}
	}
}

void HotkeyButtonnnn(int aimkeyyyy, void* changekeyyyy, int statussss)
{
	const char* preview_value = NULL;
	if (aimkeyyyy >= 0 && aimkeyyyy < IM_ARRAYSIZE(keyNamessss))
		Items_ArrayGetter(keyNamessss, aimkeyyyy, &preview_value);

	std::string menukeys;
	if (preview_value == NULL)
		menukeys = "Select Key";
	else
		menukeys = preview_value;

	if (statussss == 1)
	{
		menukeys = "Press the key";
	}
	if (ImGui::Button(menukeys.c_str(), ImVec2(125, 20)))
	{
		if (statussss == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekeyyyy, nullptr, 0, nullptr);
		}
	}
}
void HotkeyButtonnnnn(int aimkeyyyyy, void* changekeyyyyy, int statusssss)
{
	const char* preview_value = NULL;
	if (aimkeyyyyy >= 0 && aimkeyyyyy < IM_ARRAYSIZE(keyNamesssss))
		Items_ArrayGetter(keyNamesssss, aimkeyyyyy, &preview_value);

	std::string menukeys;
	if (preview_value == NULL)
		menukeys = "Select Key";
	else
		menukeys = preview_value;

	if (statusssss == 1)
	{
		menukeys = "Press the key";
	}
	if (ImGui::Button(menukeys.c_str(), ImVec2(125, 20)))
	{
		if (statusssss == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekeyyyyy, nullptr, 0, nullptr);
		}
	}
}
