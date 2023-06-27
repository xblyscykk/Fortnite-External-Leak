#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include <cstdint> // uintptr_t abuse
#include <cmath>

#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <algorithm>

#include "singleton.h"

#include "../ImGui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"

#include "fnv.h"

#include <C:\NOF\Products\Sources\Fortnite Free\d3dx9.h>
#include <d3d9.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d9.lib")

#ifdef _DEBUG
#define WRAP_IF_DEBUG(x) { x };
#else
#define WRAP_IF_DEBUG(x)
#endif
#define ERROR_MESSAGE(x) MessageBoxA(NULL, x, NULL, NULL)