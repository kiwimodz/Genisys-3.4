#include<Includes.h>
#include <menu.h>
local_s* local = (local_s*)(0x10050504);//0xE5C
menudata_s* menu = (menudata_s*)(0x10031000);//0x10030000 + 0x20164
aimbot_s bot;
CellPadData _pdPad;
cellPadButtonData pdPadBtn[PAD_MAX];
Detour Party_AcceptInvite;
Detour R_DrawIndexedPrimitiveDetour;
Detour CL_SendCmdDetour;
Detour Menu_PaintAllDetour;
Detour CL_WritePacketDetour;
Detour CG_PLayerDetour;
Detour CG_PredictPlayerStateDetour;
Detour R_EndFrameDetour;
Detour R_AddDObjToSceneDetour;
Detour _sys_io_cellPadGetDataDetour;
Detour CG_SetupWeaponCamoRenderDetour;
Detour CG_RelativeTeamColorDetour;
Detour CL_ConsolePrintDetour;
Detour Com_ErrorDetour;
Detour BG_UnlockablesGetUsedAllocationDetour;
Detour CG_FireWeaponDetour;
Detour LUI_LuaCall_DrawRectangleDetour;
Detour SE_GetString_FastFileDetour;
Detour HandleAssetsDetour;
Detour CG_PlayerSonarDetour;
Detour CG_BulletHitEventDetour;
Detour Tracer_SpawnDetour;
Detour CG_OffsetThirdPersonViewDetour;
Detour ThirdPersonViewTraceDetour;
Detour CG_DObjGetWorldTagMatrixDetour;
Detour CL_ClampViewAngleDetour;
Detour CG_CalcEntityLerpPositionsDetour;
Detour sceNpManagerGetOnlineIdDetour;
Detour sceNpManagerGetNpIdDetour;
Detour Sys_GetValueDetour;
Detour StrlenDetour;
Detour AtoiDetour;
Detour Content_DoWeHaveContentPackDetour;
Detour sceNpBasicGetFriendPresenceByIndex2Detour;
Detour sceNpBasicGetFriendListEntryCountDetour;
Detour bdAuthUtility_getUserIDDetour;
Detour sceNpBasicSendMessageDetour;
Detour sceNpManagerRequestTicket2Detour;
Detour Netchan_ProcessDetour;
Detour Tracer_DrawDetour;
Detour bdCommonAddr_serializeDetour;

Material* white;
Material* gradient_fadein;
Material* menu_safearea_arrow;
Material* frame_color_debug;
Material* menu_mp_killstreak_select;
Material* compassping_player;
Material* WeaponChams;
Material* PlayerZchams;
Material* MMS_display;
Material* rmr_lens;
Material* shell_alpha;
Material* camo_dragon_alt;
Material* rangefinder_reticle2;
Material* optic_m32_lens;
Material* shotgun_shell_alpha;
Material* ripple_trail;
Material* wpn_pda_screen;
Material* weapon_camo_gold_2;
Material* hud_scavenger_pickup;
Material* hint_mantle;
Material* compassping_dog;
Material* compass_sg_white;
Material* compass_turret_white;
Material* compass_hk;
Material* waypoint_recon_artillery_strike;

void* return_address;

int R_AllocShaderConstantSet_t[2] = { 0x077DE14, TOC };
int(*R_AllocShaderConstantSet_f)(ShaderConstantSet* scs, const char* name) = (int(*)(ShaderConstantSet*, const char*))R_AllocShaderConstantSet_t;

int __cdecl R_AllocShaderConstantSet(ShaderConstantSet* scs, const char* name)
{
	return R_AllocShaderConstantSet_f(scs, name);
}

int R_SetShaderConstantSetValueW_t[2] = { 0x77E12C, TOC };
char(*R_SetShaderConstantSetValueW_f)(ShaderConstantSet* scs, int index, float w) = (char(*)(ShaderConstantSet*, int, float))R_SetShaderConstantSetValueW_t;

char __cdecl R_SetShaderConstantSetValueW(ShaderConstantSet* scs, int index, float w)
{
	return R_SetShaderConstantSetValueW_f(scs, index, w);
}

char __cdecl R_SetShaderConstantSetValue(ShaderConstantSet* scs, int index, float x, float y, float z, float w)
{
	char* v6; // eax@3
	char result; // al@3

	if (index <= 6 && (1 << index) & scs->used)
	{
		v6 = (char*)scs + 16 * index;
		*(float*)v6 = x;
		*((float*)v6 + 1) = y;
		*((float*)v6 + 2) = z;
		*((float*)v6 + 3) = w;
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int CG_RelativeTeamColor(int clientNum, Vector4* colrr, int localClientNum)
{
	if (bot.esp.bnames)
	{
		colrr->x = menu->esp[clientNum].r;
		colrr->y = menu->esp[clientNum].g;
		colrr->z = menu->esp[clientNum].b;
	}
	else
	{
		CG_RelativeTeamColorDetour.Stub(clientNum, colrr, localClientNum);
	}
}

bool R_UnmapShaderConstantSet(ShaderConstantSet* scs, int index) {
	char result;
	if (index >= 0 && index < 7) {
		scs->used &= ~(1 << index);
		result = 1;
	}
	else {
		result = 0;
	}
	return result;
}

GfxImage* DefaultImage;

Detour R_AllocShaderConstantSetSDetour;

void R_MapShaderConstantSet(ShaderConstantSet* scs, int entnum, const char* name)
{
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu->esp[entnum].r * 20.0f);
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu->esp[entnum].g * 20.0f);
	R_SetShaderConstantSetValueW(scs, R_AllocShaderConstantSet(scs, name), menu->esp[entnum].b * 20.0f);
}

int DB_GetAllXAssetOfType_t[2] = { 0x018c4a4, TOC };
int (*DB_GetAllXAssetOfType)(XAssetType, XAssetHeader*) = (decltype(DB_GetAllXAssetOfType))DB_GetAllXAssetOfType_t;

