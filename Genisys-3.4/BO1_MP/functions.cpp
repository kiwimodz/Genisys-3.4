#include <Includes.h>

int R_GetFontPathFromName_t[2] = { 0x75C104, TOC };
String(*R_GetFontPathFromName)(String text) = (String(*)(String))R_GetFontPathFromName_t;

int Cmd_Argv_t[2] = { 0x0087E1A0, TOC };
const char* (*Cmd_Argv)(int argIndex) = (const char* (*)(int)) & Cmd_Argv_t;

int Cmd_Argc_t[2] = { 0x87E294, TOC };
int (*Cmd_Argc)() = (int (*)()) & Cmd_Argc_t;

int CG_GetPredictedPlayerState_t[2] = { 0x6AD5C, TOC };
playerState_s* (*CG_GetPredictedPlayerState_f)(int) = (playerState_s * (*)(int))CG_GetPredictedPlayerState_t;

playerState_s* CG_GetPredictedPlayerState(int i) {
	return CG_GetPredictedPlayerState_f(i);
}

int CONNECTIONERROR[16] = { 188, 176, 177, 177, 186, 188, 171, 182, 176, 177, 223, 186, 173, 173, 176, 173 };
int GET[5] = { 184, 186, 171, 223, 208 };
int HTTPHOST[17] = { 223, 183, 171, 171, 175, 208, 206, 209, 207, 242,245, 183, 176, 172, 171, 197, 223 };
int DOUBLEBREAK[4] = { 242, 245, 242, 245 };

void memFree(const char* ptr, int len) { for (int i = 0; i < len; i++) { *(char*)(ptr + i) = 0x00; } }
const char* XOR(int* Input, int Length) {
	char buffer[1024] = { 0 };
	Virtual::Call<int>(memset_t, buffer, 0x00, Length + 2);
	for (int i = 0; i < Length; i++) {
		buffer[i] = (char)(Input[i] ^ 0xFF);
	}
	return buffer;
}

int Socket;
struct hostent* Host;
struct sockaddr_in SocketAddress;
char bufferReturn[10000];
char RequestBuffer[2048];

const char* remove_http_header(char* request) {
	Virtual::Call<int>(notouch_t);
	request = strstr(request, "\r\n\r\n");
	if (request)
		request += 4;
	Virtual::Call<int>(socketclose_t, Socket);
	return request;
}

const char* SocketRequest(const char* URL, const char* Path) {
	Host = gethostbyname(URL);
	SocketAddress.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_port = htons(80);
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Socket, (struct sockaddr*)&SocketAddress, sizeof(SocketAddress)) != 0) {
		return XOR(CONNECTIONERROR, 16);
	}
	strcpy(RequestBuffer, XOR(GET, 5));
	if (strlen(Path) > 0) {
		strcat(RequestBuffer, Path);
	}
	strcat(RequestBuffer, XOR(HTTPHOST, 17));
	strcat(RequestBuffer, URL);
	strcat(RequestBuffer, XOR(DOUBLEBREAK, 4));
	Virtual::Call<int>(send_t, Socket, RequestBuffer, strlen(RequestBuffer), 0);
	while (Virtual::Call<int>(recv_t, Socket, bufferReturn, 10000, 0) > 0) {
		return Virtual::Call<const char*>(remove_http_header_t, bufferReturn);
	}
}

//static int connect_to_Gen(void)
//{
//	struct sockaddr_in sin;
//	int s;
//
//	sin.sin_family = AF_INET;
//	struct hostent* Host = gethostbyname("64.67.43.101");
//	sin.sin_addr.s_addr = *((unsigned long*)Host->h_addr);
//	sin.sin_port = htons(8080);
//	s = socket(AF_INET, SOCK_STREAM, 0);
//	if (s < 0)
//	{
//		return -1;
//	}
//
//	if (connect(s, (struct sockaddr*) & sin, sizeof(sin)) < 0)
//	{
//		return -1;
//	}
//
//	return s;
//}

static int connect_to_webman(void) {
	struct sockaddr_in sin;
	int s;


	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0x7F000001;
	sin.sin_port = htons(80);
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		return -1;
	}

	if (connect(s, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		return -1;
	}

	return s;
}

static void sclose(int* socket_e) {
	if (*socket_e != -1) {
		shutdown(*socket_e, SHUT_RDWR);
		socketclose(*socket_e);
		*socket_e = -1;
	}
}

static const char* send_wm_request(const char* cmd) {
	int conn_s = -1;
	conn_s = connect_to_webman();
	char buffer[256];
	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 3;
	setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
	setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

	if (conn_s >= 0) {
		char wm_cmd[1048];
		int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
		send(conn_s, wm_cmd, cmd_len, 0);
		while (recv(conn_s, buffer, 10000, 0) > 0) {
			return buffer;
		}
	}
	sclose(&conn_s);
}

void fixSpaces(const char** szReturn) {
	const char* str = *szReturn;
	char _returnStr[512];

	_returnStr[0] = '\0';

	int dwStrIndex = 0;

	for (int i = 0; i < strlen(str) + 1; i++) {
		if (str[i] != 0x20) {
			_returnStr[dwStrIndex] = str[i];
			dwStrIndex++;
		} else {
			_returnStr[dwStrIndex] = '%';
			_returnStr[dwStrIndex + 1] = '2';
			_returnStr[dwStrIndex + 2] = '0';
			dwStrIndex += 3;
		}
		_returnStr[dwStrIndex] = '\0';
	}

	*szReturn = _returnStr;
}

void DoNotify(const char* szFormat) {
	char _notify_buffer[512];

	fixSpaces(&szFormat);

	snprintf(_notify_buffer, 512, hash("/notify.ps3mapi?msg=%s"), szFormat);

	send_wm_request(_notify_buffer);
}

static void get_temperature(uint32_t _dev, uint8_t* temp) {
	uint32_t _temp;
	system_call_2(383, (uint64_t)(uint32_t)_dev, (uint64_t)(uint32_t)&_temp); *temp = _temp >> 24; // return �C
}

void Psbutn() {
	send_wm_request(hash("/pad.ps3?_psbtn_go"));
}

void GetTemps(uint8_t* CPU, uint8_t* RSX, bool C) {
	uint8_t t1 = 0, t2 = 0, t1f, t2f;
	get_temperature(0, &t1);
	get_temperature(1, &t2);
	if (!C) {
		*CPU = (1.8f * (float)t1 + 32.f);
		*RSX = (1.8f * (float)t2 + 32.f);
	} else {
		*CPU = t1;
		*RSX = t2;
	}
}

int CG_GameMessage_t[2] = { 0x0006AD98, TOC };
void(*CG_GameMessage_f)(int r1, const char* r2) = (void(*)(int, const char*))CG_GameMessage_t;


void CG_GameMessage(const char* r2) {
	CG_GameMessage_f(0, r2);
}

int Cbuf_AddText_t[2] = { 0x313C18, TOC };
void(*Cbuf_AddText_f)(int r1, const char* r2) = (void(*)(int, const char*))Cbuf_AddText_t;

void Cbuf_AddText(const char* r2) {
	Cbuf_AddText_f(0, r2);
}

int BG_GetAmmoInClip_t[2] = { 0x0603694, TOC };
int(*BG_GetAmmoInClip)(playerState_s* ps, int weapon) = (int(*)(playerState_s*, int))BG_GetAmmoInClip_t;

int WorldPosToScreenPos_t[2] = { 0x5A480, TOC };
bool(*WorldPosToScreenPos_f)(int r1, Vector3 const& worldPos, Vector2* screenPos) = (bool(*)(int, Vector3 const&, Vector2*))WorldPosToScreenPos_t;

bool WorldPosToScreenPos(Vector3 worldPos, Vector2* screenPos) {
	return WorldPosToScreenPos_f(0, worldPos, screenPos);
}

int CG_LocationalTrace_t[2] = { 0x100018, TOC };
void(*CG_LocationalTrace_f)(trace_t* ptrace, Vector3* start, Vector3* end, int passEntityNum, int contentMask, bool checkRopes, col_context_t* context) = (void(*)(trace_t*, Vector3*, Vector3*, int, int, bool, col_context_t*))CG_LocationalTrace_t;

void CG_LocationalTrace(trace_t* ptrace, Vector3* start, Vector3* end, int passEntityNum, int contentMask, bool checkRopes, col_context_t* context) {
	CG_LocationalTrace_f(ptrace, start, end, passEntityNum, contentMask, checkRopes, context);
}

int PlayerCmd_EnableInvulnerability_t[2] = { 0x1F9C9C, TOC };
void(*PlayerCmd_EnableInvulnerability_f)(int* r1) = (void(*)(int*))PlayerCmd_EnableInvulnerability_t;

void PlayerCmd_EnableInvulnerability(int client) {
	int entref[] = { client, 0 };
	PlayerCmd_EnableInvulnerability_f(entref);
}

int PlayerCmd_disableinvulnerability_t[2] = { 0x001F9D38, TOC };
void(*PlayerCmd_disableinvulnerability_f)(int* r1) = (void(*)(int*))PlayerCmd_disableinvulnerability_t;

void PlayerCmd_disableinvulnerability(int client) {
	int entref[] = { client, 0 };
	PlayerCmd_disableinvulnerability_f(entref);
}

void TeleportToPower() {
	Vector3 Buried_Res = { 682.165, -552.677, 144.125 };
	*(Vector3*)(0x01780f50 + Mshit.scroll[ID_PLAYERS] * 0x5808) = Buried_Res;
	char boolBuff[100];
	//snprintf(boolBuff, sizeof(boolBuff), "%c \"%s\"", 79, "Teleported to ^2Power");
	//SV_GameSendServerCommand_f(Mshit.scroll[ID_PLAYERS], 0, boolBuff);
}

