// Source made by Create#5488
// Release Date: 02.02.2023 
// Updated to Latest Patch
// If you need help dm me -> Create#5488
#include "MainIncludes.h"
#include <tchar.h>
#include "lazyimp.hpp"
#include "Imgui/imgui_internal.h"
#include "Memory/memory1.h"
#include <wininet.h>
inline uintptr_t player_controller;

Vector3 RotatePoint(Vector3 pointToRotate, Vector3 centerPoint, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck, bool angleInRadians = false);
DWORD_PTR closestPawner = NULL;
DWORD_PTR closestPawnbullet = NULL;

void DrawESP();


DWORD espthread(LPVOID IN) {
	while (true) {
		auto start = std::chrono::high_resolution_clock::now();
		DrawESP();
		auto end = std::chrono::high_resolution_clock::now();
		auto delta = end - start;
		const int FPS = 144;
		const auto targetFrameTime = std::chrono::microseconds(1000000 / FPS);
		if (delta < targetFrameTime) {
			std::this_thread::sleep_for(targetFrameTime - delta);
		}
	}
}

static std::string GetNameFromIndex(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;
	uint64_t NamePoolChunk = Memory.Read<uint64_t>(Memory.BaseAddress + 0xF237A00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	uint16_t nameEntry = Memory.Read<uint16_t>(NamePoolChunk);
	int nameLength = nameEntry >> 6;
	char buff[1024] = {};

	char* v2; // rdi
	int v8; // ecx
	int16_t v9; // ax
	int16_t result = 38i64;
	int v6 = 0;
	int v7 = 38;
	int v5 = 0;
	if (nameLength)
	{
		Memory._HyperV->ReadMem(PVOID(NamePoolChunk + 4), (PVOID)(&buff), 2 * nameLength);
		v2 = buff;
		do
		{
			v7 = v5 | result;
			++v2;
			++v5;
			v8 = ~(_BYTE)v7;
			result = (unsigned int)(2 * v7);
			*(_BYTE*)(v2 - 1) ^= v8;
		} while (v5 < nameLength);
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	return std::string("");
}

static std::string GetNameFromFName(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = Memory.Read<uint64_t>(Memory.BaseAddress + 0xF237A00 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	if (Memory.Read<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = Memory.Read<DWORD>(NamePoolChunk + 4);
		return GetNameFromIndex(a1);
	}
	else
	{
		return GetNameFromIndex(key);
	}
}


void sss()
{
	while (true)
	{
		XorS(call, "FortniteClient-Win64-Shipping.exe");
		DWORD pid = Memory.GamePID;
		if (!pid == NULL)
		{
			return;
		}
	}
}
std::string path()
{
	char shitter[_MAX_PATH];
	GetModuleFileNameA(NULL, shitter, _MAX_PATH);
	return std::string(shitter);
}

namespace Actors
{
	DWORD_PTR Uworld;
	DWORD_PTR PersistentLevel;
	DWORD_PTR Rootcomp;
	DWORD_PTR Localplayer;
	DWORD_PTR PlayerController;
	DWORD_PTR LocalPawn;
	DWORD_PTR PlayerState;
	DWORD_PTR Persistentlevel;
	uintptr_t PlayerCameraManager;
	DWORD_PTR GameState;
	DWORD_PTR PlayerArray;
	DWORD_PTR LocalPlayers;
	uintptr_t Gameinstance;
}

namespace GayLoop
{
	uintptr_t PersistentLevelActors;
	uintptr_t CurrentActor;
	std::string Ass;
	int CurrentActorID;
}

namespace Ass
{
	uintptr_t CurrentActor;
}

#define PI 3.14159265358979323846f

struct _MATRIX
{
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};

	_MATRIX() : _11(1.f), _12(0.f), _13(0.f), _14(0.f),
		_21(0.f), _22(1.f), _23(0.f), _24(0.f),
		_31(0.f), _32(0.f), _33(1.f), _34(0.f),
		_41(0.f), _42(0.f), _43(0.f), _44(1.f) {}
};
_MATRIX Matrix(Vector3 euler, Vector3 Vec4, Vector3 origin = Vector3(0, 0, 0))
{
	const float radPitch = euler.x * PI / 180.f;
	const float radYaw = euler.y * PI / 180.f;
	const float radRoll = euler.z * PI / 180.f;
	const float SP = sinf(radPitch);
	const float CP = cosf(radPitch);
	const float SY = sinf(radYaw);
	const float CY = cosf(radYaw);
	const float SR = sinf(radRoll);
	const float CR = cosf(radRoll);

	_MATRIX mat;

	mat.m[0][0] = CP * CY;
	mat.m[0][1] = CP * SY;
	mat.m[0][2] = SP;
	mat.m[0][3] = 0.f;

	mat.m[1][0] = SR * SP * CY - CR * SY;
	mat.m[1][1] = SR * SP * SY + CR * CY;
	mat.m[1][2] = -SR * CP;
	mat.m[1][3] = 0.f;

	mat.m[2][0] = -(CR * SP * CY + SR * SY);
	mat.m[2][1] = CY * SR - CR * SP * SY;
	mat.m[2][2] = CR * CP;
	mat.m[2][3] = 0.f;

	mat.m[3][0] = origin.x;
	mat.m[3][1] = origin.y;
	mat.m[3][2] = origin.z;
	mat.m[3][3] = 1.f;

	return mat;
}

Vector3 GetBoneWithRotation(DWORD_PTR mesh, int index)
{
	uintptr_t bonearray = 0;
	bonearray = Memory.Read<uintptr_t>(mesh + 0x600);
	if (!bonearray) bonearray = Memory.Read<uintptr_t>(mesh + 0x600 + 0x10);
	FTransform ComponentToWorld = Memory.Read<FTransform>(mesh + 0x240);
	FTransform bone = Memory.Read<FTransform>(bonearray + (index * 0x60));
	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

struct CamewaDescwipsion
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	char Useless[0x18];
};
CamewaDescwipsion GetViewPoint()
{
	char v1; // r8
	CamewaDescwipsion ViewPoint = Memory.Read<CamewaDescwipsion>(Memory.BaseAddress + 0xF0E8BD0);
	BYTE* v2 = (BYTE*)&ViewPoint;
	int i; // edx
	__int64 result; // rax

	v1 = 0x40;
	for (i = 0; i < 0x40; ++i)
	{
		*v2 ^= v1;
		result = (unsigned int)(i + 0x17);
		v1 += i + 0x17;
		v2++;
	}

	return ViewPoint;
}

std::string replaceAll(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
std::string DownloadString(const char* URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	std::string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL, NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			std::string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	std::string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}
Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	CamewaDescwipsion vCamera = GetViewPoint();
	_MATRIX tempMatrix = Matrix(vCamera.Rotation, Vector3(0, 0, 0));
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f) vTransformed.z = 1.f;
	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}
int width;
int height;
int milox;
int main()
{//
	system(skCrypt("color e"));
	// add museo.ttf font (neverlose font) download here / change the font
	Memory.Initialize();
	if (!Memory.Initialize()) {
		printf(skCrypt("Prerequisties not loaded, rebooting. If the error persists contact support. \n"));
		// add pasteager loader here
	}
	SetConsoleTitleA("Administrator: Command Prompt");
	system(skCrypt("cls"));
	std::cout << skCrypt("\n");
	system("cls");
	std::cout << "[NOF] Waiting for Fortnite...";
	sss(); 
	MessageBox(NULL, skCrypt(L"Click OK In Lobby"), skCrypt(L"Information"), NULL);
	hwnd = FindWindowA(0, "Fortnite  ");
	std::cout << skCrypt("\n");
	system("cls");
	Sleep(200);
	xCreateWindow();
	xInitD3d();
	xMainLoop();
	HANDLE handle = CreateThread_Esp(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(espthread), nullptr, NULL, nullptr);
	xShutdown();
}
//dtc
bool isVisible(uint64_t Mesh)
{
	auto fLastSubmitTime = Memory.Read<float>(Mesh + 0x360);
	auto fLastRenderTimeOnScreen = Memory.Read<float>(Mesh + 0x368);
	const float fVisionTick = 0.15f;
	return fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
}

void memory(float x, float y, DWORD_PTR playercontroller)
{
	int AimSpeed = Smoothness;

	float screen_center_x = (Width / 2);
	float screen_center_y = (Height / 2);
	float TargetX = 0;
	float TargetY = 0;
	if (x != 0)
	{
		if
			(x > screen_center_x)
		{
			TargetX = -(screen_center_x - x); if (TargetX + screen_center_x > screen_center_x * 2)TargetX = 0;
		}
		if
			(x < screen_center_x)
		{
			TargetX = x - screen_center_x; if (TargetX + screen_center_x < 0)TargetX = 0;
		}
	}
	if (y != 0)
	{
		if
			(y > screen_center_y)
		{
			TargetY = -(screen_center_y - y); if (TargetY + screen_center_y > screen_center_y * 2) TargetY = 0;
		}
		if
			(y < screen_center_y)
		{
			TargetY = y - screen_center_y; if (TargetY + screen_center_y < 0) TargetY = 0;
		}
	}

	Vector3 Angles;
	Angles = Vector3(-TargetY / AimSpeed, TargetX / AimSpeed, 0);

	Memory.Write<double>(Actors::PlayerController + 0x518, Angles.x);
	Memory.Write<double>(Actors::PlayerController + 0x518 + 0x8, Angles.y);

}

auto SetGlobalTimeDilationForLevels(float NewTimeDilation, bool bReset)
{
	auto WorldContext = GWorld;
	if (!WorldContext) return;

	static auto OldTimeDilation = 0.0f;

	for (auto LevelIndex = 0; LevelIndex < Memory.Read<int>(WorldContext + (0x160 + sizeof(uintptr_t))); ++LevelIndex)
	{
		auto Levels = Memory.Read<uintptr_t*>(WorldContext + 0x170);
		if (!Levels) break;

		auto CurrentLevel = Levels[LevelIndex];
		if (!CurrentLevel) continue;

		auto CurrentLevelID = Memory.Read<int>(CurrentLevel + 0x98);

		auto WorldSettings = Memory.Read<uintptr_t>(CurrentLevel + 0x298);
		if (!WorldSettings) continue;

		// Save old TimeDilation.
		if (!OldTimeDilation) OldTimeDilation = Memory.Read<float>(WorldSettings + 0x390);

		// Reset the TimeDilation to the original cached value.
		if (bReset) Memory.Write<float>(WorldSettings + 0x390, OldTimeDilation), OldTimeDilation = 0.0f;

		// Set the TimeDilation to the new value.
		if (NewTimeDilation) Memory.Write<float>(WorldSettings + 0x390, NewTimeDilation);
	}
}

#pragma once
#include "input.hpp"
// Source made by Create#5488
// Release Date: 02.02.2023 
// Updated to Latest Patch
// If you need help dm me -> Create#5488 
float gaysmooth = 5;
void mouseory(float x, float y)
{
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = gaysmooth;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	//WriteAngles(TargetX / 3.5f, TargetY / 3.5f);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

	return;
}




void AimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = Memory.Read<uint64_t>(entity + Offsets::External::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, def::hitbox);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		memory(rootHeadOut.x, rootHeadOut.y, Actors::PlayerController);
	}
}

void NotAimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = Memory.Read<uint64_t>(entity + Offsets::External::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, def::hitbox);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		mouseory(rootHeadOut.x, rootHeadOut.y);
	}
}

ImU32 RGBtoU32(int r, int g, int b)
{
	float fr = (float)r / 255.0;
	float fg = (float)g / 255.0;
	float fb = (float)b / 255.0;
	return ImGui::GetColorU32(ImVec4(fr, fg, fb, 1));
}
DWORD_PTR CurrentActorMesh;

Vector3 GetLoc(Vector3 Loc) {
	Vector3 Location = Vector3(Loc.x, Loc.y, Loc.z);
	return Location;
}

// RADAR CREDITS GOES TO -> ud man#1337
void DrawESP() {
	if (circletype == true)
	{
		if (square_fov) {
			ImVec2 rectMin = ImVec2(ScreenCenterX - def::AimbotFov, ScreenCenterY - def::AimbotFov);
			ImVec2 rectMax = ImVec2(ScreenCenterX + def::AimbotFov, ScreenCenterY + def::AimbotFov);
			ImU32 color = IM_COL32(255, 255, 255, 128);
			float rounding = 0.f;
			float thickness = 0.5f;
			ImGui::GetBackgroundDrawList()->AddRect(rectMin, rectMax, color, rounding, ImDrawCornerFlags_All, thickness);
		}

		if (fovcircle) {
			ImVec2 center = ImVec2(ScreenCenterX, ScreenCenterY);
			float radius = def::AimbotFov;
			ImU32 color = IM_COL32(255, 255, 255, 255);
			int numSegments = 100;
			float thickness = 0.5f;
			ImGui::GetBackgroundDrawList()->AddCircle(center, radius, color, numSegments, thickness);
		}

		if (fovcirclefilled) {
			ImVec2 center = ImVec2(ScreenCenterX, ScreenCenterY);
			float radius = def::AimbotFov;
			int numSegments = 100;
			ImU32 color = IM_COL32(0, 0, 0, 160);
			float thickness = 220.0f;
			float outlineThickness = 0.5f;
			ImGui::GetBackgroundDrawList()->AddCircleFilled(center, radius, color, numSegments);
			ImGui::GetBackgroundDrawList()->AddCircle(center, radius, IM_COL32(255, 80, 80, 255), thickness, outlineThickness);
		}
		if (SquareFovFilled) {
			ImVec2 rectMin = ImVec2(ScreenCenterX - def::AimbotFov, ScreenCenterY - def::AimbotFov);
			ImVec2 rectMax = ImVec2(ScreenCenterX + def::AimbotFov, ScreenCenterY + def::AimbotFov);
			ImU32 color = IM_COL32(255, 80, 80, 255);
			float rounding = 0.f;
			float thickness = 0.5f;
			ImGui::GetBackgroundDrawList()->AddRectFilled(rectMin, rectMax, IM_COL32(0, 0, 0, 160));
			ImGui::GetBackgroundDrawList()->AddRect(rectMin, rectMax, color, rounding, ImDrawCornerFlags_All, thickness);
		}
	}

	HitBoxAimKey();

	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;


	//aa\\
	// -------------------------------------------------------
	Actors::Uworld = Memory.Read<uint64_t>(Memory.BaseAddress + GWorld);

	Actors::PersistentLevel = Memory.Read<uintptr_t>(Actors::Uworld + 0x30);

	Actors::Gameinstance = Memory.Read<uint64_t>(Actors::Uworld + Offsets::External::Gameinstance);

	Actors::LocalPlayers = Memory.Read<uint64_t>(Actors::Gameinstance + Offsets::External::LocalPlayers);

	Actors::Localplayer = Memory.Read<uint64_t>(Actors::LocalPlayers);

	Actors::PlayerController = Memory.Read<uint64_t>(Actors::Localplayer + Offsets::External::PlayerController);

	Actors::LocalPawn = Memory.Read<uint64_t>(Actors::PlayerController + Offsets::External::LocalPawn);

	Actors::PlayerState = Memory.Read<uint64_t>(Actors::LocalPawn + Offsets::External::PlayerState);

	Actors::Rootcomp = Memory.Read<uint64_t>(Actors::LocalPawn + Offsets::External::RootComponet);

	Actors::GameState = Memory.Read<uint64_t>(Actors::Uworld + Offsets::External::GameState);

	Actors::PlayerArray = Memory.Read<uint64_t>(Actors::GameState + Offsets::External::PlayerArray);
	// -------------------------------------------------------
		
	// -------------------------------------------------------
	const uintptr_t CURRENT_ACTOR_OFFSET = 0x300;
	const uintptr_t MESH_OFFSET = 0x310;
	const uintptr_t TEAM_ID_OFFSET = Offsets::External::TeamId;
	const uintptr_t PLAYER_STATE_OFFSET = Offsets::External::PlayerState;
	const uintptr_t WEAPON_OFFSET = 0x908;
	const uintptr_t RELOADING_OFFSET = 0x348;
	const uintptr_t TARGETING_OFFSET = 0xB05;
	const uintptr_t OTHER_PLAYER_STATE_OFFSET = 0x290;
	// -------------------------------------------------------
	uintptr_t PlayerArrayOffset = Offsets::External::PlayerArray;
	int PlayerSize = Memory.Read<int>(Actors::GameState + (PlayerArrayOffset + sizeof(uintptr_t)));
	for (int i = 0; i < PlayerSize; i++)
	{
		uintptr_t player = Memory.Read<uintptr_t>(Actors::PlayerArray + i * 0x8);
		Ass::CurrentActor = Memory.Read<uintptr_t>(player + CURRENT_ACTOR_OFFSET);
		int CurrentActorId = Memory.Read<int>(Ass::CurrentActor + 0x18);
		const auto& SkeletalMesh = Memory.Read<uintptr_t>(Ass::CurrentActor + 0x5a8);
		const auto& UCapsuleComponent = Memory.Read<uintptr_t>(Ass::CurrentActor + 0x320);
		const uint64_t CurrentActorMesh = Memory.Read<uint64_t>(Ass::CurrentActor + MESH_OFFSET);
		const int MyTeamId = Memory.Read<int>(Actors::PlayerState + TEAM_ID_OFFSET);
		const DWORD64 otherPlayerState = Memory.Read<uint64_t>(Ass::CurrentActor + OTHER_PLAYER_STATE_OFFSET);
		const int ActorTeamId = Memory.Read<int>(otherPlayerState + TEAM_ID_OFFSET);
		const uintptr_t CurrentWeapon = Memory.Read<uintptr_t>(Ass::CurrentActor + WEAPON_OFFSET);
		const bool bIsReloadingWeapon = Memory.Read<bool>(CurrentWeapon + RELOADING_OFFSET);
		const bool bIsTargeting = Memory.Read<bool>(CurrentWeapon + TARGETING_OFFSET);
		if (MyTeamId == ActorTeamId) continue;


		if (SelfEsp) {
		}
		else {
			if (Ass::CurrentActor == Actors::LocalPawn) {
				continue;
			}
		}
		// --- Vector3 ---
		Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 68);
		Vector3 bone66 = GetBoneWithRotation(CurrentActorMesh, 66);
		Vector3 top = ProjectWorldToScreen(bone66);
		Vector3 bone0 = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 bottom = ProjectWorldToScreen(bone0);
		Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
		Vector3 w2shead = ProjectWorldToScreen(Headpos);
		Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 68);
		Vector3 vRootBone = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 vHeadBoneOut = ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z + 15));
		localactorpos = Memory.Read<Vector3>(Actors::Rootcomp + 0x128);


		// --- Float's ---
		const float distanceThreshold = def::VisDist * ChangerFOV;
		float distance = localactorpos.Distance(Headpos) / ChangerFOV;
		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * BoxWidthValue;
		// ----------------
			if (distance <= distanceThreshold)
			{


				if (BigPlayers)
				{
					////////////
					if (Ass::CurrentActor != Actors::LocalPawn)
					{
						const auto& UCapsuleComponent = Memory.Read<uintptr_t>(Ass::CurrentActor + UCAPSULECOMPONENT);
						Memory.Write<Vector3>(UCapsuleComponent + RELATIVESCALE3D, Vector3(300, 300, 300));
					}
				}

				if (carFly)
				{
					uint64_t CurrentVehicle = Memory.Read<uint64_t>(Actors::LocalPawn + CURRENTVEHICLE);
					if (GetAsyncKeyState(VK_SPACE))Memory.Write<char>(CurrentVehicle + BUSEGRAVITY, 1);
				}


				if (InstaRes) {
					Memory.Write<float>(Actors::LocalPawn + 0x4540, .001);
				}


				if (AirStuck) {  //Freezes You in the Air
					if (GetAsyncKeyState(VK_CAPITAL)) { //Alt Keybind
						Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 0); //CustomTimeDilation
					}
					else {
						Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 1); //CustomTimeDilation
					}
				}

				if (FakeLag) {  //Freezes You in the Air

					Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 0); //CustomTimeDilation
					Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 1); //CustomTimeDilation
				}


				if (FakeLag)
				{

				}

				if (InstaReload) {
					bool bIsReloadingWeapon = Memory.Read<bool>(CurrentWeapon + BISRELOADINGWEAPON);
					uintptr_t Mesh = Memory.Read<uintptr_t>(Actors::LocalPawn + MESH);

					if (bIsReloadingWeapon)
					{
						Memory.Write<float>(Mesh + GLOBALANIMRATESCALE, 999); //0xa28 globalanimratescale
					}
					else
					{
						Memory.Write<float>(Mesh + GLOBALANIMRATESCALE, 1); //0xa28
					}
				}


				if (LightMode) {
					ImGui::StyleColorsLight();
				}

				if (DarkMode) {
					ImGui::StyleColorsDark();
				}

				if (instantall)
				{
					auto worldsettings = Memory.Read<uintptr_t>(Actors::LocalPawn + 0x298);

					Memory.Write(worldsettings + 0x390, 5.f);
				}

				if (NoBloom) {
					Memory.Write<float>(Actors::PlayerController + CUSTOMTIMEDILATION, -1);
					Memory.Write<float>(CurrentWeapon + CUSTOMTIMEDILATION, FLT_MAX);
				}

				if (ClientInvisibility)
				{
					if (Actors::LocalPawn)
					{
						auto Mesh = Memory.Read<uint64_t>(Actors::LocalPawn + MESH);
						Memory.Write<Vector3>(Mesh + RELATIVESCALE3D, Vector3(0, 0, 0));
					}
				}

				if (BigPlayers)
				{
					if (Actors::LocalPawn)
					{
						auto Mesh = Memory.Read<uint64_t>(Actors::LocalPawn + MESH);
						Memory.Write<Vector3>(Mesh + RELATIVESCALE3D, Vector3(1, 1, 1));
					}
				}

				if (SmallPlayer)
				{
					if (Actors::LocalPawn)
					{
						auto Mesh = Memory.Read<uint64_t>(Actors::LocalPawn + MESH);
						Memory.Write<Vector3>(Mesh + RELATIVESCALE3D, Vector3(0.5, 0.5, 0.5));
					}
				}

				if (doublepump)
				{
					uintptr_t CurrentWeapon = Memory.Read<uintptr_t>(Actors::LocalPawn + CURRENTWEAPON);
					if (CurrentWeapon)
					{
						Memory.Write<bool>(CurrentWeapon + BIGNORETRYTOFIRE, true); //AFortWeapon    bIgnoreTryToFireSlotCooldownRestriction    0xf41    bool
					}
				}

				if (PlayerDistanceEsp)
				{
					char name[64];
					sprintf_s(name, skCrypt("[%2.fm]"), distance);
					DrawString(16, Headbox.x, Headbox.y - 15, &Col.white, true, true, name);
				}
				if (PlayerFly)
				{
					Memory.Write<float>(Actors::LocalPawn + ZIPLINESPEEDFACTOR, 10.0f); // ZiplineSpeedFactor
					Memory.Write<bool>(Actors::LocalPawn + ZIPLINESTATE + 0x18, true); // ZiplineState
				}



				if (InfiniteFuel)
				{			
						uint64_t CurrentVehicle = Memory.Read<uint64_t>(Actors::LocalPawn + CURRENTVEHICLE);
						auto FuelComponent = Memory.Read<uintptr_t>((uintptr_t)CurrentVehicle + CACHEDFUELCOMPONENT); //FortAthenaVehicle::CachedFuelComponent 0x10A0
						Memory.Write<float>(FuelComponent + 0xf0, 20000.f);
				}

				if (NoWeaponAnimation)
				{
					uintptr_t CurrentWeapon = Memory.Read<uintptr_t>(Actors::LocalPawn + CURRENTWEAPON); //CurrentWeapon Offset
					if (CurrentWeapon) {
						Memory.Write<bool>(CurrentWeapon + 0x34a, true); //bDisableEquipAnimation Offset (update this yourself)
					}
				}

				if (RapidFire)
				{
					auto ScaleX = Memory.Read<float>(CurrentWeapon + 0xb20);
					auto ScaleY = Memory.Read<float>(CurrentWeapon + 0xb24);
					Memory.Write<float>(CurrentWeapon + 0xb20, ScaleX + ScaleY - 2);
				}
		

				if (Spinbot)
				{
					uintptr_t Mesh = Memory.Read<uintptr_t>((uintptr_t)Actors::LocalPawn + MESH);

					if (Spinbot)
					{
						Memory.Write<Vector3>(Mesh + RELATIVEROTATION, Vector3(0, -rand() % (int)360, 0));
					}
					else
					{
						Memory.Write<Vector3>(Mesh + RELATIVEROTATION, Vector3(0, -90, 0));
					}
				}

				if (BigPlayers)
				{

					if (Ass::CurrentActor != Actors::LocalPawn)
					{
						Memory.Write<Vector3>(UCapsuleComponent + RELATIVESCALE3D, Vector3(490, 490, 490));
					}
				}

				if (BigPlayerss)
				{

					if (Ass::CurrentActor != Actors::LocalPawn)
					{
						Memory.Write<Vector3>(UCapsuleComponent + RELATIVESCALE3D, Vector3(5, 5, 5));
					}
				}

				if (NormalPlayers)
				{

					if (Ass::CurrentActor != Actors::LocalPawn)
					{
						Memory.Write<Vector3>(UCapsuleComponent + RELATIVESCALE3D, Vector3(1, 1, 1));
					}
				}

				if (WindowStreamProof) {
					SetWindowDisplayAffinity(Window, WDA_EXCLUDEFROMCAPTURE);
				}
				if (!WindowStreamProof) {
					SetWindowDisplayAffinity(Window, !WDA_EXCLUDEFROMCAPTURE);
				}

				if (fillbox)
				{
					DrawFilledRect(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(0, 0, 0, 125));
				}

				if (CornerBoxEsp)
				{
					if (isVisible(CurrentActorMesh) && CurrentActorMesh != Actors::LocalPawn)
					{
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 255, 255), Boxthinkness);
					}
					else if (!isVisible(CurrentActorMesh) && CurrentActorMesh != Actors::LocalPawn)
					{
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 0, 0), Boxthinkness);
					}
				}
				if (BoxEsp)
				{
					if (isVisible(CurrentActorMesh) && CurrentActorMesh != Actors::LocalPawn)
					{
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(0, 255, 0), Boxthinkness);
					}
					else if (!isVisible(CurrentActorMesh) && CurrentActorMesh != Actors::LocalPawn)
					{
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, RGBtoU32(255, 0, 0), Boxthinkness);
					}

				}

				//if (NoSpread) {
