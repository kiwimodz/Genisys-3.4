#include "Includes.h"
using namespace std;
INI Ini;

void INI::ReadFromFile(const char* FileName, int FileSize) {

	auto permission = cellFsChmod(FileName, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}

	int err = cellFsOpen(FileName, CELL_FS_O_RDWR, &fd, NULL, 0);
	cellFsRead(fd, &Ini.buffer, GetFileSize(FileName), &nrw);
}
void INI::Init(const char* filename) {
	int fileSize = GetFileSize(filename);
	if (fileSize) {
		ReadFromFile(filename, fileSize);
	}
}

void  INI::Free() {
	if (buffer != 0)
		memset(buffer, 0, sizeof(buffer));
}
char* INI::GetSection(const char* section) {
	if (!buffer)
		return 0;

	char* found = strstr(buffer, section);
	if (found) {
		found += strlen(section) + 1;

		return (char*)found;
	}
	return 0;
}

char* INI::GetValue(char* found, const char* value) {
	if (!buffer)
		return 0;

	char* v_found = strstr(found, value);
	if (v_found) {
		v_found += strlen(value);

		char character = '\0';
		while ((character = *v_found) != '\0') {
			if (character == ' ')
				v_found++;
			else if (character == '=')
				v_found++;
			else
				break;
		}

		return v_found;
	}

	return 0;
}
int my_atoi(const char* s) {
	int sum = 0;
	char ch;
	char sign = *s;
	if (*s == '-' || *s == '+')
		s++;
	while ((ch = *s++) >= '0' && ch <= '9') {
		sum = sum * 10 - (ch - '0');
	}
	if (sign != '-') {
		sum = -sum;
	}
	return sum;
}
#define atoi my_atoi
float my_atof(const char* p) {
	// here i took another two  variables for counting the number of digits in mantissa
	int i, num = 0, num2 = 0, pnt_seen = 0, x = 0, y = 1;
	float f1, f2, f3;
	for (i = 0; p[i]; i++)
		if (p[i] == '.') {
			pnt_seen = i;
			break;
		}
	for (i = 0; p[i]; i++) {
		if (i < pnt_seen) num = num * 10 + (p[i] - 48);
		else if (i == pnt_seen) continue;
		else {
			num2 = num2 * 10 + (p[i] - 48);
			++x;
		}
	}
	// it takes 10 if it has 1 digit ,100 if it has 2 digits in mantissa
	for (i = 1; i <= x; i++)
		y = y * 10;
	f2 = num2 / (float)y;
	f3 = num + f2;
	return f3;
}

void tokenize(const std::string& s, const char delim,
	std::vector<std::string>& out) {
	std::string::size_type beg = 0;
	for (auto end = 0; (end = s.find(delim, end)) != std::string::npos; ++end) {
		out.push_back(s.substr(beg, end - beg));
		beg = end + 1;
	}

	out.push_back(s.substr(beg));
}
#define atof my_atof
template <class Container>
void split3(const std::string& str, Container& cont,
	char delim = ',') {
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

char* INI::FillInValue(char* v_found) {
	char* val_buf = new char[100];
	memset(val_buf, 0, 100);
	int index = 0;
	char character = '\0';
	while ((character = *v_found) != '\0') {
		if (character == '\n' || character == '\r')
			break;

		val_buf[index++] = character;
		v_found++;
	}

	return val_buf;
}

bool INI::ReadBool(const char* section, std::string value) {
	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			bool bReturn = false;
			if (strcmp(val_buf, "true") == 0)
				bReturn = true;

			delete[] val_buf;

			return bReturn;
		}
	}

	return false;
}

int INI::ReadInt(const char* section, std::string value) {
	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			int iReturn = atoi(val_buf);

			delete[] val_buf;

			return iReturn;
		}
	}

	return 0;
}

color INI::ReadColor(const char* section, std::string value) {
	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			std::string val = val_buf;

			if (strcmp(val_buf, "true") == 0 || strcmp(val_buf, "false") == 0)
				return color(0, 0, 255);

			std::vector<std::string> words;
			words = split(val, ",");

			float rf = atof(words.at(0).c_str());
			float gf = atof(words.at(1).c_str());
			float bf = atof(words.at(2).c_str());
			float af = atof(words.at(3).c_str());

			delete[] val_buf;

			return color(rf * 255.f, gf * 255.f, bf * 255.f, af * 255.f);
		}
	}

	return color(0, 0, 255);
}

float atof_a(char* str) {
	float rez = 0, fact = 1;
	if (*str == '-') {
		str++;
		fact = -1;
	}

	for (int32_t point_seen = 0; *str; str++) {
		if (*str == '.') {
			point_seen = 1;
			continue;
		}

		int32_t d = *str - '0';
		if (d >= 0 && d <= 9) {
			if (point_seen) fact /= 10.0f;
			rez = rez * 10.0f + (float)d;
		}
	}

	return rez * fact;
}

float INI::ReadFloat(const char* section, std::string value) {
	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			float fReturn = atof_a(val_buf);

			delete[] val_buf;

			return fReturn;
		}
	}

	return 0.0f;
}

char INI::ReadChar(const char* section, std::string value) {
	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			char cReturn = atoi(val_buf);

			delete[] val_buf;

			return (char)cReturn;
		}
	}

	return 0;
}

