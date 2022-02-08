#ifndef aimassist_mp_h
#define aimassist_mp_h
//#define  CG_ReadNextSnapshot(localClientNum) Invoke<snapshot_s*>(0xC564C, 0)
#define penetrationDepthTable ((float*)0x296EB30)
//bool AimTarget_GetTarget(int localClientNum, unsigned int * ptarget);
#pragma region aim functions
extern void enable_hvh();
extern WeaponDef* BG_GetWeaponDef(int Weapon);
extern WeaponVariantDef* BG_GetWeaponVariantDef(unsigned int weapon);
extern void aim_type(int type);
extern void tag_type(int type);
extern void key_type(int type);
extern void camo_type(int type);
extern void player_type(int type);
extern void anti_typeFX(int type);
extern void anti_typeSX(int type);
extern void anti_typeCX(int type);
extern void anti_typeMX(int type);
extern void anti_typeSTX(int type);
extern void anti_typeFY(int type);
extern void anti_typeSY(int type);
extern void anti_typeCY(int type);
extern void anti_typeMY(int type);
extern void anti_typeSTY(int type);
extern void ShouldSimulateCheck();
extern void ResetConfig();
extern bool BulletTrace(int localClientNum, BulletFireParams* bulletFireParams, WeaponDef* weaponIndex, centity_s* centityAttacker, BulletTraceResults* btr, int surfacetype, bool simulate);
extern bool CG_GetPlayerViewOrigin(Vector3* Origin);
//extern void WritePacketH(usercmd_s* pUserCmd);
extern String Com_SurfaceTypeOofName(int index);
//extern void PredictPlayerStateH(usercmd_s* pOldCmd, usercmd_s* pCurrentCmd, usercmd_s* pNewCmd);
extern void Writepacket();
extern void SendCMD();
extern void PredictPlayerState();
extern void aimbot();
extern void pspin(usercmd_s* NewCmd);
extern bool isButtonDown(int button);
char __cdecl HasPerk(int weapon, unsigned int perkIndex);
extern void noshit();
class ClientAutoBone {
public:
	int stat[12];
	short BoneBest = -1;
	short BoneBestAuto = -1;
	short BoneBestVis = -1;
	int Iter = 0;
	void sort() {
		BoneBest = BoneBestAuto = BoneBestVis = -1;
		Iter--;
		if (Iter < 0 || Iter > bot.loop_multipoint) {
			Iter = bot.loop_multipoint;
		}
		for (int a = bot.loop_multipoint; a >= 0; a--) {
			if (stat[a] == 2 & BoneBestVis == -1) BoneBestVis = a;
			if (stat[a] == 1 & BoneBestAuto == -1) BoneBestAuto = a;
		}
		BoneBest = BoneBestVis != -1 ? BoneBestVis : BoneBestAuto;
	}
};
extern short HandleTag(int i);
extern ClientAutoBone ClientArray[18];
extern void setanglesMP();
extern int Trace_GetEntityHitId_t[2];
//extern void setanglesZM();

