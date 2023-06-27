#include <Windows.h>
#include <iostream>
namespace def
{
	// Aimbot Definition's
	bool Aimbot = false;
	bool Mousebot = false;
	static int aimkey;
	static int hitbox;
	float AimbotFov = 150;
	static int VisDist = 2500;
	static int aimkeypos = 1;
	static int hitboxpos = 0;
}

// Fov - Crosshair - AimKey
bool fovcircle = false;
bool square_fov = false;
bool crosshair = false;
bool fovcirclefilled = false;
bool circletype = false;
int keybind = 0;
bool SquareFovFilled = false; 
int CrosshairSize = 10;


// Esp
bool SelfEsp = false;
bool Esp = true;
bool CornerBoxEsp = false;
bool TriangleEsp = false;
bool ThreeDBoxEsp = false;
bool BoxEsp = true;
bool Triggerbot = false;
bool FovChanger = true;
bool playertp = false;
bool KillAll = false;
bool PlayerDistanceEsp = false;
bool InLobby = false;
bool Snaplines = true;
bool drawbase = true;
bool slefESP = false;
bool fillbox = false;
bool thick = false;
float BoxWidthValue = 0.550;
int LineThinkness = 1;
int Boxthinkness = 0.5;
float ChangerFOV = 90;
bool Skeleton = false;

// Other
int RenderOption = 0;
int tab;
bool WindowStreamProof = false;
bool reloadcheck = false;
bool targetingcheck = false;
bool norecoil = false;
bool DynamicEsp = false;


bool AimWhileJumping = false;
bool SilentAim = false;
bool StickySilent = false;
bool AirStuck = false;
bool NoBloom = false;
bool NoColision = false;
bool SpeedHack = false;
bool instantall = false;
bool FakeLag = false;
bool InstaReload = false;
bool LightMode = false;
bool DarkMode = false;
bool TPose = false;
bool ClientInvisibility = false;
bool doublepump = false;
bool PlayerFly = false;
bool InfiniteFuel = false;
bool RapidFire = false;
bool Spinbot = false;
bool BulletTP = false;
bool InstaRes = false;
bool MagicBullet = false;
bool BigPlayers = false;
bool BigPlayerss = false;
bool NormalPlayers = false;
bool SmallPlayer = false;
bool carFly = false;
bool NoWeaponAnimation = false;

// radar
bool radar = false;
bool rect_radar = false;
float radar_position_x{ 84.494f };
float radar_position_y{ 77.841f };
float radar_size{ 150.f };
float RadarDistance = { 700.f };

// Menu
bool ShowMenu = true;