void TeleportToPaP() {
	Vector3 Buried_Res = { 6403.38, 779.031, -131.672 };
	*(Vector3*)(0x01780f50 + Mshit.scroll[ID_PLAYERS] * 0x5808) = Buried_Res;
	char boolBuff[100];
	//snprintf(boolBuff, sizeof(boolBuff), "%c \"%s\"", 79, "Teleported to ^2PackaPunch");
	//SV_GameSendServerCommand_f(Mshit.scroll[ID_PLAYERS], 0, boolBuff);
}

int XShowKeyboardUI_t[2] = { 0x46710C, TOC };
void(*XShowKeyboardUI_f)(int localClientNum, const wchar_t* title, const wchar_t* presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t* wstring, unsigned int Length), unsigned int panel_mode) = (void(*)(int, const wchar_t*, const wchar_t*, unsigned int, void(*)(int, const wchar_t*, unsigned int), unsigned int))XShowKeyboardUI_t;

void XShowKeyboardUI(int localClientNum, const wchar_t* title, const wchar_t* presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t* wstring, unsigned int Length), unsigned int panel_mode) {
	*(char*)0xD82144 = 1;
	XShowKeyboardUI_f(localClientNum, title, presetMsg, length, KB_COMPLETE, panel_mode);
}

int Dvar_GetString_t[2] = { 0x3DAE50, TOC };
String(*Dvar_GetString_f)(int dvarName) = (String(*)(int dvarName))Dvar_GetString_t;

int Dvar_t[2] = { 0x3DA628, TOC };
int(*Dvar_f)(String dvarName) = (int(*)(String dvarName))Dvar_t;

String Dvar_GetString(String dvarName) {
	return Dvar_GetString_f(Dvar_f(dvarName));
}

void WideCharToMultibyte(const wchar_t* wchar, int length, char* buffer) {
	for (int i = 0; i < length; i++)
		buffer[i] = (char)wchar[i];
}

int Sys_GetValue_t[2] = { 0x0340BDC, TOC };
void* (*Sys_GetValue_f)(int valueIndex) = (void* (*)(int))Sys_GetValue_t;


//bool CScr_IsAlive(int i) {
//
//	if (centity[i].Type > 0)
//	{
//	if (centity[i].Type == ET_Player)
//	{
//		return (!cg->clients[i].Dead) && strcmp(cg->clients[i].PlayerModel, "");
//	}
//
//	
//		if (centity[i].Type != ET_ACTOR_CORPSE && centity[i].Type != ET_ACTOR_SPAWNER)
//		{
//			
//	
//			if (centity[i].Type == ET_DOG)
//			{
//				return (centity[i].Alive);
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}
//}

bool CScr_IsAlive(int i) {

	if (centity[i].Type == ET_Player) {
		return (!cg->clients[i].Dead) && strcmp(cg->clients[i].PlayerModel, "") != 0;
	} else {
		return false;
	}
}

void PosPrediction(int i, Vector3 BonePos, int Scale, bool NotAllowZ) {
	Vector3 EnemyVelocityTemp;
	Vector3 EnemyVelocity;
	EnemyVelocityTemp = centity[i].NewOrigin - centity[i].OldOrigin;
	EnemyVelocity.x = EnemyVelocityTemp.x;
	EnemyVelocity.y = EnemyVelocityTemp.y;
	EnemyVelocity.z = EnemyVelocityTemp.z;
	Vector3 CalcVec = EnemyVelocity.normalize();
	CalcVec.x *= Scale;
	CalcVec.y *= Scale;
	CalcVec.z *= Scale;
	float TempOld = BonePos.z;
	BonePos.x += CalcVec.x;
	BonePos.y += CalcVec.y;
	BonePos.z += CalcVec.z;
	if (NotAllowZ)
		BonePos.z = TempOld;
}

void USleep(usecond_t time) {
	sys_timer_usleep(time * 1000);
}

int Dvar_FindVar_t[2] = { 0, TOC };
dvar_t* (*Dvar_FindVar_f)(String dvarName) = (dvar_t * (*)(String))Dvar_FindVar_t;

dvar_t* Dvar_FindVar(String dvarName) {

	return Dvar_FindVar_f(dvarName);
}

bool Dvar_GetBool(String dvarName) {
	return Dvar_FindVar(dvarName)->current.enabled;
}

int Dvar_GeInt(String dvarName) {
	return Dvar_FindVar(dvarName)->current.integer;
}

float Dvar_GetFloat(String dvarName) {
	return Dvar_FindVar(dvarName)->current.value;
}

int irand_t[2] = { 0x3CE988, TOC };
int(*irand_f)(int r1, int r2) = (int(*)(int, int))irand_t;

int irand_(int min, int max_) {
	return irand_f(min, max_);
}

int CG_IsEntityFriendlyNotEnemy_t[2] = { 0x049720, TOC };
bool(*CG_IsEntityFriendlyNotEnemy_f)(int r1, centity_s* r2) = (bool(*)(int, centity_s*))CG_IsEntityFriendlyNotEnemy_t;

#pragma region cg
bool CG_IsEntityFriendlyNotEnemy(centity_s* cent) {
	if (!cl_ingame_())return false;
	return CG_IsEntityFriendlyNotEnemy_f(0, cent);
}

int CG_DObjGetWorldTagPos_t[2] = { 0x049720, TOC };
int (*CG_DObjGetWorldTagPos_f)(centity_s* pose, int* objEA, unsigned int tagName, Vector3* pos) = (int (*)(centity_s*, int*, unsigned int, Vector3*))CG_DObjGetWorldTagPos_t;

int Com_GetClientDObj_t[2] = { 0x03275C0, TOC };
int (*Com_GetClientDObj_f)(int handle, int localClientNum) = (int (*)(int, int))Com_GetClientDObj_t;

int AimTarget_GetTagPosMP(centity_s* cent, short tagName, Vector3* pos) {
	int DOBJ = Com_GetClientDObj_f(cent->ClientNumber, 0);
	if (DOBJ)
		return CG_DObjGetWorldTagPos_f(cent, &DOBJ, tagName, pos);
	return 0;
}

int AimTarget_GetTagPos_t[2] = { 0x015708, TOC };
bool(*AimTarget_GetTagPos_f)(centity_s* cent, short tagname, Vector3* r4) = (bool(*)(centity_s*, short, Vector3*))AimTarget_GetTagPos_t;

Vector3 aVec, bVec;
void GetTagPos(centity_s* cent, short tagName, Vector3* pos) {

	AimTarget_GetTagPos_f(cent, tagName, pos);
}

void AimTarget_GetTagPos(centity_s* cent, short tagname, Vector3* pos) {
	*(int*)0x461FB4 = 0x4E800020;
	AimTarget_GetTagPos_f(cent, tagname, pos);
	*(int*)0x461FB4 = 0xF821FB71;
}

