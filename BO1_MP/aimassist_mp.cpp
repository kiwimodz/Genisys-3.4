#include<Includes.h>

char nop2[] = { 0x60, 0x00, 0x00, 0x00 };
char recss[] = { 0x4B, 0xFF, 0xE6, 0x09 };
char recsss[] = { 0xF8, 0x21, 0xFF, 0x21 };
char stdu[] = { 0xF8, 0x21, 0xFF, 0x21 };
char blr_[] = { 0x4E, 0x80, 0x00, 0x20 };
char rec[] = { 0x48, 0x50, 0x6D, 0x65 };
char reck[] = { 0x4B, 0xFF, 0x2F, 0xDD };
char reckf[] = { 0x4B, 0xFF, 0xD1, 0x15 };

color NavyBlue = { 0, 0.2, 0.4, 1 };
color White = { 1, 1, 1, 1 };
char Nop[] = { 0x60, 0x00, 0x00, 0x00 };
char Restore32[] = { 0x41, 0x81, 0x00, 0x08 };
char nightcolor[16] = { 0x3F, 0x7C, 0xAB, 0x93, 0x3E, 0xDD, 0x57, 0x15, 0xBC, 0x0B, 0xBD, 0x38, 0x00, 0x00, 0x00, 0x00 };

void noshit() {
	PartyTime();
	WriteMemory(0x611288, bot.bnosway ? nop2 : recss, 4);
	WriteMemory(0xF9E54, bot.bnorec ? nop2 : rec, 4);//no recoil
	WriteMemory(0xF05FC, bot.bnokick ? nop2 : reck, 4);//no kick
	WriteMemory(0x6055D0, menu->Iammo ? nop2 : reckf, 4);//Iammo
	//bot.bnoflinch ? WriteMemory(0x0085588, blr_, 4) : WriteMemory(0x0085588, stdu, 4);
	bot.bnobob ? *(float*)0x006108a8 = 0.0f : *(float*)0x06108a8 = 2.0f;
	bot.bnobob ? *(float*)0x006108a4 = 0.0f : *(float*)0x06108a4 = 1.0f;
	bot.bnobob ? *(float*)0x006108bc = 0.0f : *(float*)0x06108bc = 3.14159f;
	bot.bnobob ? *(float*)0x006108c0 = 0.0f : *(float*)0x06108c0 = 6.28319f;
	bot.bnobob ? *(float*)0x006108c4 = 0.0f : *(float*)0x06108c4 = 0.16f;
	bot.bfullbright ? *(int*)0x2F95680 = 1 : *(int*)0x2F95680 = 3;
	bot.hidename ? *(uint8_t*)0x26C0703 = 0x04 : *(uint8_t*)0x26C0703 = 0x00;
	bot.bantif ? *(int*)0x67B824 = 0x60000000 : *(int*)0x67B824 = 0x909A0000;
	bot.bantif ? *(int*)0x67B798 = 0x486CDD59 : *(int*)0x67B798 = 0x481C6E19;
	bot.bantif ? *(int*)0x67B820 = 0x486CDC99 : *(int*)0x67B820 = 0x38600001;
	bot.noflsh ? *(int*)0x0DA580 = 0x60000000 : *(int*)0x0DA580 = 0x4BFE55A1;
	bot.noflsh ? *(int*)0x0DA5B0 = 0x60000000 : *(int*)0x0DA5B0 = 0x4BFE5781;
	bot.noflsh ? *(int*)0x0d900c = 0x60000000 : *(int*)0x0d900c = 0x4BFE73ED;

	if (menu->nightmode) {
		//*(int*)0x07599D0 = 0x60000000;
		*(int*)0x01cc1018 = 0x01000000;//0x2B28CC4 <-- pointer from r_exposureTweak
		*(int*)0x01CC1078 = 0x40900000;//r_exposureValue
		//*(int*)0x01CC19D8 = 0xffffffff;
		*(int*)0x01cbc214 = 0x01000000;//r_lighttweaksuncolor
		WriteMemory(0x01cbc218, &NavyBlue, 16);//r_lighttweaksuncolor
		WriteMemory(skycolor, &nightcolor, 16);//skycolor
	}

	else {
		Cbuf_AddText("reset r_exposureTweak;reset r_exposureValue;reset r_lighttweaksuncolor;");
		//*(int*)0x01CC19D8 = 0x45CB2000;
	}

	if (menu->i32_Name) {
		WriteMemory(0x52DFC0, &Nop, 4);
	}

	else {
		WriteMemory(0x52DFC0, &Restore32, 4);
	}
}

#pragma region aim functions
void camo_type(int type) { bot.camotype = (camotype_t)type; }
void player_type(int type) { bot.playertype = (playertype_t)type; }

void anti_typeFX(int type) { bot.antitypeX[FIRING] = (antitype_tX)type; }
void anti_typeSX(int type) { bot.antitypeX[SPRINTING] = (antitype_tX)type; }
void anti_typeCX(int type) { bot.antitypeX[CROUCHING] = (antitype_tX)type; }
void anti_typeMX(int type) { bot.antitypeX[MOVING] = (antitype_tX)type; }
void anti_typeSTX(int type) { bot.antitypeX[STANDING] = (antitype_tX)type; }

void anti_typeFY(int type) { bot.antitypeY[FIRING] = (antitype_tY)type; }
void anti_typeSY(int type) { bot.antitypeY[SPRINTING] = (antitype_tY)type; }
void anti_typeCY(int type) { bot.antitypeY[CROUCHING] = (antitype_tY)type; }
void anti_typeMY(int type) { bot.antitypeY[MOVING] = (antitype_tY)type; }
void anti_typeSTY(int type) { bot.antitypeY[STANDING] = (antitype_tY)type; }

void aim_type(int type) { bot.aimtype = (aimtype_t)type; }
void tag_type(int type) { bot.tagtype = (tagtype_t)type; }
void key_type(int type) { bot.keytype = (keytype_t)type; }

void enable_hvh() {
	ReadFromIniFile("/dev_hdd0/tmp/Genisys/HvH.ini");
	noshit();
	menu->flagx = 44;
	Mshit.ch = "Status: ^2Loaded";
}

void ResetConfig() {
	ReadFromIniFile("/dev_hdd0/tmp/Genisys/Default.ini");
	noshit();
	menu->flagx = 0;
	Mshit.ch = "Status: ^2Reset";
}

#pragma endregion
#pragma region autowall

int ThreadInfo1;
int BG_GetWeaponVariantDef_t[2] = { 0x606EE0, TOC };
WeaponVariantDef* (*BG_GetWeaponVariantDef_f)(unsigned int r1) = (WeaponVariantDef * (*)(unsigned int))BG_GetWeaponVariantDef_t;
WeaponVariantDef* BG_GetWeaponVariantDef(unsigned int weapon) {
	return BG_GetWeaponVariantDef_f(weapon);
}

int BG_GetWeaponDef_t[2] = { 0x606F08, TOC };
WeaponDef* (*BG_GetWeaponDef_f)(int r1) = (WeaponDef * (*)(int))BG_GetWeaponDef_t;

WeaponDef* BG_GetWeaponDef(int Weapon) {
	return BG_GetWeaponDef_f(Weapon);
}

int BulletTrace_t[2] = { 0xE9FBC, TOC };
bool(*BulletTrace_f)(int localClientNum, BulletFireParams* bulletFireParams, WeaponDef* weaponIndex, centity_s* centityAttacker, BulletTraceResults* btr, int surfacetype, bool simulate) = (bool(*)(int, BulletFireParams*, WeaponDef*, centity_s*, BulletTraceResults*, int, bool))BulletTrace_t;

char blrx[0x4] = { 0x60, 0x00, 0x00, 0x00 };
char restthread[0x4] = { 0x48, 0x38, 0x4C, 0x79 };
bool BulletTrace(int localClientNum, BulletFireParams* bulletFireParams, WeaponDef* weaponIndex, centity_s* centityAttacker, BulletTraceResults* btr, int surfacetype, bool simulate) {
	bool ret = BulletTrace_f(localClientNum, bulletFireParams, weaponIndex, centityAttacker, btr, surfacetype, simulate);
	return ret;
}