//
					//   __int64 xor_key = ((Memory.Read<__int8>(CurrentWeapon + 5231) - 60985) & 0x82FFFFFE | 0x4C000001);
					//   __int64 offset = CurrentWeapon + 4 * Memory.Read<__int8>(CurrentWeapon + 5230) + 5214;
					//   Memory.Write<int>(offset, VALUE ^ xor_key);
				  // }
				if (Triggerbot)
				{

					if (CurrentActorMesh != Actors::LocalPawn)
					{
						if (isVisible(CurrentActorMesh) && GetAsyncKeyState(hotkeys::triggerkey))
						{
							mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
							mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
						}
					}
				}

				if (FovChanger)
				{
				}



				if (KillAll) {
					if (Ass::CurrentActor != Actors::LocalPawn){
						if (GetAsyncKeyState(VK_CAPITAL)) { //Alt Keybind
							Memory.Write<double>(Actors::Rootcomp + 0x260, vRootBone.x);
							Memory.Write<double>(Actors::Rootcomp + 0x260 + 0x8, vRootBone.y);
							Memory.Write<double>(Actors::Rootcomp + 0x260 + 0x10, vRootBone.z);
							Memory.Write<Vector3>(UCapsuleComponent + RELATIVESCALE3D, Vector3(3, 3, 3));
							const auto& UCapsuleComponent = Memory.Read<uintptr_t>(Ass::CurrentActor + UCAPSULECOMPONENT);
						}
					}

				}

				if (AirStuck) {  //Freezes You in the Air
					if (GetAsyncKeyState(VK_CAPITAL)) { //Alt Keybind
						Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 0); //CustomTimeDilation
					}
					else {
						Memory.Write<float>(Actors::LocalPawn + CUSTOMTIMEDILATION, 1); //CustomTimeDilation
					}
				}

				if (crosshair)
				{
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 - CrosshairSize, Height / 2), RGBtoU32(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 + CrosshairSize, Height / 2), RGBtoU32(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 - CrosshairSize), RGBtoU32(255, 255, 255));
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 + CrosshairSize), RGBtoU32(255, 255, 255));
				}
				if (Skeleton)
				{
					ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();
					Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 68);
					Vector3 vHip = GetBoneWithRotation(CurrentActorMesh, 7);
					Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
					Vector3 vUpperArmLeft = GetBoneWithRotation(CurrentActorMesh, 9);
					Vector3 vUpperArmRight = GetBoneWithRotation(CurrentActorMesh, 38);
					Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 30);
					Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 58);
					Vector3 vLeftHand1 = GetBoneWithRotation(CurrentActorMesh, 11);
					Vector3 vRightHand1 = GetBoneWithRotation(CurrentActorMesh, 40);
					Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 78);
					Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 71);
					Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 79);
					Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 72);
					Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 74);
					Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 81);
					Vector3 vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
					Vector3 vHipOut = ProjectWorldToScreen(vHip);
					Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
					Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
					Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
					Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
					Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
					Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
					Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
					Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
					Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
					Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
					Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
					Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
					Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
					if (isVisible(CurrentActorMesh)) {
						Drawlist->AddLine(ImVec2(vHipOut.x, vHipOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vLeftHandOut1.x, vLeftHandOut1.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vRightHandOut1.x, vRightHandOut1.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vHipOut.x, vHipOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vHipOut.x, vHipOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vLeftFootOut.x, vLeftFootOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), RGBtoU32(0, 255, 0));
						Drawlist->AddLine(ImVec2(vRightFootOut.x, vRightFootOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), RGBtoU32(0, 255, 0));
					}
					else {
						Drawlist->AddLine(ImVec2(vHipOut.x, vHipOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vNeckOut.x, vNeckOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vLeftHandOut.x, vLeftHandOut.y), ImVec2(vLeftHandOut1.x, vLeftHandOut1.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vRightHandOut.x, vRightHandOut.y), ImVec2(vRightHandOut1.x, vRightHandOut1.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vHipOut.x, vHipOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vHipOut.x, vHipOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vLeftFootOut.x, vLeftFootOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), RGBtoU32(255, 0, 0));
						Drawlist->AddLine(ImVec2(vRightFootOut.x, vRightFootOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), RGBtoU32(255, 0, 0));
					}
				}
				if (Snaplines)
				{
					if (isVisible(CurrentActorMesh))
					{
						DrawLine(Width / 2 - 0, Height / 2 - 540, bottom.x, bottom.y, &Col.green, 0.5);
					}
					else
					{
						DrawLine(Width / 2 - 0, Height / 2 - 540, bottom.x, bottom.y, &Col.red, 0.5);
					}
				}

				if (DynamicEsp)
				{
					Vector3 bottom1 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 1, vRootBone.z));
					Vector3 bottom2 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 1, vRootBone.z));
					Vector3 bottom3 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 1, vRootBone.z));
					Vector3 bottom4 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 1, vRootBone.z));
					Vector3 top1 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y, vHeadBone.z + 15));
					Vector3 top2 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y, vHeadBone.z + 15));
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImColor(0, 0, 0, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImColor(0, 0, 0, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImColor(0, 0, 0, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImColor(0, 0, 0, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImColor(255, 255, 255, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImColor(255, 255, 255, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImColor(255, 255, 255, 255), 3.1f);
					ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImColor(255, 255, 255, 255), 3.1f);
				}
				if (reloadcheck)
				{
					if (bIsReloadingWeapon)
						ImGui::GetBackgroundDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 0, 0, 0), "RELOADING");
					else
						ImGui::GetBackgroundDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 255, 255, 255), "NOT RELOADING");
				}
				if (targetingcheck)
				{
					if (bIsReloadingWeapon)
						ImGui::GetBackgroundDrawList()->AddText(ImVec2(top.x, top.y + 30), IM_COL32(255, 0, 0, 0), "Player is Targeting");
					else
						ImGui::GetBackgroundDrawList()->AddText(ImVec2(top.x, top.y + 30), IM_COL32(255, 255, 255, 255), "Player is Not Targeting");
				}
				if (ThreeDBoxEsp)
				{
					if (vHeadBoneOut.x != 0 || vHeadBoneOut.y != 0 || vHeadBoneOut.z != 0)
					{
						ImU32 ESPSkeleton;
						if (isVisible(CurrentActorMesh))
						{
							ESPSkeleton = RGBtoU32(255, 255, 255);
						}
						else if (!isVisible(CurrentActorMesh))
						{
							ESPSkeleton = RGBtoU32(255, 0, 0);
						}
						Vector3 bottom1 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y - 40, vRootBone.z));
						Vector3 bottom2 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y - 40, vRootBone.z));
						Vector3 bottom3 = ProjectWorldToScreen(Vector3(vRootBone.x - 40, vRootBone.y + 40, vRootBone.z));
						Vector3 bottom4 = ProjectWorldToScreen(Vector3(vRootBone.x + 40, vRootBone.y + 40, vRootBone.z));
						Vector3 top1 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y - 40, vHeadBone.z + 15));
						Vector3 top2 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y - 40, vHeadBone.z + 15));
						Vector3 top3 = ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y + 40, vHeadBone.z + 15));
						Vector3 top4 = ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y + 40, vHeadBone.z + 15));
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ESPSkeleton, 0.6f);
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ESPSkeleton, 0.6f);
					}
				}
			}
			auto dx = w2shead.x - (Width / 2);
			auto dy = w2shead.y - (Height / 2);
			auto dist = sqrtf(dx * dx + dy * dy);
			if (isVisible(CurrentActorMesh)) {

				if (dist < def::AimbotFov && dist < closestDistance) {
					closestDistance = dist;
					closestPawn = Ass::CurrentActor;
				}
			}
		}
	DWORD_PTR LOL;
	if (def::Aimbot)
	{
		if (isVisible(CurrentActorMesh))
		{
			if (keybind == 0)
			{
				if (closestPawn != 0)
				{
					if (closestPawn && GetAsyncKeyState(hotkeys::aimkey))
					{
						if (def::Aimbot)
						{
							Vector3 hitbone = ProjectWorldToScreen(GetBoneWithRotation(def::hitbox, LOL));

							if (hitbone.x != 0 || hitbone.y != 0 || hitbone.z != 0)
							{
								if (def::Aimbot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0) {
									AimAt(closestPawn);
								}
							}
						}
					}
				}

				else
				{
					closestDistance = FLT_MAX;
					closestPawn = NULL;
				}
			}
		}
	}


	DWORD_PTR NIGGER;