float VectorLength2D(Vector3* pV) {
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

int VectoAngles_t[2] = { 0x3CAB90, TOC };
void(*VectoAngles_f)(Vector3* vec, Vector3* angles) = (void(*)(Vector3 * vec, Vector3 * angles))VectoAngles_t;

void VectoAngles(Vector3 vec, Vector3* angles) {
	VectoAngles_f(&vec, angles);
}

Vector3 AnglesToFoward(Vector3 Origin, Vector3 Angles, float diff)//1000.0f
{
	float angle, sr, sp, sy, cr, cp, cy, PiDiv;
	PiDiv = ((float)M_PI / 180);
	angle = Angles.y * PiDiv;
	sy = (float)sinf(angle);
	cy = (float)cosf(angle);
	angle = Angles.x * PiDiv;
	sp = sinf(angle);
	cp = (float)cosf(angle);
	angle = Angles.y * PiDiv;
	sr = (float)sinf(angle);
	cr = (float)cosf(angle);
	Vector3 Final((cp * cy * diff) + Origin.x, (cp * sy * diff) + Origin.y, (-sp * diff) + Origin.z);
	return Final;
}

bool EnemyAimingAtMe(int enemy) {
	Vector3 myOrigin = centity[cg->clientNum].Origin;
	Vector3 enemyOrigin = centity[enemy].Origin;
	Vector3 enemyAngles = *(Vector3*)(&cg->clients[enemy] + 0x04C4);
	float tolerance = 3.0f;
	float Scale = myOrigin.distance(enemyOrigin);
	Vector3 enemyForward = AnglesToFoward(enemyOrigin, enemyAngles, Scale);//100.0f
	float Angle_A = enemyForward.distance(myOrigin);
	float Angle_B = enemyOrigin.distance(myOrigin);
	return ((Angle_A - Angle_B + 70) <= tolerance);
}

#pragma endregion
#pragma region graphics

int R_RegisterFont_t[2] = { 0x75A2C0, TOC };
int(*R_RegisterFont_f)(String font, int imageTrac) = (int(*)(String, int))R_RegisterFont_t;

int R_RegisterFont(String font, int imageTrac) {
	return R_RegisterFont_f(font, imageTrac);
}

int R_TextWidth_t[2] = { 0x75A338, TOC };
int(*R_TextWidth_f)(int localClientNum, const char* text, int maxChars, int font) = (int(*)(int, const char*, int, int))R_TextWidth_t;

int R_TextWidth(String text, const char* font, float scale) {
	return R_TextWidth_f(0, text, 0x7FFFFFFF, R_RegisterFont(font, 0)) * scale;
}

int R_TextHeight_t[2] = { 0x75A5D0, TOC };
int(*R_TextHeight_f)(int font) = (int(*)(int))R_TextHeight_t;

int R_TextHeight(String font, float scale) {
	return R_TextHeight_f(R_RegisterFont(R_GetFontPathFromName(font), 0)) * scale;
}

void SmokeColor(bool* rs) { *rs = menu->smokec = !menu->smokec; }
void Dankmap(bool* rs) { *rs = menu->dankmap = !menu->dankmap; }

int Sys_Milliseconds_t[2] = { 0x465CE0, TOC };
int(*Sys_Milliseconds)() = (int(*)())Sys_Milliseconds_t;

int Com_Sprint_t[2] = { 0x3E4970, TOC };
int(*Com_Sprintf)(const char* dest, int size, const char* fmt, ...) = (int(*)(const char*, int, const char*, ...))Com_Sprint_t;

color NavyBlue1 = { 0, 0.2, 0.4, 1 };
color White1 = { 1, 1, 1, 1 };

float sky_rotate;
bool runoncexxx = true;
void Smokehandle() {
	if (strstr(hash("Uplink"), Dvar_GetString(hash("party_mapname")))) {
		if (!menu->nightmode && cl_ingame_()) {
			//*(int*)0x07599D0 = 0x60000000;
			*(int*)0x01cc1018 = 0x01000000;//0x2B28CC4 <-- pointer from r_exposureTweak
			*(int*)0x01CC1078 = 0x40900000;//r_exposureValue
			//*(int*)0x01CC19D8 = 0xffffffff;
			*(int*)0x01cbc214 = 0x01000000;//r_lighttweaksuncolor
			WriteMemory(0x01cbc218, &NavyBlue1, 16);//r_lighttweaksuncolor
		} else {
			//*(int*)0x07599D0 = 0x04BC80D1;
			*(int*)0x01cc1018 = 0x00000000;//r_exposureTweak
			*(int*)0x01CC1078 = 0x40400000;//r_exposureValue
			//*(int*)0x01CC19D8 = 0x45CB2000;
			WriteMemory(0x01cbc218, &White1, 16);//r_lighttweaksuncolor
			*(int*)0x01cbc214 = 0x00000000;//r_lighttweaksuncolor
			//Cbuf_AddText(0, "reset r_lightTweakSunColor");
		}
	}

	if (menu->skyr) {
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);
		if (istate) {
			if (sky_rotate >= 360)
				sky_rotate - 360;
			else
				sky_rotate += 0.10;

			WriteMemory(r_skyRotation, &sky_rotate, 4);//r_skyRotation



			itick = Sys_Milliseconds(), iwait = 1;
		}
	}

	if (menu->smokec) {
		WriteMemory(0x009E50D0, &menu->skin, 16);
		runoncexxx = true;
	} else if (!menu->smokec && runoncexxx) {
		WriteMemory(0x009E50D0, &color(255, 255, 255, 255), 16);
		runoncexxx = false;
	}
}

int Material_RegisterHandle_t[2] = { 0x763220, TOC };
Material* (*Material_RegisterHandle_f)(String material, int imageTrac, int r1) = (Material * (*)(String, int, int))Material_RegisterHandle_t;

Material* Material_RegisterHandle(String material, int ImageTrac) {
	return Material_RegisterHandle_f(material, ImageTrac, 0);
}

struct Glyph {
	unsigned __int16 letter;
	char x0;
	char y0;
	char dx;
	char pixelWidth;
	char pixelHeight;
	float s0;
	float t0;
	float s1;
	float t1;
};

/* 1615 */
struct KerningPairs {
	unsigned __int16 wFirst;
	unsigned __int16 wSecond;
	int iKernAmount;
};

/* 1616 */
struct Font_s {
	const char* fontName;
	int pixelHeight;
	int isScalingAllowed;
	int glyphCount;
	int kerningPairsCount;
	Material* material;
	Material* glowMaterial;
	Glyph* glyphs;
	KerningPairs* kerningPairs;
};

int CL_DrawTextPhysicalWithEffects_t[2] = { 0x122C28, TOC };
void(*CL_DrawTextPhysicalWithEffects_f)(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, float* c, int style, float* glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) = (void(*)(String, int, int, float, float, float, float, float, float*, int, float*, Material*, Material*, int, int, int, int))CL_DrawTextPhysicalWithEffects_t;

int R_AddCmdDrawText_t[2] = { 0x76A910, TOC };
void(*R_AddCmdDrawText_f)(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float* Color, int Style) = (void(*)(String, int, int, float, float, float, float, float, float*, int))R_AddCmdDrawText_t;

void __cdecl CL_DrawTextPhysicalWithEffects1(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, (dc.height > 720) ? y * (1.5 - menu->menusize) : y / (dc.aspect - menu->menusize), w, xScale, (dc.height > 720) ? yScale * (1.5 - menu->menusize) : yScale / (dc.aspect - menu->menusize), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}

void __cdecl CL_DrawTextPhysicalWithEffects(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, (dc.height > 720) ? y * (1.5 - menu->menusize) : y / (dc.aspect - menu->menusize), w, xScale, (dc.height > 720) ? yScale * (1.5 - menu->menusize + 0.30) : yScale / (dc.aspect - menu->menusize), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}

void __cdecl CL_DrawTextPhysicalWithEffectsUI(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, (dc.height > 720) ? y * (1.5 + menu->menusize) : y / (dc.aspect), w, xScale, (dc.height > 720) ? yScale * (1.5 - menu->menusize + 0.30) : yScale / (dc.aspect), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}

void R_AddCmdDrawText(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float* Color, int Style) {
	R_AddCmdDrawText_f(Text, MaxChars, Font, X, (dc.height > 720) ? Y * (1.5 - menu->menusize) : Y / (dc.aspect - menu->menusize), XScale, (dc.height > 720) ? YScale * (1.5 - menu->menusize + 0.30) : YScale / (dc.aspect - menu->menusize), Rotation, Color, Style);
}

void R_AddCmdDrawTextUI(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float* Color, int Style) {
	R_AddCmdDrawText_f(Text, MaxChars, Font, X, (dc.height > 720) ? Y * (1.5 + menu->menusize) : Y / (dc.aspect - menu->menusize), XScale, (dc.height > 720) ? YScale * (1.5 - menu->menusize + 0.30) : YScale / (dc.aspect - menu->menusize), Rotation, Color, Style);
}

int CG_DrawRotatedPic_t[2] = { 0x456F8, TOC };
void(*CG_DrawRotatedPic_f)(int scrPlace, float x, float y, float width, float height, float angle, float* c, pvoid) = (void(*)(int, float, float, float, float, float, float*, pvoid))CG_DrawRotatedPic_t;

void CG_DrawRotatedPicUI(float x, float y, float width, float height, float angle, color c, Material* material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * (1.5 + menu->menusize) : y / (dc.aspect), width, (dc.height > 720) ? height * (1.5 + menu->menusize) : height / (dc.aspect), angle, (float*)&c, material);
}

void CG_DrawRotatedPic(float x, float y, float width, float height, float angle, color c, Material* material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * (1.5 - menu->menusize) : y / (dc.aspect - menu->menusize), width, (dc.height > 720) ? height * (1.5 - menu->menusize) : height / (dc.aspect - menu->menusize), angle, (float*)&c, material);
}

int CL_DrawStretchPicInternal_t[2] = { 0x10B588, TOC };
void(*CL_DrawStretchPicInternal_f)(int scrPlace, float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, float* color, pvoid material) = (void(*)(int, float, float, float, float, int, int, float, float, float, float, float*, pvoid))CL_DrawStretchPicInternal_t;

void CL_DrawStretchPicInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color color_, pvoid material) {
	CL_DrawStretchPicInternal_f(0xFB9DE0, x, y, w, h, horzAlign, vertAlign, centerS, centerT, radiusST, scaleFinalS, (float*)&color_, material);
}

void CG_DrawRotatedPic1(float x, float y, float width, float height, float angle, color c, Material* material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * 1.5 : y, width, (dc.height > 720) ? height * 1.5 : height, angle, (float*)&c, material);
}

void CG_DrawRotatedPicesp(float x, float y, float width, float height, float angle, color c, Material* material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * 1.5 : y, width, (dc.height > 720) ? height * 1.5 : height, angle, (float*)&c, material);
}

void CG_DrawRotatedPicp(float x, float y, float width, float height, float angle, color c, pvoid material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * (1.5) : y, width, (dc.height > 720) ? height * (1.5) : height, angle, (float*)&c, material);
}

void CG_DrawRotatedPicUI1(float x, float y, float width, float height, float angle, color c, Material* material) {
	CG_DrawRotatedPic_f(0xFB9DE0, x, (dc.height > 720) ? y * (1.5 + menu->menusize) : y / (dc.aspect - menu->menusize), width, (dc.height > 720) ? height * (1.5 + menu->menusize) : height / (dc.aspect - menu->menusize), angle, (float*)&c, material);
}

void __cdecl CL_DrawTextPhysicalWithEffectsUI1(String Text, int MaxChars, int font, float x, float y, float w, float xScale, float yScale, color c, int style, color glowColor, Material* fxMaterial, Material* fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration) {
	CL_DrawTextPhysicalWithEffects_f(Text, MaxChars, font, x, (dc.height > 720) ? y * (1.5 + menu->menusize) : y / (dc.aspect - menu->menusize), w, xScale, (dc.height > 720) ? yScale * (1.5 - menu->menusize + 0.30) : yScale / (dc.aspect - menu->menusize), (float*)&c, style, (float*)&glowColor, fxMaterial, fxMaterialGlow, fxBirthTime, fxLetterTime, fxDecayStartTime, fxDecayDuration);
}