int idk1_t[2] = { 0x3CFD98, TOC };
void(*idk1_f)(float* r1, float* r2, float* r3, float* r4) = (void(*)(float*, float*, float*, float*))idk1_t;

void anglevectors(Vector3 v, Vector3* forward, Vector3* right, Vector3* up) {
	float fv[] = { v.x, v.y, v.z };
	float vf[3], vr[3], vu[3];
	idk1_f(fv, vf, vr, vu);
	*forward = Vector3(vf[0], vf[1], vf[2]);
	*right = Vector3(vr[0], vr[1], vr[2]);
	*up = Vector3(vu[0], vu[1], vu[2]);
}

#define __PAIR__(high, low) (((unsigned long)(high)<<sizeof(high)*8) | low)

int BG_AdvanceTrace_t[2] = { BG_AdvanceTrace_a, TOC };
bool(*BG_AdvanceTrace_f)(BulletFireParams* bp, BulletTraceResults* br, float dist) = (bool(*)(BulletFireParams*, BulletTraceResults*, float))BG_AdvanceTrace_t;

bool __cdecl BG_AdvanceTrace(BulletFireParams* bp, BulletTraceResults* br, float dist) {
	return BG_AdvanceTrace_f(bp, br, dist);
}

int BG_GetFireType_t[2] = { 0x60AD94, TOC };
weapFireType_t(*BG_GetFireType)(int weapon) = (weapFireType_t(*)(int))BG_GetFireType_t;
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a,b)(((a) < (b)) ? (a) : (b))
int BG_GetSurfacePenetrationDepth_t[2] = { 0x05EFFC0, TOC };
float (*BG_GetSurfacePenetrationDepth_f)(PenetrateType pentype, int surfaceType) = (float(*)(PenetrateType, int))BG_GetSurfacePenetrationDepth_t;

float BG_GetSurfacePenetrationDepth(PenetrateType pentype, int surfaceType) {

	if (surfaceType >= 0x20) {
		return;
	}
	return  BG_GetSurfacePenetrationDepth_f(pentype, surfaceType);;
}

float Get3dDistance(Vector3 myCoords, Vector3 enemyCoords) {
	return sqrtf(
		powf(double(enemyCoords.x - myCoords.x), 2.0) +
		powf(double(enemyCoords.y - myCoords.y), 2.0) +
		powf(double(enemyCoords.z - myCoords.z), 2.0)
	);
}

void _VectorMA(const Vector3 veca, float scale, const Vector3 vecb, Vector3 vecc) {
	vecc.x = veca.x + scale * vecb.x;
	vecc.y = veca.y + scale * vecb.y;
	vecc.z = veca.z + scale * vecb.z;
}

double __cdecl Vec3DistanceSq(const float* p1, const float* p2) {
	float v_4; // ST04_4@1
	float v_8; // ST08_4@1

	v_4 = p2[1] - p1[1];
	v_8 = p2[2] - p1[2];
	return v_8 * v_8 + v_4 * v_4 + (float)(*p2 - *p1) * (float)(*p2 - *p1);
}

double __cdecl Abs(const float* v) {
	return (float)sqrtf((float)((float)((float)(*v * *v) + (float)(v[1] * v[1])) + (float)(v[2] * v[2])));
}

int Trace_GetEntityHitId_t[2] = { 0, TOC };
int(*Trace_GetEntityHitId_f)(trace_t* trace) = (int(*)(trace_t*))Trace_GetEntityHitId_t;

int __cdecl Trace_GetEntityHitId(trace_t* trace) {
	return Trace_GetEntityHitId_f(trace);
}

#define SLODWORD(x)  (*((int*)&(x)))

double __cdecl Vec3Distance(Vector3* v1, Vector3* v2) {
	Vector3 dir; // [sp+4h] [bp-Ch]@1

	dir.x = v2 - v1;
	dir.y = v2->y - v1->y;
	dir.z = v2->z - v1->z;
	return Abs((const float*)&dir);
}

const double XM_PI = 3.14;
void VectorAngles(Vector3& forward, Vector3& angles) {
	float tmp, yaw, pitch;

	if (forward.z == 0 && forward.x == 0) {
		yaw = 0;

		if (forward.z > 0)
			pitch = 90;
		else
			pitch = 270;
	} else {
		yaw = (atan2f(forward.z, -forward.x) * 180 / XM_PI) - 90;

		if (yaw < 0)
			yaw += 360;

		tmp = sqrtf(forward.x * forward.x + forward.z * forward.z);
		pitch = (atan2f(forward.y, tmp) * 180 / XM_PI);

		if (pitch < 0)
			pitch += 360;
	}

	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
}

int Com_SurfaceTypeOofName_t[2] = { 0x3E7ED8, TOC };
String(*Com_SurfaceTypeOofName_f)(int iTypeIndex) = (String(*)(int iTypeIndex))Com_SurfaceTypeOofName_t;

String Com_SurfaceTypeOofName(int index) {
	return Com_SurfaceTypeOofName_f(index);
}

int Com_SurfaceTypeFromName_t[2] = { 0x3E7E08, TOC };
int (*Com_SurfaceTypeFromName_f)(const char* name) = (int(*)(const char* name))Com_SurfaceTypeFromName_t;

int BG_GetPenetrateType_t[2] = { 0x60DF2C, TOC };
PenetrateType(*BG_GetPenetrateType_f)(int weapon) = (PenetrateType(*)(int weapon))BG_GetPenetrateType_t;

PenetrateType __cdecl BG_GetPenetrateType(int weapon) {
	return BG_GetPenetrateType_f(weapon);
}

int BG_GetPerkIndexForName_t[2] = { 0x05C8E80, TOC };
unsigned int(*BG_GetPerkIndexForName_f)(const char* perkName) = (unsigned int(*)(const char* perkName))BG_GetPerkIndexForName_t;

int BG_GetPerkNameForIndex_t[2] = { 0x5C8EE8, TOC };
const char* (*BG_GetPerkNameForIndex_f)(unsigned int perkIndex) = (const char* (*)(unsigned int perkIndexe))BG_GetPerkNameForIndex_t;

unsigned int BG_GetPerkIndexForName(const char* perkName) {
	return BG_GetPerkIndexForName_f(perkName);
}

const char* __cdecl BG_GetPerkNameForIndex(unsigned int perkIndex) {
	return BG_GetPerkNameForIndex_f(perkIndex);
}

int BG_WeaponHasPerk_t[2] = { 0x05C97C8, TOC };
char(*BG_WeaponHasPerk_f)(int weapon, unsigned int perkIndexn) = (char(*)(int weapon, unsigned int perkIndex))BG_WeaponHasPerk_t;

char __cdecl HasPerk(int weapon, unsigned int perkIndex) {
	return BG_WeaponHasPerk_f(weapon, perkIndex);
}

char resetammo[0x4] = { 0x4B, 0xFF, 0xD1, 0x15 };

int BG_GetWeaponHitLocationMultiplier_t[2] = { 0x060eda0, TOC };
float(*BG_GetWeaponHitLocationMultiplier)(int weapon, short hitLoc) = (float(*)(int, short))BG_GetWeaponHitLocationMultiplier_t;

int BG_GetWeaponDamageForRange_t[2] = { 0x060a908, TOC };
float(*BG_GetWeaponDamageForRange)(int weapon, Vector3* start, Vector3* end) = (float(*)(int, Vector3*, Vector3*))BG_GetWeaponDamageForRange_t;

float DotProduct1(Vector3 hax, Vector3 Vector) {
	return (hax.x * Vector.x) + (hax.y * Vector.y) + (hax.z * Vector.z);
}