enum CriticalSection {
	CRITSECT_ALLOC_MARK = 0x0,
	CRITSECT_FX_VIS = 0x1,
	CRITSECT_OCCLUSION_QUERY = 0x2,
	CRITSECT_PHYSICS = 0x3,
	CRITSECT_PHYSICS_UPDATE = 0x4,
	CRITSECT_PHYSICS_DESTRUCTIBLE_HIT = 0x5,
	CRITSECT_FX_UNIQUE_HANDLE = 0x6,
	CRITSECT_SOUND_COMMAND_ALLOC = 0x7,
	CRITSECT_SOUND_COMMAND_PUSH = 0x8,
	CRITSECT_SOUND_NOTIFY_ALLOC = 0x9,
	CRITSECT_SOUND_NOTIFY_PUSH = 0xA,
	CRITSECT_SOUND_BANK = 0xB,
	CRITSECT_SOUND_LOOKUP_CACHE = 0xC,
	CRITSECT_CAREER_STATS = 0xD,
	CRITSECT_CONSOLE = 0xE,
	CRITSECT_DEBUG_SOCKET = 0xF,
	CRITSECT_COM_ERROR = 0x10,
	CRITSECT_STATMON = 0x11,
	CRITSECT_MEM_ALLOC0 = 0x12,
	CRITSECT_MEM_ALLOC1 = 0x13,
	CRITSECT_DEBUG_LINE = 0x14,
	CRITSECT_DEBUG_BRUSHES_AND_PATCHES = 0x15,
	CRITSECT_CLIENT_MESSAGE = 0x16,
	CRITSECT_CLIENT_CMD = 0x17,
	CRITSECT_DOBJ_ALLOC = 0x18,
	CRITSECT_XANIM_ALLOC = 0x19,
	CRITSECT_KEY_BINDINGS = 0x1A,
	CRITSECT_SERVER_MESSAGE = 0x1B,
	CRITSECT_SERVER_PLAYERINFO = 0x1C,
	CRITSECT_SCRIPT_STRING = 0x1D,
	CRITSECT_MEMORY_TREE = 0x1E,
	CRITSECT_ASSERT = 0x1F,
	CRITSECT_RD_BUFFER = 0x20,
	CRITSECT_SYS_EVENT_QUEUE = 0x21,
	CRITSECT_FATAL_ERROR = 0x22,
	CRITSECT_DXDEVICE = 0x23,
	CRITSECT_DXDEVICE_GLOB = 0x24,
	CRITSECT_DXCONTEXT = 0x25,
	CRITSECT_SCRIPT_DEBUGGER_ALLOC = 0x26,
	CRITSECT_SCRIPT_DEBUGGER = 0x27,
	CRITSECT_REMOTE = 0x28,
	CRITSECT_MISSING_ASSET = 0x29,
	CRITSECT_LIVE = 0x2A,
	CRITSECT_AUDIO_PHYSICS = 0x2B,
	CRITSECT_LUI = 0x2C,
	CRITSECT_VCS = 0x2D,
	CRITSECT_CINEMATIC = 0x2E,
	CRITSECT_CINEMATIC_TARGET_CHANGE = 0x2F,
	CRITSECT_CINEMATIC_UPDATEFRAME = 0x30,
	CRITSECT_RB_TRANSFER = 0x31,
	CRITSECT_NETTHREAD_OVERRIDE = 0x32,
	CRITSECT_DEMONWARE = 0x33,
	CRITSECT_IK = 0x34,
	CRITSECT_TL_MEMALLOC = 0x35,
	CRITSECT_VA_ALLOC = 0x36,
	CRITSECT_MEMTRACK = 0x37,
	CRITSECT_CBUF = 0x38,
	CRITSECT_CURVEALLOC = 0x39,
	CRITSECT_NETQUEUE = 0x3A,
	CRITSECT_ZLIB = 0x3B,
	CRITSECT_BLACKBOX = 0x3C,
	CRITSECT_GDT_COMMAND = 0x3D,
	CRITSECT_STRINGED_COMMAND = 0x3E,
	CRITSECT_RADIANT_SERVER_COMMAND = 0x3F,
	CRITSECT_RADIANT_CLIENT_COMMAND = 0x40,
	CRITSECT_RECORDER = 0x41,
	CRITSECT_SERVERDEMO = 0x42,
	CRITSECT_IO_SCHEDULER = 0x43,
	CRITSECT_FILE_ID_ARRAY = 0x44,
	CRITSECT_MEMFIRSTFIT = 0x45,
	CRITSECT_FXBEAM = 0x46,
	CRITSECT_GLASS_ACTIONS = 0x47,
	CRITSECT_DBHASH = 0x48,
	CRITSECT_DEVHOST = 0x49,
	CRITSECT_CLUMP = 0x4A,
	CRITSECT_SNAPSHOT_PROFILE = 0x4B,
	CRITSEC_WEBM_STREAM_ACCESS = 0x4C,
	CRITSEC_SV_LEADERBOARDS = 0x4D,
	CRITSECT_COUNT = 0x4E,
};

extern void Sys_EnterCriticalSection(CriticalSection critSect);
extern void Sys_LeaveCriticalSection(CriticalSection critSect);

#endif