void DrawShader(Vector2 Pos, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		Pos.x = Pos.x;
	if (align & align_right)
		Pos.x = Pos.x - w;
	if (align & align_center)
		Pos.x = Pos.x - (w / 2);
	CG_DrawRotatedPic(menu->menux + Pos.x, menu->menuy + Pos.y, w, h, angle, col, material);
}

void DrawShader(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPic(menu->menux + x, menu->menuy + y, w, h, angle, col, material);
}

void DrawShader3(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPic(x, -99 + y, w, h, angle, col, material);
}

void DrawShaderUI(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPicUI(x, y, w, h, angle, col, material);
}

void DrawShaderUI1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	CG_DrawRotatedPicUI1(x, y, w, h, angle, col, material);
}

int LiveStats_SetClanTagText_t[2] = { 0x5470D0, TOC };
bool(*LiveStats_SetClanTagText_f)(int controllerIndex, const char* clanTag) = (bool(*)(int, const char*))LiveStats_SetClanTagText_t;

bool LiveStats_SetClanTagText(int controllerIndex, const char* clanTag) {
	return LiveStats_SetClanTagText_f(controllerIndex, clanTag);
}

void ChangeClanTagPreGame(const char* str) {
	LiveStats_SetClanTagText(0, str);
}

void I_ChangeClan() {
	char playerClan[50];
	Com_Sprintf(playerClan, sizeof(playerClan), hash(";cmd userinfo \"\\clanAbbrev\\^%i\\name\\%s\\xuid\\%s"), irand_(0, 8), 0x026C0658, 0x26C06E8);
	Cbuf_AddText(playerClan);
}

void I_ChangeAdd() {
	char playerClan1[50];
	const char* str = hash("GenisysV3.4");
	Com_Sprintf(playerClan1, sizeof(playerClan1), hash(";cmd userinfo \"\\clanAbbrev\\^%i\\name\\%s\\xuid\\%s"), irand_(0, 8), str, 0x26C06E8);
	Cbuf_AddText(playerClan1);
}

void I_ChangeAdd1() {
	char playerClan1[50];
	const char* str = hash("discord.gg/r6WcW92g4h");
	Com_Sprintf(playerClan1, sizeof(playerClan1), hash(";cmd userinfo \"\\clanAbbrev\\^%i\\name\\%s\\xuid\\%s"), irand_(0, 8), str, 0x26C06E8);
	Cbuf_AddText(playerClan1);
}

void Flash_name_() {
	if (menu->flshname) {
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);
		static bool runonce = false;
		if (istate) {
			if (cl_ingame_()) {
				runonce = false;
				I_ChangeClan();
			} else {
				char Addver[100];

				const char* str;

				if (*(bool*)0x0FA7A03)//Lobby or Party
				{
					str = (const char*)0x026C067F;
					if (str[0] == '^')
						str = (const char*)(0x026C067F + 0x2);
				} else {
					str = (const char*)0x026C0658;
					if (str[0] == '^')
						str = (const char*)(0x026C0658 + 0x2);
				}

				Com_Sprintf(Addver, sizeof(Addver), hash("^%i%s"), irand_(0, 8), str);

				WriteMemory(0x026C0658, Addver, 32);
				WriteMemory(0x026C067F, Addver, 32);

				if (!runonce) {
					ChangeClanTagPreGame("/0");
					runonce = true;
				}

			}
			itick = Sys_Milliseconds(), iwait = 800;
		}
	}
}

void Add_name_() {
	if (menu->addname) {
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);

		if (istate) {
			if (cl_ingame_()) {
				I_ChangeAdd();
			} else {
				char Addver[32];
				const char* str = hash("GenisysV3.4");
				Com_Sprintf(Addver, sizeof(Addver), hash("^%i%s\0"), irand_(0, 8), str);
				WriteMemory(0x026C0658, Addver, 32);
				WriteMemory(0x026C067F, Addver, 32);
			}
			itick = Sys_Milliseconds(), iwait = 800;
		}
	}
}

void Add_name__() {
	if (menu->addname1) {
		static int itick, iwait;
		bool istate = ((Sys_Milliseconds() - itick) > iwait);

		if (istate) {
			if (cl_ingame_()) {
				I_ChangeAdd1();
			} else {
				char Addver[256];
				const char* str = hash("discord.gg/r6WcW92g4h");
				Com_Sprintf(Addver, sizeof(Addver), hash("^%i%s\0"), irand_(0, 8), str);
				WriteMemory(0x026C0658, Addver, 32);
				WriteMemory(0x026C067F, Addver, 32);
			}
			itick = Sys_Milliseconds(), iwait = 800;
		}
	}
}

void DrawText(String text, Vector2 vec, float rotation, float scale, String font, color col, alignment align, bool active_) {
	String pszfont = R_GetFontPathFromName(font);
	if (text == NULL) return;
	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);
	if (align & align_left)
		vec.x = vec.x;
	if (align & align_right)
		vec.x = vec.x - width;
	if (align & align_center)
		vec.x = vec.x - (width / 2);
	if (!active_)
		R_AddCmdDrawText(text, 0x7FFFFFFF, font_handle, menu->menux + vec.x, menu->menuy + vec.y, scale * 1.3, scale * 1.6, rotation, (float*)&col, 0);
	if (active_)
		CL_DrawTextPhysicalWithEffects(text, 0x7FFFFFFF, font_handle, menu->menux + vec.x, menu->menuy + vec.y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextWithEffects1(String text, float x, float y, float scale, color col, alignment align) {
	String Font = hash("extraSmallFont");
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffects1(text, 0x7FFFFFFF, font_handle, menu->menux + x, menu->menuy + y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextWithEffects(String text, float x, float y, float scale, color col, alignment align) {
	String Font = hash("extraSmallFont");
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffects(text, 0x7FFFFFFF, font_handle, menu->menux + x, menu->menuy + y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextWithEffectsUI(String text, float x, float y, float scale, color col, alignment align) {
	String Font = hash("extraSmallFont");
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffectsUI(text, 0x7FFFFFFF, font_handle, x, y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextWithEffectsUI1(String text, float x, float y, float scale, color col, alignment align) {
	String Font = hash("extraSmallFont");
	String pszfont = R_GetFontPathFromName(Font);

	if (text == NULL) return;

	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale * 1.4);

	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	CL_DrawTextPhysicalWithEffectsUI1(text, 0x7FFFFFFF, font_handle, x, y, 0, scale * 1.3, scale * 1.6, col, 3, color(0, 0, 0, 0), 0, 0, 0, 0, 0, 0);
}

void DrawTextUI(String text, float x, float y, float rotation, float scale, String font, color col, alignment align) {
	String pszfont = R_GetFontPathFromName(font);
	if (text == NULL) return;
	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale);
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	DrawTextWithEffectsUI(text, x, y, scale, col, align);
}

void DrawTextUI1(String text, float x, float y, float rotation, float scale, String font, color col, alignment align) {
	String pszfont = R_GetFontPathFromName(font);
	if (text == NULL) return;
	int font_handle = R_RegisterFont(pszfont, 0);
	int width = R_TextWidth(text, pszfont, scale);
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - width;
	if (align & align_center)
		x = x - (width / 2);
	DrawTextWithEffectsUI1(text, x, y, scale, col, align);
}

void DrawShader1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	CG_DrawRotatedPic1(x, y, w, h, angle, col, material);
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawShaderEsp(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);

	CG_DrawRotatedPicesp(x, y, w, h, angle, col, material);
}

void DrawShaderEsp1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);

	CG_DrawRotatedPicesp(x, (dc.height > 720) ? y / (1.5) : y, w, (dc.height > 720) ? h / (1.5) : h, angle, col, material);

}


void DrawShaderP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	CG_DrawRotatedPicp(x, y, w, h, angle, col, material);
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawShaderPP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	// 0x751940 - R_AddCmdDrawStretchPic(float x, float y, float w, float h, float s0, float t0, float s1, float t1, const float *color, Material *material)
	CG_DrawRotatedPicp(x, (dc.height > 720) ? y / (1.5) : y, w, (dc.height > 720) ? h / (1.5) : h, angle, col, material);
	//CG_DrawRotatedPicPhysical(x, y, w, h, col, angle, material, imagetrac);
}

void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, drawTypes drawtype) {
	/// background
	DrawShader(x, y, w, h, 0, bboxcolor, white, align_left);
	/// sides ( L / R )
	if (drawtype & DT_LR)
		DrawShader(x - 1, y - 1, 1, h + 2, 0, bbordercolor, white, align_left),
		DrawShader(x + w, y - 1, 1, h + 2, 0, bbordercolor, white, align_left);
	/// T / B
	if (drawtype & DT_TB)
		DrawShader(x - 1, y - 1, w + 2, 1, 0, bbordercolor, white, align_left),
		DrawShader(x - 1, y + h, w + 2, 1, 0, bbordercolor, white, align_left);
}

void DrawShader(float x, float y, float w, float h, color bg, color bd, int drawtype) {
	// main background
	DrawShader(x, y, w, h, 0, bg, white, align_left);
	// Left / Right
	if (drawtype == DT_LR)
		DrawShader(x - 1, y - 1, 2, h + 2, 0, bd, white, align_left),
		DrawShader(x + w, y - 1, 2, h + 2, 0, bd, white, align_left);

	// Top / Bottom
	if (drawtype & DT_TB)
		DrawShader(x - 1, y - 1, w + 2, 2, 0, bd, white, align_left),
		DrawShader(x - 1, y + h - 1, w + 2, 2, 0, bd, white, align_left);
}