int CG_ShouldSimulateBulletFire_t[2] = { 0xEA788, TOC };
bool(*CG_ShouldSimulateBulletFire)(int client, BulletFireParams* bp) = (bool(*)(int, BulletFireParams*))CG_ShouldSimulateBulletFire_t;

int EntityIsDeployedRiotshield_t[2] = { 0x06bf0e0, TOC };
int(*EntityIsDeployedRiotshield)(centity_s* cent) = (int(*)(centity_s*))EntityIsDeployedRiotshield_t;

bool HitRiotshield(BulletTraceResults* traceresults) {
	if (traceresults->ignoreHitEnt)
		return false;

	if (traceresults->trace.partGroup == 20)
		return true;

	int wHitID = Trace_GetEntityHitId(&traceresults->trace);

	if (wHitID != 1022) {
		if (EntityIsDeployedRiotshield(&centity[wHitID])) {
			return true;
		}
	}

	return false;
}

#define VectorLength(a)         sqrtf(POW((a).x)+POW((a).y)+POW((a).z))
#define VectorNormalize(a)      {float l = VectorLength(a); (a).x /= l; (a).y /= l; (a).z /= l;}

int  BG_GetDamageRangeScale_t[2] = { 0x060A890  , TOC };
float (*BG_GetDamageRangeScale_f)(int weapon) = (float (*)(int)) BG_GetDamageRangeScale_t;

bool weapon_is_buckshot() {
	auto* weapon_def = BG_GetWeaponDef(centity[cg->clientNum].WeaponID);
	if (weapon_def && (weapon_def->weaponClass == 3 || weapon_def->weaponClass == 13))
		return true;

	return false;
}

float get_bullet_range() {
	if (weapon_is_buckshot()) {
		auto* weapon_def = BG_GetWeaponDef(centity[cg->clientNum].WeaponID);
		auto min_damage = BG_GetDamageRangeScale_f(centity[cg->clientNum].WeaponID) * weapon_def->damageRange[5];

		return std::min(min_damage, min_damage);
	}

	return Dvar_FindVar("bulletrange")->current.value;
}

bool CG_SimulateBulletFire_Internal(BulletFireParams* bp, BulletTraceResults* br, Vector3 end, int target) {
	BulletTraceResults backbr;

	memset(&backbr.trace.normal, 0, 16);

	memset(bp, 0, sizeof(BulletFireParams));

	memset(br, 0, sizeof(BulletTraceResults));

	auto weapon = cg->playerstate.weapon;

	if (!weapon) return false;

	auto* weapverintDef = BG_GetWeaponVariantDef(weapon);

	if (!weapverintDef) return false;

	auto* weapDef = BG_GetWeaponDef(weapon);

	if (!weapDef) return false;

	auto* cent = &centity[cg->clientNum];

	auto penetrationCount = Dvar_FindVar("penetrationCount");

	auto perk_bulletPenetrationMultiplier = Dvar_FindVar("perk_bulletPenetrationMultiplier");

	auto bullet_penetrationMinFxDist = Dvar_FindVar("bullet_penetrationMinFxDist");

	PenetrateType pentype = BG_GetPenetrateType(weapon);

	bp->damageMultiplier = 1.00f;

	bp->worldEntNum = 1022;

	bp->skipNum = cg->clientNum;

	bp->methodOfDeath = (weapDef->bRifleBullet != 0) + 1;

	bp->origStart = local->vorigin;

	bp->start = local->vorigin;

	bp->end = end;

	bp->dir = bp->end - bp->start;

	VectorNormalize(bp->dir);

	if (get_bullet_range() < local->vorigin.distance(end))
		return false;

	bool fronttrace = BulletTrace(0, bp, weapDef, cent, br, 0, true);

	if (!fronttrace || HitRiotshield(br))
		return false;

	if (Trace_GetEntityHitId(&br->trace) == target) {
		if (bot.bvisible)
			return true;
	}

	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	if (!playerState)
		return false;

	if (BG_UsingVehicleWeapon(playerState))
		return false;

	if (bot.bvisible && !bot.bautowall)
		return false;

	Vector3 lastHitPos;

	if (br->trace.startsolid == 0) {
		int NumOfLoops = 5;

		if (BG_GetFireType(weapon) != 8)
			NumOfLoops = penetrationCount->current.integer;

		float fmjMultiplier = perk_bulletPenetrationMultiplier->current.value;

		float minFXDist = bullet_penetrationMinFxDist->current.value;

		minFXDist = (minFXDist * minFXDist);

		for (int i = 0; i < NumOfLoops && fronttrace; i++) {
			float frontsurfaceDepth = BG_GetSurfacePenetrationDepth_f(pentype, br->surfaceType);

			if (HasPerk(weapon, 6))
				frontsurfaceDepth = frontsurfaceDepth * fmjMultiplier;

			if (frontsurfaceDepth <= 0.0f)
				return false;

			lastHitPos = br->hitPos;

			if (!BG_AdvanceTrace(bp, br, 0.135f))
				break;

			fronttrace = BulletTrace(0, bp, weapDef, cent, br, br->surfaceType, true);

			if (HitRiotshield(br)) return false;

			BulletFireParams backwallbp;

			memcpy(&backwallbp, bp, sizeof(BulletFireParams));

			memcpy(&backbr, br, sizeof(BulletTraceResults));

			backwallbp.dir = bp->dir * -1.0f;

			backwallbp.start = bp->end;

			backwallbp.end = (backwallbp.dir * 0.01f) + lastHitPos;

			backbr.trace.normal *= -1.0f;

			if (fronttrace)
				BG_AdvanceTrace(&backwallbp, &backbr, 0.01f);

			bool backtrace = BulletTrace(0, &backwallbp, weapDef, cent, &backbr, backbr.surfaceType, true);

			if (HitRiotshield(&backbr)) return false;

			bool allsolid = false;

			allsolid = (backtrace && backbr.trace.allsolid) || (br->trace.startsolid && backbr.trace.startsolid);

			if (!backtrace && !allsolid) {
				Vector3 vec_length = lastHitPos - br->hitPos;

				float length = VectorLength(vec_length);

				if (!br->trace.allsolid && (minFXDist < length)) {
					if (Trace_GetEntityHitId(&br->trace) == target)
						return true;
				}

				if (Trace_GetEntityHitId(&br->trace) == target)
					return true;
			} else {
				float tempdepth;

				if (allsolid)
					tempdepth = VectorLength(backwallbp.end - backwallbp.start);

				else
					tempdepth = VectorLength(lastHitPos - backbr.hitPos);

				float depth = 1.0f;
				if (1.0f <= tempdepth)
					depth = tempdepth;

				if (backtrace) {
					float backSurfaceDepth = BG_GetSurfacePenetrationDepth_f(pentype, backbr.surfaceType);

					if (HasPerk(weapon, 6))
						backSurfaceDepth = backSurfaceDepth * fmjMultiplier;

					if (backSurfaceDepth - frontsurfaceDepth <= 0.0f)
						frontsurfaceDepth = backSurfaceDepth;

					if (frontsurfaceDepth <= 0.0f)
						break;
				}

				bp->damageMultiplier -= (depth / frontsurfaceDepth);

				if (bp->damageMultiplier <= 0.0f)
					return false;

				if (Trace_GetEntityHitId(&br->trace) == target || Trace_GetEntityHitId(&backbr.trace) == target)
					return true;

				Vector3 vec_length = backbr.hitPos - br->hitPos;

				float length = VectorLength(vec_length);

				if (!allsolid && !weapDef->weaponType && (minFXDist < length)) {
					if (!fronttrace)
						return false;
				}
			}
		}
	}

	return false;
}

#pragma endregion

