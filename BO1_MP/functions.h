#ifndef Functions_h
#define Functions_h

extern bool CScr_IsAlive(int i);
extern bool Dvar_GetBool(String dvarName);
extern const char* (*Cmd_Argv)(int argIndex);
extern int (*Cmd_Argc)();
extern bool cl_ingame_();
extern void sendtozmint();
extern void pull_client_to_lobby(SceNpId npid, int requestCount, std::uint64_t interval, uint64_t timeout);
std::vector<std::string> split(std::string s, std::string del);
extern bool WorldPosToScreenPos(Vector3 worldPos, Vector2 * screenPos);
extern void XShowKeyboardUI(int localClientNum, const wchar_t * title, const wchar_t * presetMsg, unsigned int length, void(*KB_COMPLETE)(int localClientNum, const wchar_t * wstring, unsigned int Length), unsigned int panel_mode);
extern void WideCharToMultibyte(const wchar_t * wchar, int length, char * buffer);
extern void PosPrediction(int i, Vector3 BonePos, int Scale, bool NotAllowZ);
extern void DrawHaxShader3(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void USleep(usecond_t time);
extern void TeleportToPower();
extern void TeleportToPaP();
#pragma region cg
extern bool CG_IsEntityFriendlyNotEnemy(centity_s * cent);
extern void AimTarget_GetTagPos(centity_s * cent, short tagname, Vector3 *pos);
extern void VectoAngles(Vector3 vec, Vector3* angles);
extern Vector3 AnglesToFoward(Vector3 Origin, Vector3 Angles, float diff);
extern void GetTagPos(centity_s* cent, short tagName, Vector3* pos);
extern bool EnemyAimingAtMe(int enemy);
extern int getUserID(const char* username);
#pragma endregion
#pragma region graphics
extern int getFileSize(char* file);
extern GfxImage* ReadAssetGFX(std::string str);
extern int R_TextWidth(String text, const char * font, float scale);
extern int R_TextHeight(String font, float scale);
Material* Material_RegisterHandle(String material, int ImageTrac);
extern bool isHostMigrating();
extern void Global_Ingame();
extern String Dvar_GetString(String dvarName);
extern float Dvar_GetFloat(String dvarName);
extern bool(*AimTarget_GetTagPos_f)(centity_s * cent, short tagname, Vector3* r4);
extern void R_AddCmdDrawText(String Text, int MaxChars, int Font, float X, float Y, float XScale, float YScale, float Rotation, float * Color, int Style);
extern void DrawTextWithEffects(String text, float x, float y, float scale, color col, alignment align);
extern void DrawTextWithEffectsUI(String text, float x, float y, float scale, color col, alignment align);
extern void DrawTextWithEffects1(String text, float x, float y, float scale, color col, alignment align);
extern void CL_DrawStretchPicInternal(float x, float y, float w, float h, int horzAlign, int vertAlign, float centerS, float centerT, float radiusST, float scaleFinalS, color color, pvoid material);
extern void DrawText(String text, Vector2 vec, float rotation, float scale, String font, color col, alignment align, bool active_);
extern float DrawTextWithBackground_UI(String text, float x, float y, float scale, color textColor, color backgroundColor, color backgroundColor1, alignment align);
extern void DrawShaderUI(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void DrawHaxStaticShaderSpin(float x, float y, float w, float h, float angle, float s, color col, Material* material, alignment align);
extern void Flash_name_();
extern void disableDLC(bool* rs);
extern bool CScr_GetInKillcam(cg_s* pcg);
extern void readFile(char* file, char buf[], int size);
extern void Cancel_Reload();
extern String(*R_GetFontPathFromName)(String text);
extern int(*Com_Sprintf)(char *dest, int size, const char *fmt, ...);
extern int(*Sys_Milliseconds)();
extern int (*BG_GetAmmoInClip)(playerState_s* ps, int weapon);
extern void CG_GameMessage(char * r2);
extern void Cbuf_AddText(char * r2);
extern void isave();
extern void iload();
extern void Add_name_();
extern void Add_name__();
extern void DrawTextUI(String text, float x, float y, float rotation, float scale, String font, color col, alignment align);
extern int notouch();
extern char* remove_http_header(char* request);
extern void DrawSkybox(String image);
extern int irand_(int min, int max_);
extern void DrawHaxStaticShader1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void CG_DrawRotatedPic(float x, float y, float width, float height, float angle, color c, Material* material);
extern void DrawShaderEsp(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void DrawShaderEsp1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void CG_DrawRotatedPic1(float x, float y, float width, float height, float angle, color c, Material* material);
extern void DrawShader1(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void DrawShaderP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align);
extern void DrawShaderPP(float x, float y, float w, float h, float angle, color col, pvoid material, alignment align);
extern void DrawShader(Vector2 Pos, float w, float h, float angle, color col, Material* material, alignment align);
extern void DrawShader(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void DrawOutline(float x, float y, float width, float height, color color, int thickness, alignment ali);
extern void DrawStaticOutline(float x, float y, float width, float height, color color1, color color2, float thickness);
extern void DrawStaticOutline1(float x, float y, float width, float height, color color1, int thickness);
extern void DrawBorderBox(float x, float y, float w, float h, color bboxcolor, color bbordercolor, drawTypes drawtype);
extern void ChangeIP();
extern dvar_t* Dvar_FindVar(String dvarName);
extern int Dvar_GeInt(String dvarName);
extern void StealName(int clientNum);
extern float DrawTextWithBackground(String text, float x, float y, float scale, color textColor, color backgroundColor, alignment align);
extern void SmokeColor(bool * rs);
extern void Smokehandle();
extern float sky_rotate;
extern void rssm(bool * rs);
extern void Psbutn();
extern void test69();
extern void GetTemps(uint8_t* CPU, uint8_t* RSX, bool C);
extern CellFsErrno ReadAsset(const char* path, void* data, size_t size);
extern void loadcamo(String camo);
extern void Dankmap(bool* rs);
extern void loadgp();
extern void CreateConfig();
extern void DelConfig();
extern void loadchck();
extern void ChangeClanTagPreGame(char* str);
extern void* Memcp__(void* dst0, const void* src0, size_t len0);
extern void CScr_VisionSetNaked();
inline const char* decrypt(const char* str, float key)
{
	int length = strlen(str);

	char* decrypted = new char[0x400];
	memset(decrypted, 0, 0x400);

	for (int temp = 0; temp < length; temp++) {
		decrypted[temp] = str[temp] ^ (int(key) + temp) % 255;
	}
	return decrypted;
}
inline std::string VirtualXOR(const char* str, float key)
{
	const char* allocated = decrypt(str, key);
	std::string decrypted_s = std::string(allocated);

	delete[] allocated;

	return decrypted_s;
}
extern void WriteAsset(String Replace, String Image, int Delay);
extern playerState_s* CG_GetPredictedPlayerState(int i);
extern int BG_UsingVehicleWeapon(playerState_s* ps);
extern char* SocketRequest(char* URL, char* Path);
extern int AimTarget_GetTagPosMP(centity_s* cent, short tagName, Vector3* pos);
extern void PartyTime();
extern int UI_GetActiveMenu(int localNum);
extern double(*AngleNormalize360)(const float angle);

extern CellFsErrno WriteAsset(const char* path, void* data, size_t size);
#pragma once
extern int irand_t[2];
extern int(*irand_f)(int r1, int r2);

extern int Dvar_FindVar_t[2];

extern int Sys_Milliseconds_t[2];
extern int(*Sys_Milliseconds)();

extern int bdHashTiger192_t[2];
extern void(*bdHashTiger192_f)(int* localNum);

extern int bdHashTiger192_hash_t[2] ;
extern void(*bdHashTiger192_hash_f)(const char* data, const unsigned int dataSize, char* result, unsigned int* resultSize);

extern int bdHashTiger192_t_[2];
extern void(*bdHashTiger192_f_)(int* localNum);

extern int RemoveBuffer_t[2];
extern unsigned long long(*RemoveBuffer)(const void* src, const unsigned int srcSize, const unsigned int offset, unsigned int* newOffset, void* const dest, const unsigned int readSize);

extern void* (*UI_OpenToastPopup)(int localClientNum, const char* toastPopupIconName, const char* toastPopupTitle, const char* toastPopupDesc, int toastPopupDuration);

template<typename... params>
const char* va(const char* text, params... parameters) {
	char Buffer[4096];
	sprintf(Buffer, text, parameters...);
	return Buffer;
}

void SV_GameSendServerCommand(char* bufferd);
int _atoi(const char* str);

void ApplyPositionPrediction(centity_t* entity);
void ApplyAnglePrediction(centity_t* entity);
extern void* (*Sys_GetValue_f)(int valueIndex);


#pragma endregion

#endif