bool runnonly2frames;
bool playertexturesrunonce = false;
char dbodies[] = { 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00 };
void R_AddDObjToScene(DObj* obj, int pose, unsigned int entnum, unsigned int renderFxFlags, Vector3* lightingOrigin, const float* materialTime, const float* burnFraction, int altXModel, int textureOverrideIndex, ShaderConstantSet* dobjConstantSet, float lightingOriginToleranceSq, float scale, bool isMarkableViewmodel, int rs, int rt, int rst)
{
	scale = menu->props != 1.0f ? menu->props : 1.0f;

	if (menu->renderchamsonme || bot.esp.bweaponchams) {
		menu->camo.RainbowSpeed = 0.0001f;
		menu->camo.Rainbow = true;
		menu->camo.Interpolate();
	}


	static bool runonce = false;
	if (!runonce) {
		WeaponChams = Material_RegisterHandle("mc/mtl_t5_weapon_camera_spike", 7);
		PlayerZchams = Material_RegisterHandle("mc/mtl_german_shepherd_fur_black", 7);
		MMS_display = Material_RegisterHandle("mc/mtl_t6_attach_optic_mms_display", 6);
		rmr_lens = Material_RegisterHandle("mc/mtl_t6_attach_optic_rmr_lens", 6);
		shell_alpha = Material_RegisterHandle("mc/mtl_fx_shell_alpha", 6);
		camo_dragon_alt = Material_RegisterHandle("mc/mtl_weapon_camo_dragon_alt", 6);
		rangefinder_reticle2 = Material_RegisterHandle("mc/mtl_t6_attach_optic_rangefinder_reticle2", 6);
		optic_m32_lens = Material_RegisterHandle("mc/mtl_t6_attach_optic_m32_lens", 6);
		shotgun_shell_alpha = Material_RegisterHandle("mc/mtl_fx_shotgun_shell_alpha", 6);
		ripple_trail = Material_RegisterHandle("gfx_fxt_fx_distortion_ripple_trail", 6);
		wpn_pda_screen = Material_RegisterHandle("mc/mtl_t6_wpn_pda_screen", 6);
		weapon_camo_gold_2 = Material_RegisterHandle("mc/mtl_weapon_camo_gold_2", 6);

		XAssetHeader* headers = (XAssetHeader*)_sys_malloc(sizeof(int) * 5000);
		auto count = DB_GetAllXAssetOfType(XAssetType::ASSET_TYPE_MATERIAL, headers);

		for (int i = 0; i < count; i++)
		{
			if (headers[i].material)
			{
				if (strstr(headers[i].material->info.name, "toxic") || strstr(headers[i].material->info.name, "dlc4"))
					headers[i].material->cameraRegion = 4;
				//headers[i].material->info.drawSurf.packed = 0xe20007be00000000; //0x100003cc00000000;
			}
		}
		memset(headers, 0, sizeof(int) * 5000);
		delete[] headers;

		runonce = true;
	}

	if (menu->wireframe)
	{
		*(char*)0x07C47A3 = 4;
	}
	else
	{
		*(char*)0x07C47A3 = 5;
	}

	//auto* Gloves = Material_RegisterHandle("mc/mtl_viewarm_usa_mp_seal6_glove", 7);

	if (centity[entnum].Type == ET_PLAYER || (centity[entnum].Type == ET_DOG))
	{
		if (bot.esp.bwall) {
			renderFxFlags = -1;//Render Players through Walls
			*(char*)0x1CBF9F8 = 0x00;//r_dof_enable - No Blur
		}
	}

	if (centity[entnum].eType == ET_ITEM && bot.esp.bwwall)
	{
		if (bot.esp.bwwall) {
			renderFxFlags = -1;//Render Players through Walls
			*(char*)0x1CBF9F8 = 0x00;//r_dof_enable - No Blur
		}
	}

	if (bot.esp.ebwall) {
		renderFxFlags = -1;//Render Everything through Walls
	}

	if (bot.esp.bweaponchams || bot.playertype > 0)
	{
		for (int i = 0; i < obj->numModels; i++)
		{
			for (int c = 0; c < obj->models[i]->numsurfs; c++)
			{
				switch (bot.playertype)
				{
				case 0:
					break;
				case 1:
					if (obj->models[i]->materialHandles[c] != rmr_lens)
						obj->models[i]->materialHandles[c] = rmr_lens;
					break;
				case 2:
					if (obj->models[i]->materialHandles[c] != shell_alpha)
						obj->models[i]->materialHandles[c] = shell_alpha;
					break;
				case 3:
					if (obj->models[i]->materialHandles[c] != camo_dragon_alt)
						obj->models[i]->materialHandles[c] = camo_dragon_alt;
					break;
				case 4:
					if (obj->models[i]->materialHandles[c] != rangefinder_reticle2)
						obj->models[i]->materialHandles[c] = rangefinder_reticle2;
					break;
				case 5:
					if (obj->models[i]->materialHandles[c] != optic_m32_lens)
						obj->models[i]->materialHandles[c] = optic_m32_lens;
					break;
				case 6:
					if (obj->models[i]->materialHandles[c] != shotgun_shell_alpha)
						obj->models[i]->materialHandles[c] = shotgun_shell_alpha;
					break;
				case 7:
					if (obj->models[i]->materialHandles[c] != ripple_trail)
						obj->models[i]->materialHandles[c] = ripple_trail;
					break;
				case 8:
					if (obj->models[i]->materialHandles[c] != wpn_pda_screen)
						obj->models[i]->materialHandles[c] = wpn_pda_screen;
					break;
				case 9:
					if (obj->models[i]->materialHandles[c] != weapon_camo_gold_2)
						obj->models[i]->materialHandles[c] = weapon_camo_gold_2;
					break;
				case 10:
					if (obj->models[i]->materialHandles[c] != PlayerZchams)
						obj->models[i]->materialHandles[c] = PlayerZchams;
					break;
				default:
					break;
				}

				if (centity[entnum].eType == ET_ITEM)
					if (obj->models[i]->materialHandles[c] != WeaponChams && obj->models[i]->materialHandles[c] != MMS_display)
						obj->models[i]->materialHandles[c] = WeaponChams;
			}
		}
	}

	if (dobjConstantSet) {

		if (centity[entnum].ClientNumber == cg->clientNum)
		{
			if (menu->renderchamsonme)
			{
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), menu->camo.r * bot.chamsintensity);//Set chameleon skin Red
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), menu->camo.g * bot.chamsintensity);//Set chameleon skin Green
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), menu->camo.b * bot.chamsintensity);//Set chameleon skin Blue
				R_AddDObjToSceneDetour.Stub(obj, pose, entnum, renderFxFlags, lightingOrigin, materialTime, burnFraction, altXModel, textureOverrideIndex, dobjConstantSet, lightingOriginToleranceSq, scale, 0, 0, 0, 0);

			}

			else
			{
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
				R_AddDObjToSceneDetour.Stub(obj, pose, entnum, renderFxFlags, lightingOrigin, materialTime, burnFraction, altXModel, textureOverrideIndex, dobjConstantSet, lightingOriginToleranceSq, scale, 0, 0, 0, 0);
			}
		}

		if (centity[entnum].eType == ET_ITEM)
		{
			if (bot.esp.bweaponchams)
			{
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), menu->camo.r * 10.f);//Set chameleon skin Red
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), menu->camo.g * 10.f);//Set chameleon skin Green
				R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), menu->camo.b * 10.f);//Set chameleon skin Blue
			}

			else
			{
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
			}
		}

		if (centity[entnum].Type == ET_PLAYER || (centity[entnum].Type == ET_DOG))
		{
			if (bot.esp.bchams)
			{
				if (CG_IsEntityFriendlyNotEnemy(&centity[entnum]) && bot.esp.ballies) {
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), menu->esp[entnum].r * bot.chamsintensity);//Set chameleon skin Red
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), menu->esp[entnum].g * bot.chamsintensity);//Set chameleon skin Green
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), menu->esp[entnum].b * bot.chamsintensity);//Set chameleon skin Blue
				}

				else if (!CG_IsEntityFriendlyNotEnemy(&centity[entnum]) && bot.esp.baxis) {
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"), menu->esp[entnum].r * bot.chamsintensity);//Set chameleon skin Red
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"), menu->esp[entnum].g * bot.chamsintensity);//Set chameleon skin Green
					R_SetShaderConstantSetValueW(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"), menu->esp[entnum].b * bot.chamsintensity);//Set chameleon skin Blue
				}

				else
				{
					R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
					R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
					R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
				}
			}

			else
			{
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingR"));//Unmap chameleon skin Red
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingG"));//Unmap chameleon skin Green
				R_UnmapShaderConstantSet(dobjConstantSet, R_AllocShaderConstantSet(dobjConstantSet, "heroLightingB"));//Unmap chameleon skin Blue
			}
		}
	}

	R_AddDObjToSceneDetour.Stub(obj, pose, entnum, renderFxFlags, lightingOrigin, materialTime, burnFraction, altXModel, textureOverrideIndex, dobjConstantSet, lightingOriginToleranceSq, scale, 0, 0, 0, 0);

}

int CG_SetupWeaponCamoRender(int localClientNum, float* origin, WeaponDobjInfo* weaponSlot, unsigned int camo, WeaponDobjInfo* weaponDobjInfo, int* textureOverrideIndex)
{
	if (menu->flagx == 50)
	{
		camo = menu->flagy;
	}

	else
	{
		camo = menu->flagx;
	}

	if (menu->flagx == 0)
	{
		camo = camo;
	}

	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, HELD, camo, weaponDobjInfo, textureOverrideIndex);
	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, STOWED, camo, weaponDobjInfo, textureOverrideIndex);
	CG_SetupWeaponCamoRenderDetour.Stub(localClientNum, origin, MELEE, camo, weaponDobjInfo, textureOverrideIndex);
}

void BG_PlayerAnimationStub(...) {
	__asm("li %r3, 4");
}

float rotate;
void __cdecl BG_PlayerAnimation(int localClientNum, int* es, int* ci, Vector3 origin, Vector3 angles)
{
	BG_PlayerAnimationStub(cg->clientNum, es, ci, origin, 0);
}

#define ingame Dvar_GetBool("cl_ingame")
bool ingame_;
#pragma endregion

#pragma region menu paint
int camoentrydatables;
int camoentrydatablus;
int camodata;
char zero[] = { 0x00, 0x00,0x00,0x00 };
char NOPE[] = { 0x60, 0x00,0x00,0x00 };
char Skycolora[16] = { 0x3F, 0x7C, 0xAB, 0x93, 0x3E, 0xDD, 0x57, 0x15, 0xBC, 0x0B, 0xBD, 0x38 };
char Skycolorb[16] = { 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x5E, 0x70, 0x32, 0x3F, 0x1A, 0x94, 0x6F };
char Skycolorc[4] = { 0x45, 0xCB, 0x20, 0x00 };
char array__[0x8] = { 0x62, 0x1E, 0xF4, 0xEF, 0x25, 0x21, 0x93, 0x23 };
char array[0x8] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
char structt[12] = { 0x34, 0xED, 0x80, 0x00, 0x01, 0x85, 0x29, 0x00, 0x01, 0xAA, 0xE4 };
bool runoncegfg = true;

#pragma endregion

#pragma region write packet

#pragma endregion

#pragma region send cmd

bool SendPacket;
float tick;

int CG_PredictPlayerState(int localClientNum)
{
	if (menu->bInGame && cg->health > 0)
	{
		local->ishost = Session_IsHost_f(0x26C2BC8, cg->clientNum);

		PredictPlayerState();
	}

	CG_PredictPlayerStateDetour.Stub(localClientNum);
}

int CL_SendCmd(int localClientNum)
{
	if (menu->bInGame)
	{
		SendCMD();
	}
	CL_SendCmdDetour.Stub(localClientNum);
}

int CL_WritePacket(int localClientNum)
{
	SendPacket = true;

	Writepacket();

	if (menu->bInGame)
	{
		if (bot.fakelagscale > 0.00)
		{
			SendPacket = false;
			tick++;
			if (tick >= bot.fakelagscale)
			{
				tick = 0;
				SendPacket = true;
			}
		}
	}

	if (SendPacket || (local->shooting))
	{
		CL_WritePacketDetour.Stub(localClientNum);
	}
	local->shooting = false;
}

#pragma endregion
#pragma region cell pad

int _sys_io_cellPadGetData(uint32_t port_no, CellPadData* data)
{
	CellPadData tmpCellPad = { 0 };

	tmpCellPad.len = data->len;
	cellPadGetData(port_no, &tmpCellPad);
	memcpy((void*)data, (void*)&tmpCellPad, sizeof(CellPadData));
	if (data->len != 0 && port_no == 0)
		memcpy((void*)&_pdPad, (void*)&tmpCellPad, sizeof(CellPadData));

	if (Mshit.Mopened && data->len != 0)
	{
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_UP;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_DOWN;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_LEFT;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_RIGHT;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_CROSS;
		data->button[CELL_PAD_BTN_OFFSET_DIGITAL2] &= ~CELL_PAD_CTRL_CIRCLE;
	}

	if (!Mshit.Mopened && menu->bInGame)
	{
		if (bot.blean)
		{
			data->button[CELL_PAD_BTN_OFFSET_DIGITAL1] &= ~CELL_PAD_CTRL_RIGHT;
		}
	}

	if (cg->health > 0) {
		if (menu->bInGame && bot.benablal && local->alive && bot.aimtype != AIM_TYPE_SILENT && bot.aimtype != AIM_TYPE_TRIGGERBOT && bot.keytype != KEY_L1 && centity[cg->clientNum].WeaponID != 89) {

			playerState_s* playerState = CG_GetPredictedPlayerState(0);

			if (!BG_UsingVehicleWeapon(playerState))
			{
				int ammo = BG_GetAmmoInClip(&cg->playerstate, cg->playerstate.weapon);

				if (ammo > 0)
				{
					data->button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_X] = 0x80;
					data->button[CELL_PAD_BTN_OFFSET_ANALOG_RIGHT_Y] = 0x80;
				}
			}
		}
	}

	if (!bot.benable)
	{
		local->alive = false;
	}
	return 0;
}
#pragma endregion