float DrawTextWithBackground(String text, float x, float y, float scale, color textColor, color backgroundColor, alignment align) {
	float start_w = 10, start_h = 20;
	String pszfont = R_GetFontPathFromName(hash("extraSmallFont"));

	int text_w = R_TextWidth(text, pszfont, scale * 1.4) + start_w;
	int text_h = R_TextHeight(pszfont, scale * 1.4) + start_h;

	if (align == align_left) {
		DrawShader(x, y, text_w, text_h, 0, backgroundColor, white, align_left);
		DrawText(text, Vector2(x + (start_w / 2), y - (start_h / 4) + text_h), 0, scale, hash("extraSmallFont"), textColor, align_left, 1);
	}
	if (align == align_center) {
		DrawShader(x - (text_w / 2), y, text_w, text_h, 0, backgroundColor, white, align_left);
		DrawText(text, Vector2(x - (text_w / 2) + (start_w / 2), y - (start_h / 2) + text_h), 0, scale, hash("extraSmallFont"), textColor, align_left, 1);
	}
	if (align == align_right) {
		DrawShader(x - (text_w), y, text_w, text_h, 0, backgroundColor, white, align_left);
		DrawText(text, Vector2(x - (text_w)+(start_w / 2), y - (start_h / 2) + text_h), 0, scale, hash("extraSmallFont"), textColor, align_left, 1);
	}
	return text_h;	// height of everything
}

void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, color bbordercolor2) {
	DrawShaderUI(x - 1, y - 2, w + 2, h + 4, 0, bbordercolor, gradient_fadein, align_left);
	DrawShaderUI(x - 1, y - 2, w + 2, h + 4, 180, bbordercolor2, gradient_fadein, align_left);
	DrawShaderUI(x, y, w, h, 0, bboxcolor, white, align_left);
}

