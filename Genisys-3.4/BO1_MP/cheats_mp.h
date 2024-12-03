#ifndef cheats_mp_h
#define cheats_mp_h

extern void slide_fovx(float value);
extern void wint(int rank_id);
extern void slide_zoommap(float value);
extern void toggleantifreeze(bool* rs);
extern void Sint(int id);
extern void StyleInt(int rank_id);
extern void toggleconsole(bool* rs);
extern void toggleucs(bool* rs);
extern void unlimitedrank(int rank_id);
extern void FXint(int rank_id);
extern void Dvisint(float rank_id);
extern void slide_ymap(float value);
extern void slide_xmap(float value);
extern void toggleP(bool* rs);
extern void togglePi(bool* rs);

#pragma region account
extern void rank(int rank_id);
extern void Prrank(int rank_id);
extern void unlock_all();
#pragma endregion

#endif