void INI::ReadString(const char* section, std::string value, char* out) {



	char* found = GetSection(section);

	if (found) {
		char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			char* val_buf = FillInValue(v_found);

			memcpy(out, val_buf, strlen(val_buf));

			delete[] val_buf;
		}
	}
}

void INI::PrepareSave(const char* filename) {
	auto permission = cellFsChmod(filename, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf("perm: 0x%X\n", permission);
	}
	rtn = cellFsTruncate(filename, 0);
	rtn = cellFsOpen(filename, CELL_FS_O_WRONLY | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);

	const char* header = "# BO2 Genisys V3 Menu Config File\r\n";
	cellFsWrite(fd, header, strlen(header), NULL);
}

void INI::WriteSection(const char* section) {
	char out[100] = { 0 };
	sprintf(out, "\r\n[%s]\r\n", section);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteBool(const char* option, bool value) {
	char out[100] = { 0 };
	sprintf(out, "%s = %s\r\n", option, value ? "true" : "false");

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void INI::WriteInt(const char* option, int value) {
	char out[100] = { 0 };
	sprintf(out, "%s = %i\r\n", option, value);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteColor(const char* option, color value) {
	char out[100] = { 0 };
	Com_Sprintf(out, sizeof(out), "%s = %.2f,%.2f,%.2f,%.2f,\r\n", option, value.r, value.g, value.b, value.a);
	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteFloat(const char* option, float value) {
	
	char out[100] = { 0 };
	Com_Sprintf(out, sizeof(out), "%s = %.2f,\r\n", option, value);
	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteChar(const char* option, char value) {
	char out[100] = { 0 };
	sprintf(out, "%s = %i\r\n", option, value);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteString(const char* option, const char* value) {
	char out[100] = { 0 };
	sprintf(out, "%s = %s\r\n", option, value);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void INI::Save() {
	cellFsClose(fd);
}

size_t GetFileSize(const char* fileName) {
	CellFsStat stat_handle;
	cellFsStat(fileName, &stat_handle);
	return (stat_handle.st_size);

}

void ReadFromIniFile(const char* fileName) {
	int fileSize = GetFileSize(fileName);
	if (!fileSize)
		return;
	//Start
	Ini.Init(fileName);
	//Aimbot
	bot.benable = Ini.ReadBool("Aimbot", "Player Aimbot");
	bot.aimtype = Ini.ReadInt("Aimbot", "Aim Type");
	bot.keytype = Ini.ReadInt("Aimbot", "Key Type");
	bot.tagtype = Ini.ReadInt("Aimbot", "Tag Type");
	bot.loop_number_autobone = Ini.ReadInt("Aimbot", "Bone Scan Strength");
	bot.bcircle = Ini.ReadBool("Aimbot", "Fov Circle");
	bot.fovs = Ini.ReadFloat("Aimbot", "Fov Circle Scale");
	bot.snaps = Ini.ReadFloat("Aimbot", "Smooth Snap Scale");
	bot.ads = Ini.ReadFloat("Aimbot", "ADS Zoom Scale");
	bot.bpingp = Ini.ReadBool("Aimbot", "Ping Prediction");
	bot.bvisible = Ini.ReadBool("Aimbot", "Visible");
	bot.bautowall = Ini.ReadBool("Aimbot", "Autowall");
	menu->fpssaving = Ini.ReadBool("Aimbot", "FPS Saving");
	bot.benablal = Ini.ReadBool("Aimbot", "Aim Lock");
	bot.bnospread = Ini.ReadBool("Aimbot", "Remove Spread");
	bot.bnoflinch = Ini.ReadBool("Aimbot", "Remove Flinch");
	bot.bnosway = Ini.ReadBool("Aimbot", "Remove Sway");
	bot.bnobob = Ini.ReadBool("Aimbot", "Remove Bob");
	bot.bnorec = Ini.ReadBool("Aimbot", "Remove Recoil");
	bot.bnokick = Ini.ReadBool("Aimbot", "Remove Kick");
	bot.cancelreload = Ini.ReadBool("Aimbot", "Cancel Reload");
	bot.bautocrouch = Ini.ReadBool("Aimbot", "Auto Crouch");
	bot.blean = Ini.ReadBool("Aimbot", "Lean");
	bot.bIsAirStuck = Ini.ReadBool("Aimbot", "Air Stuck");
	bot.snake_bot = Ini.ReadBool("Aimbot", "Snake");

	bot.bautoshoot = Ini.ReadBool("Aimbot", "Autoshoot");
	//Antiaim
	bot.benableanti = Ini.ReadBool("Anti-Aim", "Enable Antiaim");
	bot.bthirdp = Ini.ReadBool("Anti-Aim", "Third Person");
	bot.block3dpaa = Ini.ReadBool("Anti-Aim", "Unlock Angles");
	bot.baaadvanced = Ini.ReadBool("Anti-Aim", "Advanced Options");
	bot.antitypeX[FIRING] = Ini.ReadInt("Anti-Aim", "Firing X");
	bot.antitypeX[SPRINTING] = Ini.ReadInt("Anti-Aim", "Sprinting X");
	bot.antitypeX[CROUCHING] = Ini.ReadInt("Anti-Aim", "Crouching X");
	bot.antitypeX[STANDING] = Ini.ReadInt("Anti-Aim", "Standing X");
	bot.antitypeX[MOVING] = Ini.ReadInt("Anti-Aim", "Moving X");
	bot.antitypeX[SNAKE] = Ini.ReadInt("Anti-Aim", "Snake X");
	bot.antitypeY[FIRING] = Ini.ReadInt("Anti-Aim", "Firing Y");
	bot.antitypeY[SPRINTING] = Ini.ReadInt("Anti-Aim", "Sprinting Y");
	bot.antitypeY[CROUCHING] = Ini.ReadInt("Anti-Aim", "Crouching Y");
	bot.antitypeY[STANDING] = Ini.ReadInt("Anti-Aim", "Standing Y");
	bot.antitypeY[MOVING] = Ini.ReadInt("Anti-Aim", "Moving Y");
	bot.antitypeY[SNAKE] = Ini.ReadInt("Anti-Aim", "Snake Y");
	bot.custompitchscale = Ini.ReadFloat("Anti-Aim", "Custom Pitch");
	bot.breversebot = Ini.ReadBool("Anti-Aim", "Riot Backwards");
	bot.blockup = Ini.ReadBool("Anti-Aim", "Simi-Up");
	bot.pitchscalex = Ini.ReadFloat("Anti-Aim", "Jitter X Scale");
	bot.pitchscaley = Ini.ReadFloat("Anti-Aim", "Jitter Y Scale");
	bot.spinscale = Ini.ReadFloat("Anti-Aim", "Spin Y Scale");
	bot.fakelagscale = Ini.ReadFloat("Anti-Aim", "Fake Lag Scale");
	//Esp
	bot.esp.ballies = Ini.ReadBool("Visuals", "Friendlys");
	bot.esp.baxis = Ini.ReadBool("Visuals", "Enemys");
	bot.esp.bound = Ini.ReadInt("Visuals", "Bound");
	bot.esp.snaplines = Ini.ReadInt("Visuals", "Snaplines");
	bot.esp.bnames = Ini.ReadBool("Visuals", "Names");
	bot.esp.bcompass = Ini.ReadBool("Visuals", "Crosshair Compass");
	bot.esp.bhealthbar = Ini.ReadBool("Visuals", "Health Bar");
	bot.esp.sprintmeter = Ini.ReadBool("Visuals", "Sprint Meter");
	bot.esp.bdynamic = Ini.ReadBool("Visuals", "Dynamic Crosshair");
	bot.customxh = Ini.ReadBool("Visuals", "Custom Crosshair");
	bot.customxhd = Ini.ReadBool("Visuals", "Custom Dynamic");
	bot.customw = Ini.ReadFloat("Visuals", "Pattern X");
	bot.customh = Ini.ReadFloat("Visuals", "Pattern Y");
	bot.customt = Ini.ReadFloat("Visuals", "Thickness");
	bot.customr = Ini.ReadFloat("Visuals", "Rotation");
	bot.customrs = Ini.ReadFloat("Visuals", "Spin speed");
	bot.esp.btracers = Ini.ReadBool("Visuals", "Tracers");
	bot.esp.clienthealth = Ini.ReadBool("Visuals", "Client Health Bars");
	bot.esp.btargetinfo = Ini.ReadBool("Visuals", "Target Info");
	bot.esp.bprox = Ini.ReadBool("Visuals", "Proximity Warning");
	bot.esp.bvangles = Ini.ReadBool("Visuals", "V-Angles");
	bot.blaser = Ini.ReadBool("Visuals", "Laser");
	//Chams
	bot.esp.bchams = Ini.ReadBool("Visuals", "Enable Chams");
	bot.esp.bweaponchams = Ini.ReadBool("Visuals", "Weapon Chams");
	menu->renderchamsonme = Ini.ReadBool("Visuals", "Chams On Me");
	bot.chamsintensity = Ini.ReadFloat("Visuals", "Chams Intensity");
	bot.esp.bwall = Ini.ReadBool("Visuals", "Player Wallhack");
	bot.esp.bwwall = Ini.ReadBool("Visuals", "Weapon Wallhack");
	bot.esp.ebwall = Ini.ReadBool("Visuals", "Entity Wallhack");
	//World ents
	bot.esp.benableworldents = Ini.ReadBool("Visuals", "Enable World Ents");
	bot.esp.bweapsworld = Ini.ReadBool("Visuals", "Weapons");
	bot.esp.bpickupweaponsworld = Ini.ReadBool("Visuals", "Weapon Items");
	bot.esp.bnadesworld = Ini.ReadBool("Visuals", "Grenades");
	bot.esp.bpickupscavsworld = Ini.ReadBool("Visuals", "Scavenger Bags");
	bot.esp.benablenadefuse = Ini.ReadBool("Visuals", "Projectile Fuse Time");
	bot.esp.bnadetracers = Ini.ReadBool("Visuals", "Projectile Tracers");
	//Radar
	bot.esp.bradar = Ini.ReadBool("Visuals", "Enable Radar");
	bot.esp.bplayers = Ini.ReadBool("Visuals", "Orbital VSAT");
	bot.esp.scale = Ini.ReadFloat("Visuals", "Compass Scale");
	bot.esp.scalewh = Ini.ReadFloat("Visuals", "Compass Size");
	bot.esp.bradrpickupweaps = Ini.ReadBool("Visuals", "Weapon Items");
	bot.esp.bradrnades = Ini.ReadBool("Visuals", "Grenades");
	bot.esp.bradrpickupscavs = Ini.ReadBool("Visuals", "Scavenger Bags");
	bot.esp.bradrhelis = Ini.ReadBool("Visuals", "Helicopters");
	bot.esp.bradrdogos = Ini.ReadBool("Visuals", "Dogos");
	bot.esp.bradrvehicles = Ini.ReadBool("Visuals", "Vehicles");
	bot.esp.bradrturrets = Ini.ReadBool("Visuals", "Turrets");
	bot.esp.bradrartillery = Ini.ReadBool("Visuals", "Artillery");
	//Tracers
	bot.esp.bradartracers = Ini.ReadBool("Visuals", "Tracers");
	menu->fadeTime = Ini.ReadFloat("Visuals", "Fade Time");
	menu->fadeScale = Ini.ReadFloat("Visuals", "Fade Scale");
	menu->beamWidth = Ini.ReadFloat("Visuals", "Beam Width");
	menu->beamLength = Ini.ReadFloat("Visuals", "Beam Length");
	menu->screwRadius = Ini.ReadFloat("Visuals", "Screw Radius");
	menu->screwDist = Ini.ReadFloat("Visuals", "Screw Dist");
	//Cheats
	local->unlimitedSlots = Ini.ReadBool("Cheats", "Unlimited Class Slots");
	menu->frenderfovx = Ini.ReadFloat("Cheats", "Fov");
	menu->nightmode = Ini.ReadBool("Cheats", "Night Mode");
	bot.noflsh = Ini.ReadBool("Cheats", "Remove Flash");
	bot.bfullbright = Ini.ReadBool("Cheats", "Full Bright");
	menu->i32_Name = Ini.ReadBool("Cheats", "32 Name Patcher");
	menu->flshname = Ini.ReadBool("Cheats", "Flash Name");
	menu->addname = Ini.ReadBool("Cheats", "Advertise Menu");
	menu->bForceInv = Ini.ReadBool("Cheats", "Force Invite");
	menu->bClosedBypass = Ini.ReadBool("Cheats", "Bypass Closed Sessions");
	menu->props = Ini.ReadFloat("Cheats", "Prop Size");
	menu->bgunsound = Ini.ReadBool("Cheats", "Gun Sounds");
	menu->smokec = Ini.ReadBool("Cheats", "Smoke Color");
	menu->skyc = Ini.ReadBool("Cheats", "Sky Color");
	menu->skyr = Ini.ReadBool("Cheats", "Sky Rotate");
	//Settings
	menu->fahrenheit = Ini.ReadBool("Settings", "Celsius");
	menu->temp1 = Ini.ReadBool("Settings", "Disable CPU");
	menu->temp2 = Ini.ReadBool("Settings", "Disable RSX");
	menu->fps = Ini.ReadBool("Settings", "Disable FPS");
	menu->res = Ini.ReadBool("Settings", "Disable Resolution");
	menu->disabledlc = Ini.ReadBool("Settings", "Disable DLC");
	menu->benablecamos = Ini.ReadBool("Settings", "Enable DLC Camos");
	menu->sping = Ini.ReadBool("Settings", "Spinning Weapons");
	menu->engnsounds = Ini.ReadBool("Settings", "Disable Menu Sounds");
	menu->btrickmode = Ini.ReadBool("Settings", "Trickshot Mode");
	bot.scspeed = Ini.ReadFloat("Settings", "Scroll Speed");
	menu->SMPing = Ini.ReadInt("Settings", "Search Session Max Ping");
	//Server Info
	menu->serverinfo = Ini.ReadBool("Server Info", "Disable Server Info");
	menu->host = Ini.ReadBool("Server Info", "Disable Host Name");
	menu->map = Ini.ReadBool("Server Info", "Disable Map Name");
	menu->game = Ini.ReadBool("Server Info", "Disable Game Type Name");
	menu->ping = Ini.ReadBool("Server Info", "Disable Ping");
	menu->ents = Ini.ReadBool("Server Info", "Disable Entitys");
	menu->maxc = Ini.ReadBool("Server Info", "Disable Max Clients");
	//Camo
	bot.camotype = Ini.ReadInt("Camo", "Camo Type");
	menu->flagx = Ini.ReadInt("Camo", "Camo Spoofer");
	menu->camocolor = Ini.ReadBool("Camo", "Enable Camo Color");
	menu->Reflection = Ini.ReadFloat("Camo", "Reflection");
	menu->normalheight = Ini.ReadFloat("Camo", "Normal Map Height");
	menu->Emissive_Amo = Ini.ReadFloat("Camo", "Emissive");
	menu->Gloss_Amount = Ini.ReadFloat("Camo", "Gloss");
	menu->Layer1ScrollX = Ini.ReadFloat("Camo", "Animate Layer1 X");
	menu->Layer1ScrollY = Ini.ReadFloat("Camo", "Animate Layer1 Y");
	menu->Layer1Depth = Ini.ReadFloat("Camo", "Layer1 Depth");
	menu->Layer1W = Ini.ReadFloat("Camo", "Layer1 Width");
	menu->Layer1H = Ini.ReadFloat("Camo", "Layer1 Height");
	menu->Layer1Alpha = Ini.ReadFloat("Camo", "Layer1 Alpha");
	menu->Layer2ScrollX = Ini.ReadFloat("Camo", "Animate Layer2 X");
	menu->Layer2ScrollY = Ini.ReadFloat("Camo", "Animate Layer2 Y");
	menu->Layer3Scroll = Ini.ReadFloat("Camo", "Animate Layer3");
	//Theme
	menu->bo2theme = Ini.ReadBool("Theme", "Custom BO2 Theme");
	menu->msize = Ini.ReadInt("Theme", "Width Size");
	menu->fade = Ini.ReadBool("Theme", "Enable Fade");
	menu->lockcolor = Ini.ReadBool("Theme", "Lock Colors");
	//Colors
	menu->en = Ini.ReadColor("Theme", "Enemy Color");
	menu->fn = Ini.ReadColor("Theme", "Friendly Color");
	menu->hitble = Ini.ReadColor("Theme", "Hittable Color");
	menu->vis = Ini.ReadColor("Theme", "Visible Color");
	menu->trcr = Ini.ReadColor("Theme", "Tracer Color");
	menu->hb = Ini.ReadColor("Theme", "Shield Color");
	menu->xh = Ini.ReadColor("Theme", "Crosshair Color");
	menu->fc = Ini.ReadColor("Theme", "Fov Circle Color");
	menu->skin = Ini.ReadColor("Theme", "Main Color");
	menu->skin2 = Ini.ReadColor("Theme", "Secondary Color");
	menu->skin3 = Ini.ReadColor("Theme", "Border Primary");
	menu->skin4 = Ini.ReadColor("Theme", "Border Secondary");
	menu->skin5 = Ini.ReadColor("Theme", "Border Tertiary");
	menu->skin6 = Ini.ReadColor("Theme", "Border Quaternary");
	menu->rgbac = Ini.ReadColor("Theme", "Camo Color");
	//Rgba
	menu->en.Rainbow = Ini.ReadBool("Theme", "Enemy Color Rainbow");
	menu->fn.Rainbow = Ini.ReadBool("Theme", "Friendly Color Rainbow");
	menu->hitble.Rainbow = Ini.ReadBool("Theme", "Hittable Color Rainbow");
	menu->vis.Rainbow = Ini.ReadBool("Theme", "Visible Color Rainbow");
	menu->trcr.Rainbow = Ini.ReadBool("Theme", "Tracer Color Rainbow");
	menu->hb.Rainbow = Ini.ReadBool("Theme", "Shield Color Rainbow");
	menu->xh.Rainbow = Ini.ReadBool("Theme", "Crosshair Color Rainbow");
	menu->fc.Rainbow = Ini.ReadBool("Theme", "Fov Circle Color Rainbow");
	menu->skin3.Rainbow = Ini.ReadBool("Theme", "Border Primary Color Rainbow");
	menu->skin4.Rainbow = Ini.ReadBool("Theme", "Border Secondary Color Rainbow");
	menu->skin5.Rainbow = Ini.ReadBool("Theme", "Border Tertiary Color Rainbow");
	menu->skin6.Rainbow = Ini.ReadBool("Theme", "Border Quaternary Color Rainbow");
	menu->rgbac.Rainbow = Ini.ReadBool("Theme", "Camo Color Rainbow");

	menu->menufade = Ini.ReadFloat("Theme", "Main Color Theme Rainbow Speed");
	menu->en.RainbowSpeed = Ini.ReadFloat("Theme", "Enemy Color Rainbow Speed");
	menu->fn.RainbowSpeed = Ini.ReadFloat("Theme", "Friendly Color Rainbow Speed");
	menu->hitble.RainbowSpeed = Ini.ReadFloat("Theme", "Hittable Color Rainbow Speed");
	menu->vis.RainbowSpeed = Ini.ReadFloat("Theme", "Visible Color Rainbow Speed");
	menu->trcr.RainbowSpeed = Ini.ReadFloat("Theme", "Tracer Color Rainbow Speed");
	menu->hb.RainbowSpeed = Ini.ReadFloat("Theme", "Shield Color Rainbow Speed");
	menu->xh.RainbowSpeed = Ini.ReadFloat("Theme", "Crosshair Color Rainbow Speed");
	menu->fc.RainbowSpeed = Ini.ReadFloat("Theme", "Fov Circle Color Rainbow Speed");
	menu->rgbac.RainbowSpeed = Ini.ReadFloat("Theme", "Camo Color Rainbow Speed");
	//End
	Ini.Free();
	char Filename[30];
	_sys_sprintf(Filename, "%s Configuration File Loaded", fileName);
	CG_GameMessage(Filename);

	if (!cl_ingame_()) {
		UI_OpenToastPopup(0, "thumbsup", "Configuration", Filename, 3000);
	} else {
		CG_GameMessage(Filename);
	}
}

void SaveToIniFile(const char* fileName) {
	Ini.PrepareSave(fileName);

	Ini.WriteSection("Aimbot");
	Ini.WriteBool("Player Aimbot", bot.benable);
	Ini.WriteInt("Aim Type", bot.aimtype);
	Ini.WriteInt("Key Type", bot.keytype);
	Ini.WriteInt("Tag Type", bot.tagtype);
	Ini.WriteInt("Bone Scan Strength", bot.loop_number_autobone);
	Ini.WriteBool("Fov Circle", bot.bcircle);
	Ini.WriteFloat("Fov Circle Scale", bot.fovs);
	Ini.WriteFloat("Smooth Snap Scale", bot.snaps);
	Ini.WriteFloat("ADS Zoom Scale", bot.ads);
	Ini.WriteBool("Visible", bot.bvisible);
	Ini.WriteBool("Autowall", bot.bautowall);
	Ini.WriteBool("FPS Saving", menu->fpssaving);
	Ini.WriteBool("Aim Lock", bot.benablal);
	Ini.WriteBool("Remove Spread", bot.bnospread);
	Ini.WriteBool("Remove Flinch", bot.bnoflinch);
	Ini.WriteBool("Remove Sway", bot.bnosway);
	Ini.WriteBool("Remove Bob", bot.bnobob);
	Ini.WriteBool("Remove Recoil", bot.bnorec);
	Ini.WriteBool("Remove Kick", bot.bnokick);
	Ini.WriteBool("Cancel Reload", bot.cancelreload);
	Ini.WriteBool("Auto Crouch", bot.bautocrouch);
	Ini.WriteBool("Lean", bot.blean);
	Ini.WriteBool("Air Stuck", bot.bIsAirStuck);
	Ini.WriteBool("Snake", bot.snake_bot);
	Ini.WriteBool("Lean", bot.blean);
	Ini.WriteBool("Autoshoot", bot.bautoshoot);
	Ini.WriteSection("Anti-Aim");//Antiaim
	Ini.WriteBool("Enable Antiaim", bot.benableanti);
	Ini.WriteBool("Third Person", bot.bthirdp);
	Ini.WriteBool("Unlock Angles", bot.block3dpaa);
	Ini.WriteBool("Advanced Options", bot.baaadvanced);
	Ini.WriteInt("Firing X", bot.antitypeX[FIRING]);
	Ini.WriteInt("Sprinting X", bot.antitypeX[SPRINTING]);
	Ini.WriteInt("Crouching X", bot.antitypeX[CROUCHING]);
	Ini.WriteInt("Standing X", bot.antitypeX[STANDING]);
	Ini.WriteInt("Moving X", bot.antitypeX[MOVING]);
	Ini.WriteInt("Snake X", bot.antitypeX[SNAKE]);
	Ini.WriteInt("Firing Y", bot.antitypeY[FIRING]);
	Ini.WriteInt("Sprinting Y", bot.antitypeY[SPRINTING]);
	Ini.WriteInt("Crouching Y", bot.antitypeY[CROUCHING]);
	Ini.WriteInt("Standing Y", bot.antitypeY[STANDING]);
	Ini.WriteInt("Moving Y", bot.antitypeY[MOVING]);
	Ini.WriteInt("Snake Y", bot.antitypeY[SNAKE]);
	Ini.WriteFloat("Custom Pitch", bot.custompitchscale);
	Ini.WriteBool("Riot Backwards", bot.breversebot);
	Ini.WriteBool("Simi-Up", bot.blockup);
	Ini.WriteFloat("Jitter X Scale", bot.pitchscalex);
	Ini.WriteFloat("Jitter Y Scale", bot.pitchscaley);
	Ini.WriteFloat("Spin Y Scale", bot.spinscale);
	Ini.WriteFloat("Fake Lag Scale", bot.fakelagscale);
	Ini.WriteSection("Visuals");//Esp
	Ini.WriteBool("Friendlys", bot.esp.ballies);
	Ini.WriteBool("Enemys", bot.esp.baxis);
	Ini.WriteInt("Bound", bot.esp.bound);
	Ini.WriteInt("Snaplines", bot.esp.snaplines);
	Ini.WriteBool("Names", bot.esp.bnames);
	Ini.WriteBool("Crosshair Compass", bot.esp.bcompass);
	Ini.WriteBool("Health Bar", bot.esp.bhealthbar);
	Ini.WriteBool("Sprint Meter", bot.esp.sprintmeter);
	Ini.WriteBool("Dynamic Crosshair", bot.esp.bdynamic);
	Ini.WriteBool("Custom Crosshair", bot.customxh);
	Ini.WriteBool("Custom Dynamic", bot.customxhd);
	Ini.WriteFloat("Pattern X", bot.customw);
	Ini.WriteFloat("Pattern Y", bot.customh);
	Ini.WriteFloat("Thickness", bot.customt);
	Ini.WriteFloat("Rotation", bot.customr);
	Ini.WriteFloat("Spin Speed", bot.customrs);
	Ini.WriteBool("Tracers", bot.esp.btracers);
	Ini.WriteBool("Client Health Bars", bot.esp.clienthealth);
	Ini.WriteBool("Target Info", bot.esp.btargetinfo);
	Ini.WriteBool("Proximity Warning", bot.esp.bprox);
	Ini.WriteBool("V-Angles", bot.esp.bvangles);
	Ini.WriteBool("Laser", bot.blaser);
	Ini.WriteBool("Enable Chams", bot.esp.bchams);
	Ini.WriteBool("Weapon Chams", bot.esp.bweaponchams);
	Ini.WriteBool("Chams On Me", menu->renderchamsonme);
	Ini.WriteFloat("Chams Intensity", bot.chamsintensity);
	Ini.WriteBool("Player Wallhack", bot.esp.bwall);
	Ini.WriteBool("Weapon Wallhack", bot.esp.bwwall);
	Ini.WriteBool("Entity Wallhack", bot.esp.ebwall);
	Ini.WriteBool("Enable World Ents", bot.esp.benableworldents);
	Ini.WriteBool("Weapons", bot.esp.bweapsworld);
	Ini.WriteBool("Weapon Items", bot.esp.bpickupweaponsworld);
	Ini.WriteBool("Grenades", bot.esp.bnadesworld);
	Ini.WriteBool("Scavenger Bags", bot.esp.bpickupscavsworld);
	Ini.WriteBool("Projectile Fuse Time", bot.esp.benablenadefuse);
	Ini.WriteBool("Projectile Tracers", bot.esp.bnadetracers);
	Ini.WriteBool("Enable Radar", bot.esp.bradar);
	Ini.WriteBool("Orbital VSAT", bot.esp.bplayers);
	Ini.WriteFloat("Compass Scale", bot.esp.scale);
	Ini.WriteFloat("Compass Size", bot.esp.scalewh);
	Ini.WriteBool("Weapon Items", bot.esp.bradrpickupweaps);
	Ini.WriteBool("Grenades", bot.esp.bradrnades);
	Ini.WriteBool("Scavenger Bags", bot.esp.bradrpickupscavs);
	Ini.WriteBool("Helicopters", bot.esp.bradrhelis);
	Ini.WriteBool("Dogos", bot.esp.bradrdogos);
	Ini.WriteBool("Vehicles", bot.esp.bradrvehicles);
	Ini.WriteBool("Turrets", bot.esp.bradrturrets);
	Ini.WriteBool("Artillery", bot.esp.bradrartillery);
	Ini.WriteBool("Tracers", bot.esp.bradartracers);
	Ini.WriteFloat("Fade Time", menu->fadeTime);
	Ini.WriteFloat("Fade Scale", menu->fadeScale);
	Ini.WriteFloat("Beam Width", menu->beamWidth);
	Ini.WriteFloat("Beam Length", menu->beamLength);
	Ini.WriteFloat("Screw Radius", menu->screwRadius);
	Ini.WriteFloat("Screw Dist", menu->screwDist);
	Ini.WriteSection("Cheats");//Cheats
	Ini.WriteBool("Unlimited Class Slots", local->unlimitedSlots);
	Ini.WriteFloat("Fov", menu->frenderfovx);
	Ini.WriteBool("Night Mode", menu->nightmode);
	Ini.WriteBool("Remove Flash", bot.noflsh);
	Ini.WriteBool("Full Bright", bot.bfullbright);
	Ini.WriteBool("32 Name Patcher", menu->i32_Name);
	Ini.WriteBool("Flash Name", menu->flshname);
	Ini.WriteBool("Advertise Menu", menu->addname);
	Ini.WriteBool("Force Invite", menu->bForceInv);
	Ini.WriteBool("Bypass Closed Sessions", menu->bClosedBypass);
	Ini.WriteFloat("Prop Size", menu->props);
	Ini.WriteBool("Gun Sounds", menu->bgunsound);
	Ini.WriteBool("Smoke Color", menu->smokec);
	Ini.WriteBool("Sky Color", menu->skyc);
	Ini.WriteBool("Sky Rotate", menu->skyr);
	Ini.WriteSection("Settings");//Settings
	Ini.WriteBool("Celsius", menu->fahrenheit);
	Ini.WriteBool("Disable CPU", menu->temp1);
	Ini.WriteBool("Disable RSX", menu->temp2);
	Ini.WriteBool("Disable FPS", menu->fps);
	Ini.WriteBool("Disable Resolution", menu->res);
	Ini.WriteBool("Disable DLC", menu->disabledlc);
	Ini.WriteBool("Enable DLC Camos", menu->benablecamos);
	Ini.WriteBool("Spinning Weapons", menu->sping);
	Ini.WriteBool("Disable Menu Sounds", menu->engnsounds);
	Ini.WriteBool("Trickshot Mode", menu->btrickmode);
	Ini.WriteFloat("Scroll Speed", bot.scspeed);
	Ini.WriteInt("Search Session Max Ping", menu->SMPing);
	Ini.WriteSection("Server Info");//Server Info
	Ini.WriteBool("Disable Server Info", menu->serverinfo);
	Ini.WriteBool("Disable Host Name", menu->host);
	Ini.WriteBool("Disable Map Name", menu->map);
	Ini.WriteBool("Disable Game Type Name", menu->game);
	Ini.WriteBool("Disable Entitys", menu->ents);
	Ini.WriteBool("Disable Max Clients", menu->maxc);
	Ini.WriteSection("Camo");//Camo
	Ini.WriteInt("Camo Type", bot.camotype);
	Ini.WriteInt("Camo Spoofer", menu->flagx);
	Ini.WriteBool("Enable Camo Color", menu->camocolor);
	Ini.WriteFloat("Reflection", menu->Reflection);
	Ini.WriteFloat("Normal Map Height", menu->normalheight);
	Ini.WriteFloat("Emissive", menu->Emissive_Amo);
	Ini.WriteFloat("Gloss", menu->Gloss_Amount);
	Ini.WriteFloat("Animate Layer1 X", menu->Layer1ScrollX);
	Ini.WriteFloat("Animate Layer1 Y", menu->Layer1ScrollY);
	Ini.WriteFloat("Layer1 Depth", menu->Layer1Depth);
	Ini.WriteFloat("Layer1 Width", menu->Layer1W);
	Ini.WriteFloat("Layer1 Height", menu->Layer1H);
	Ini.WriteFloat("Layer1 Alpha", menu->Layer1Alpha);
	Ini.WriteFloat("Animate Layer2 X", menu->Layer2ScrollX);
	Ini.WriteFloat("Animate Layer2 Y", menu->Layer2ScrollY);
	Ini.WriteFloat("Animate Layer3", menu->Layer3Scroll);
	Ini.WriteSection("Theme");//Theme
	Ini.WriteBool("Custom BO2 Theme", menu->bo2theme);
	Ini.WriteInt("Width Size", menu->msize);
	Ini.WriteBool("Enable Fade", menu->fade);
	Ini.WriteBool("Lock Colors", menu->lockcolor);
	Ini.WriteColor("Enemy Color", menu->en);
	Ini.WriteColor("Friendly Color", menu->fn);
	Ini.WriteColor("Hittable Color", menu->hitble);
	Ini.WriteColor("Visible Color", menu->vis);
	Ini.WriteColor("Tracer Color", menu->trcr);
	Ini.WriteColor("Shield Color", menu->hb);
	Ini.WriteColor("Crosshair Color", menu->xh);
	Ini.WriteColor("Fov Circle Color", menu->fc);
	Ini.WriteColor("Main Color", menu->skin);
	Ini.WriteColor("Secondary Color", menu->skin2);
	Ini.WriteColor("Border Primary", menu->skin3);
	Ini.WriteColor("Border Secondary", menu->skin4);
	Ini.WriteColor("Border Tertiary", menu->skin5);
	Ini.WriteColor("Border Quaternary", menu->skin6);
	Ini.WriteColor("Camo Color", menu->rgbac);
	Ini.WriteBool("Enemy Color Rainbow", menu->en.Rainbow);
	Ini.WriteBool("Friendly Color Rainbow", menu->fn.Rainbow);
	Ini.WriteBool("Hittable Color Rainbow", menu->hitble.Rainbow);
	Ini.WriteBool("Visible Color Rainbow", menu->vis.Rainbow);
	Ini.WriteBool("Tracer Color Rainbow", menu->trcr.Rainbow);
	Ini.WriteBool("Shield Color Rainbow", menu->hb.Rainbow);
	Ini.WriteBool("Crosshair Color Rainbow", menu->xh.Rainbow);
	Ini.WriteBool("Fov Circle Color Rainbow", menu->fc.Rainbow);
	Ini.WriteBool("Border Primary Color Rainbow", menu->skin3.Rainbow);
	Ini.WriteBool("Border Secondary Color Rainbow", menu->skin4.Rainbow);
	Ini.WriteBool("Border Tertiary Color Rainbow", menu->skin5.Rainbow);
	Ini.WriteBool("Border Quaternary Color Rainbow", menu->skin6.Rainbow);
	Ini.WriteBool("Camo Color Rainbow", menu->rgbac.Rainbow);
	Ini.WriteFloat("Main Color Theme Rainbow Speed", menu->menufade);
	Ini.WriteFloat("Enemy Color Rainbow Speed", menu->en.RainbowSpeed);
	Ini.WriteFloat("Friendly Color Rainbow Speed", menu->fn.RainbowSpeed);
	Ini.WriteFloat("Hittable Color Rainbow Speed", menu->hitble.RainbowSpeed);
	Ini.WriteFloat("Visible Color Rainbow Speed", menu->vis.RainbowSpeed);
	Ini.WriteFloat("Tracer Color Rainbow Speed", menu->trcr.RainbowSpeed);
	Ini.WriteFloat("Shield Color Rainbow Speed", menu->hb.RainbowSpeed);
	Ini.WriteFloat("Crosshair Color Rainbow Speed", menu->xh.RainbowSpeed);
	Ini.WriteFloat("Fov Circle Color Rainbow Speed", menu->fc.RainbowSpeed);
	Ini.WriteFloat("Camo Color Rainbow Speed", menu->rgbac.RainbowSpeed);
	Ini.Save();
	char Filename[30];
	_sys_sprintf(Filename, "%s Configuration File Saved", fileName);
	CG_GameMessage(Filename);

	if (!cl_ingame_()) {
		UI_OpenToastPopup(0, "thumbsup", "Configuration", Filename, 3000);
	} else {
		CG_GameMessage(Filename);
	}

}