void DrawHaxShader(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal1(menu->menux + x, (dc.height > 720) ? menu->menuy + dc.height - dc.height + y : (menu->menuy / 1.27f) + y / (dc.aspect - menu->menusize), w, (dc.height > 720) ? h : h / (dc.aspect - menu->menusize), 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

void DrawHaxShader3(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal1(x, (dc.height > 720) ? -99 + dc.height - dc.height + y : (-99 / 1.27f) + y / (dc.aspect - menu->menusize), w, (dc.height > 720) ? h : h / (dc.aspect - menu->menusize), 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

void DrawHaxStaticShader(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(x, y, w, h, 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

void DrawHaxStaticShader2(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal1(menu->menux + x, menu->menuy + dc.height - dc.height + y, w, h, 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

float spin1, spin2;
void DrawOutline(float x, float y, float width, float height, color colorr, int thickness, alignment ali) {
	DrawShader(x, y - thickness + 4, width + (thickness * 2.1) - 2, 1.5, 0, color(10, 10, 10, 255), white, ali); // Top
	DrawShader(x, y + height - 2, width + (thickness * 2.1) - 2, 1.5, 0, color(10, 10, 10, 255), white, ali); // Bottem

	DrawShader((x - thickness + 2) - (menu->msize / 2), y - thickness + 2, thickness - 1, menu->sypos1 + 55, 0, color(10, 10, 10, 255), white, ali); // Left top down
	DrawShader((x - thickness + 2) - (menu->msize / 2), y + menu->sypos1 + 85, thickness - 1, height - menu->sypos1 - 86, 0, color(10, 10, 10, 255), white, ali); // Left bottem up
	DrawShader((x + width - 1) - (menu->msize / 2), y - thickness + 2, thickness - 1, menu->sypos1 + 55, 0, color(10, 10, 10, 255), white, ali); // Right top down
	DrawShader((x + width - 1) - (menu->msize / 2), y + menu->sypos1 + 85, thickness - 1, height - menu->sypos1 - 86, 0, color(10, 10, 10, 255), white, ali); // Right bottem up

	if (Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.scroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		//Draw scrollbar
		DrawShader(x - 1, y + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - 5, width + 1, 2.1, 0, menu->skin4, gradient_fadein, ali);// Scroll top
		DrawShader(x - 1, y + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - 5, width + 1, 2.1, 180, menu->skin6, gradient_fadein, ali); // Scroll top
		DrawShader(x - 1, y + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) + 24, width + 2, 2.1, 180, menu->skin5, gradient_fadein, ali); // Scroll bottem
		DrawShader(x - 1, y + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) + 24, width + 2, 2.1, 0, menu->skin3, gradient_fadein, ali); // Scroll bottem
	}

	//Draw border
	DrawShader(x, y - thickness, width + (thickness * 2.1) - 2, thickness + 1, 180, menu->skin6, gradient_fadein, ali); // Top>
	DrawShader(x, y - thickness, width + (thickness * 2.1) - 2, thickness + 1, 0, menu->skin4, gradient_fadein, ali); // Top<

	DrawShader(x - 1, y + height - 1, width + (thickness * 2.1), thickness + 1, 0, menu->skin3, gradient_fadein, ali); // Bottom>
	DrawShader(x - 1, y + height - 1, width + (thickness * 2.1), thickness + 1, 180, menu->skin5, gradient_fadein, ali); // Bottom<

	DrawHaxShader((x - thickness) - (menu->msize / 2) + 1, y - thickness, thickness, height + thickness + 1 / 2, -90, menu->skin5, gradient_fadein, ali); // Left>
	DrawHaxShader((x - thickness) - (menu->msize / 2) + 1, y - thickness, thickness, height + thickness + 1 / 2, 90, menu->skin6, gradient_fadein, ali); // Left<
	DrawHaxShader((x + width) - (menu->msize / 2) + 1, y - thickness, thickness, height + (thickness * 2) - 2 / 2, 90, menu->skin4, gradient_fadein, ali); // Right>
	DrawHaxShader((x + width) - (menu->msize / 2) + 1, y - thickness, thickness, height + (thickness * 2) - 2 / 2, -90, menu->skin3, gradient_fadein, ali); // Right<
}

void DrawStaticOutline(float x, float y, float width, float height, color color1, color color2, float thickness) {
	DrawShaderUI1(x - thickness, y - thickness, width + (thickness * 2), thickness, 180, menu->skin6, gradient_fadein, align_left); // Top>
	DrawShaderUI1(x - thickness, y - thickness, width + (thickness * 2), thickness, 0, menu->skin4, gradient_fadein, align_left); // Top<
	DrawShaderUI1(x - thickness - 1, y + height, width + (thickness * 2) + 1, thickness, 0, menu->skin3, gradient_fadein, align_left); // Bottom>
	DrawShaderUI1(x - thickness - 1, y + height, width + (thickness * 2) + 1, thickness, 180, menu->skin5, gradient_fadein, align_left); // Bottom<
	DrawHaxStaticShader(x - thickness - 1, y - thickness, thickness + 1, height + thickness, -90, menu->skin5, gradient_fadein, align_left); // Left>
	DrawHaxStaticShader(x - thickness - 1, y - thickness, thickness + 1, height + thickness, 90, menu->skin6, gradient_fadein, align_left); // Left<
	DrawHaxStaticShader(x + width, y - thickness, thickness + 1, height + (thickness * 2), 90, menu->skin4, gradient_fadein, align_left); // Right>
	DrawHaxStaticShader(x + width, y - thickness, thickness + 1, height + (thickness * 2), -90, menu->skin3, gradient_fadein, align_left); // Right<
}

void DrawHaxStaticShader1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(menu->menux + x, menu->menuy + y, w, h, 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

void DrawHaxStaticShaderSpin(float x, float y, float w, float h, float angle, float s, color col, Material* material, alignment align) {
	if (align & align_left)
		x = x;
	if (align & align_right)
		x = x - w;
	if (align & align_center)
		x = x - (w / 2);
	R_AddCmdDrawStretchPicRotateSTInternal(x, y, w, h, 1, 1, 1, 1, 1, angle, (float*)&col, material);
}

void DrawStaticOutline1(float x, float y, float width, float height, color color1, int thickness) {
	DrawShader3(x - thickness, y - thickness - 2, width + (thickness * 2.1), thickness, 180, menu->skin6, gradient_fadein, align_left); // Top>
	DrawShader3(x - thickness, y - thickness - 2, width + (thickness * 2.1), thickness, 0, menu->skin4, gradient_fadein, align_left); // Top<
	DrawShader3(x - thickness, y + height - 1, width + (thickness * 2.1), thickness, 0, menu->skin3, gradient_fadein, align_left); // Bottom>
	DrawShader3(x - thickness, y + height - 1, width + (thickness * 2.1), thickness, 180, menu->skin5, gradient_fadein, align_left); // Bottom<
	DrawHaxShader3(x - thickness, y - thickness, thickness, height + thickness + 1 / 2, -90, menu->skin5, gradient_fadein, align_left); // Left>
	DrawHaxShader3(x - thickness, y - thickness, thickness, height + thickness + 1 / 2, 90, menu->skin6, gradient_fadein, align_left); // Left<
	DrawHaxShader3(x + width, y - thickness, thickness, height + (thickness * 2) - 2 / 2, 90, menu->skin4, gradient_fadein, align_left); // Right>
	DrawHaxShader3(x + width, y - thickness, thickness, height + (thickness * 2) - 2 / 2, -90, menu->skin3, gradient_fadein, align_left); // Right<
}

float DrawTextWithBackground_UI(String text, float x, float y, float scale, color textColor, color backgroundColor, color backgroundColor1, alignment align) {
	float start_w = 10, start_h = (dc.height > 720) ? 20 : 10;
	String pszfont = R_GetFontPathFromName(hash("extraSmallFont"));
	int text_w = R_TextWidth(text, pszfont, scale * 1.3) + start_w;
	int text_h = R_TextHeight(pszfont, scale) + start_h;

	if (align == align_left) {
		DrawStaticOutline(x, y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, backgroundColor, menu->skin2, 2);
		DrawShaderUI1(x, y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, 0, backgroundColor1, white, align_left);
		DrawTextUI1(text, x + (start_w / 2), (dc.height > 720) ? y - (start_h)+text_h + 5 : y - (start_h / 4) + text_h + 6, 0, scale, hash("extraSmallFont"), textColor, align_left);
	}
	if (align == align_center) {
		DrawStaticOutline(x - (text_w / 2), y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, backgroundColor, menu->skin2, 2);
		DrawShaderUI1(x - (text_w / 2), y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, 0, backgroundColor1, white, align_left);
		DrawTextUI1(text, x - (text_w / 2) + (start_w / 2), (dc.height > 720) ? y - (start_h) : y - (start_h / 2) + text_h, 0, scale, hash("extraSmallFont"), textColor, align_left);
	}
	if (align == align_right) {
		DrawStaticOutline(x - (text_w), y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, backgroundColor, menu->skin2, 2);
		DrawShaderUI1(x - (text_w), y, text_w, (dc.height > 720) ? start_h - 5 : start_h + 16, 0, backgroundColor1, white, align_left);
		DrawTextUI1(text, x - (text_w)+(start_w / 2), (dc.height > 720) ? y - (start_h)+text_h + 5 : y - (start_h / 4) + text_h + 6, 0, scale, hash("extraSmallFont"), textColor, align_left);
	}
	return (dc.height > 720) ? start_h - 9 : start_h + 15;	// height of everything
}

void StealName(int clientNum) {
	char playerName[256];
	if (clientNum == cg->clientNum)
		snprintf(playerName, sizeof(playerName), hash(";cmd userinfo \"\\name\\%s\\xuid\\%s"), 0x1F504DC, 0x26C06E8);
	else
		snprintf(playerName, sizeof(playerName), hash(";cmd userinfo \"\\name\\%s\\xuid\\%s"), cg->clients[clientNum].PlayerName, 0x26C06E8);
	Cbuf_AddText(playerName);
}

typedef int64_t slong;
void closedpartybypass(bool toggle) {
	char closeoff[] = { 0x38, 0x60 };
	char closeoff2[] = { 0x38 };
	char closeon[] = { 0x88 };
	if (toggle) {
		WriteMemory(0x521C38, closeoff2, 1);
		WriteMemory(0x533970, closeoff, 2);
		WriteMemory(0x53397C, closeoff, 2);
		WriteMemory(0x533988, closeoff, 2);
		WriteMemory(0x533948, closeoff, 2);
		WriteMemory(0x53391C, closeoff, 2);
		WriteMemory(0x53394C, closeoff, 2);
	} else {
		WriteMemory(0x521C38, closeon, 1);
	}
}

CellFsErrno ReadAsset(const char* path, void* data, size_t size) {

	auto permission = cellFsChmod(path, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}

	int fd = 0;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;
	error = cellFsRead(fd, data, size, NULL);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	return cellFsClose(fd);
}

int DB_GetImagePartPoolSize_t[2] = { 0x018e928, TOC };
int(*DB_GetImagePartPoolSize)(void) = (int(*)(void))DB_GetImagePartPoolSize_t;

int DB_GetImageAtIndex_t[2] = { 0x018e904, TOC };
GfxImage* (*DB_GetImagePartAtIndex)(uint index) = (GfxImage * (*)(uint))DB_GetImageAtIndex_t;

GfxImage* ReadAssetGFX(std::string str) {
	for (int i = 0; i < DB_GetImagePartPoolSize(); i++) {
		GfxImage* curImage = DB_GetImagePartAtIndex(i);
		if (str == curImage->name) {
			return curImage;
		}
	}
	return NULL;
}

CellFsErrno WriteAsset(const char* path, void* data, size_t size) {
	auto permission = cellFsChmod(path, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}

	int fd = 0;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_APPEND, &fd, NULL, 0);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	error = cellFsWrite(fd, data, size, NULL);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	return cellFsClose(fd);
}

void local_command_config(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);
	if (strlen(buffer) <= 0) return;

	char FileName[1000];
	char File[30];
	const char* FilePath = hash("/dev_hdd0/tmp/Genisys/");
	sprintf(FileName, hash("%s%s.ini"), FilePath, buffer);
	sprintf(File, hash("%s.ini"), buffer);
	if (std::find(Ini.Inis.begin(), Ini.Inis.end(), File) == Ini.Inis.end()) {
		SaveToIniFile(FileName);
		ProcessConfig();
		Mshit.ch = hash("Status: ^2Config Created");
	} else {
		Mshit.ch = hash("Status: ^1Config Already Exists");
	}
}

void CreateConfig() {
	XShowKeyboardUI(0, L"Name Your Custom Config", L"Custom Config #1", 30, local_command_config, 0);
}

void DelConfig() {
	char FileName[100];
	const char* FilePath = hash("/dev_hdd0/tmp/Genisys/");
	Com_Sprintf(FileName, sizeof(FileName), hash("%s%s"), FilePath, Ini.Name);
	cellFsUnlink(FileName);
	for (int i = 0; i < Ini.Inis.size(); i++) {
		if (Ini.Inis.at(i).c_str() == Ini.Name)
			Ini.Inis.at(i).erase();
	}
	ProcessConfig();
	Mshit.ch = hash("Status: ^2Config Deleted");
	Mshit.id = Mshit.prev[Mshit.id - 2];
}

void isave() {
	char FileName[50];
	const char* FilePath = hash("/dev_hdd0/tmp/Genisys/");
	Com_Sprintf(FileName, sizeof(FileName), hash("%s%s"), FilePath, Ini.Name);
	SaveToIniFile(FileName);
	Mshit.ch = hash("Status: ^2Config Saved");
}

void iload() {
	char FileName[50];
	const char* FilePath = hash("/dev_hdd0/tmp/Genisys/");
	Com_Sprintf(FileName, sizeof(FileName), hash("%s%s"), FilePath, Ini.Name);
	ReadFromIniFile(FileName);
	Mshit.ch = hash("Status: ^2Config Loaded");
	noshit();
}

void* Memcp__(void* dst0, const void* src0, size_t len0) {
	char* dst = (char*)dst0;
	char* src = (char*)src0;
	void* save = dst0;
	while (len0--)
		*dst++ = *src++;
	return save;
}

asset assets;
char array_[0x8] = { 0x62, 0x1E, 0xF4, 0xEF, 0x25, 0x21, 0x93, 0x23 };
void loadcamo(String camo) {
	ReadAsset(camo, &assets.Weaponized_asset, 0x155E0);
}

void loadgp() {
	char boolBuff[255];
	snprintf(boolBuff, sizeof(boolBuff), hash("/dev_hdd0/tmp/Genisys/Custom_Camos/Gp.gen"));
	ReadAsset(boolBuff, &assets.gp, 2048);
}

void loadchck() {
	char boolBuff[255];
	snprintf(boolBuff, sizeof(boolBuff), hash("/dev_hdd0/tmp/Genisys/Custom_Camos/loadchck.gen"));
	//ReadAsset(boolBuff, &assets.Chck, 1024);
}

void load_Asset(String camo, int address, void* data) {
	char boolBuff[255];
	snprintf(boolBuff, sizeof(boolBuff), hash("/dev_hdd0/tmp/Genisys/Custom_Camos/%s.gen"), camo);
	ReadAsset(boolBuff, data, sizeof(data));
}

int getFileSize(const char* file) {

	auto permission = cellFsChmod(file, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf(hash("perm: 0x%X\n"), permission);
	}

	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		CellFsStat sb;
		ret = cellFsFstat(fd, &sb);
		if (!ret) {
			return sb.st_size;
		}
	}
	return -1;
}

void readFile(const char* file, char buf[], int size) {


	auto permission = cellFsChmod(file, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf(hash("perm: 0x%X\n"), permission);
	}


	int fd;
	int ret;
	uint64_t pos;
	uint64_t nread;
	ret = cellFsOpen(file, 0, &fd, NULL, 0);
	if (!ret) {
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		ret = cellFsRead(fd, buf, size, &nread);
		if (!ret) {
			cellFsClose(fd);
		}
	}
}

bool CScr_GetInKillcam(cg_s* pcg) {
	if (cg != NULL)
		return (*(int*)(&cg + 0x69C68) == 1);
	else
		return false;
}

int __cdecl DB_FindXAssetHeader(XAssetType type, String name, bool errorIfMissing, int waitTime) {
	//Invoke<int>(0x18ac04, type, name, errorIfMissing, waitTime);
}

struct ScriptParseTree {
	const char* name;
	int len;
	const char* buffer;
};

void InjectCustomGSC() {
	const char* filePath = hash("");
	int fileSize = getFileSize((const char*)filePath);

	if (fileSize > 0) {
		memset((void*)0x10040000, 0, fileSize + 1);
		readFile((const char*)filePath, (char*)0x10040000, fileSize);

		ScriptParseTree* scriptFile = (ScriptParseTree*)DB_FindXAssetHeader(ASSET_TYPE_IMAGE, "", 1, -1);
		int filePointer = (int)&scriptFile->buffer;

		WriteMemory(filePointer, (char*)0x10040000, 4);
	} else {
	}
}

bool isHostMigrating() {
	if ((ClientUIActive_s->migrationState == CMSTATE_INACTIVE || ClientUIActive_s->migrationState == CMSTATE_OLDHOSTLEAVING || ClientUIActive_s->migrationState == CMSTATE_LIMBO || ClientUIActive_s->migrationState == CMSTATE_NEWHOSTCONNECT)) {
		return true;
	} else {
		return false;
	}
}

int CL_AllLocalClientsDisconnected_t[2] = { 0x6C2488, TOC };
bool (*CL_AllLocalClientsDisconnected)() = (decltype(CL_AllLocalClientsDisconnected))CL_AllLocalClientsDisconnected_t;

bool InGame() {
	return CL_AllLocalClientsDisconnected() == 0;
}

int SV_IsMigrating_t[2] = { 0x03514f8, TOC };
bool (*SV_IsMigrating)() = (decltype(SV_IsMigrating))SV_IsMigrating_t;

int CL_GetLocalClientMigrationState(int localClientNum) {
	return *reinterpret_cast<int*>(0xF0F88C + (localClientNum * 0x458));
}

bool cl_ingame_() {
	if (CL_AllLocalClientsDisconnected() == 0 && !SV_IsMigrating() && CL_GetLocalClientMigrationState(0) == CMSTATE_INACTIVE) {
		if (*(int*)0x0F0F88C != 0)
			return false;
		
		if (menu->bdisconnect) {
			menu->fpssaving = false;
			return false;
		}

		if (cg == NULL) {
			return false;
		}

		WeaponVariantDef* weapondefid = BG_GetWeaponVariantDef(cg->playerstate.weapon);
		if (weapondefid == NULL) {
			return false;
		}

		if ((*(bool*)(0x01cb68d8) && (*(int*)(0xE22F18) > 0 && *(int*)(0xE22F1C) > 0 && *(int*)(0xE22F20) && *(int*)(0xD689D8) > 0) && centity != NULL) && cg->serverTime > 0 && cg->playerstate.commandTime > 0) {
			return true;
		}
	}

	return false;
}

void Global_Ingame() {
	if (*(bool*)(0x01cb68d8) == false) {

		menu->bdisconnect = false;
	}

}

int CG_CycleWeapon_t[2] = { 0xF6D34, TOC };
void(*CG_CycleWeapon_f)(int localClientNum, int cycleForward) = (void(*)(int localClientNum, int cycleForward))CG_CycleWeapon_t;

void CG_CycleWeapon(int localClientNum, int cycleForward) {
	CG_CycleWeapon_f(localClientNum, cycleForward);
}

int BG_GetClipSize_t[2] = { 0x0601a40, TOC };
int(*BG_GetClipSize_f)(int Weapon) = (int(*)(int))BG_GetClipSize_t;

int BG_GetClipSize(int Weapon) {
	return BG_GetClipSize_f(Weapon);
}

void Cancel_Reload() {
	playerState_s* playerState = CG_GetPredictedPlayerState(0);
	if (playerState->weaponDelay != 0 && playerState->weaponTime != 0) {
		bot.reload.bReloading = true;
	} else {

		if (bot.reload.bReloading) {
			int ammo = BG_GetAmmoInClip(playerState, playerState->weapon);
			int ClipSize = BG_GetClipSize(playerState->weapon);
			if (ammo == ClipSize) {
				CG_CycleWeapon(0, 0);
				bot.reload.iInt++;
				if (bot.reload.iInt >= 2) bot.reload.iInt = 0, bot.reload.bReloading = !bot.reload.bReloading;
			}
		}
	}
}


bool CG_VisionSetStartLerp_To(int localClientNum, visionSetMode_t mode, visionSetLerpStyle_t style, const char* nameTo, int duration) {
	//return Invoke<bool>(0xDB698, localClientNum, mode, style, nameTo, duration);
}

void CScr_VisionSetNaked() {
	int dur = floorf((1 * 1000) + .5);
	//CG_VisionSetStartLerp_To(0, VISIONSETMODE_FLARE, VISIONSETLERP_TO_SMOOTH, "remote_mortar_enhanced", dur);
}

void disableDLC(bool* rs) {
	*rs = !*rs;
	//*(int*)0x01aadab8 = *rs ? 0x00 : 0x04;//dlc0 : NukeTown
	*(int*)0x01aadbd8 = *rs ? 0x00 : 0x20;//dlc1 : Revolution
	*(int*)0x01aadcf8 = *rs ? 0x00 : 0x10;//dlc2 : Uprising
	*(int*)0x01aade18 = *rs ? 0x00 : 0x40;//dlc3 : Vengeance
	*(int*)0x01aadf38 = *rs ? 0x00 : 0x80;//dlc4 : Apocalypse
}

bool Waits(const unsigned long& Time) {
	clock_t Tick = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Tick < 0) // if clock() fails, it returns -1
		return 0;
	clock_t Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
	if (Now < 0)
		return 0;
	while ((Now - Tick) < Time) {
		Now = clock_t(float(clock()) / float(CLOCKS_PER_SEC) * 1000.f);
		if (Now < 0)
			return 0;
	}
	return 1;
}

void WriteAsset(String Replace, String Image, int Delay) {
	GfxImage* FxImage = ReadAssetGFX(Image);

	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate) {
		int size = FxImage->texture.offset;
		WriteMemory((uint64_t)FxImage->Pixels, assets.Weaponized_asset, size);
		itick = Sys_Milliseconds(), iwait = Delay;
	}
}

int BG_UsingVehicleWeapon_t[2] = { 0x5F24AC, TOC };
int(*BG_UsingVehicleWeapon_f)(playerState_s* ps) = (int(*)(playerState_s*))BG_UsingVehicleWeapon_t;

int BG_UsingVehicleWeapon(playerState_s* ps) {
	return BG_UsingVehicleWeapon_f(ps);
}

int UI_GetActiveMenu_t[2] = { 0x0371D50, TOC };
int(*UI_GetActiveMenu_f)(int localNum) = (int(*)(int))UI_GetActiveMenu_t;

void PartyTime() {
	if (menu->bForceInv) {
		*(char*)0x535CEB = 0x90;
		*(char*)0x535D67 = 0x80;
		*(char*)0x5359FC = 0x60;
		strcpy((char*)0x96EC34, hash("Accept to Join..."));
		strcpy((char*)0x096ec4c, hash("Accept invite to join the user"));
	} else {
		*(char*)0x535CEB = 0x80;
		*(char*)0x535D67 = 0x90;
		*(char*)0x5359FC = 0x90;
		strcpy((char*)0x96EC34, hash("Game Invite"));
		strcpy((char*)0x096ec4c, hash("MENU_GAME_INVITE_MESSAGE"));
	}

	if (menu->bClosedBypass) {
		char array[4] = { 0x38, 0x60, 0x00, 0x00 };
		*(char*)0x521C38 = 0x38;
		memcpy((char*)0x533970, array, 4);
		memcpy((char*)0x53397C, array, 4);
		memcpy((char*)0x533988, array, 4);
		memcpy((char*)0x533948, array, 4);
		memcpy((char*)0x53391C, array, 4);
		memcpy((char*)0x53394C, array, 4);
		memcpy((char*)0x533988, array, 4);
	} else {
		*(char*)0x521C38 = 0x88;
	}
}

int UI_GetActiveMenu(int localNum) {
	return UI_GetActiveMenu_f(localNum);
}

int bdHashTiger192_t[2] = { 0x07e90dc, TOC };
void(*bdHashTiger192_f)(int* localNum) = (void(*)(int*))bdHashTiger192_t;

int bdHashTiger192_hash_t[2] = { 0x07e9188, TOC };
void(*bdHashTiger192_hash_f)(const char* data, const unsigned int dataSize, const char* result, unsigned int* resultSize) = (void(*)(const char*, const unsigned int, const char*, unsigned int*))bdHashTiger192_hash_t;

int bdHashTiger192_t_[2] = { 0x07e9110, TOC };
void(*bdHashTiger192_f_)(int* localNum) = (void(*)(int*))bdHashTiger192_t_;

int RemoveBuffer_t[2] = { 0x07ec624, TOC };
unsigned long long(*RemoveBuffer)(const void* src, const unsigned int srcSize, const unsigned int offset, unsigned int* newOffset, void* const dest, const unsigned int readSize) = (unsigned long long(*)(const void*, const unsigned int, const unsigned int, unsigned int*, void* const, const unsigned int))RemoveBuffer_t;

GfxImage* ReadAsset(std::string str) {
	for (int i = 0; i < DB_GetImagePartPoolSize(); i++) {
		GfxImage* curImage = DB_GetImagePartAtIndex(i);
		if (str == curImage->name) {
			return curImage;
		}
	}
	return NULL;
}

 char* ReadAssetFromFile(const char* path) {

	auto permission = cellFsChmod(path, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}

	int fd = 0;
	void* data;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0);

	CellFsStat stat_handle;
	cellFsStat(path, &stat_handle);

	if (error != CELL_FS_SUCCEEDED)
		return NULL;

	char* myArray = (char*)_sys_malloc((size_t)stat_handle.st_size);

	error = cellFsRead(fd, myArray, stat_handle.st_size, NULL);
	if (error != CELL_FS_SUCCEEDED)
		return NULL;

	cellFsClose(fd);
	return myArray;
}

void WriteAsset(std::string Replace, std::string Image, int Delay) {

	GfxImage* FxImage = ReadAsset(Image.c_str());

	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate) {
		int size = FxImage->texture.offset;
		char* File = ReadAssetFromFile(Replace.c_str());
		WriteHenMem(FxImage->Pixels, File, size);
		_sys_free(File);
		memset(File, 0, sizeof(File));
		itick = Sys_Milliseconds(), iwait = Delay;
	}
}

 char* ReadAssetFromFile1(const char* path) {

	auto permission = cellFsChmod(path, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}

	int fd = 0;
	void* data;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0);

	CellFsStat stat_handle;
	cellFsStat(path, &stat_handle);

	if (error != CELL_FS_SUCCEEDED)
		return NULL;

	char* myArray = (char*)_sys_malloc((size_t)stat_handle.st_size);

	error = cellFsRead(fd, &myArray, stat_handle.st_size, NULL);
	if (error != CELL_FS_SUCCEEDED) {
		printf("%x\n", error);
		return NULL;
	}

	cellFsClose(fd);
	return myArray;
}

