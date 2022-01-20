#ifndef visuals_mp_h
#define visuals_mp_h

enum meansOfDeath_t
{
	MOD_PISTOL_BULLET = 0x1,
	MOD_RIFLE_BULLET = 0x2,
	MOD_HEAD_SHOT = 0x9,
};

extern float rx, ry, rw, rh, cw, ch;
extern void set_mod(int index);
extern void set_pen(int index);
extern String bound_type[6];
extern String bound_typedec[6];
extern String snap_type[4];
extern String snap_typedec[4];
extern String mod_type[3];
extern String mod_typedec[3];
extern String pen_type[3];
extern String pen_typedec[3];
extern void __cdecl ScrPlace_ApplyRect(float *x, float *y, float *w, float *h, int horzAlign, int vertAlign);
extern bool __cdecl CG_IsClientInOurParty(int localClientNum, int clientNum);
extern void __cdecl R_AddCmdDrawStretchPicRotateSTInternal(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float * color, void * material);
#pragma region visual handles
extern bool __cdecl Com_SessionMode_IsMode(eSessionModes_mode mode);
extern float _mm_xor_ps(float v15, float _mask__NegFloat_);
extern void DrawLineV(Vector2 From, Vector2 To, color col, int s);
extern void set_bound(int index);
extern void set_snap(int index);
extern void DrawShader3(float x, float y, float w, float h, float angle, color col, Material* material, alignment align);
extern void __cdecl R_AddCmdDrawStretchPicRotateSTInternal1(float x, float y, float w, float h, float centerS, float centerT, float radiusST, float scaleFinalS, float scaleFinalT, float angle, const float* color, void* material);
extern Vector2 Bound;
#pragma endregion
extern void visual_rendermp();
extern void DrawRadarOutLines(float x, float y, float width, float height, int thickness);
extern void CG_CompassDrawPlayerMap();
extern void EntityCount();
extern short SL_GetString(const char* str, unsigned int user);
#endif