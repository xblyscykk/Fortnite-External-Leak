#pragma once
#include <Windows.h>

#define GWorld 0xF1BEEE8 // gworld is a pointer of uworld.
#define UCAPSULECOMPONENT 0x320
#define RELATIVESCALE3D 0x158
#define CURRENTVEHICLE 0x24C8
#define BUSEGRAVITY 0x6DA 
#define CUSTOMTIMEDILATION 0x64
#define BISRELOADINGWEAPON 0x348
#define MESH 0x310
#define GLOBALANIMRATESCALE 0xA80
#define BIGNORETRYTOFIRE 0x10B1
#define CACHEDFUELCOMPONENT 0x10F0
#define CURRENTWEAPON 0x908
#define DEFAULTFOV 0x29c
#define RELATIVELOCATION 0x128
#define RELATIVEROTATION 0x140
#define ROOTCOMPONENT 0x190
#define PLAYERCAMERAMANAGER 0x340
#define ZIPLINESPEEDFACTOR 0x22DC
#define ZIPLINESTATE 0x21E0
namespace Offsets
{
    enum External : uint64_t
    {
        // TeamIndex - TeamID - ActorID
        TeamId = 0x10B8,
        //
        // Local
        LocalActorPos = 0x128,
        LocalPawn = 0x330,
        LocalPlayers = 0x38,

        // Player - BoneArray
        BoneArray = 0x600,
        PlayerState = 0x2A8,
        PlayerArray = 0x2a0,
        PlayerController = 0x30,
        PlayerCameraManager = 0x340,

        // Game - World
        Gameinstance = 0x1B8,
        GameState = 0x158,
        ComponetToWorld = 0x240,

        // Actor
        ActorCount = 0xA0,
        AActor = 0x98,
        CurrentActor = 0x300,

        // Other
        RootComponet = 0x190,
        PersistentLevel = 0x30,
        Mesh = 0x310,
        Velocity = 0xb8,
        PawnPrivate = 0x300,

        // Visible Check
        fLastSubmitTime = 0x360,
        fLastRenderTimeOnScreen = 0x368,
    };
}