struct Material__ {
	const char* name;
};

struct LUI_Element {
	Material__* material;
};
bool runonc23e = false;
int GScr_AllocString_t[2] = { 0x23E940, TOC };
unsigned int(*GScr_AllocString_f)(const char* s) = (unsigned int(*)(const char*))GScr_AllocString_t;

char* SNames[13] = {
	"j_head",
	"j_helmet",
	"j_neck",
	"j_spineupper",
	"j_knee_le",
	"j_knee_ri",
	"j_ankle_le",
	"j_ankle_ri",
	"j_ball_le",
	"j_ball_ri",
	"j_wrist_le",
	"j_wrist_ri",
	"tag_origin"
};

float spinYy;
bool ingame3;

int frametimeGame = 0;
int frametimeThread = 0;

char resetpsn[] = { 0x4B, 0xFF, 0xFF, 0xD8 };
#define ReturnAddr(X) (__builtin_return_address() == (void*)X)
void* ThreadInfo;
bool blo = false;

bool precacheAssets() {
	for (int i = 0; i < 13; i++)
	{
		AimBoneIndex[i] = GScr_AllocString_f(SNames[i]);
		EspBoneIndex[i] = GScr_AllocString_f(SNames[i]);
	}

	white = Material_RegisterHandle("white", 0);
	gradient_fadein = Material_RegisterHandle("gradient_fadein", 7);
	menu_safearea_arrow = Material_RegisterHandle("menu_safearea_arrow", 7);
	frame_color_debug = Material_RegisterHandle("frame_color_debug", 7);
	menu_mp_killstreak_select = Material_RegisterHandle("menu_mp_killstreak_select", 7);
	compassping_player = Material_RegisterHandle("compassping_player", 7);
	hud_scavenger_pickup = Material_RegisterHandle("hud_scavenger_pickup", 7);
	hint_mantle = Material_RegisterHandle("hint_mantle", 7);
	compassping_dog = Material_RegisterHandle("compassping_dog", 7);
	compass_sg_white = Material_RegisterHandle("compass_sg_white", 7);
	compass_turret_white = Material_RegisterHandle("compass_turret_white", 7);
	compass_hk = Material_RegisterHandle("compass_hk", 7);
	waypoint_recon_artillery_strike = Material_RegisterHandle("waypoint_recon_artillery_strike", 7);

	if (white && gradient_fadein && menu_safearea_arrow && frame_color_debug && menu_mp_killstreak_select && compassping_player && hud_scavenger_pickup && hint_mantle &&
		compassping_dog && compass_sg_white && compass_turret_white && compass_hk && waypoint_recon_artillery_strike)
		return true;
	else
		return false;
}

int R_EndFrame()
{
	Global_Ingame();
	HandleMenu();
	RenderMenu();
	combo_render_ui();

	Flash_name_();
	Add_name_();
	Add_name__();

	if (menu->bInGame)
	{
		runreauthonce = false;
		ingame3 = true;
		spinYy = (spinYy > 360) ? (spinYy - 360) : (spinYy + 2);

		if (!runonc23e)
		{
		int addy = (*(int*)(0x128B6FC + 0x28) + 0x400);
				Memcp__((void*)addy, &assets.gp, 2048);
				runonc23e = true;
		}
	}

	static bool assets_precached = false;
	if (!assets_precached)
	{
		Mshit.ch = "Status: Waiting";
		local->stausrank = "Status: Waiting";
		if (precacheAssets())
			assets_precached = true;
	}

	if (!menu->maxc || !menu->ents) {
		EntityCount();
	}

	R_EndFrameDetour.Stub();
}

#pragma region ...
SYS_MODULE_INFO(BO1_MP, 0, 1, 1);
SYS_MODULE_START(_BO1_MP_prx_entry);
SYS_MODULE_STOP(_BO1_MP_prx_exit);

sys_prx_id_t export_module;
int info;
int res;
char blr[] = { 0x4E, 0x80, 0x00, 0x20 };
char nop[] = { 0x60, 0x00, 0x00, 0x00 };
char li7[] = { 0x38, 0x80, 0x00, 0x7 };
char li17[] = { 0x38, 0x60, 0x00, 0x7 };

void RB_StandardDrawCommands(GfxViewInfo* viewInfo)
{
	viewInfo->charPrimaryLightScale.specularScale = 100.f;
}

struct weaponState_t
{
	playerState_s* ps;
	float xyspeed;
	float frametime;
	float fLastIdleFactor;
	int time;
	int damageTime;
	float v_dmg_pitch;
	float v_dmg_roll;
	int* removeMeUnusedInt;
	Vector3 baseAngles;
	Vector3 baseOrigin;
	Vector3 recoilAngles;
	Vector3 recoilSpeed;
	Vector3 swayAngles;
	Vector3 swayOrigin;
	Vector3 swayViewAngles;
	Vector3 bobAngles;
	int shellShockStart;
	int shellShockDuration;
	int shellShockFadeTime;
};

Vector3 zero_ = Vector3(1, 1, 1);
Console console;

void CL_ConsolePrint(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, int flags)
{
	if (menu->bInGame)
	{
		if (bot.drawconsole)
		{
			CL_ConsolePrintDetour.Stub(localClientNum, channel, txt, duration, pixelWidth, flags);
		}

		else
		{
			if (channel < 10)
			{
				console.write(txt, color(255, 255, 255, 255), color(42, 42, 42, 255), (color)menu->skin, (color)menu->skin2);
			}
		}
	}
}

void Com_Error(int code, const char* fmt, char* ap)
{
	char buffer[400];
	Com_Sprintf(buffer, sizeof(buffer), fmt, ap);
	CG_GameMessage(buffer);
	Com_ErrorDetour.Stub(code, fmt, ap);
}

void LUI_LuaCall_DrawRectangleH(LUI_Element* r3, float f1, float f2, float f3, float f4, float red, float green, float blue, float alpha, int r9, int r10) {

	if (menu->bo2theme && !menu->bInGame)
	{
		const char* icon = r3->material->name;

		if (strstr(icon, "menu_mp_soldiers"))
		{
			red = menu->skin.r;
			green = menu->skin.g;
			blue = menu->skin.b;
			alpha = menu->skin.a / 2;
		}

		if (strstr(icon, "ui_smoke"))
		{
			red = menu->skin2.r / 2;
			green = menu->skin2.g / 2;
			blue = menu->skin2.b / 2;
			alpha = menu->skin2.a / 2;
		}

		if (strstr(icon, "lui_bkg")
			|| strstr(icon, "menu_mp_cac_backing")
			|| strstr(icon, "menu_mp_backing_frame") || strstr(icon, "holotable"))
		{
			red = menu->skin.r;
			green = menu->skin.g;
			blue = menu->skin.b;
			alpha = menu->skin.a;
		}

		if (strstr(icon, "globe"))
		{
			red = menu->skin2.r;
			green = menu->skin2.g;
			blue = menu->skin2.b;
			alpha = menu->skin2.a;
		}
	}

	LUI_LuaCall_DrawRectangleDetour.Stub(r3, f1, f2, f3, f4, red, green, blue, alpha, r9, r10);
}

const char* SE_GetString_FastFile(const char* psPackageAndStringReference) {

	if (!strcmp(psPackageAndStringReference, "MENU_SEARCHING_FOR_PLAYER"))
	{
		return "Searching for ^1gaybab users";
	}

	if (!strcmp(psPackageAndStringReference, "MPUI_HOST_MIGRATION")) {
		menu->bInGame = false;
	}

	if (!strcmp(psPackageAndStringReference, "MENU_SELECT_GRENADE"))
	{
		return "Select Ball Buster";
	}

	if (!strcmp(psPackageAndStringReference, "WEAPON_FRAGGRENADE"))
	{
		return "Ball Buster";
	}

	if (!strcmp(psPackageAndStringReference, "SCRIPT_GRENADE_DEATH"))
	{
		return "M8 You were killed by a Ball Buster";
	}

	SE_GetString_FastFileDetour.Stub(psPackageAndStringReference);
}

enum loadoutClass_t {
	CLASS_INVALID = 0xFFFFFFFF,
	CUSTOM_CLASS_1 = 0x0,
	CUSTOM_CLASS_FIRST = 0x0,
	CUSTOM_CLASS_2 = 0x1,
	CUSTOM_CLASS_3 = 0x2,
	CUSTOM_CLASS_4 = 0x3,
	CUSTOM_CLASS_5 = 0x4,
	BASIC_CUSTOM_CLASS_COUNT = 0x5,
	CUSTOM_CLASS_6 = 0x5,
	CUSTOM_CLASS_7 = 0x6,
	CUSTOM_CLASS_8 = 0x7,
	CUSTOM_CLASS_9 = 0x8,
	CUSTOM_CLASS_10 = 0x9,
	CUSTOM_CLASS_COUNT = 0xA,
	DEFAULT_CLASS_FIRST = 0xA,
	DEFAULT_CLASS_SMG = 0xA,
	DEFAULT_CLASS_CQB = 0xB,
	DEFAULT_CLASS_ASSAULT = 0xC,
	DEFAULT_CLASS_LMG = 0xD,
	DEFAULT_CLASS_SNIPER = 0xE,
	DEFAULT_CLASS_LAST = 0xE,
	TOTAL_CLASS_COUNT = 0xF,
};

int BG_UnlockablesGetUsedAllocationH(int* cacRoot, loadoutClass_t customClass) {

	if (local->unlimitedSlots) {
		return -1337;
	}
	BG_UnlockablesGetUsedAllocationDetour.Stub(cacRoot, customClass);
}

void CG_FireWeaponH(int localClientNum, centity_t* cent, int event, int eventParm, const unsigned __int16 tagName, Weapon weapon, playerState_s* ps, bool leftGun)
{
	if (menu->bInGame && (ps->weaponstate == WEAPON_FIRING))
	{
		if (CScr_IsAlive(localClientNum) && (cent[localClientNum].pose.localClientNum == localClientNum)) {
			if (menu->flagx == 50)
			{
				menu->flagy = irand_(0, 45);
			}
		}
	}
	if (!menu->bgunsound)
		CG_FireWeaponDetour.Stub(localClientNum, cent, event, eventParm, tagName, weapon, ps, leftGun);
}

