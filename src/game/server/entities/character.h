/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_CHARACTER_H
#define GAME_SERVER_ENTITIES_CHARACTER_H

#include <generated/protocol.h>

#include <game/gamecore.h>
#include <game/server/entity.h>

class CGameTeams;

class CCharacter : public CEntity
{
	MACRO_ALLOC_POOL_ID()

public:
	//character's size
	static const int ms_PhysSize = 28;

	CCharacter(CGameWorld *pWorld);

	virtual void Reset();
	virtual void Destroy();
	virtual void Tick();
	virtual void Tick2();
	virtual void TickDefered();
	virtual void TickPaused();
	virtual void Snap(int SnappingClient);
	virtual void PostSnap();

	virtual int NetworkClipped(int SnappingClient);
	virtual int NetworkClipped(int SnappingClient, vec2 CheckPos);

	bool IsGrounded();

	void SetWeapon(int W);
	void SetSolo(bool Solo);
	bool IsSolo() { return m_Solo; }
	void HandleWeaponSwitch();
	void DoWeaponSwitch();

	void HandleWeapons();
	void HandleNinja();
	void HandleJetpack();

	void OnPredictedInput(CNetObj_PlayerInput *pNewInput);
	void OnDirectInput(CNetObj_PlayerInput *pNewInput);
	void ResetInput();
	void FireWeapon();

	void Die(int Killer, int Weapon);
	bool TakeDamage(vec2 Force, vec2 Source, int Dmg, int From, int Weapon);

	bool Spawn(class CPlayer *pPlayer, vec2 Pos);
	bool Remove();

	bool IncreaseHealth(int Amount);
	bool IncreaseArmor(int Amount);

	void GiveWeapon(int Weapon, bool Remove = false);
	void GiveNinja();
	void RemoveNinja();

	void SetEmote(int Emote, int Tick);

	void Rescue();

	bool IsAlive() const { return m_Alive; }
	bool IsPaused() const { return m_Paused; }
	class CPlayer *GetPlayer() { return m_pPlayer; }

private:
	// player controlling this character
	class CPlayer *m_pPlayer;

	bool m_Alive;
	bool m_Paused;

	// weapon info
	CEntity *m_apHitObjects[10];
	int m_NumObjectsHit;

	struct WeaponStat
	{
		int m_AmmoRegenStart;
		int m_Ammo;
		bool m_Got;

	} m_aWeapons[NUM_WEAPONS];

	int m_ActiveWeapon;
	int m_LastWeapon;
	int m_QueuedWeapon;

	int m_ReloadTimer;
	int m_AttackTick;

	int m_EmoteType;
	int m_EmoteStop;

	// last tick that the player took any action ie some input
	int m_LastAction;
	int m_LastNoAmmoSound;

	// these are non-heldback inputs
	CNetObj_PlayerInput m_LatestPrevInput;
	CNetObj_PlayerInput m_LatestInput;

	// input
	CNetObj_PlayerInput m_SavedInput;
	CNetObj_PlayerInput m_Input;
	int m_NumInputs;
	int m_Jumped;

	int m_Health;
	int m_Armor;

	int m_TriggeredEvents;

	// ninja
	struct
	{
		vec2 m_ActivationDir;
		int m_ActivationTick;
		int m_CurrentMoveTime;
		int m_OldVelAmount;
	} m_Ninja;

	// the player core for the physics
	CCharacterCore m_Core;

	// info for dead reckoning
	int m_ReckoningTick; // tick that we are performing dead reckoning From
	CCharacterCore m_SendCore; // core that we should send
	CCharacterCore m_ReckoningCore; // the dead reckoning core

	// DDrace

	void HandleTiles(int Index);
	float m_Time;
	int m_LastBroadcast;
	void DDraceInit();
	void HandleSkippableTiles(int Index);
	void DDraceTick();
	void DDracePostCoreTick();
	void HandleBroadcast();
	void HandleTuneLayer();
	void SendZoneMsgs();

	bool m_SetSavePos;
	vec2 m_PrevSavePos;
	bool m_Solo;

public:
	CGameTeams* Teams();
	void Pause(bool Pause);
	bool Freeze(int Time);
	bool Freeze();
	bool UnFreeze();
	void GiveAllWeapons();
	int m_DDRaceState;
	int Team();
	bool CanCollide(int ClientID);
	bool SameTeam(int ClientID);
	bool m_Super;
	bool m_SuperJump;
	bool m_Jetpack;
	bool m_NinjaJetpack;
	int m_TeamBeforeSuper;
	int m_FreezeTime;
	int m_FreezeTick;
	bool m_DeepFreeze;
	bool m_EndlessHook;
	bool m_FreezeHammer;
	enum
	{
		HIT_ALL = 0,
		DISABLE_HIT_HAMMER = 1,
		DISABLE_HIT_SHOTGUN = 2,
		DISABLE_HIT_GRENADE = 4,
		DISABLE_HIT_RIFLE = 8
	};
	int m_Hit;
	int m_TuneZone;
	int m_TuneZoneOld;
	int m_PainSoundTimer;
	int m_LastMove;
	int m_StartTime;
	vec2 m_PrevPos;
	int m_TeleCheckpoint;
	int m_CpTick;
	int m_CpActive;
	int m_CpLastBroadcast;
	float m_CpCurrent[25];
	int m_TileIndex;
	int m_TileFlags;
	int m_TileFIndex;
	int m_TileFFlags;
	int m_TileSIndex;
	int m_TileSFlags;
	int m_TileIndexL;
	int m_TileFlagsL;
	int m_TileFIndexL;
	int m_TileFFlagsL;
	int m_TileSIndexL;
	int m_TileSFlagsL;
	int m_TileIndexR;
	int m_TileFlagsR;
	int m_TileFIndexR;
	int m_TileFFlagsR;
	int m_TileSIndexR;
	int m_TileSFlagsR;
	int m_TileIndexT;
	int m_TileFlagsT;
	int m_TileFIndexT;
	int m_TileFFlagsT;
	int m_TileSIndexT;
	int m_TileSFlagsT;
	int m_TileIndexB;
	int m_TileFlagsB;
	int m_TileFIndexB;
	int m_TileFFlagsB;
	int m_TileSIndexB;
	int m_TileSFlagsB;
	vec2 m_Intersection;
	int64 m_LastStartWarning;
	int64 m_LastRescue;
	bool m_LastRefillJumps;
	bool m_LastPenalty;
	bool m_LastBonus;
	bool m_HasTeleGun;
	bool m_HasTeleGrenade;
	bool m_HasTeleLaser;
	vec2 m_TeleGunPos;
	bool m_TeleGunTeleport;
	bool m_IsBlueTeleGunTeleport;
	int m_StrongWeakID;

