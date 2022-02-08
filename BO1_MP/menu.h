#ifndef menu_h
#define menu_h

#define max 40
void Wait(float timeout);
enum ids : int {
	ID_MAIN,
	ID_AIMBOT,
	ID_ESP,
	ID_CHEATS,
	ID_EXPLOITS,
	ID_ENTITY,
	ID_PLAYERSLIST,
	ID_RECENTLIST,
	ID_PLAYERS,
	ID_PLAYERSV1,
	ID_ACCOUNT,
	ID_SETTINGS,
	ID_PLAYERS_SUB,
	ID_PLAYERS_SUBV1,
	ID_RECENTS_SUB,
	ID_ANTIAIM,
	ID_RADAR,
	ID_RADARENTS,
	ID_CROSSHAIR,
	ID_WORLDENTS,
	ID_THEME,
	ID_TRACERS,
	ID_F,
	ID_E,
	ID_H,
	ID_V,
	ID_T,
	ID_HB,
	ID_XH,
	ID_FC,
	ID_CH,
	ID_CRGB,
	ID_PRIMERY,
	ID_SECONDARY,
	ID_CUSTOMTHEME,
	ID_ESPTHEME,
	ID_PLACEMENT,
	ID_GAMERTAG,
	ID_CAMO,
	ID_CAMOS,
	ID_CAMO1,
	ID_DEBUG,
	ID_CHAMS,
	ID_HVH,
	ID_CONFIG,
	ID_DEV,
	SERVER_INFO,
	ID_WEAPONIZED,
	ID_CHAM,
	ID_ASSET,
	ID_HOST,
	ID_SKY,
	ID_PLAYER,
	ID_XHC,
	ID_CG
};
typedef void(*combo_func)(int data);

struct combodata_s {
	bool opened;
	int tick, wait, scroll, maxscroll, size;
	float height;
	const char** data;
	combo_func func;
};

static color dflash = color(255, 0, 0, 255), dflash1 = color(255, 0, 0, 255);
struct menushit {
	bool Mopened, active_option;

	int colori, max_options, id, tick, scroll[max], prev[max], maxscroll[max], menu_offsets[max], maxscrollT[max], islide[max][max], barslide[max][max];
	char* ch;
	float wait;
};


typedef struct asset {
	unsigned char Weaponized_asset[0x155E0], gp[2048];//unsigned char Weaponized_asset[0x155E0], gp[2048];
};

extern Detour CL_DispatchConnectionlessPacket_d;
extern char CL_DispatchConnectionlessPacket(int localClientNum, netadr_t from, msg_t* msg, int time);

extern Detour Party_ReadMember_d;
extern bool Party_ReadMember(PartyMember* partyMember, msg_t* msg, bool check);
extern void(*Live_SendJoinRequest)(SceNpId* r3, int r4);
extern SceNpId DefaultNpInfo;
struct menudata_s {
public:
	char DefName[16];
	int Offset;
	Vector2 OptPos;

	bool entityaimbot, cham, rgba, i32_Name, camocolor, Grab, bInGame, bdisconnect, hostaw, hostawor;
	bool engnsounds, renderonme, renderonplayers, renderchamsonme, sping, bo2theme, ip_spoofing, btrickmode, bgunsound, disabledlc, benablecamos, flshname, addname, addname1, combo_active, smokec, nightmode, dankmap, skyc, skyr, fade, lockcolor, mp, fps, fmpssaving, fpssaving, res, serverinfo, host, map, game, ents, maxc, ping, temp1, temp2, fahrenheit, bForceInv, bClosedBypass;
	int flagx, fpsstrnth, flagy, bfade, sypos1, inttyp, signin, msize, SMPing, drawInterval;
	float frenderfovx;
	float dvis;
	bool Irapid, Iammo, wireframe;
	float x, y, scrollbarsize, menusize, menufade, props, fmj, damage, tracerSpeed, fadeTime, beamLength, fadeScale, beamWidth, screwRadius, screwDist;
	float height, sypos2, menux, menuy, menuxc, menuyc, Reflection, Layer3Scroll, Layer1ScrollX, Layer1ScrollY, Layer1Alpha, Layer1H, Layer1W, Layer1Depth, Layer2ScrollX, Layer2ScrollY, Gloss_Amount, Emissive_Amo, normalheight;
	color camo, rgbac, trcr, en, fn, vis, hitble, xh, fc, hb, cflash, skin, skin2, esp[18], colorslide, colorslide1, colorslide2, colorslide3, colorslide4, colorslide5, colorslide6;
	color skin3, skin4, skin5, skin6;
	color espzm[1024];
	combodata_s combos[max][max];
};

PartyData_s* get_current_party();
extern signed int(*Party_FindMember)(PartyData_s* party, netadr_t playerAddr);
extern void V3User_Pinger();
extern menudata_s* menu;
extern menushit Mshit;
extern asset assets;
extern std::vector<std::string>CamoV;
extern std::string Title;
extern PartyData_s* Datas;
extern void flash(color* rain);
extern void ResetName();
extern String(*SL_ConvertToString_f)(short s);
extern void set_color(int index);
extern void RenderMenu();
extern void cheats_render();
extern void ProcessConfig();
extern void Menufade_scale(float value);
extern void Menusize_scale(float value);
extern void Damage_scale(float value);
extern void Fmj_scale(float value);
extern void combo_render_ui();
extern void Disconnect();
extern void HandleMenu();
extern void Cancel_Reload();
extern const char* ToLower(std::string name);
extern bool(*Session_IsHost_f)(int, int);
#endif