bool xortick;

struct GfxImageRestore {
	uint32_t Offset;
	char Image[0x94];
};

char rgbarray[44] = { 0x0D, 0x34, 0xED, 0x80, 0x00, 0x01, 0x85, 0x29, 0x00, 0x01, 0xAA, 0xE4, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD, 0x34, 0xED, 0x80 };

bool Flag = false;

GfxImageRestore camos[500];

int CG_PrepFireParams_t[2] = { 0x0ED008, TOC };
bool (*CG_PrepFireParams)(int localClientNum, centity_s* ent, short boneName, playerState_s* ps, int weapon, int event_, bool isPlayer, BulletFireParams* bp, Vector3* tracerStart, int* shotCount, float* range, orientation_t* orient, Vector3* origin, float* aimSpreadAmount, int* ignoreEntity) = (bool(*)(int localClientNum, centity_s * ent, short boneName, playerState_s * ps, int weapon, int event_, bool isPlayer, BulletFireParams * bp, Vector3 * tracerStart, int* shotCount, float* range, orientation_t * orient, Vector3 * origin, float* aimSpreadAmount, int* ignoreEntity))CG_PrepFireParams_t;

int BG_TracerType_t[2] = { 0x060ABA0, TOC };
TracerDef* (*BG_TracerType)(int w, bool f) = (decltype(BG_TracerType))BG_TracerType_t;

int Tracer_Spawn_t[2] = { 0x045C038, TOC };
void (*Tracer_Spawn_f)(int localClientNum, Vector3* pstart, Vector3* pend, centity_s* instigator, int weapon) = (decltype(Tracer_Spawn_f))Tracer_Spawn_t;

TracerDef* weapon_tracer;

void Tracer_Spawn(int localClientNum, Vector3* pstart, Vector3* pend, centity_s* instigator, int weapon)
{
	if (bot.esp.btracers && menu->bInGame)
	{
		auto friends = CG_IsEntityFriendlyNotEnemy(&centity[cg->clientNum]);
		weapon_tracer = BG_TracerType(centity[cg->clientNum].WeaponID, friends);

		if (!weapon_tracer)
			return;

		weapon_tracer->material = Material_RegisterHandle("gfx_tracer", 6);
		weapon_tracer->speed = 1.0f;
		weapon_tracer->name = "smg";
		weapon_tracer->drawInterval = 1;
		weapon_tracer->type = TRACERTYPE_SMOKE;
		weapon_tracer->fadeTime = menu->fadeTime;
		weapon_tracer->beamLength = menu->beamLength;
		weapon_tracer->fadeScale = menu->fadeScale;
		weapon_tracer->beamWidth = menu->beamWidth;
		weapon_tracer->screwRadius = menu->screwRadius;
		weapon_tracer->screwDist = menu->screwDist;
		weapon_tracer->texRepeatRate = 999999.0f;
		auto weapondef = BG_GetWeaponDef(centity[cg->clientNum].WeaponID);
		//weapondef->tracerType = weapon_tracer;

		for (int i = 0; i < 5; i++)
		{
			memcpy(&weapon_tracer->colors[i], &menu->trcr, sizeof(vec4_t));
		}
	}

	Tracer_SpawnDetour.Stub(localClientNum, pstart, pend, instigator, weapon);
}

char CG_BulletHitEventH(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, Vector3* endPos, int surfacetype, Vector3* normal, Vector3* seeThruDecalNormal, int nothing, int event_, char eventParam, int hitContents, char boneIndex)
{
	if (menu->bInGame)
	{
		if (bot.esp.btracers && sourceEntityNum == cg->clientNum)
		{
			playerState_s* playerState = CG_GetPredictedPlayerState(0);
			int iShots, iIgnoreNum;
			float flRange, flSpread;
			Vector3 vTracerStart, vOrigin;
			orientation_t Orientation;
			BulletFireParams FireParams;
			memset(&FireParams, 0, sizeof(BulletFireParams));

			if (CG_PrepFireParams(0, &centity[cg->clientNum], SL_GetString("tag_flash", 7), playerState, playerState->weapon, 32, true, &FireParams, &vTracerStart, &iShots, &flRange, &Orientation, &vOrigin, &flSpread, &iIgnoreNum))
			{
				if (local->alive)
					Tracer_Spawn_f(0, &vTracerStart, &local->player[local->target_num].vtag[bot.psztag[local->target_num]], &centity[sourceEntityNum], centity[sourceEntityNum].WeaponID);
				else
					Tracer_Spawn_f(0, &vTracerStart, endPos, &centity[sourceEntityNum], centity[sourceEntityNum].WeaponID);
			}
		}
	}
	CG_BulletHitEventDetour.Stub(localClientNum, sourceEntityNum, targetEntityNum, weapon, endPos, surfacetype, normal, seeThruDecalNormal, nothing, event_, eventParam, hitContents, boneIndex);
}

void Tracer_Draw(Vector3* start, Vector3* finish, TracerInfo* tracer, TracerDrawFlags drawFlags, const float alphaScale, const bool smokeTrail) {
	Tracer_DrawDetour.Stub(start, finish, tracer, drawFlags, 1, false);
}

void CL_ClampViewAngleH(int localClientNum, const int angle, const float min, const float maxx)
{
	CL_ClampViewAngleDetour.Stub(localClientNum, angle, -360.0f, 360.0f);
}

void CG_CalcEntityLerpPositions(int localClientNum, centity_t* cent) {

	CG_CalcEntityLerpPositionsDetour.Stub(localClientNum, cent);

	if (menu->bInGame)
	{
		if (bot.benableanti)
		{
			if (cent->nextState.number == cg->clientNum)
			{
				cgst->clients[cg->clientNum].viewAngle.x = local->fakeAngles[0];

				if (bot.block3dpaa)
				{
					//UN-LOCK
					cent->pose.angles[1] = (local->fakeAngles[1]) + cg->playerstate.delta_angles.y;
				}
				else
				{
					//LOCK
					cent->pose.angles[1] = (local->fakeAngles[1]) + cactive->ViewAngles.y + cactive->BaseAngles.y;
				}
			}
		}

		if (menu->sping)
		{
			if (cent->pose.eType == ET_ITEM)
			{
				if (cent->nextState.weapon == 89 || cent->nextState.weapon == 113) return;
				cent->pose.angles[1] = (spinYy);
				cent->pose.angles[2] = 0;
				cent->pose.origin.z += 15;
			}
		}

		ApplyPositionPrediction(cent);
		ApplyAnglePrediction(cent);

	}
}

char restrmtx[0x4] = { 0x4B, 0xF7, 0x7A, 0xD5 };
char blrr[] = { 0x4E, 0x80, 0x00, 0x20 };

int __cdecl CG_DObjGetWorldTagMatrix(cpose_t* pose, DObj* obj, unsigned int tagName, Vector3* tagMat, Vector3* origin)
{
	int ret = CG_DObjGetWorldTagMatrixDetour.Stub(pose, obj, tagName, tagMat, origin);
	if (__builtin_return_address() == (void*)0x00D46B8 && obj && (obj->entnum - 1) == cg->clientNum)
	{
		playerState_s* playerState = CG_GetPredictedPlayerState(0);
		if (!BG_UsingVehicleWeapon(playerState)) {
			if (menu->bInGame)
			{
				if (bot.benableanti && bot.bthirdp)
				{
					*origin = centityt[cg->clientNum].pose.origin;
					origin->z += 70.0f;
				}
			}
		}
	}
	
	return ret;
}

#include <np.h>
int sceNpManagerGetOnlineId_hook(SceNpOnlineId* out) {
	strcpy(out->data, "KeeWeeModz");
	int ret = sceNpManagerGetOnlineIdDetour.Stub(out);
	SceNpId* out2;
	strcpy(out->data, "Reflux_Faults");
	strcpy(out2->handle.data, "Reflux_Faults");
	_sys_printf("[BO2] [OnlineId2] %s\n", out->data);
	return ret;
}

int sceNpManagerGetNpId_hook(SceNpId* out) {
	int ret = sceNpManagerGetNpId(out);
	strcpy(out->handle.data, "Reflux_Faults");
	strcpy((char*)out->opt, "b2gbps3");
	_sys_printf("[BO2] [NpIdSpoof] NpId: %s\n", out);
	strcpy((char*)out->handle.data, "GenisysV3");
	memcpy(out->opt, "a9nzps3", 8);
	out->opt[4] = 'p';
	out->opt[5] = 's';
	out->opt[6] = '3';
	out->opt[7] = 0;
	out->reserved[0] = 1;
	return ret;
}

int sceNpManagerRequestTicket2_hook(SceNpId* npId, const SceNpTicketVersion* version, const char* serviceId, const void* cookie, size_t cookieSize, const char* entitlementId, unsigned int consumedCount) {
	int ret = 0;
	strcpy(npId->handle.data, "GenisysV3");
	strcpy((char*)npId->opt, "b2nzps3");
	ret = sceNpManagerRequestTicket2(npId, version, serviceId, cookie, cookieSize, entitlementId, consumedCount);
	if (0 > ret) {
		_sys_printf("[BO2] sceNpManagerRequestTicket2_stub() failed. 0x%x\n", ret);
	}
	else {
		_sys_printf("[BO2] serviceId: %s entitlementId: %s consumedCount %s npId: %s, cookie: %s\n", serviceId, entitlementId, consumedCount, npId, cookie);
	}

	strcpy(npId->handle.data, "Reflux_Faults");
	strcpy((char*)npId->opt, "b2gbps3");
	return 0;
}

char accountId[] = { 0x49, 0xB6, 0x27, 0x6F, 0x72, 0x78, 0xDC, 0x7F };
Detour sceNpManagerGetTicketParamDetour, sceNpManagerGetTicketDetour, bdHashTiger192hashDetour;
unsigned char buff[0x156];