float GetDistance(Vector3 c1, Vector3 c2) {
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

short AimBoneIndex[13] = { 0 };
short EspBoneIndex[13] = { 0 };
short SldBoneIndex[7] = { 0 };
short LaserBoneIndex[1] = { 0 };
short EntBoneIndex = { 0 };

short HandleTag(int i) {
	if (bot.tagtype == AUTO_BONE || (centity[i].WeaponID == 89 || centity[i].OldWeapon == 89)) {
		return 1000;
	} else {
		switch (bot.tagtype) {
		case tj_ankle_ri:
			return j_ankle_ri;


		case tj_ankle_le:
			return j_ankle_le;


		case tj_knee_ri:
			return j_knee_ri;


		case tj_knee_le:
			return j_knee_le;


		case tj_spineupper:
			return j_spineupper;


		case tj_neck:
			return j_neck;


		case tj_head:
			return j_head;


		case tj_helmet:
			return j_helmet;


		default:
			break;
		}
	}
}

bool Aim_Direction(int i, float tolerance = 80.0f) {
	Vector3 myOrigin = centity[cg->clientNum].Origin;
	Vector3 eOrigin = centity[i].Origin;
	Vector3 eAngles = cgst->clients[i].viewAngle;
	float Scale = GetDistance(myOrigin, eOrigin);
	Vector3 eForward = AnglesToFoward(eOrigin, eAngles, Scale);//100.0f
	float Angle_A = GetDistance(eForward, myOrigin);
	float Angle_B = GetDistance(eOrigin, myOrigin);
	return ((Angle_A - Angle_B) < tolerance);
}

bool Aim_DirectionMe(int i, float tolerance) {
	Vector3 myOrigin = centity[i].Origin;
	Vector3 eOrigin = centity[cg->clientNum].Origin;
	Vector3 eAngles = cg->playerstate.viewAngles;
	float Scale = GetDistance(myOrigin, eOrigin);
	Vector3 eForward = AnglesToFoward(eOrigin, eAngles, Scale);//100.0f
	float Angle_A = GetDistance(eForward, myOrigin);
	float Angle_B = GetDistance(eOrigin, myOrigin);
	return ((Angle_A - Angle_B) < tolerance);
}

enum hitLocation_t {
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_MID = 0x5,
	HITLOC_TORSO_LWR = 0x6,
	HITLOC_R_ARM_UPR = 0x7,
	HITLOC_L_ARM_UPR = 0x8,
	HITLOC_R_ARM_LWR = 0x9,
	HITLOC_L_ARM_LWR = 0xA,
	HITLOC_R_HAND = 0xB,
	HITLOC_L_HAND = 0xC,
	HITLOC_R_LEG_UPR = 0xD,
	HITLOC_L_LEG_UPR = 0xE,
	HITLOC_R_LEG_LWR = 0xF,
	HITLOC_L_LEG_LWR = 0x10,
	HITLOC_R_FOOT = 0x11,
	HITLOC_L_FOOT = 0x12,
	HITLOC_GUN = 0x13,
	HITLOC_SHIELD = 0x14,
	HITLOC_NUM = 0x15,
};


int Sys_EnterCriticalSection_t[2] = { 0x003e2268 , TOC };
void (*Sys_EnterCriticalSection_f)(CriticalSection critSect) = (void (*)(CriticalSection))Sys_EnterCriticalSection_t;

int  Sys_LeaveCriticalSection_t[2] = { 0x003e2374 , TOC };
void (*Sys_LeaveCriticalSection_f)(CriticalSection critSect) = (void (*)(CriticalSection)) Sys_LeaveCriticalSection_t;


void Sys_EnterCriticalSection(CriticalSection critSect) {

	Sys_EnterCriticalSection_f(critSect);
}

void Sys_LeaveCriticalSection(CriticalSection critSect) {

	Sys_LeaveCriticalSection_f(critSect);
}

bool AimTarget_IsWallable(int i, int bone) {
	Vector3 targetbone;
	BulletFireParams bp = { 0 };
	BulletTraceResults br = { 0 };
	targetbone = local->player[i].vtag[bone];
	if (menu->bdisconnect)return;
	bool ret = CG_SimulateBulletFire_Internal(&bp, &br, targetbone, i);

	return ret;
}

bool pTriggerbot(int i) {
	BulletFireParams bp;
	BulletTraceResults br;
	WeaponDef* weapDef = BG_GetWeaponDef(cg->playerstate.weapon);
	if (!weapDef)
		return;
	bp.worldEntNum = 1022;
	bp.skipNum = cg->clientNum;
	bp.damageMultiplier = 1.0f;
	bp.methodOfDeath = 9;
	bp.origStart = local->vorigin;

	bp.start = local->vorigin;

	bp.end = bp.start + (cg->refdef.ViewAxis[0] * 8192.f);

	BulletTrace(0, &bp, weapDef, &centity[cg->clientNum], &br, br.surfaceType, false);

	return (br.trace.hitId == i && !HitRiotshield(&br));
}

char noooop[] = { 0x60, 0x00, 0x00, 0x00 };
char CG_SimulateBulletInternalrestr[] = { 0x4B, 0xFF, 0x0E, 0xB1 };
char Sys_Millisecondsstr[] = { 0x48, 0x36, 0xC0, 0x75 };
char CG_PrepFireParamsstr[] = { 0x4B, 0xFF, 0x33, 0xB9 };
char CL_ReadyToSendPacketstr[] = { 0x48, 0x36, 0x04, 0x3D };
bool oncerun = false;

bool Vis = false, Aw = false;

bool IsTargetHitable(int i, int bone) {

	if ((!bot.bvisible) && (!bot.bautowall))
		return true;

	if (bot.bautowall || bot.bvisible) {
		Aw = AimTarget_IsWallable(i, bone) ? bot.bautowall_esp[i] = true : bot.bautowall_esp[i] = false;
	}

	return Aw;
}

void ShouldSimulateCheck() {
	if (!bot.benable) return;

	if (bot.bautowall && !oncerun) {
		WriteMemory(0xF9C50, noooop, 4);
		WriteMemory(0xF9D78, noooop, 4);
		oncerun = true;
	}

	else if (!bot.bautowall && oncerun) {
		WriteMemory(0xF9C50, CG_PrepFireParamsstr, 4);
		WriteMemory(0xF9D78, CG_SimulateBulletInternalrestr, 4);
		oncerun = false;
	}
}

bool AimingAtEnemyAimbot(int i) {
	Vector3 YourOrigin = centity[cg->clientNum].Origin;
	Vector3 MyOrigin = centity[i].Origin;
	float YZ = YourOrigin.z += 70;
	float MZ = MyOrigin.z += 70;
	YZ == MZ;
	float Scale = GetDistance(MyOrigin, YourOrigin);
	float fMaxAngle = 999;
	Vector3 ToForward = AnglesToFoward(YourOrigin, cg->playerstate.viewAngles, Scale);
	float fAngle = GetDistance(ToForward, MyOrigin);
	if (fMaxAngle > fAngle && fAngle <= 40) {
		fMaxAngle = fAngle;
	}
	if (fMaxAngle != 999) {
		return true;
	}
	return false;
}

bool RAimingAtEnemyAimbot(int i) {
	Vector3 YourOrigin = centity[cg->clientNum].Origin;
	Vector3 MyOrigin = centity[i].Origin;
	float YZ = YourOrigin.z += 70;
	float MZ = MyOrigin.z += 70;
	YZ == MZ;
	float Scale = GetDistance(MyOrigin, YourOrigin);
	float fMaxAngle = 999;
	Vector3 ToForward = AnglesToFoward(YourOrigin, cg->playerstate.viewAngles, Scale);
	float fAngle = GetDistance(ToForward, MyOrigin);
	if (fMaxAngle > fAngle && fAngle <= 250) {
		fMaxAngle = fAngle;
	}
	if (fMaxAngle != 999) {
		return true;
	}
	return false;
}

bool Pshieldcheck(int i) {
	if ((centity[i].OldWeapon == 89)) {
		bot.sc[i] = true;
		if (RAimingAtEnemyAimbot(i)) {
			return true;
		}
	}
	return false;
}

bool AimTarget_GetTargetBounds(int i) {
	if (bot.psztag == NULL) return false;

	Vector2 ScreenPos;
	if (WorldPosToScreenPos(local->player[i].vtag[j_head], &ScreenPos)) {
		if (!(ScreenPos.x > ((cg->refdef.Width / 2) - (Bound.x / 4.5))
			&& ScreenPos.x < ((cg->refdef.Width / 2) + (Bound.x / 4.5))
			&& ScreenPos.y >((cg->refdef.Height / 2) - (Bound.y / 4.5))
			&& ScreenPos.y < ((cg->refdef.Height / 2) + (Bound.y / 4.5))))
			return false;
		else
			return true;
	} else
		return false;
}

bool isPlayerWallable(int ClientNumber) {
	static int iterator[18];

	if (HandleTag(ClientNumber) == 1000)//autobone
	{
		for (int i = 0; i < bot.loop_number_autobone; i++) {
			if (local->iplayer[ClientNumber])
				return;

			if (!IsTargetHitable(ClientNumber, iterator[ClientNumber])) {
				if (iterator[ClientNumber] == 12)
					iterator[ClientNumber] = 0;

				iterator[ClientNumber]++;
			} else {
				bot.psztag[ClientNumber] = iterator[ClientNumber];
				iterator[ClientNumber] = 0;
				return true;
			}
		}

		return false;
	}

	else {
		bot.psztag[ClientNumber] = HandleTag(ClientNumber);
		return IsTargetHitable(ClientNumber, HandleTag(ClientNumber));
	}

	return true;
}

bool Can_Target(int client_number) {
	bool ret;

	Sys_EnterCriticalSection(CRITSECT_XANIM_ALLOC);
	Sys_EnterCriticalSection(CRITSECT_DOBJ_ALLOC);

	ret = isPlayerWallable(client_number);

	Sys_LeaveCriticalSection(CRITSECT_DOBJ_ALLOC);
	Sys_LeaveCriticalSection(CRITSECT_XANIM_ALLOC);

	return ret;
}

int GetNearestLogicalClient() {
	float hittableResult = 99999999.f;

	float IgnoreResult = 99999999.f;

	int ViableClient = -1;

	for (int i = 0; i < 18; i++) {
		if (local->iplayer[i] || i == cg->clientNum || !CScr_IsAlive(i) || CG_IsEntityFriendlyNotEnemy(&centity[i]))
			continue;

		float flDistance = centity[i].Origin.distance(centity[cg->clientNum].Origin);

		if (get_bullet_range() < flDistance)
			continue;

		if ((flDistance < IgnoreResult || Pshieldcheck(i) || local->pplayer[i]) && !local->iplayer[i]) {
			IgnoreResult = flDistance;
			local->target_num = i;
		}

		if (!Can_Target(i))
			continue;

		if (bot.aimtype == AIM_TYPE_TRIGGERBOT) {
			if (AimTarget_GetTargetBounds(i)) {

				hittableResult = flDistance;
				ViableClient = i;
			}
		}

		else if (flDistance < hittableResult || Pshieldcheck(i) || local->pplayer[i] && !local->iplayer[i]) {
			hittableResult = flDistance;
			ViableClient = i;
		}
	}

	return ViableClient;
}

void GetNearestPlayermp() {
	float hittableResult = 99999999.f;

	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	local->target_num = -1;

	local->alive = false;

	local->inbounds = false;

	if (!BG_UsingVehicleWeapon(playerState)) {

		int ammo = BG_GetAmmoInClip(playerState, playerState->weapon);

		if (cg->health <= 0)
			return;

		if (ammo <= 0)
			return;
	}

	if (!cl_ingame_())
		return;

	if (menu->bdisconnect)
		return;

	int NearestClient = GetNearestLogicalClient();

	if (NearestClient == -1)
		return;

	if (bot.aimtype == AIM_TYPE_TRIGGERBOT) {
		if (AimTarget_GetTargetBounds(NearestClient)) {
			local->inbounds = true;
			local->target_num = NearestClient;
			local->alive = true;
		}
		return;
	}

	float flDistance = centity[NearestClient].Origin.distance(centity[cg->clientNum].Origin);

	if (local->target_num != -1 && NearestClient != local->target_num) {
		if (flDistance < hittableResult || Pshieldcheck(local->target_num) || local->pplayer[local->target_num] && !local->iplayer[local->target_num]) {
			local->target_num = NearestClient;
			local->alive = true;
			return;
		}
	}

	local->target_rnum = NearestClient;
	local->target_num = NearestClient;
	local->alive = true;
}


bool isButtonDown(int button) {
	return *(short*)0x1EF77B2 & button;
}

void SnapAimbot() {
	static Vector3 OldAngles;
	static bool ResetAngles;
	if (bot.keytype == KEY_NONE) {
		goto Next;
	}

	else if (bot.keytype == KEY_L1) {
		if (cg->zoomProgress > bot.ads) {
			goto Next;
		} else {
			goto End;
		}
	}

Next:
	if (!local->alive && ResetAngles)
		cactive->ViewAngles = OldAngles, ResetAngles = false;
	else if (!ResetAngles && local->alive)
		OldAngles = cactive->ViewAngles, ResetAngles = true;
End:
}

bool next_0;
static Vector3 vangles;

Vector3 NormalizeClamp(Vector3 Angle) {
	Vector3 dest = Angle;

	while (!(dest.x > -180 && dest.x < 180)) {
		if (dest.x > 180)  dest.x -= 360;
		if (dest.x < -180) dest.x += 360;
	}

	while (!(dest.y > -180 && dest.y < 180)) {
		if (dest.y > 180)  dest.y -= 360;
		if (dest.y < -180) dest.y += 360;
	}

	return dest;
}

float listentome;
void SmoothAngleSet(Vector3 dest, Vector3 orig, float smoothamount) {
	listentome = 8.0f - smoothamount;
	cactive->ViewAngles = NormalizeClamp(orig + (NormalizeClamp(dest - orig) / listentome));
}

int CG_GetPlayerViewOrigin_t[2] = { 0x0EC748, TOC };
bool(*CG_GetPlayerViewOrigin_f)(int localClientNum, playerState_s* ps, Vector3* origin) = (bool(*)(int localClientNum, playerState_s * ps, Vector3 * origin))CG_GetPlayerViewOrigin_t;

bool CG_GetPlayerViewOrigin(Vector3* Origin) {

	playerState_s* playerState = CG_GetPredictedPlayerState(0);
	return CG_GetPlayerViewOrigin_f(cg->clientNum, playerState, Origin);
}

Vector3 MultiPoint(Vector3 position, int i, float flMultiplier) {
	Vector3 delta;
	delta = Vector3(position.x, position.y, position.z + 7);
	return ((delta - position) / flMultiplier);
}

void PingPrediction(int i, Vector3 Bone) {
	Vector3 delta;
	VectorSubtract(centity[i].OldOrigin, centity[i].NewOrigin, delta);
	VectorMA(Bone, cg->ping * 0.001f, delta, Bone);
}

void ApplyPrediction(Vector3& position, int i, float flMultiplier) {
	Vector3 vVelocity;
	VectorSubtract(centity[i].OldOrigin, centity[i].NewOrigin, vVelocity);
	vVelocity.x *= flMultiplier;
	vVelocity.y *= flMultiplier;
	vVelocity.z *= flMultiplier;
	VectorAdd(position, vVelocity, position);
}

void AimTarget_GetTarget() {

	if (centity[cg->clientNum].WeaponID == 89) return;
	if (!cl_ingame_())return;

	GetNearestPlayermp();
}

void ClampAngles(Vector3& angles) {
	while (angles.x > 180.0f)
		angles.x -= 360.0f;

	while (angles.x < -180.0f)
		angles.x += 360.0f;

	while (angles.y > 180.0f)
		angles.y -= 360.0f;

	while (angles.y < -180.0f)
		angles.y += 360.0f;

	if (angles.z != 0.0f)
		angles.z = 0.0f;
}

//long double GetLeanFraction(const float fFrac)
//{
//	return fFrac * (2.0 - fabsf(fFrac));
//}
//
//void BG_ApplyWeaponMovement_LeanOrigin(Vector3* origin)
//{
//	playerState_s* playerState = CG_GetPredictedPlayerState(0);
//	float fDist; // ST18_4
//	float v4; // ST18_4
//	Vector3 right; // [esp+Ch] [ebp-1Ch]
//	Vector3 rollAngles; // [esp+18h] [ebp-10h]
//
//	if (playerState->leanf != 0.0 && playerState->fWeaponPosFrac < 1.0)
//	{
//		rollAngles.x = 0.0;
//		rollAngles.z = 0.0;
//		fDist = GetLeanFraction(playerState->leanf);
//		rollAngles.z = 0.0 - (float)(fDist * 2.0);
//		v4 = (float)((float)(1.0 - playerState->fWeaponPosFrac) * fDist) * 1.6;
//		anglevectors(rollAngles, 0, &right, 0);
//		origin->x = (float)(right.x * v4) + origin->x;
//		origin->y = (float)(right.y * v4) + origin->y;
//		origin->z = (float)(right.z * v4) + origin->z;
//	}
//}

void setanglesMP() {

	if (centity[cg->clientNum].WeaponID == 89) return;

	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	if (!BG_UsingVehicleWeapon(playerState)) {

		CG_GetPlayerViewOrigin_f(cg->clientNum, &cg->playerstate, &local->vorigin);

		if (cg->health <= 0)return;
	}

	else {
		local->vorigin = cg->refdef.ViewOrigin;
	}

	if (!menu->fpssaving) {

		GetNearestPlayermp();
	}

	if (bot.aimtype == AIM_TYPE_SNAP) {

		SnapAimbot();
	}

	Vector3 diff;

	diff = BoneTag(local->target_num) - local->vorigin;

	ApplyPrediction(diff, local->target_num, bot.fprediction);

	VectoAngles(diff, &local->vangles);

	if (bot.bnoflinch)
		local->vangles -= (local->fangles / 2);

	if (!local->alive) return;

	if (bot.aimtype == AIM_TYPE_TRIGGERBOT) {
		if ((bot.keytype == KEY_L1) && cg->zoomProgress > bot.ads || bot.keytype == KEY_NONE) {
			if (local->inbounds) {
				vangles.x += local->vangles.x - cg->get<Vector3>(0x64C30).x;//weapon angles 0x69B20
				vangles.y += local->vangles.y - cg->get<Vector3>(0x64C30).y;//weapon angles 0x69B20

				SmoothAngleSet(vangles, cactive->ViewAngles, bot.snaps);
				local->shoot = true;
			}
		}
	}

	if (bot.aimtype == AIM_TYPE_AIM_BOT || bot.aimtype == AIM_TYPE_SNAP) {

		if ((bot.keytype == KEY_L1) && cg->zoomProgress > bot.ads || bot.keytype == KEY_NONE) {
			cactive->ViewAngles.x += local->vangles.x - cg->get<Vector3>(0x64C30).x;
			cactive->ViewAngles.y += local->vangles.y - cg->get<Vector3>(0x64C30).y;
			local->shoot = true;
		}
	}
}

void aimbot() {

	if (menu->fpssaving) {
		AimTarget_GetTarget();
	}
}
#define	SHORT2ANGLE(x)	( (x) * ( 360.0f / 65536.0f ) )

#pragma region Movement Fix
char ClampChar_r(const int i) {
	if (i < -128) {
		return -128;
	}
	if (i > 127) {
		return 127;
	}
	return i;
}

void AdjustUserCmdMoves(usercmd_s* user_cmd, const float angle, const float old_angle, const float old_forwardMove, const float old_rightMove) {
	auto delta_view = DEG2RAD(angle - old_angle);
	user_cmd->fDir = ClampChar_r(static_cast<int>(cosf(delta_view) * old_forwardMove - sinf(delta_view) * old_rightMove));
	user_cmd->rDir = ClampChar_r(static_cast<int>(sinf(delta_view) * old_forwardMove + cosf(delta_view) * old_rightMove));
}
#pragma endregion

Vector3 viewAngles;

int BG_GetSpreadForWeapon_t[2] = { 0x5F09C8, TOC };
void(*BG_GetSpreadForWeapon_f)(playerState_s* ps, int weapon, float* min, float* maxx) = (void(*)(playerState_s*, int, float*, float*))BG_GetSpreadForWeapon_t;

int BG_seedRandWithGameTime_t[2] = { 0x05D6C54, TOC };
void(*BG_seedRandWithGameTime_f)(unsigned int* pHoldRand) = (void(*)(unsigned int*))BG_seedRandWithGameTime_t;

int CG_BulletEndpos_t[2] = { 0xEBB48, TOC };
void(*CG_BulletEndpos_f)(unsigned int* randSeed, const float spread, Vector3* start, Vector3* end, Vector3* dir, Vector3* forwardDir, Vector3* rightDir, Vector3* upDir, const float maxRange, int weapon, int shotIndex, int maxShotIndex) = (void(*)(unsigned int*, const float, Vector3*, Vector3*, Vector3*, Vector3*, Vector3*, Vector3*, const float, int, int, int))CG_BulletEndpos_t;

//void NoSpread(usercmd_s* cmd, usercmd_s* cmdcur) {
//	Vector3 viewAngles, spreadDirection, spreadEndVec, viewAxis[3];
//
//	playerState_s* playerState = CG_GetPredictedPlayerState(0);
//
//	int wnum = cg->playerstate.weapon;
//
//	if (!wnum)
//		return;
//
//	WeaponDef* weapondef = BG_GetWeaponDef(wnum);
//
//	if (!weapondef)
//		return;
//
//	if (!playerState)
//		return;
//
//	if (BG_UsingVehicleWeapon(playerState))
//		return;
//
//	float minSpread, maxSpread, spread;
//
//	BG_GetSpreadForWeapon_f(playerState, playerState->weapon, &minSpread, &maxSpread);
//
//	if (cg->zoomProgress) {
//		spread = (maxSpread - weapondef->fAdsSpread) * (cg->spreadMultiplier / 255.0f) + weapondef->fAdsSpread;
//	}
//
//	else {
//		spread = (minSpread + ((maxSpread - minSpread) * (cg->spreadMultiplier / 255.0f)));
//	}
//
//	anglevectors(local->vangles, &viewAxis[0], &viewAxis[1], &viewAxis[2]);
//
//	unsigned int seed = cmdcur->time;
//
//	BG_seedRandWithGameTime_f(&seed);
//
//	CG_BulletEndpos_f(&seed, spread, &local->vangles, &spreadEndVec, &spreadDirection, &viewAxis[0], &viewAxis[1], &viewAxis[2], 8192.0f, playerState->weapon, 0, 1);
//	VectoAngles(spreadDirection, &viewAngles);
//
//	cmd->viewAngles[1] += ANGLE2SHORT(local->vangles.y - viewAngles.y);
//	cmd->viewAngles[0] += ANGLE2SHORT(local->vangles.x - viewAngles.x);
//}

void NoSpread(usercmd_s* cmd, int servertime) {
	Vector3 viewAngles, spreadDirection, spreadEndVec, viewAxis[3];

	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	int wnum = cg->playerstate.weapon;

	if (!wnum)
		return;

	WeaponDef* weapondef = BG_GetWeaponDef(wnum);

	if (!weapondef)
		return;

	if (!playerState)
		return;

	float minSpread, maxSpread, spread;

	BG_GetSpreadForWeapon_f(playerState, playerState->weapon, &minSpread, &maxSpread);

	if (cg->zoomProgress == 1.0f) {
		spread = (maxSpread - weapondef->fAdsSpread) * (cg->spreadMultiplier / 255.0f) + weapondef->fAdsSpread;
	}

	else {
		spread = (minSpread + ((maxSpread - minSpread) * (cg->spreadMultiplier / 255.0f)));
	}

	anglevectors(local->vangles, &viewAxis[0], &viewAxis[1], &viewAxis[2]);

	unsigned int seed = servertime;

	BG_seedRandWithGameTime_f(&seed);

	CG_BulletEndpos_f(&seed, spread, &local->vangles, &spreadEndVec, &spreadDirection, &viewAxis[0], &viewAxis[1], &viewAxis[2], 8192.0f, playerState->weapon, 0, 1);
	VectoAngles(spreadDirection, &viewAngles);

	cmd->viewAngles[1] += ANGLE2SHORT(local->vangles.y - viewAngles.y);
	cmd->viewAngles[0] += ANGLE2SHORT(local->vangles.x - viewAngles.x);

}

void psilent(usercmd_s* cmd) {

	if (bot.benable) {

		playerState_s* playerState = CG_GetPredictedPlayerState(0);

		if (bot.bautocrouch)
			*(bool*)0xee4d30 = (playerState->damageCount > 0) ? true : false;

		float OldAngleY = SHORT2ANGLE(cmd->viewAngles[1]);
		if (local->alive) {
			cmd->viewAngles[0] += ANGLE2SHORT(local->vangles.x - cg->get<Vector3>(0x64C30).x);//slient
			cmd->viewAngles[1] += ANGLE2SHORT(local->vangles.y - cg->get<Vector3>(0x64C30).y);
			local->shoot = true;
		}
	}
}

void autoshoot(usercmd_s* curcmd, usercmd_s* oldcmd) {

	if (bot.benable || (curcmd->buttons[0] & AUTO_SHOOT)) {
		if ((local->shoot && bot.bautoshoot) && cg->playerstate.weapon != 89) {

			oldcmd->buttons[0] &= ~AUTO_SHOOT;
			oldcmd->buttons[1] &= ~0x20000000;
			curcmd->buttons[0] |= AUTO_SHOOT;
			curcmd->buttons[1] |= 0x20000000;

			local->shoot = false;
		}
	}
}

float spinY, spinR, spinP;
bool ssw = false;
bool holdingB = false;

bool WeaponIsVehicle() {

	playerState_s* playerState = CG_GetPredictedPlayerState(0);

	return BG_UsingVehicleWeapon(playerState);
}

void pspin(usercmd_s* NewCmd) {

	if (!cl_ingame_())
		return;

	local->fakeAngles[0] = 0.0f;
	local->fakeAngles[1] = 0.0f;

	if (NewCmd->buttons[0] & CMD_MASK_FIRE) {
		NewCmd->buttons[0] &= ~CMD_MASK_FIRE;
	}

	if (bot.benableanti) {
		////ProneBlock
		if (__builtin_return_address() == (void*)0x07F5FC)return;

		playerState_s* playerState = CG_GetPredictedPlayerState(0);
		if (BG_UsingVehicleWeapon(playerState))return;

		int ammo = BG_GetAmmoInClip(playerState, playerState->weapon);

		//Shield
		if (cg->playerstate.weapon == 89)return;

		//Prone
		if (centityt[cg->clientNum].nextState.lerp.eFlags & 8) return;

		//Dive
		if (cg->playerstate.pm_flags & 0x200000) return;

		//RiotShield
		if (cg->playerstate.weapon == 89) return;

		//Mantle
		if ((cg->playerstate.pm_flags & 4) && (ammo > 0)) return;

		//Ladder
		if (cg->playerstate.pm_flags & 8) return;

		static int itickx, iwaitx, iticky, iwaity;

		bool istatex = ((Sys_Milliseconds() - itickx) > iwaitx);
		bool istatey = ((Sys_Milliseconds() - iticky) > iwaity);

		static bool jitterx = false;
		if (istatex && bot.pitchscalex > 0.00) {
			jitterx ^= true;
			itickx = Sys_Milliseconds(), iwaitx = bot.pitchscalex;
		}

		static bool jittery = false;
		if (istatey && (bot.pitchscaley > 0.00)) {
			jittery ^= true;
			iticky = Sys_Milliseconds(), iwaity = bot.pitchscaley;
		}

		if (CScr_IsAlive(cg->clientNum)) {
			if (!bot.baaadvanced) {
				if (bot.block3dpaa) {
					if (bot.breversebot) {
						bot.bspinbot = false, bot.spinscale = 0.0f, bot.pitchscaley = 0.0f;
						local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
						NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
					}
				}

				else {
					if (bot.breversebot) {
						bot.bspinbot = false, bot.spinscale = 0.0f, bot.pitchscaley = 0.0f;
						local->fakeAngles[1] = 0.0f - 180.0f;
						NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
					}
				}

				if (bot.blockup)
					bot.pitchscalex = 0.0f,
					local->fakeAngles[0] = 0.0f - 50.0f,
					NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0]);
				if (bot.spinscale > 0.00)
					bot.pitchscaley = 0.0f,
					local->fakeAngles[1] = spinY,
					spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale),
					NewCmd->viewAngles[1] = ANGLE2SHORT(local->fakeAngles[1]);
				if (bot.pitchscalex > 0.00)
					local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f,
					NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
				if (bot.pitchscaley > 0.00)
					local->fakeAngles[1] = jittery ? 180.0f : 0.0f,
					NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
			}

			else {
				if (bot.block3dpaa) {
					//X
					//FIRING
					if (cg->playerstate.weaponstate == WEAPON_FIRING) {
						switch (bot.antitypeX[FIRING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
							NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}
					//SPRINTING
					else if (cg->playerstate.weaponstate == WEAPON_SPRINT_LOOP || cg->playerstate.weaponstate == WEAPON_SPRINT_RAISE || cg->playerstate.weaponstate == WEAPON_SPRINT_DROP) {
						switch (bot.antitypeX[SPRINTING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
							NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}
					//CROUCHING
					else if (centityt[cg->clientNum].nextState.lerp.eFlags & 4) {
						switch (bot.antitypeX[CROUCHING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
							NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}
					//STANDING
					else if ((centityt[cg->clientNum].nextState.lerp.eFlags != 4) && cg->playerstate.movementDir == 0) {
						switch (bot.antitypeX[STANDING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
							NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}

					//MOVING
					else if (cg->playerstate.movementDir != 0) {
						switch (bot.antitypeX[MOVING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = local->vangles.y - 180.0f - cg->playerstate.delta_angles.y;
							NewCmd->viewAngles[1] += ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}
				}

				else {
					//Y
					//FIRING
					if (cg->playerstate.weaponstate == WEAPON_FIRING) {
						switch (bot.antitypeX[FIRING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = 0.0f - 180.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}

					//SPRINTING
					else if (cg->playerstate.weaponstate == WEAPON_SPRINT_LOOP || cg->playerstate.weaponstate == WEAPON_SPRINT_RAISE || cg->playerstate.weaponstate == WEAPON_SPRINT_DROP) {
						switch (bot.antitypeX[SPRINTING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = 0.0f - 180.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}

					//CROUCHING
					else if (centityt[cg->clientNum].nextState.lerp.eFlags & 4) {
						switch (bot.antitypeX[CROUCHING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = 0.0f - 180.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}

					//STANDING
					else if ((centityt[cg->clientNum].nextState.lerp.eFlags != 4) && cg->playerstate.movementDir == 0) {
						switch (bot.antitypeX[STANDING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = 0.0f - 180.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}

					//MOVING
					else if (cg->playerstate.movementDir != 0) {
						switch (bot.antitypeX[MOVING]) {
						case 0://DISABLED
							break;
						case 1://BACKWARDS
							local->fakeAngles[1] = 0.0f - 180.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 2://JITTER
							local->fakeAngles[1] = jittery ? 180.0f : 0.0f;
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						case 3://SPIN
							local->fakeAngles[1] = spinY;
							spinY = (spinY > 360) ? (spinY - 360) : (spinY + bot.spinscale);
							NewCmd->viewAngles[1] -= ANGLE2SHORT(local->fakeAngles[1]);
							break;
						}
					}
				}

				//X
				//FIRING
				if (cg->playerstate.weaponstate == WEAPON_FIRING) {

					switch (bot.antitypeY[FIRING]) {
					case 0://DISABLED
						break;
					case 1://UP
						local->fakeAngles[0] = 0.0f - 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 2://DOWN
						local->fakeAngles[0] = 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 3://SEMI-UP
						local->fakeAngles[0] = 0.0f - 50.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 4://JITTER
						local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 5://JITTER-UP
						local->fakeAngles[0] = jitterx ? 0.0f - 50.0f : 0.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 6://CUSTOM
						local->fakeAngles[0] = 0.0f - bot.custompitchscale;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					}
				}

				//SPRINTING
				else if (cg->playerstate.weaponstate == WEAPON_SPRINT_LOOP || cg->playerstate.weaponstate == WEAPON_SPRINT_RAISE || cg->playerstate.weaponstate == WEAPON_SPRINT_DROP) {

					switch (bot.antitypeY[SPRINTING]) {
					case 0://DISABLED
						break;
					case 1://UP
						local->fakeAngles[0] = 0.0f - 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 2://DOWN
						local->fakeAngles[0] = 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 3://SEMI-UP
						local->fakeAngles[0] = 0.0f - 50.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 4://JITTER
						local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 5://JITTER-UP
						local->fakeAngles[0] = jitterx ? 0.0f - 50.0f : 0.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 6://CUSTOM
						local->fakeAngles[0] = 0.0f - bot.custompitchscale;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					}
				}
				//CROUCHING
				else if (centityt[cg->clientNum].nextState.lerp.eFlags & 4) {
					switch (bot.antitypeY[CROUCHING]) {
					case 0://DISABLED
						break;
					case 1://UP
						local->fakeAngles[0] = 0.0f - 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 2://DOWN
						local->fakeAngles[0] = 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 3://SEMI-UP
						local->fakeAngles[0] = 0.0f - 50.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 4://JITTER
						local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 5://JITTER-UP
						local->fakeAngles[0] = jitterx ? 0.0f - 50.0f : 0.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 6://CUSTOM
						local->fakeAngles[0] = 0.0f - bot.custompitchscale;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					}
				}

				//STANDING
				else if ((centityt[cg->clientNum].nextState.lerp.eFlags != 4) && cg->playerstate.movementDir == 0) {
					switch (bot.antitypeY[STANDING]) {
					case 0://DISABLED
						break;
					case 1://UP
						local->fakeAngles[0] = 0.0f - 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 2://DOWN
						local->fakeAngles[0] = 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 3://SEMI-UP
						local->fakeAngles[0] = 0.0f - 50.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 4://JITTER
						local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 5://JITTER-UP
						local->fakeAngles[0] = jitterx ? 0.0f - 50.0f : 0.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 6://CUSTOM
						local->fakeAngles[0] = 0.0f - bot.custompitchscale;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					}
				}
				//MOVING
				else if (cg->playerstate.movementDir != 0) {
					switch (bot.antitypeY[MOVING]) {
					case 0://DISABLED
						break;
					case 1://UP
						local->fakeAngles[0] = 0.0f - 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 2://DOWN
						local->fakeAngles[0] = 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 3://SEMI-UP
						local->fakeAngles[0] = 0.0f - 50.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 4://JITTER
						local->fakeAngles[0] = jitterx ? 0.0f - 60.0f : 60.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 5://JITTER-UP
						local->fakeAngles[0] = jitterx ? 0.0f - 50.0f : 0.0f;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					case 6://CUSTOM
						local->fakeAngles[0] = 0.0f - bot.custompitchscale;
						NewCmd->viewAngles[0] = ANGLE2SHORT(local->fakeAngles[0] - cg->playerstate.delta_angles.x);
						break;
					}
				}
			}
		} else {
			cactive->ViewAngles = cactive->BaseAngles;
			cactive->ViewAngles.y = 0;
		}
	}
}



int snakebotTick = 0; bool toggleL;
bool toggleR;
void PredictPlayerState() {
	if (cl_ingame_()) {

		static int iBackupAngles[3];

		usercmd_s* pNewCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber + 1) & 0x7F];
		usercmd_s* pCurrentCmd = &cactive->UserCmd[cactive->CurrentCmdNumber & 0x7F];
		usercmd_s* pOldCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber - 1) & 0x7F];

		if (bot.bIsAirStuck) {
			if (PadDown(PAD_UP)) {
				memcpy(pCurrentCmd, pOldCmd, sizeof(usercmd_s));
			}
		}

		if (bot.snake_bot) {
			if (__builtin_return_address() == (void*)0x07F5FC && bot.snake) {
				bot.snake = false;
			}

			if (ready && PadDown(PAD_DOWN) && !Mshit.Mopened) {
				Wait(500);

				bot.snake = !bot.snake;
			}

			if (bot.snake) {

				if (snakebotTick > 10 && snakebotTick < 15) {
					pCurrentCmd->buttons[0] |= 0x800000;
					pOldCmd->buttons[0] &= 0x7FFFFFFF;
				}

				if (snakebotTick == 15)
					snakebotTick = 0;
				snakebotTick++;
				pCurrentCmd->buttons[0] |= 0x40040000;
			}
		} else {
			bot.snake = false;
		}

		*pNewCmd = *pCurrentCmd;
		++cactive->CurrentCmdNumber;

		pOldCmd->viewAngles[0] = iBackupAngles[0];
		pOldCmd->viewAngles[1] = iBackupAngles[1];
		pOldCmd->viewAngles[2] = iBackupAngles[2];

		if (bot.blean) {
			static int itick, iwait;
			bool istate = ((Sys_Milliseconds() - itick) > iwait);

			if (!PadDown(PAD_R3)) {
				if (isButtonDown(B_DpadLeft) && !Mshit.Mopened) {
					if (istate) {
						toggleL = !toggleL;
						itick = Sys_Milliseconds(), iwait = 500;
					}
				}
			}
			if (toggleL) {
				toggleR = false;
				pCurrentCmd->buttons[0] |= 0x2000000;
				pCurrentCmd->buttons[1] |= 0x0;
			}

			if (ready && PadDown(PAD_RIGHT) && !Mshit.Mopened) {
				Wait(500);
				toggleR = !toggleR;
			}

			if (toggleR) {
				toggleL = false;
				pCurrentCmd->buttons[0] |= 0x1000000;
				pCurrentCmd->buttons[1] |= 0x0;
			}
		} else {
			toggleL = false;
			toggleR = false;
		}

		iBackupAngles[0] = pCurrentCmd->viewAngles[0];
		iBackupAngles[1] = pCurrentCmd->viewAngles[1];
		iBackupAngles[2] = pCurrentCmd->viewAngles[2];

		++pOldCmd->time;
		--pCurrentCmd->time;

		if (!WeaponIsVehicle()) {
			psilent(pOldCmd);
		}

		NoSpread(pOldCmd, pCurrentCmd->time);
	}
}

void SendCMD() {
	usercmd_s* pOldCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber - 1) & 0x7F];

	autoshoot(pOldCmd, pOldCmd);
}

void Writepacket() {
	usercmd_s* pNewCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber + 1) & 0x7F];
	usercmd_s* pCurrentCmd = &cactive->UserCmd[cactive->CurrentCmdNumber & 0x7F];
	usercmd_s* pOldCmd = &cactive->UserCmd[(cactive->CurrentCmdNumber - 1) & 0x7F];

	if (WeaponIsVehicle()) {
		psilent(pCurrentCmd);
		autoshoot(pOldCmd, pOldCmd);
		autoshoot(pCurrentCmd, pCurrentCmd);
	}

	pspin(pCurrentCmd);
}