	// Setters/Getters because i don't want to modify vanilla vars access modifiers
	int GetLastWeapon() { return m_LastWeapon; };
	void SetLastWeapon(int LastWeap) { m_LastWeapon = LastWeap; };
	int GetActiveWeapon() { return m_ActiveWeapon; };
	void SetActiveWeapon(int ActiveWeap) { m_ActiveWeapon = ActiveWeap; };
	void SetLastAction(int LastAction) { m_LastAction = LastAction; };
	int GetArmor() { return m_Armor; };
	void SetArmor(int Armor) { m_Armor = Armor; };
	CCharacterCore GetCore() { return m_Core; };
	void SetCore(CCharacterCore Core) { m_Core = Core; };
	CCharacterCore* Core() { return &m_Core; };
	int GetQueuedWeapon() { return m_QueuedWeapon; };
	void SetQueuedWeapon(int Weapon) { m_QueuedWeapon = Weapon; };
	bool GetWeaponGot(int Type) { return m_aWeapons[Type].m_Got; };
	void SetWeaponGot(int Type, bool Value) { m_aWeapons[Type].m_Got = Value; };
	int GetWeaponAmmoRegenStart(int Type) { return m_aWeapons[Type].m_AmmoRegenStart; };
	void SetWeaponAmmoRegenStart(int Type, int Value) { m_aWeapons[Type].m_AmmoRegenStart = Value; };
	int GetWeaponAmmo(int Type) { return m_aWeapons[Type].m_Ammo; };
	void SetWeaponAmmo(int Type, int Value) { m_aWeapons[Type].m_Ammo = Value; };
	void SetEmoteType(int EmoteType) { m_EmoteType = EmoteType; };
	void SetEmoteStop(int EmoteStop) { m_EmoteStop = EmoteStop; };
	void SetNinjaActivationDir(vec2 ActivationDir) { m_Ninja.m_ActivationDir = ActivationDir; };
	void SetNinjaActivationTick(int ActivationTick) { m_Ninja.m_ActivationTick = ActivationTick; };
	void SetNinjaCurrentMoveTime(int CurrentMoveTime) { m_Ninja.m_CurrentMoveTime = CurrentMoveTime; };
	void SetAlive(bool Alive) { m_Alive = Alive; }

	void SetPos(vec2 Pos) { m_Pos = Pos; };
	void SetPrevPos(vec2 PrevPos) { m_PrevPos = PrevPos; };

	void SetCoreHook(int Hook) { m_Core.m_Hook = Hook; }
	void SetCoreCollision(int Collision) { m_Core.m_Collision = Collision; }
	void SetCoreJumped(int Jumped) { m_Core.m_Jumped = Jumped; }
	void SetCoreJumpedTotal(int JumpedTotal) { m_Core.m_JumpedTotal = JumpedTotal; }
	void SetCoreJumps(int Jumps) { m_Core.m_Jumps = Jumps; }
	void SetCoreHookTick(int HookTick) { m_Core.m_HookTick = HookTick; }
	void SetCoreHookedPlayer(int HookedPlayer) { m_Core.m_HookedPlayer = HookedPlayer; }
	void SetCoreHookState(int HookState) { m_Core.m_HookState = HookState; }
	void SetCoreHookPos(vec2 HookPos) { m_Core.m_HookPos = HookPos; }
	void SetCoreHookDir(vec2 HookDir) { m_Core.m_HookDir = HookDir; }
	void SetCoreHookTeleBase(vec2 HookTeleBase) { m_Core.m_HookTeleBase = HookTeleBase; }

	void SetCorePos(vec2 Pos) { m_Core.m_Pos = Pos; };
	void SetCoreVel(vec2 Vel) { m_Core.m_Vel = Vel; };
	void ResetNumInputs() { m_NumInputs = 0; };
};

enum
{
	DDRACE_NONE = 0,
	DDRACE_STARTED,
	DDRACE_CHEAT, // no time and won't start again unless ordered by a mod or death
	DDRACE_FINISHED
};

#endif