int r_sys_net_sendto[4] = { 0x39800000, 0x658C00D5, 0x818C0D98, 0xF8410028 };
int r_sys_net_sendmsg[4] = { 0x39800000, 0x658C00D5, 0x818C0DA8, 0xF8410028 };
int r_sys_net_send[4] = { 0x39800000, 0x658C00D5, 0x818C0DBC, 0xF8410028 };
int r_cellHttp_cellHttpSendRequest[4] = { 0x39800000, 0x658C00D5, 0x818C09C4, 0xF8410028 };
int r_cellHttp_cellHttpRecvResponse[4] = { 0x39800000, 0x658C00D5, 0x818C09B4, 0xF8410028 };
int r_sys_net_recvfrom[4] = { 0x39800000, 0x658C00D5, 0x818C0D70, 0xF8410028 };
int r_sys_net_recv[4] = { 0x39800000, 0x658C00D5, 0x818C0DC0, 0xF8410028 };

int Content_DoWeHaveContentPack(int ContentPack)
{
	if (ContentPack == 2) return 1;//normal maps
	if (ContentPack == 4) return 1;//nuketown
	if (ContentPack == 8) return 1;//nuketownZ
	if (menu->benablecamos) {
		*(unsigned long long*)0x03265e0 = 0x386000014E800020;
		*(unsigned long long*)0x05e2b3c = 0x386000004E800020;
	}
	else {
		*(unsigned long long*)0x03265e0 = 0xF821FF817C0802A6;
		*(unsigned long long*)0x05e2b3c = 0xF821FF417C0802A6;
	}
	return menu->disabledlc ? 0 : ContentPack;
}

String honkList[] = {
"Messing with the honk",
"Honk?, get the bonk",
"Bonk", "Oooooooh yea you like my ASSets HUH?",
"Fuck.....",
"Peace was never an option",
"Im an agent of chaos",
"wAckY BoNkErs!",
"Ending skids with V3",
"Can I use mod menu on chimken",
"Grab a bonk load of my ASSets",
"This isn't real",
"Reality is a lie",
"Crashing on memset",
"You just got robloxed",
"Hazy gay",
"Hmmm you wish you had these ASSets bro",
"Hmmmmmmm you want these ASSets HUH???",
 "bruh moment",
"Boof",
"Developing Dexters excuse for a cheat",
"Eat my ass",
"Get stick bugged",
"Go to horny jail",
"Lupos is the fake Lupos",
"About 12",
"Red looking sus",
"Hello, how are u, I'm unda da water",
"1000% zoom = code go brrrrrrrr",
"BOOOOONEZZZZzzzzz",
"blasts mods likes men"
};

int FakeListCounter = 0;
int FakeListIncrement = 0;

int sceNpBasicGetFriendPresenceByIndex2_f(uint32_t index, SceNpUserInfo* user, SceNpBasicPresenceDetails2* pres, uint32_t options) {

	SceNpUserInfo usr;
	SceNpBasicPresenceDetails2 prs;
	SceNpId Usr;

	sceNpBasicGetFriendPresenceByIndex2Detour.Stub(index, user, pres, options);
	if (strcmp(user->userId.handle.data, "") == 0) {
		std::string name = Fr.vFriends.at(FakeListIncrement);
		std::string npid = Fr.vFriends.at(FakeListIncrement);

		if (name != "") {
			std::string c = Fr.vFriends.at(FakeListIncrement);
			int first = c.find(":");
			char out[32];
			Com_Sprintf(out, first + 1, "%s", c.c_str());
			npid.erase(0, first + 1);

			size_t pos = npid.find(":");
			if (pos != std::string::npos) {
				npid.erase(pos, 1);
			}
			if (npid.empty())
				Usr = doLookupNpId(out).first;
			else
				Memcp__(Usr.opt, npid.c_str(), sizeof(SceNpId));

			strcpy(pres->status, honkList[irand_(0, SizeOf(honkList))]);
			strcpy(user->userId.handle.data, out);
			memcpy(user->userId.opt, Usr.opt, sizeof(Usr.opt));
			user->userId.opt[4] = 'p';
			user->userId.opt[5] = 's';
			user->userId.opt[6] = '3';
			user->userId.reserved[0] = 1;
			pres->state = 2;
			FakeListIncrement++;
			if (FakeListIncrement == FakeListCounter)
				FakeListIncrement = 0;
		}
	}
}

int sceNpBasicGetFriendListEntryCount_f(uint32_t* count) {
	uint32_t iCount = 0;
	Fr.ReadFriends();
	FakeListCounter = Fr.vFriends.size();
	int ret = sceNpBasicGetFriendListEntryCount(&iCount);
	if (ret < 0) {
		printf("err");
	}
	*count = iCount + FakeListCounter;
	return 0;
}