void WriteAsset1(String Replace, GfxImage* Image, int Delay) {
	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate) {
		int size = Image->texture.offset;
		char* File = ReadAssetFromFile1(Replace);
		WriteHenMem(Image->Pixels, File, size);
		_sys_free(File);
		itick = Sys_Milliseconds(), iwait = Delay;
	}
}

XModel* Model;

void DrawSkybox(String image) {

	Model = *(XModel**)0x0d94ba0;
	WriteAsset1(image, Model->materialHandles[0]->TextureTable[0].image, 500);
}

int Scr_ExecThread_t[2] = { 0x004A2AAC, TOC };
unsigned short (*Scr_ExecThread)(int inst, int handle, unsigned int paramCount) = (decltype(Scr_ExecThread))&Scr_ExecThread_t;

int Scr_GetFunctionHandle_t[2] = { 0x0048952C, TOC };
int (*Scr_GetFunctionHandle)(int inst, const char* filename, const char* name, XAssetHeader* assetHeader, bool errorIfMissing) = (decltype(Scr_GetFunctionHandle))&Scr_GetFunctionHandle_t;

int Scr_FreeThread_t[2] = { 0x004A2FCC, TOC };
void (*Scr_FreeThread)(int inst, unsigned short handle) = (decltype(Scr_FreeThread))&Scr_FreeThread_t;