if (def::Mousebot)
{
	if (isVisible(CurrentActorMesh))
	{
		if (keybind == 0)
		{
			if (closestPawn != 0)
			{
				if (closestPawn && GetAsyncKeyState(hotkeys::aimkey))
				{
					if (def::Mousebot)
					{
						Vector3 hitbone = ProjectWorldToScreen(GetBoneWithRotation(def::hitbox, NIGGER));

						if (hitbone.x != 0 || hitbone.y != 0 || hitbone.z != 0)
						{
							if (def::Mousebot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0) {
								NotAimAt(closestPawn);
							}
						}
					}
				}
			}

			else
			{
				closestDistance = FLT_MAX;
				closestPawn = NULL;
			}
		}
	}
}
}



void render() {
	switch (keybind)
	{
	case 0:
		def::aimkeypos = 1;
		break;
	case 1:
		def::aimkeypos = 0;
		break;
	case 2:
		def::aimkeypos = 2;
		break;
	}
	if (RenderOption == 0)
	{
		fovcirclefilled = false;
		square_fov = false;
		fovcircle = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 1)
	{
		fovcircle = false;
		fovcirclefilled = false;
		square_fov = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 2)
	{
		square_fov = false;
		fovcircle = false;
		fovcirclefilled = true;
		SquareFovFilled = false;
	}
	if (RenderOption == 3)
	{
		square_fov = false;
		fovcircle = false;
		fovcirclefilled = false;
		SquareFovFilled = true;
	}
	for (int index = 0; index < Memory.Read<int>(Actors::PersistentLevel + (0x98 + sizeof(uintptr_t))); index++)
	{
		GayLoop::CurrentActorID = Memory.Read<int>(GayLoop::CurrentActor + 0x18);
		GayLoop::PersistentLevelActors = Memory.Read<uintptr_t>(Actors::PersistentLevel + 0x98);
		GayLoop::CurrentActor = Memory.Read<uintptr_t>(GayLoop::PersistentLevelActors + (index * sizeof(uintptr_t)));
		if (BulletTP)
		{
			{
				if (isVisible)
				{
					if (!isVisible(closestPawn))
					{
						continue;
					}
				}
				std::string AllAct = GetNameFromFName(GayLoop::CurrentActorID);
				if (AllAct == "B_Prj_Bullet_DMR_C") {
					std::cout << "B_Prj_Bullet_DMR_C Shot Registered \n";
				}


				if (AllAct == "B_Prj_Bullet_Sniper_C" or AllAct == "B_Prj_Bullet_DMR_C" or AllAct == "B_Prj_Bullet_Sniper_Heavy_C" or AllAct == "B_Prj_Bullet_Cosmos_AR_C" or AllAct == "B_Shotgun_Standard_Athena_C" or AllAct == "Tracer_Shotgun_C")
				{

					uint64_t CurrentActorMesh = Memory.Read<uint64_t>(closestPawn + 0x310);
					Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 68);


					DWORD_PTR BulletRootComp = Memory.Read<DWORD_PTR>(Ass::CurrentActor + 0x190);
					Memory.Write<char>(BulletRootComp + 0x190, 0);
					Memory.Write<Vector3>(BulletRootComp + 0x128, Vector3{ Headpos.x, Headpos.y, Headpos.z });
				}


			}

		}
	}
	ImGui::StyleColorsDark();
	ImGuiStyle* style = &ImGui::GetStyle();


	ImVec4* colors = style->Colors;

	ImVec4* colorz = ImGui::GetStyle().Colors;

	ImGuiStyle* stylez = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(8.00f, 8.00f);
	style->FramePadding = ImVec2(5.00f, 2.00f);
	style->CellPadding = ImVec2(6.00f, 6.00f);
	style->ItemSpacing = ImVec2(6.00f, 6.00f);
	style->ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style->TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style->IndentSpacing = 25;
	style->ScrollbarSize = 15;
	style->GrabMinSize = 10;
	style->WindowBorderSize = 1;
	style->ChildBorderSize = 1;
	style->PopupBorderSize = 1;
	style->FrameBorderSize = 1;
	style->TabBorderSize = 1;
	style->WindowRounding = 7;
	style->ChildRounding = 4;
	style->FrameRounding = 33;
	style->PopupRounding = 4;
	style->ScrollbarRounding = 9;
	style->GrabRounding = 3;
	style->LogSliderDeadzone = 4;
	style->TabRounding = 4;

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	DrawESP();
	if (GetAsyncKeyState(hotkeys::backkey) & 1) {  // 0x2D = Insert
		ShowMenu = !ShowMenu;
	}
	if (ShowMenu)
	{
		ImGui::SetNextWindowSize(ImVec2(385.000f, 236.000f), ImGuiCond_Once);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 24.f);

		ImGui::Begin("NOF Free", NULL, 34);
		ImDrawList* pDrawList;
		const auto& CurrentWindowPos = ImGui::GetWindowPos();
		const auto& pWindowDrawList = ImGui::GetWindowDrawList();
		const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
		const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

		switch (tab)
		{
		case 0:

			ImGui::SetCursorPos(ImVec2(10.000f, 20.000f));
			ImGui::Checkbox("Memory Aimbot [Rage]", &def::Aimbot);

			ImGui::SetCursorPos(ImVec2(183.000f, 20.000f));
			HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
			ImGui::SetCursorPos(ImVec2(313.000f, 24.000f));
			ImGui::Text("Aim Key");


			ImGui::SetCursorPos(ImVec2(10.000f, 200.000f));

			ImGui::SetCursorPos(ImVec2(10.000f, 40.000f));
			ImGui::Checkbox("Mouse Aimbot [Legit]", &def::Mousebot);

			ImGui::SetCursorPos(ImVec2(183.000f, 40.000f));
			ImGui::SetNextItemWidth(70.000f);
			ImGui::Combo(skCrypt("Aim Bone"), &def::hitboxpos, hitboxes, sizeof(hitboxes) / sizeof(*hitboxes));

			ImGui::SetCursorPos(ImVec2(10.000f, 60.000f));
			ImGui::Checkbox(skCrypt("FOV Circle"), &circletype);
			ImGui::SetNextItemWidth(150.000f);
			ImGui::SameLine();

			ImGui::Combo(skCrypt(""), &RenderOption, skCrypt("Circle\0Square\0"));
			ImGui::SetNextItemWidth(250.000f);

			ImGui::SetCursorPos(ImVec2(10.000f, 80.000f));
			ImGui::SliderInt(skCrypt("View Distance"), &def::VisDist, 50, 300);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(10.000f, 100.000f));
			ImGui::SliderFloat(skCrypt("FOV Size"), &def::AimbotFov, 50, 800);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(10.000f, 120.000f));
			ImGui::SliderFloat(skCrypt("Memory Smoothing"), &Smoothness, 1.000f, 140.000f);

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(10.000f, 140.000f));
			ImGui::SliderFloat(skCrypt("Mouse Smoothing"), &gaysmooth, 2.000f, 50.000f);


			if (ImGui::Button(skCrypt("Next Page ->"))) {
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
				if (tab == 0) {
					tab = 1;
				}

			}
			if (ImGui::Button(skCrypt("<- Previous Page"))) {
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);

			}

			ImGui::Text("Page 1/4: Aimbot");

			ImGui::SetCursorPos(ImVec2(243.000f, 170.000f));
			ImGui::SetNextItemWidth(250.000f);
			NiggerButton(hotkeys::backkey, ChangeKeyyyyy, keystatusssss);
			ImGui::SetCursorPos(ImVec2(277.000f, 190.000f));
			ImGui::Text("Menu Key");
			break;
		case 1:

			ImGui::SetNextItemWidth(250.000f);
			ImGui::SetCursorPos(ImVec2(10.000f, 20.000f));
			ImGui::Checkbox(skCrypt("Stream Proof"), &WindowStreamProof);

			ImGui::SetCursorPos(ImVec2(10.000f, 40.000f));
			ImGui::Checkbox(skCrypt("Box Esp"), &BoxEsp);

			ImGui::SetCursorPos(ImVec2(10.000f, 60.000f));
			ImGui::Checkbox(skCrypt("Distance"), &PlayerDistanceEsp);

			ImGui::SetCursorPos(ImVec2(10.000f, 80.000f));
			ImGui::Checkbox(skCrypt("Snaplines"), &Snaplines);

			ImGui::SetCursorPos(ImVec2(10.000f, 100.000f));
			ImGui::Checkbox(skCrypt("Instant Reload"), &InstaReload);

			ImGui::SetCursorPos(ImVec2(10.000f, 120.000f));
			ImGui::Checkbox(skCrypt("Self Esp"), &BulletTP);

			ImGui::SetCursorPos(ImVec2(10.000f, 140.000f));
			ImGui::Checkbox(skCrypt("Skeleton Esp"), &Skeleton);

			if (ImGui::Button(skCrypt("Next Page ->"))) {
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
				if (tab == 1) {
					tab = 2;
				}

			}
			if (ImGui::Button(skCrypt("<- Previous Page"))) {
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
				if (tab == 1) {
					tab = 0;
				}

			
			}
			ImGui::Text("Page 2/4: ESP/Visuals");
			break;
		case 2:
				ImGui::SetCursorPos(ImVec2(10.000f, 20.000f));
				ImGui::Checkbox(skCrypt("Aim While Jumping"), &AimWhileJumping);

				ImGui::SetCursorPos(ImVec2(10.000f, 40.000f));
				ImGui::Checkbox(skCrypt("Airstuck [CAPS]"), &AirStuck);

				ImGui::SetCursorPos(ImVec2(10.000f, 60.000f));
				ImGui::Checkbox(skCrypt("Car Fly"), &carFly);

				ImGui::SetCursorPos(ImVec2(10.000f, 80.000f));
				ImGui::Checkbox(skCrypt("Instant Revive"), &InstaRes);

				ImGui::SetCursorPos(ImVec2(10.000f, 100.000f));
				ImGui::Checkbox(skCrypt("Player Fly"), &PlayerFly);

				ImGui::SetCursorPos(ImVec2(10.000f, 120.000f));
				ImGui::Checkbox(skCrypt("Double Pump"), &doublepump);

				ImGui::SetCursorPos(ImVec2(10.000f, 140.000f));
				ImGui::Checkbox(skCrypt("No Bloom"), &NoBloom);

				if (ImGui::Button(skCrypt("Next Page ->"))) {
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
					if (tab == 2) {
						tab = 3;
					}

				}
				if (ImGui::Button(skCrypt("<- Previous Page"))) {
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
					if (tab == 2) {
						tab = 1;
					}

				
				}
				ImGui::Text("Page 3/4: Exploits");
				break;
		case 3:
				ImGui::SetCursorPos(ImVec2(10.000f, 20.000f));
				ImGui::Checkbox(skCrypt("Invisibility [CLIENTSIDE]"), &ClientInvisibility);

				ImGui::SetCursorPos(ImVec2(10.000f, 40.000f));
				ImGui::Checkbox(skCrypt("Infinite Fuel"), &InfiniteFuel);

				ImGui::SetCursorPos(ImVec2(10.000f, 60.000f));
				ImGui::Checkbox(skCrypt("SpinBot"), &Spinbot);

				ImGui::SetCursorPos(ImVec2(10.000f, 80.000f));
				ImGui::Checkbox(skCrypt("Pickaxe Kill [10M]"), &BigPlayers);

				ImGui::SetCursorPos(ImVec2(10.000f, 100.000f));
				ImGui::Checkbox(skCrypt("Small Player [CLIENTSIDE]"), &SmallPlayer);

				ImGui::SetCursorPos(ImVec2(10.000f, 120.000f));
				ImGui::Checkbox(skCrypt("TriggerBot"), &Triggerbot);

				ImGui::SetCursorPos(ImVec2(113.000f, 118.000f));
				HotkeyButtonnn(hotkeys::triggerkey, ChangeTrigger, triggerstatus);

				ImGui::SetCursorPos(ImVec2(10.000f, 140.000f));
				ImGui::SliderFloat(skCrypt("FOV Changer"), &ChangerFOV, 0.f, 180.f);

				if (ImGui::Button(skCrypt("Next Page ->"))) {
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
					if (tab == 3) {
					}

				}
				if (ImGui::Button(skCrypt("<- Previous Page"))) {
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 150.f);
					if (tab == 3) {
						tab = 2;
					}

				

				}
				ImGui::Text("Page 4/4: Exploits");
			break;

		}

	}


	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

D3DPRESENT_PARAMETERS p_Params = { NULL };
HRESULT DirectXInit(HWND hWnd)
{
	//hide_thread(LI_FN(GetCurrentThread).get()());
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		LI_FN(exit).get()(3);

	RtlSecureZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;




	p_Object->Release();
	return S_OK;
}
HWND hijacked_hwnd{};


void xMainLoop()
{
	MSG Message;
	RtlZeroMemory(&Message, sizeof(Message));
	DirectXInit(hijacked_hwnd);
	while ((Message.message != WM_QUIT) /* && (dt_info->tm_mday == DAY) */)
	{
		if (PeekMessageA(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessageA(&Message);
			continue;
		}
		HWND hwnd_active = GetForegroundWindow();
		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;
		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	DestroyWindow(Window);
}