char Data[0x58] = { 0x00, 0x00, 0x00, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x4A, 0xEA, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
int sceNpBasicSendMessage_f(const SceNpId* to, const void* data, size_t size) {
	auto join_message_data = (JoinSessionMessage*)data;

	if (__builtin_return_address() == (void*)0x0533E74)
	{
		if (messages.empty())
			return sceNpBasicSendMessageDetour.Stub(to, data, size);

		join_message_data->inviteInfo.fromMPInvite = false;
		join_message_data->inviteInfo.sessionInfo.sessionID.ab[0] = irand_f(0, 255);
		return sceNpBasicSendMessageDetour.Stub(to, join_message_data, size);
	}
	return sceNpBasicSendMessageDetour.Stub(to, data, size);
}

int bdAuthUtility_getUserID_f(const char* name) {
	if (name == "RefluxFaultz")
		name = "GenisysV3";
	if (__builtin_return_address() == (void*)0x0535ef0)
		return bdAuthUtility_getUserIDDetour.Stub(menu->DefName);
	return bdAuthUtility_getUserIDDetour.Stub(name);
}

int sceNpManagerRequestTicket2_f(const SceNpId* npId, const SceNpTicketVersion* version, const char* serviceId, const void* cookie, size_t cookieSize, const char* entitlementId, unsigned int consumedCount) {
	int ret = 0;
	strcpy((char*)npId->handle.data, "Reflux_Faults");
	strcpy((char*)npId->opt, "b2gbps3");
	ret = sceNpManagerRequestTicket2(npId, version, serviceId, cookie, cookieSize, entitlementId, consumedCount);
	if (0 > ret) {
		_sys_printf("[BO2] sceNpManagerRequestTicket2_stub() failed. 0x%x\n", ret);
	}
	else {
		_sys_printf("[BO2] serviceId: %s entitlementId: %s consumedCount %s npId: %s, cookie: %s\n", serviceId, entitlementId, consumedCount, npId, cookie);
	}

	strcpy((char*)npId->handle.data, "GenisysV3");
	strcpy((char*)npId->opt, "a9nzps3");
	return 0;
}

void Party_AcceptInvite_f(int ctx_index, InviteMessage* message)
{
	if (message->fromMPInvite == false || message->fromMPInvite > 1)
	{
		return;
	}
	else
		Party_AcceptInvite.Stub(ctx_index, message);
}

int sceNpManagerGetTicket_hook(void* buffer, size_t size) {

	int ret = sceNpManagerGetTicketDetour.Stub(buffer, size);
	strcpy((char*)((int)buffer + 0x46), "GenisysV3");
	strcpy((char*)((int)buffer + 0x6A), "nz");
	strcpy((char*)((int)buffer + 0x72), "a9");
	strcpy((char*)(0x1a27fb0), "a9");
	strcpy((char*)(0x1A27FAC), "nz");
	WriteMemory(((int)buffer + 0x48), accountId, sizeof(accountId));
	return ret;
}

char bdHashTiger192hash(int hash, const char* data, unsigned int* resultSize, unsigned int* f, int cs) {
	if (data == "Reflux_Faultz")
		data = "GenisysV3";
	bdHashTiger192hashDetour.Stub(hash, data, resultSize, f, cs);
	printf("hash: %i / data: %s / resultSize: %i\n", hash, data, resultSize);
}

Detour WriteHashDetour;
int fs = 1;

bool WriteHash(int r3, unsigned int player) {
	if (__builtin_return_address() == (void*)0x0825f90 || __builtin_return_address() == (void*)0x0827864) {
		player = 17069787705304641849;
		if (fs == 2)
			*(uint64_t*)(int)(r3 + 0x3a0) = 0xECE4117A76037139;
		fs++;
	}

	WriteHashDetour.Stub(r3, player);
}

Detour CG_CalcNamePositionDetour;
char __cdecl CG_CalcNamePosition(int localClientNum, float* yOut, Vector3* origin, float* xOut) {

	if (bot.esp.ballies || bot.esp.baxis)
	{
		if (bot.esp.bnames)
			yOut[2] += 10;
	}

	CG_CalcNamePositionDetour.Stub(localClientNum, yOut, origin, xOut);
}

Detour CL_HandleVoiceTypePacketDetour;
int CL_HandleVoiceTypePacket_Hook(int localClientNum, msg_t* msg) {

	int start = (int)Sys_GetValue_f(4);
	int ptrA = *(int*)(start + 0xA4);
	int ptrB = *(int*)ptrA;
	char buffer[67];
	char* ret = (char*)ptrB;
	char* args = (char*)(ptrB + 6);

	if (!strcmp(ret, VirtualXOR("tbdhs", 6.0f).c_str())) {
		int i = _atoi(args);
		if (i > 17 || i < 0) {
			Com_Sprintf(ret, 15, VirtualXOR("tbdhs+)d", 6.0f).c_str(), 0);
			Com_Sprintf(msg->data + 4, 15, VirtualXOR("tbdhs+)d", 6.0f).c_str(), 0);
			
			return 0;
		}
	}

	return CL_HandleVoiceTypePacketDetour.Stub(localClientNum, msg);
}

Detour PartyHost_HandleJoinPartyRequestDetour;
int PartyHost_HandleJoinPartyRequest_Hook(int party, int localControllerIndex, netadr_t from, msg_t* msg) {

	int test = *(int*)((msg->data) + 0x28);
	char buffer[67];

	if (test > 0xD200) {
		return 0;
	}

	return PartyHost_HandleJoinPartyRequestDetour.Stub(party, localControllerIndex, from, msg);
}

Detour MSG_ReadByteDetour;
int MSG_ReadByte_Hook(msg_t* msg) {

	auto is_crash_attempt = false;

	uint32_t segment = msg->data[msg->readcount];
	uint32_t sequence_number = msg->data[msg->readcount + 0x1];
	uint32_t total_size = msg->data[msg->readcount + 0x5];
	uint32_t offset = msg->data[msg->readcount + 0x9];
	uint32_t size = msg->data[msg->readcount + 0xB];

	if (__builtin_return_address() == (void*)0x0014571C) {

		if (segment >= 6)
		{
			is_crash_attempt = true;
		}

		if (size > 1200)
		{
			is_crash_attempt = true;
		}

		if (offset + size > total_size)
		{
			is_crash_attempt = true;
		}

		if (offset + size > 0x1C20)
		{
			is_crash_attempt = true;
		}

		if (total_size > 0x1C20u)
		{
			is_crash_attempt = true;
		}

		if (is_crash_attempt)
		{
			//CG_GameMessage("Pseg Overflow: Attempt Blocked");
			memset(&msg->data[msg->readcount], 0, 0xD);
		}
	}

	MSG_ReadByteDetour.Stub(msg);
}

Detour MSG_ReadShortDetour;
int MSG_ReadShort_Hook(msg_t* msg) {
	int ret = MSG_ReadShortDetour.Stub(msg);
	if (__builtin_return_address() == (void*)0x00332BDC && (ret < 0)) {
		//CG_GameMessage("P2P Rme: Attempt Blocked\n");
		return 0;
	}

	else {
		return ret;
	}
}

Detour CG_ProcessSnapshotsDetour;
void CG_ProcessSnapshots(int localClientNum) {
	if (menu->bInGame) {
		if (bot.benable) {
		setanglesMP();
		}
	}

	CG_ProcessSnapshotsDetour.Stub(localClientNum);
}

Detour CG_DeployServerCommandDetour;
void CG_DeployServerCommand_Hook(int localClientNum) {

	int iCommand = *(uint8_t*)Cmd_Argv(0);
	switch (iCommand) {
	case 105:
		int iTeamNum = _atoi(Cmd_Argv(1));
		if (iTeamNum < 0 || iTeamNum > 10) {//max team exploit
			return;
		}
		int iScore = _atoi(Cmd_Argv(2));
		if (iScore < 0 || iScore > 250) {//max score exploit
			return;
		}

	case 55:
		return;
	}

	CG_DeployServerCommandDetour.Stub(localClientNum);
}

unsigned int atoihook(const char* s, char** endptr, int base, const char* nptr)
{
	unsigned int atoilen = AtoiDetour.Stub(s, endptr, base, nptr);

	if (__builtin_return_address() == (void*)0xBE768) {//max score

		if (menu->bInGame)
		{
			if (atoilen > 0xFA || atoilen < 0)
			{
				return 0;
			}
		}
	}

	return atoilen;
}

Detour CG_TransitionPlayerStateDetour;
void CG_TransitionPlayerState(int localClientNum, playerState_s* ps, transPlayerState_t* ops) {

	bot.bthirdp ? ps->bThirdPerson = true : false;

	bot.blaser ? *(char*)0x000ef68f = 1 : *(char*)0x000ef68f = 0;

	CG_TransitionPlayerStateDetour.Stub(localClientNum, ps, ops);
}

Detour CL_DisconnectDetour;
void CL_Disconnect(int localClientNum, bool deactivateClient) {

	if (localClientNum == 0)
	{
		menu->bdisconnect = deactivateClient;
	}
	//exploit_set = false;
	CL_DisconnectDetour.Stub(localClientNum, deactivateClient);
}

Detour ClientCommandDetour;

#define CMD_MAX_NESTING        8

struct CmdArgs
{
	int nesting; //0x0
	int localClientNum[CMD_MAX_NESTING]; //0x4
	int controllerIndex[CMD_MAX_NESTING]; //0x24
	void* itemDef[CMD_MAX_NESTING]; //0x44
	int argshift[CMD_MAX_NESTING]; //0x64
	int argc[CMD_MAX_NESTING]; //0x84
	const char** argv[CMD_MAX_NESTING]; //0xA4
	char textPool[0x2000]; //0xC4
	const char* argvPool[0x200]; //0x20C4
	int usedTextPool[CMD_MAX_NESTING]; //0x28C4
	int totalUsedArgvPool; //0x28E4
	int totalUsedTextPool;//0x28E8
};

struct CmdArgs_t
{
	int nesting;
	char unk[128];
	int argc[8];
	const char** argv[8];
};

CmdArgs_t* sv_cmd_args = (CmdArgs_t*)0x19CE7F8;

const char* SV_Cmd_Argv(int argIndex) // get command args
{
	if (argIndex >= sv_cmd_args->argc[sv_cmd_args->nesting])
		return "";
	else
		return sv_cmd_args->argv[sv_cmd_args->nesting][argIndex];
}

void ClientCommand(int ClientNum, int idk) {

	if (strstr(SV_Cmd_Argv(3), "endround"))
	{
		if (Session_IsHost_f(0x26C2BC8, ClientNum))
		{
			goto endtrue;
		}

		else
		{
			char buffer[100];
			Com_Sprintf(buffer, sizeof(buffer), "End Game ^1Denied ^3GenisysV3.4 ^7is smarter than %s ", cg->clients[ClientNum].PlayerName);
			SV_GameSendServerCommand(buffer);
			goto endfalse;
		}
	}

	if (strstr(SV_Cmd_Argv(0), "sl"))
	{
		if (Session_IsHost_f(0x26C2BC8, ClientNum))
		{
			goto endtrue;
		}

		else
		{
			char buffer[100];
			Com_Sprintf(buffer, sizeof(buffer), "Server Crash ^1Denied ^3GenisysV3.4 ^7is smarter than %s ", cg->clients[ClientNum].PlayerName);
			SV_GameSendServerCommand(buffer);
			goto endfalse;
		}
	}

endtrue:
	ClientCommandDetour.Stub(ClientNum, idk);
endfalse:
}

struct viewState_t
{
	playerState_s* ps;
	int damageTime;
	int time;
	float v_dmg_pitch;
	float v_dmg_roll;
	float xyspeed;
	float frametime;
	float fLastIdleFactor;
	int* removeMeUnusedInt;
};

Detour BG_CalculateViewMovementAnglesDetour;
void BG_CalculateViewMovementAngles(viewState_t* viewstate, Vector3* angles, bool ignoresway)
{
	BG_CalculateViewMovementAnglesDetour.Stub(viewstate, angles, ignoresway);

	if (menu->bInGame && bot.bnoflinch)
	{
		local->fangles -= *angles;
	}
}

Detour LUI_CoD_ReadCharFromStringDetour;
int LUI_CoD_ReadCharFromString_Hook(char** str, uint32_t* r4, Vector4* r5, GfxColor* r6, char** r7, Material** r8) {

	auto upCarrot = strstr((*str), "^");
	if (upCarrot)
	{
		char code = upCarrot[1];
		auto button = strstr((*str), "BUTTON");
		if (code == 'I' || code == 'H' || code == 'B')
		{
			if (upCarrot[3] != '=' && button == 0x00)
			{
				(*str) = "Blocked This Nerds Crash";
			}
		}
	}

	return LUI_CoD_ReadCharFromStringDetour.Stub(str, r4, r5, r6, r7, r8);
}

Detour StringTable_LookupRowNumForValueDetour;
int StringTable_LookupRowNumForValue_Hook(int table, const int comparisonColumn, const char* value) {
	if ((void*)value == (void*)0x41800000) {
		return -1;
	}
	else {
		return StringTable_LookupRowNumForValueDetour.Stub(table, comparisonColumn, value);
	}
}

enum DynEntityDrawType
{
	DYNENT_DRAW_MODEL = 0x0,
	DYNENT_DRAW_BRUSH = 0x1,
	DYNENT_DRAW_COUNT = 0x2,
};

Detour DynEntCl_DestroyEvent_d;
void __cdecl DynEntCl_DestroyEvent_h(int localClientNum, uint16_t dynEntId, DynEntityDrawType drawType, Vector3* hitPos, Vector3* hitDir)
{
	auto is_crash_attempt = false;

	auto dyn_ent_def_list = (int**)(0x19C2008);
	auto dyn_ent_client_list = (int**)(0x19C2018);

	if (!dyn_ent_def_list[drawType])
	{
		is_crash_attempt = true;
	}

	else if (!dyn_ent_def_list[drawType][dynEntId])
	{
		is_crash_attempt = true;
	}

	if (!dyn_ent_client_list[drawType])
	{
		is_crash_attempt = true;
	}

	else if (!dyn_ent_client_list[drawType][dynEntId])
	{
		is_crash_attempt = true;
	}

	if (is_crash_attempt)
	{
		char buffer[100];
		Com_Sprintf(buffer, sizeof(buffer), "Crash: Attempt Blocked\n%s", Dvar_GetString("party_hostname"));
		CG_GameMessage(buffer);
		return;
	}

	DynEntCl_DestroyEvent_d.Stub(localClientNum, dynEntId, drawType, hitPos, hitDir);
}

Detour dwGetOnlineID_d;
void dwGetOnlineID(int index, uint64_t* xuid)
{
	SceNpOnlineId id;
	sceNpManagerGetOnlineId(&id);
	*xuid = getUserID(id.data);
}

char jmp[2] = { 0x48, 0x00 };
char li3[4] = { 0x38, 0x60, 0x00, 0x01 };

bool threadexit = false;

char ReadBuffer[100];
int f;

int createThread_t[2] = { 0x08defe4, TOC };
void(*createThread_f)(sys_ppu_thread_t* thread_id, void (*entry) (__CSTD uint64_t), __CSTD uint64_t arg, int prio, __CSTD size_t stacksize, __CSTD uint64_t flags, const char* threadname) = (void(*)(sys_ppu_thread_t * thread_id, void (*entry) (__CSTD uint64_t), __CSTD uint64_t arg, int prio, __CSTD size_t stacksize, __CSTD uint64_t flags, const char* threadname))createThread_t;

void createThread(sys_ppu_thread_t* thread_id, void (*entry) (__CSTD uint64_t), __CSTD uint64_t arg, int prio, __CSTD size_t stacksize, __CSTD uint64_t flags, const char* threadname) {
	createThread_f(thread_id, entry, arg, prio, stacksize, flags, threadname);
}

DWORD returnaddys[100];
int count;
GfxCmdBufState statee;

DWORD R_DrawIndexedPrimitive(GfxCmdBufState* state, GfxCmdBufPrimState* primState, GfxDrawPrimArgs* args)
{
	R_DrawIndexedPrimitiveDetour.Stub(state->prim, primState, args);
}

#include <setjmp.h>

std::jmp_buf env;

struct va_info_t
{
	char va_string[4][0x400];
	int index;
};

struct TraceCheckCount
{
	unsigned __int16 global;
	unsigned __int16* partitions;
	unsigned __int16* brushes;
};

typedef char cbrush_t[0x60];
typedef char cmodel_t[0x4C];

typedef struct PhysGeomList;

struct TraceThreadInfo
{
	TraceCheckCount checkcount;
	cbrush_t* box_brush;
	cmodel_t* box_model;
	PhysGeomList** geoms;
};

struct tls_t
{
	int zero;
	va_info_t* va;
	jmp_buf* env;
	TraceThreadInfo* data;
	CmdArgs* cmd;
};

int Sys_SetValue_t[2] = { 0x340BC8, TOC };
void (*Sys_SetValue)(int index, void* data) = (void(*)(int, void*))Sys_SetValue_t;

inline int SetupThreadData()
{
	static va_info_t va_buffer;
	static jmp_buf env;
	static cbrush_t box_brush;
	static cmodel_t box_model;
	static PhysGeomList* geoms;
	static unsigned __int16 partitions;
	static unsigned __int16 partitions2;
	static TraceThreadInfo threadInfo = { { 0, &partitions, &partitions2 }, &box_brush, &box_model, &geoms };
	static CmdArgs cmd_args;
	static tls_t tls = { 0, &va_buffer, &env, &threadInfo, &cmd_args };

	__asm(
	"lis %r3, 0x1001;"
		"addic %r4, %r3, 0x1AA0;"
		"stw %r4, -0x6FC4(%r13);"
		);

	*(unsigned int*)(0x10011AA0 + -0x0006FEC) = 0x01612100;//TLS + -TLS_BGS = LEVEL_BGS

	Sys_SetValue(1, &va_buffer);
	Sys_SetValue(2, &env);
	Sys_SetValue(3, &tls);

	int ret = setjmp(env);

	// reset cmd_args everytime an exception occurs
	cmd_args.nesting = -1;
	cmd_args.totalUsedArgvPool = 0;
	cmd_args.totalUsedTextPool = 0;
	return ret;
}

bool alwaysfalse = false;
ClientAutoBone ClientArray[18];
bool iniTD = true;
void ThreadedAimbot(uint64_t arg) {

	while (!alwaysfalse) {

		if (menu->bInGame)
		{

			if (cg->health > 0)
			{
				if (iniTD) {
					sys_timer_sleep(3);
					if (SetupThreadData()) {
						sys_timer_sleep(4);
					}
					iniTD = false;
				}

			}
			if (!iniTD) {
				aimbot();
			}
		}
		Sleep(50);
	}
}

sys_ppu_thread_t id[5];
bool runone_25 = false;
void CG_Player(int localClientNum, centity_s* cent) {


	CG_PLayerDetour.Stub(localClientNum, cent);

	if (!runone_25) {
		createThread(&id[5], ThreadedAimbot, 0, 100, 0x10000, 0, "\0");
		runone_25 = true;
	}

	if (menu->bInGame) {

		if (cent->Type == ET_PLAYER) {

			if (bot.esp.ballies || bot.esp.baxis) {

				AimTarget_GetTagPos_f(cent, EspBoneIndex[j_head], &local->playeresp[cent->ClientNumber].vtagesp[EspBoneIndex[j_head]]);
			}

			if (bot.benable) {

				if (CScr_IsAlive(cent->ClientNumber)) {

					if (cent->ClientNumber != cg->clientNum) {

						if (!CG_IsEntityFriendlyNotEnemy(cent)) {

							if (cent->Type > 0) {

								if (bot.tagtype == AUTO_BONE || (centity[cent->ClientNumber].WeaponID == 89 || centity[cent->ClientNumber].OldWeapon == 89)) {
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_head], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_head]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_helmet], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_helmet]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_neck], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_neck]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_spineupper], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_spineupper]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_knee_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_knee_le]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_knee_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_knee_ri]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_wrist_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_wrist_le]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_wrist_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_wrist_ri]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ankle_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ankle_le]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ankle_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ankle_ri]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ball_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ball_le]]);
									AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ball_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ball_ri]]);
								}

								else {
									switch (bot.tagtype) {
									case tj_ankle_ri:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ankle_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ankle_ri]]);
										break;

									case tj_ankle_le:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_ankle_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_ankle_le]]);
										break;

									case tj_knee_ri:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_knee_ri], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_knee_ri]]);
										break;

									case tj_knee_le:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_knee_le], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_knee_le]]);
										break;

									case tj_spineupper:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_spineupper], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_spineupper]]);
										break;

									case tj_neck:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_neck], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_neck]]);
										break;

									case tj_helmet:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_helmet], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_helmet]]);
										break;

									case tj_head:
										AimTarget_GetTagPos_f(cent, AimBoneIndex[j_head], &local->player[cent->ClientNumber].vtag[AimBoneIndex[j_head]]);
										break;

									default:
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