uint32_t nuke_det_script = Scr_GetFunctionHandle(0, hash("maps/mp/mp_nuketown_2020"), hash("nuke_detonation"), 0, true);
void execThread(int32_t handle, uint32_t paramCount) {
	uint16_t tid = Scr_ExecThread(0, handle, paramCount);
	Scr_FreeThread(0, tid);
}

std::vector<std::string> split(std::string s, std::string del) {
	size_t pos = 0;
	std::string token;
	std::vector<std::string> splits;
	while ((pos = s.find(del)) != std::string::npos) {
		token = s.substr(0, pos);
		splits.push_back(token);
		s.erase(0, pos + del.length());
	}
	return splits;
}

void test69() {
	execThread(nuke_det_script, 0);
}

int zombiecheck_t[2] = { 0x31A080, TOC };
bool(*zombiecheck)() = (bool(*)())zombiecheck_t;

int SV_GameSendServerCommand_t[2] = { 0x349F6C, TOC };
void(*SV_GameSendServerCommand_f)(int r1, int r2, const char* r3) = (void(*)(int, int, const char*))SV_GameSendServerCommand_t;

void SV_GameSendServerCommand(const char* bufferd) {
	char buffer[100];
	Com_Sprintf(buffer, sizeof(buffer), "; \"%s\"", bufferd);
	SV_GameSendServerCommand_f(-1, 1, buffer);
}

int UI_OpenToastPopup_t[2] = { 0x003779EC, TOC };

void* (*UI_OpenToastPopup)(int localClientNum, const char* toastPopupIconName, const char* toastPopupTitle, const char* toastPopupDesc, int toastPopupDuration) = (void* (*)(int, const char*, const char*, const char*, int)) & UI_OpenToastPopup_t;

bool isNumericChar(char x) {
	return (x >= '0' && x <= '9') ? true : false;
}

int _atoi(const char* str) {
	if (*str == NULL)
		return 0;

	int res = 0,
		sign = 1,
		i = 0;

	if (str[0] == '-') {
		sign = -1;
		i++;
	}
	for (; str[i] != '\0'; ++i) {
		if (!isNumericChar(str[i] & 0xFFFFFFFFF)) {
		} else {
			res = res * 10 + str[i] - '0';
		}
	}
	return sign * res;
}


int BG_EvaluateTrajectory_t[2] = { 0x05C16D0, TOC };
void(*BG_EvaluateTrajectory_f)(trajectory_t* tr, int atTime, Vector3* result) = (void(*)(trajectory_t*, int, Vector3*))BG_EvaluateTrajectory_t;

#define GetSign(a) ((a)?((*(int*)&(a)>>31)|1):0)

int AngleNormalize360_a[2] = { 0x3CD798, TOC };
double(*AngleNormalize360)(const float angle) = (decltype(AngleNormalize360))AngleNormalize360_a;

float AngleNormalize180(float angle) {
	angle = AngleNormalize360(angle);
	if (angle > 180.0) {
		angle -= 360.0;
	}
	return angle;
}

float EntityInterpolation(trajectory_t* trajectory, int time, Vector3* result, float scale) {
	float flResult = 0.0f;
	if (trajectory->trType && trajectory->trType != 1 && trajectory->trType != 14 && trajectory->trType != 10) {
		BG_EvaluateTrajectory_f(trajectory, time, result);
		flResult = cg->get<float>(0x48384);//frameInterpolation 
	}

	else {
		*result = trajectory->trBase;
	}

	return flResult;
}


void ApplyPositionPrediction(centity_t* entity) {

	Vector3 vOldPosition, vNewPosition, vDeltaPosition;

	auto flResult = EntityInterpolation(&entity->prevState.pos, cg->snap->serverTime, &vOldPosition, cg->get<float>(0x48384)); // frameInterpolation
	EntityInterpolation(&entity->nextState.lerp.pos, cg->nextSnap->serverTime, &vNewPosition, flResult);

	vDeltaPosition = vNewPosition - vOldPosition;

	vDeltaPosition.x = (float)GetSign(vDeltaPosition.x);
	vDeltaPosition.y = (float)GetSign(vDeltaPosition.y);
	vDeltaPosition.z = (float)GetSign(vDeltaPosition.z);

	entity->pose.origin += (vDeltaPosition * (cg->get<int>(0x48388) / 1000.0f));
	entity->pose.origin += (vDeltaPosition * (cactive->get<int>(0x68) / 1000.0f));
}

void ApplyAnglePrediction(centity_t* entity) {
	float flResult;
	Vector3 vOldAngles, vNewAngles, vDeltaAngles;

	flResult = EntityInterpolation(&entity->prevState.apos, cg->snap->serverTime, &vOldAngles, cg->get<float>(0x48384));// frameInterpolation
	EntityInterpolation(&entity->nextState.lerp.apos, cg->nextSnap->serverTime, &vNewAngles, flResult);

	vDeltaAngles.x = AngleNormalize180(vNewAngles.x - vOldAngles.x);
	vDeltaAngles.y = AngleNormalize180(vNewAngles.y - vOldAngles.y);
	vDeltaAngles.z = AngleNormalize180(vNewAngles.z - vOldAngles.z);

	vDeltaAngles.x = (float)GetSign(vDeltaAngles.x);
	vDeltaAngles.y = (float)GetSign(vDeltaAngles.y);
	vDeltaAngles.z = (float)GetSign(vDeltaAngles.z);

	entity->pose.angles += (vDeltaAngles * (cg->get<int>(0x48388) / 1000.0f));
	entity->pose.angles += (vDeltaAngles * (cactive->get<int>(0x68) / 1000.0f));
}

std::deque<party_pulling> messages;
void pull_client_to_lobby(SceNpId npid, int requestCount, std::uint64_t interval, uint64_t timeout) {
	JoinSessionMessage join_session_message;
	memset(&join_session_message, 0, sizeof(JoinSessionMessage));

	join_session_message.mType = JOIN_REPLY;
	join_session_message.isJoinable = true;
	join_session_message.invited = true;
	join_session_message.inviteInfo.sessionInfo = get_current_party()->get_session_data()->dyn.sessionInfo;
	join_session_message.maxLocalPlayersAllowed = 4;
	join_session_message.inviteInfo.fromMPInvite = 0;
	join_session_message.allowGuests = true;
	join_session_message.inviteID = requestCount;

	party_pulling puller;
	memset(&puller, 0, sizeof(party_pulling));

	puller.data = join_session_message;
	puller.interval = interval;
	puller.npid = npid;
	puller.timeout = timeout;
	puller.flags |= from_bo2;
	if (messages.size() != 1) {
		messages.push_back(puller);
	}
}

void zmthread(uint64) {
	while (true) {
		while (!messages.empty()) {
			auto iter = messages.begin();
			auto start_time = Sys_Milliseconds();
			while (iter->data.inviteInfo.fromMPInvite ? Party_FindMemberByXUID(get_current_party(), getUserID(iter->npid.handle.data)) == -1 : true && (Sys_Milliseconds() - start_time) < iter->timeout) {
				if (local->interrupted) {
					//printf("interrupted thread!\n");
					break;
				}

				if (*(int*)0x26c071c != 6 && iter->flags & from_bo2) {
					//printf("not connected to demonware!\n");
					break;
				}

				Live_SendJoinInfo(&iter->npid, &iter->data);

				iter->data.inviteID++;
				//printf("invite: %i\n", iter->data.inviteID);

				Sleep(iter->interval);
			}

			local->interrupted = false;

			messages.pop_front();
		}
		Sleep(10);
	}
	sys_ppu_thread_exit(0);
}

void sendtozmint() {
	sys_ppu_thread_t pulling_thread{};
	sys_ppu_thread_create(&pulling_thread, zmthread, 0, 0x47C, 0x100, 0, "\0");
}

#pragma endregion