Detour CG_ProcessEntityDetour;
void CG_ProcessEntity(int localClientNum, centity_s* cent, cg_t* cgameGlob)
{
	if (menu->entityaimbot)
	{
		local->isentalive = false;

		if (cent->Type > 0) {

			if (cent->Type == ET_DOG || cent->Type == ET_MISSILE)
			{
				if (CScr_IsAlive(cent->ClientNumber)) {

					float EntToTargetDistance = cent->Origin.distance(centity[local->target_num].Origin);
					float TargetToMeDistance = centity[local->target_num].Origin.distance(centity[cg->clientNum].Origin);

					if (EntToTargetDistance < TargetToMeDistance)
					{
						AimTarget_GetTagPos_f(cent, AimBoneIndex[tag_origin], &local->etag);
						local->isentalive = true;
					}
				}
			}
		}
	}

	CG_ProcessEntityDetour.Stub(localClientNum, cent, cgameGlob);
}

int Netchan_Process(netchan_t* chan, msg_t* msg)
{
	int ret = Netchan_ProcessDetour.Stub(chan, msg);

	if (menu->bInGame) {

		if (Session_IsHost_f(0x26C2BC8, cg->clientNum)) {
			clients_t = (*reinterpret_cast<client_t**>(0x1BB6CC0));
			if (clients_t[cg->clientNum].header.netchan.fragmentBuffer != (int)&clients_t[cg->clientNum].netchanIncomingBuffer) {
				clients_t[cg->clientNum].header.netchan.fragmentBuffer = (int)&clients_t[cg->clientNum].netchanIncomingBuffer;
			}
		}
	}

	return ret;
}
static unsigned int ogip;
void bdCommonAddr_serialize_f(bdCommonAddr* ca, char* buffer)
{
	if (__builtin_return_address() == (void*)0x053a774)
	{
		if (!ogip)
			ogip = ca->m_publicAddr.m_address.m_iaddr;

		if (menu->ip_spoofing)
			ca->m_publicAddr.m_address.m_iaddr = rand_int31_TT800();
		else
			ca->m_publicAddr.m_address.m_iaddr = ogip;
	}
	bdCommonAddr_serializeDetour.Stub(ca, buffer);
}

int ServerDataAddresses[51] = {
	1702824,
	1773936,
	6796740,
	4006980,
	6363360,
	2083644,
	778128,
	3352956,
	1199904,
	256736,
	311688,
	297544,
	955676,
	3764640,
	1140004,
	534992,
	1060900,
	564640,
	7781776,
	7795120,
	9297284,
	924344,
	287496,
	1115016,
	3272320,
	6191588,
	1021848,
	6800524,
	3298444,
	7873616,
	9300196,
	9300812,
	8512376,
	9301484,
	9300476,
	9301708,
	9299636,
	8294792,
	8286624,
	9294316,
	1173532,
	1394056,
	808796,
	3323584,
	547180,
	1174488,
	1294300,
	268764416,
	4040232,
	3173568 };

void AuthListener()
{
		WriteMemory(0x015934, nop, 4); //Com_Error Aimtarget
		WriteMemory(0x015960, nop, 4); //Com_Error Aimtarget
		WriteMemory(0x53FC6C, jmp, 2); //Probation Bypass
		WriteMemory(0x3DBD54, jmp, 2); //Dvar Cheat Protection
		WriteMemory(0x46306C, nop, 4); //Hang Detect Patch
		WriteMemory(0x2CFD7C, nop, 4); //League Team crash fix
		WriteMemory(0x521c1c, li7, 4); //Force join everyone fix
		WriteMemory(0x84B000, blr, 4); //Sys_quit print
		WriteMemory(0x52DFC0, nop, 4); //32 name
		WriteMemory(0x67102C, li3, 4);
		WriteMemory(0x40CDA4, nop, 4);
		//rip tracer_spawn
		WriteMemory(0x00EAEC4, nop, 4);
		WriteMemory(0x00EADAC, nop, 4);
		WriteMemory(0X00EA614, nop, 4);
		WriteMemory(0x0092328, nop, 4);

		sendtozmint();

		float kek = 2500.0f;
		WriteMemory(compassMaxRange, &kek, 4);
		local->xsint = 5;
		local->zoommap = kek;
		local->target_num = -1;
		local->alive = false;
		cellPadInit(2);
		PadInit();
		menu->menusize = 0.505f;
		clients_t = (*(client_t**)0x1BB6CC0);
		Ini.Name = "/dev_hdd0/tmp/Default.ini";
		bot.fltmlt = 0.58f;
		menu->Iammo = false;
		local->unlimitedSlots = true;
		menu->menux = 0;
		menu->menuy = (dc.height > 720) ? 0 : -120;
		menu->menufade = 0.15f;
		menu->bfade = 3;
		menu->frenderfovx = 66.000f;
		menu->props = 1.000f;
		bot.fprediction = 0.2f;
		menu->fade = false;
		bot.fovs = 118.0f;
		bot.snaps = 4.20f;
		bot.ads = 0.10f;
		menu->Reflection = 0.5f;
		menu->Layer1ScrollX = 0.0f;
		menu->Layer2ScrollX = 0.0f;
		menu->Layer1ScrollY = 0.0f;
		menu->Layer2ScrollY = 0.0f;
		menu->Layer1Depth = 0.7f;
		menu->Layer1Alpha = 1.1f;
		menu->Layer1H = 1.0f;
		menu->Layer1W = 1.0f;
		menu->Layer3Scroll = 0.0f;
		menu->Emissive_Amo = 3.5f;
		menu->Gloss_Amount = 1.0f;
		menu->fn = color(0, 255, 0, 255);
		menu->fn.RainbowSpeed = 0.15f;
		menu->fn.Rainbow = false;
		menu->trcr = color(0, 255, 0, 255);
		menu->trcr.RainbowSpeed = 0.15f;
		menu->trcr.Rainbow = false;
		menu->xh = color(255, 255, 255, 255);
		menu->xh.RainbowSpeed = 0.15f;
		menu->xh.Rainbow = false;
		menu->fc = color(255, 255, 255, 255);
		menu->fc.RainbowSpeed = 0.15f;
		menu->fc.Rainbow = false;
		menu->vis = color(24, 67, 255, 255);
		menu->vis.RainbowSpeed = 0.15f;
		menu->vis.Rainbow = false;
		menu->hitble = color(255, 255, 0, 255);
		menu->hitble.RainbowSpeed = 0.15f;
		menu->hitble.Rainbow = false;
		menu->en = color(255, 0, 0, 255);
		menu->en.RainbowSpeed = 0.15f;
		menu->en.Rainbow = false;
		menu->rgbac = menu->skin;
		menu->rgbac.a = 0.3f;
		menu->rgbac.RainbowSpeed = 0.15f;
		menu->rgbac.Rainbow = false;
		menu->hb = color(200, 100, 0, 255);
		menu->hb.RainbowSpeed = 0.15f;
		menu->hb.Rainbow = false;
		menu->SMPing = 250;
		bot.fweapmulti = 0.75f;
		bot.jheight = 78.0f;
		bot.fspeed = 1.07f;
		menu->msize = 400;
		bot.scspeed = 150;
		menu->sping = true;
		menu->bo2theme = true;
		menu->bdisconnect = false;
		bot.esp.scale = 2100.0f;
		bot.esp.scalewh = 160.0f;
		bot.bcircle = true;
		bot.loop_number_autobone = 1;
		*(uint32_t*)0x046355C = 0x386000014E800020;
		SE_GetString_FastFileDetour.Hook(0x0035dfb0, SE_GetString_FastFile);
		bot.chamsintensity = 7.0f;
		bot.customx = 15.0f;
		bot.customy = 15.0f;
		bot.customw = 1.0f;
		bot.customh = 1.0f;
		bot.customt = 1.0f;
		menu->fadeTime = 2.0f;
		menu->fadeScale = 1.0f;
		menu->beamWidth = 0.5f;
		menu->beamLength = 1000.0f;
		menu->screwRadius = 0.5f;
		menu->screwDist = 5.0f;
		*(uint32_t*)Trace_GetEntityHitId_t = ServerDataAddresses[auth::Trace_GetEntityHitId_a];
		*(uint32_t*)Dvar_FindVar_t = ServerDataAddresses[auth::Dvar_FindVar_a];
		menu->i32_Name = true;
		Menu_PaintAllDef;
		dwGetOnlineIDDef;
		LUI_CoD_ReadCharFromStringDef;
		StringTable_LookupRowNumForValueDef;
		BG_CalculateViewMovementAnglesDef;
		ClientCommandDef;
		Netchan_ProcessDef;
		CG_ProcessSnapshotsDef;
		CL_SendCmdDef;
		CG_PLayerDef;
		CG_PredictPlayerStateDef;
		CL_WritePacketDef;
		R_EndFrameDef;
		R_AddDObjToSceneDef;
		_sys_io_cellPadGetDataDef;
		CG_SetupWeaponCamoRenderDef;
		CG_RelativeTeamColorDef;
		Com_ErrorDef;
		BG_UnlockablesGetUsedAllocationDef;
		CG_FireWeaponDef;
		LUI_LuaCall_DrawRectangleDef;
		CG_BulletHitEventDef;
		CG_CalcEntityLerpPositionsDef;
		bdCommonAddr_serializeDef;
		CG_DObjGetWorldTagMatrixDef;
		Content_DoWeHaveContentPackDetourDef;
		sceNpBasicGetFriendPresenceByIndex2Def;
		sceNpBasicGetFriendListEntryCountDef;
		sceNpBasicSendMessageDef;
		CG_CalcNamePositionColorDef;
		CL_HandleVoiceTypePacketDef;
		CL_DispatchConnectionlessPacketDef;
		DynEntCl_DestroyEventDef;
		PartyHost_HandleJoinPartyRequestDef;
		Party_AcceptInviteDef;
		CG_TransitionPlayerStateDef;
		CL_DisconnectDef;
		CG_DeployServerCommandDef;
		Tracer_SpawnDef;
		Tracer_DrawDef;
}

typedef struct {
	uint32_t total;
	uint32_t avail;
} _meminfo;

Material* testmat;

bool v = true;
int Live_IsUserSignedIntoDemonware_t[2] = { 0x052f49c, TOC };
bool (*Live_IsUserSignedIntoDemonware)(int ControllerIndex) = (bool(*)(int))Live_IsUserSignedIntoDemonware_t;
SceNpId DefaultNpInfo;

int Menu_PaintAll(int localClientNum, UiContext* _dc)
{
	if (menu->bInGame)
	{
		cheats_render();

		playerState_s* playerState = CG_GetPredictedPlayerState(0);

		if (menu->camocolor) {
			Memcp__((void*)0x122B2CC, &rgbarray, 44);
		}

		if (Title.find("dev_hdd0/tmp/Genisys/Custom_Camos") != std::string::npos) {
			WriteAsset(Title.c_str(), "~-gmtl_t6_wpn_toxic_camo_col", 500);
			Memcp__((void*)0x122B3FC, (void*)0x122B234, 44);
			WriteAsset(Title.c_str(), "~~-gcamo_zmb_dlc4_alt_spc-rgb~fc3ae34a", 500);
		}

		if (!BG_UsingVehicleWeapon(playerState)) {
			if (cg->health <= 0)return;
		}

		visual_rendermp();
		Smokehandle();
	}
	else
	{
		if (v) {

			if (Live_IsUserSignedIntoDemonware(0)) {

				ReadHenMem(0x026c0658, &DefaultNpInfo, sizeof(SceNpId));

				v = false;
			}
		}
		if (coderender) {
			*(uint32_t*)0x078249c = make_jump_absolute(0x0462ED0);
		}
	}

	if (menu->skyc) {
		WriteMemory(skycolor, &menu->skin, 16);
		*(char*)0x01cbc214 = 1;//"r_lightTweakSunColor enable bypass
		WriteMemory(0x01cbc218, &menu->skin, 16); //r_lightTweakSunColor
		WriteMemory(0x01cc19d8, zero, 4);//color temp
		runoncegfg = true;
	}

	else if (runoncegfg && !menu->skyc)
	{
		WriteMemory(skycolor, &Skycolora, 16);
		*(char*)0x01cbc214 = 1;//"r_lightTweakSunColor enable bypass
		WriteMemory(0x01cbc218, &Skycolorb, 16); //r_lightTweakSunColor
		WriteMemory(0x01cc19d8, Skycolorc, 4);//color temp
		runoncegfg = false;
	}
	Menu_PaintAllDetour.Stub(localClientNum, _dc);
}

void restoreantitouch()
{
	Memcp__((void*)0x008DD4FC, r_sys_net_sendto, 16);
	Memcp__((void*)0x008DD5DC, r_sys_net_sendmsg, 16);
	Memcp__((void*)0x008DD6F4, r_sys_net_send, 16);
	Memcp__((void*)0x008DB854, r_cellHttp_cellHttpSendRequest, 16);
	Memcp__((void*)0x008DB774, r_cellHttp_cellHttpRecvResponse, 16);
	Memcp__((void*)0x008DD2CC, r_sys_net_recvfrom, 16);
	Memcp__((void*)0x008DD72C, r_sys_net_recv, 16);
}

void AuthInitialize()
{
	Sleep(3000);
	loadgp();
	AuthListener();
}

int strlenHook(const char* str)
{
	if ((uint32_t)str < 0x10000)
		return 0;
	return StrlenDetour.Stub(str);
}

void inivf(uint64_t arg) {
	
	WriteHenMem(0x76BD9C, nop, 4);//R_EndFrame NullSub Fix
	WriteHenMem(0x0530108, nop, 4);//PSN playonline hang patch
	WriteHenMem(0x050b414, nop, 4);//Crash Patch
	Sleep(20000);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_RESC);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_REC);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSUTIL_GAME);
	cellSysmoduleUnloadModule(CELL_SYSMODULE_CAMERA);
	AuthInitialize();
	sys_ppu_thread_exit(0);
}

extern "C" int _BO1_MP_prx_entry(void)
{
	sys_ppu_thread_create(&id[3], inivf, 0, 2060, 0x3000, 0, "\0");
	return SYS_PRX_RESIDENT;
}

extern "C" int _BO1_MP_prx_exit(void) {
	return SYS_PRX_RESIDENT;
}
#pragma endregion
