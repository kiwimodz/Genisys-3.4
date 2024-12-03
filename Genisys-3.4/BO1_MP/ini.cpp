#include "Includes.h"
using namespace std;
INI Ini;

void INI::ReadFromFile(const char* FileName, int FileSize) {

	auto permission = cellFsChmod(FileName, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		printf(hash("perm: 0x%X\n"), permission);
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
const char* INI::GetSection(const char* section) {
	if (!buffer)
		return 0;

	const char* found = strstr(buffer, section);
	if (found) {
		found += strlen(section) + 1;

		return (const char*)found;
	}
	return 0;
}

const char* INI::GetValue(const char* found, const char* value) {
	if (!buffer)
		return 0;

	char* v_found = (char*)strstr(found, value);
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

const char* INI::FillInValue(const char* v_found) {
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
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			bool bReturn = false;
			if (strcmp(val_buf, hash("true")) == 0)
				bReturn = true;

			delete[] val_buf;

			return bReturn;
		}
	}

	return false;
}

int INI::ReadInt(const char* section, std::string value) {
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			int iReturn = atoi(val_buf);

			delete[] val_buf;

			return iReturn;
		}
	}

	return 0;
}

color INI::ReadColor(const char* section, std::string value) {
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			std::string val = val_buf;

			if (strcmp(val_buf, hash("true")) == 0 || strcmp(val_buf, hash("false")) == 0)
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

float atof_a(const char* str) {
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
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			float fReturn = atof_a(val_buf);

			delete[] val_buf;

			return fReturn;
		}
	}

	return 0.0f;
}

char INI::ReadChar(const char* section, std::string value) {
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			char cReturn = atoi(val_buf);

			delete[] val_buf;

			return (char)cReturn;
		}
	}

	return 0;
}

void INI::ReadString(const char* section, std::string value, const char* out) {
	const char* found = GetSection(section);

	if (found) {
		const char* v_found = GetValue(found, value.c_str());
		if (v_found) {
			const char* val_buf = FillInValue(v_found);

			memcpy((char*)out, val_buf, strlen(val_buf) + 1);

			delete[] val_buf;
		}
	}
}

void INI::PrepareSave(const char* filename) {
	auto permission = cellFsChmod(filename, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		//printf(hash("perm: 0x%X\n"), permission);
	}
	rtn = cellFsTruncate(filename, 0);
	rtn = cellFsOpen(filename, CELL_FS_O_WRONLY | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);

	const char* header = hash("# BO2 Genisys V3.4 Menu Config File\r\n");
	cellFsWrite(fd, header, strlen(header), NULL);
}

void INI::PrepareFriendsSave(const char* filename) {
	auto permission = cellFsChmod(filename, CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (permission != 0) {
		//printf(hash("perm: 0x%X\n"), permission);
	}
	rtn = cellFsTruncate(filename, 0);
	rtn = cellFsOpen(filename, CELL_FS_O_WRONLY | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);

	const char* header = hash("# BO2 Genisys V3.4 Menu Fake Friends File\r\n");
	cellFsWrite(fd, header, strlen(header), NULL);
}

void INI::WriteSection(const char* section) {
	char out[100] = { 0 };
	sprintf(out, hash("\r\n[%s]\r\n"), section);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteBool(const char* option, bool value) {
	char out[100] = { 0 };
	sprintf(out, hash("%s = %s\r\n"), option, value ? hash("true") : hash("false"));

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void INI::WriteInt(const char* option, int value) {
	char out[100] = { 0 };
	sprintf(out, hash("%s = %i\r\n"), option, value);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteColor(const char* option, color value) {
	char out[100] = { 0 };
	Com_Sprintf(out, sizeof(out), hash("%s = %.2f,%.2f,%.2f,%.2f,\r\n"), option, value.r, value.g, value.b, value.a);
	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteFloat(const char* option, float value) {
	
	char out[100] = { 0 };
	Com_Sprintf(out, sizeof(out), hash("%s = %.2f,\r\n"), option, value);
	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteChar(const char* option, char value) {
	char out[100] = { 0 };
	sprintf(out, hash("%s = %i\r\n"), option, value);

	int len = strlen(out);
	cellFsWrite(fd, out, len, NULL);
}

void  INI::WriteString(const char* option, const char* value) {
	char out[100] = { 0 };
	sprintf(out, hash("%s = %s\r\n"), option, value);

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
	bot.benable = Ini.ReadBool(hash("Aimbot"), hash("Player Aimbot"));
	bot.aimtype = Ini.ReadInt(hash("Aimbot"), hash("Aim Type"));
	bot.keytype = Ini.ReadInt(hash("Aimbot"), hash("Key Type"));
	bot.tagtype = Ini.ReadInt(hash("Aimbot"), hash("Tag Type"));
	bot.loop_number_autobone = Ini.ReadInt(hash("Aimbot"), hash("Bone Scan Strength"));
	bot.bcircle = Ini.ReadBool(hash("Aimbot"), hash("Fov Circle"));
	bot.fovs = Ini.ReadFloat(hash("Aimbot"), hash("Fov Circle Scale"));
	bot.snaps = Ini.ReadFloat(hash("Aimbot"), hash("Smooth Snap Scale"));
	bot.ads = Ini.ReadFloat(hash("Aimbot"), hash("ADS Zoom Scale"));
	bot.bpingp = Ini.ReadBool(hash("Aimbot"), hash("Ping Prediction"));
	bot.bvisible = Ini.ReadBool(hash("Aimbot"), hash("Visible"));
	bot.bautowall = Ini.ReadBool(hash("Aimbot"), hash("Autowall"));
	menu->fpssaving = Ini.ReadBool(hash("Aimbot"), hash("FPS Saving"));
	bot.benablal = Ini.ReadBool(hash("Aimbot"), hash("Aim Lock"));
	bot.bnospread = Ini.ReadBool(hash("Aimbot"), hash("Remove Spread"));
	bot.bnoflinch = Ini.ReadBool(hash("Aimbot"), hash("Remove Flinch"));
	bot.bnosway = Ini.ReadBool(hash("Aimbot"), hash("Remove Sway"));
	bot.bnobob = Ini.ReadBool(hash("Aimbot"), hash("Remove Bob"));
	bot.bnorec = Ini.ReadBool(hash("Aimbot"), hash("Remove Recoil"));
	bot.bnokick = Ini.ReadBool(hash("Aimbot"), hash("Remove Kick"));
	bot.cancelreload = Ini.ReadBool(hash("Aimbot"), hash("Cancel Reload"));
	bot.bautocrouch = Ini.ReadBool(hash("Aimbot"), hash("Auto Crouch"));
	bot.blean = Ini.ReadBool(hash("Aimbot"), hash("Lean"));
	bot.bIsAirStuck = Ini.ReadBool(hash("Aimbot"), hash("Air Stuck"));
	bot.snake_bot = Ini.ReadBool(hash("Aimbot"), hash("Snake"));

	bot.bautoshoot = Ini.ReadBool(hash("Aimbot"), hash("Autoshoot"));
	//Antiaim
	bot.benableanti = Ini.ReadBool(hash("Anti-Aim"), hash("Enable Antiaim"));
	bot.bthirdp = Ini.ReadBool(hash("Anti-Aim"), hash("Third Person"));
	bot.block3dpaa = Ini.ReadBool(hash("Anti-Aim"), hash("Unlock Angles"));
	bot.baaadvanced = Ini.ReadBool(hash("Anti-Aim"), hash("Advanced Options"));
	bot.antitypeX[FIRING] = Ini.ReadInt(hash("Anti-Aim"), hash("Firing X"));
	bot.antitypeX[SPRINTING] = Ini.ReadInt(hash("Anti-Aim"), hash("Sprinting X"));
	bot.antitypeX[CROUCHING] = Ini.ReadInt(hash("Anti-Aim"), hash("Crouching X"));
	bot.antitypeX[STANDING] = Ini.ReadInt(hash("Anti-Aim"), hash("Standing X"));
	bot.antitypeX[MOVING] = Ini.ReadInt(hash("Anti-Aim"), hash("Moving X"));
	bot.antitypeX[SNAKE] = Ini.ReadInt(hash("Anti-Aim"), hash("Snake X"));
	bot.antitypeY[FIRING] = Ini.ReadInt(hash("Anti-Aim"), hash("Firing Y"));
	bot.antitypeY[SPRINTING] = Ini.ReadInt(hash("Anti-Aim"), hash("Sprinting Y"));
	bot.antitypeY[CROUCHING] = Ini.ReadInt(hash("Anti-Aim"), hash("Crouching Y"));
	bot.antitypeY[STANDING] = Ini.ReadInt(hash("Anti-Aim"), hash("Standing Y"));
	bot.antitypeY[MOVING] = Ini.ReadInt(hash("Anti-Aim"), hash("Moving Y"));
	bot.antitypeY[SNAKE] = Ini.ReadInt(hash("Anti-Aim"), hash("Snake Y"));
	bot.custompitchscale = Ini.ReadFloat(hash("Anti-Aim"), hash("Custom Pitch"));
	bot.breversebot = Ini.ReadBool(hash("Anti-Aim"), hash("Riot Backwards"));
	bot.blockup = Ini.ReadBool(hash("Anti-Aim"), hash("Simi-Up"));
	bot.pitchscalex = Ini.ReadFloat(hash("Anti-Aim"), hash("Jitter X Scale"));
	bot.pitchscaley = Ini.ReadFloat(hash("Anti-Aim"), hash("Jitter Y Scale"));
	bot.spinscale = Ini.ReadFloat(hash("Anti-Aim"), hash("Spin Y Scale"));
	bot.fakelagscale = Ini.ReadFloat(hash("Anti-Aim"), hash("Fake Lag Scale"));
	//Esp
	bot.esp.ballies = Ini.ReadBool(hash("Visuals"), hash("Friendlys"));
	bot.esp.baxis = Ini.ReadBool(hash("Visuals"), hash("Enemys"));
	bot.esp.bound = Ini.ReadInt(hash("Visuals"), hash("Bound"));
	bot.esp.snaplines = Ini.ReadInt(hash("Visuals"), hash("Snaplines"));
	bot.esp.bnames = Ini.ReadBool(hash("Visuals"), hash("Names"));
	bot.esp.bcompass = Ini.ReadBool(hash("Visuals"), hash("Crosshair Compass"));
	bot.esp.bhealthbar = Ini.ReadBool(hash("Visuals"), hash("Health Bar"));
	bot.esp.sprintmeter = Ini.ReadBool(hash("Visuals"), hash("Sprint Meter"));
	bot.esp.bdynamic = Ini.ReadBool(hash("Visuals"), hash("Dynamic Crosshair"));
	bot.customxh = Ini.ReadBool(hash("Visuals"), hash("Custom Crosshair"));
	bot.customxhd = Ini.ReadBool(hash("Visuals"), hash("Custom Dynamic"));
	bot.customw = Ini.ReadFloat(hash("Visuals"), hash("Pattern X"));
	bot.customh = Ini.ReadFloat(hash("Visuals"), hash("Pattern Y"));
	bot.customt = Ini.ReadFloat(hash("Visuals"), hash("Thickness"));
	bot.customr = Ini.ReadFloat(hash("Visuals"), hash("Rotation"));
	bot.customrs = Ini.ReadFloat(hash("Visuals"), hash("Spin speed"));
	bot.esp.btracers = Ini.ReadBool(hash("Visuals"), hash("Tracers"));
	bot.esp.clienthealth = Ini.ReadBool(hash("Visuals"), hash("Client Health Bars"));
	bot.esp.btargetinfo = Ini.ReadBool(hash("Visuals"), hash("Target Info"));
	bot.esp.bprox = Ini.ReadBool(hash("Visuals"), hash("Proximity Warning"));
	bot.esp.bvangles = Ini.ReadBool(hash("Visuals"), hash("V-Angles"));
	bot.blaser = Ini.ReadBool(hash("Visuals"), hash("Laser"));
	//Chams
	bot.esp.bchams = Ini.ReadBool(hash("Visuals"), hash("Enable Chams"));
	bot.esp.bweaponchams = Ini.ReadBool(hash("Visuals"), hash("Weapon Chams"));
	menu->renderchamsonme = Ini.ReadBool(hash("Visuals"), hash("Chams On Me"));
	bot.chamsintensity = Ini.ReadFloat(hash("Visuals"), hash("Chams Intensity"));
	bot.esp.bwall = Ini.ReadBool(hash("Visuals"), hash("Player Wallhack"));
	bot.esp.bwwall = Ini.ReadBool(hash("Visuals"), hash("Weapon Wallhack"));
	bot.esp.ebwall = Ini.ReadBool(hash("Visuals"), hash("Entity Wallhack"));
	//World ents
	bot.esp.benableworldents = Ini.ReadBool(hash("Visuals"), hash("Enable World Ents"));
	bot.esp.bweapsworld = Ini.ReadBool(hash("Visuals"), hash("Weapons"));
	bot.esp.bpickupweaponsworld = Ini.ReadBool(hash("Visuals"), hash("Weapon Items"));
	bot.esp.bnadesworld = Ini.ReadBool(hash("Visuals"), hash("Grenades"));
	bot.esp.bpickupscavsworld = Ini.ReadBool(hash("Visuals"), hash("Scavenger Bags"));
	bot.esp.benablenadefuse = Ini.ReadBool(hash("Visuals"), hash("Projectile Fuse Time"));
	bot.esp.bnadetracers = Ini.ReadBool(hash("Visuals"), hash("Projectile Tracers"));
	//Radar
	bot.esp.bradar = Ini.ReadBool(hash("Visuals"), hash("Enable Radar"));
	bot.esp.bplayers = Ini.ReadBool(hash("Visuals"), hash("Orbital VSAT"));
	bot.esp.scale = Ini.ReadFloat(hash("Visuals"), hash("Compass Scale"));
	bot.esp.scalewh = Ini.ReadFloat(hash("Visuals"), hash("Compass Size"));
	bot.esp.bradrpickupweaps = Ini.ReadBool(hash("Visuals"), hash("Weapon Items"));
	bot.esp.bradrnades = Ini.ReadBool(hash("Visuals"), hash("Grenades"));
	bot.esp.bradrpickupscavs = Ini.ReadBool(hash("Visuals"), hash("Scavenger Bags"));
	bot.esp.bradrhelis = Ini.ReadBool(hash("Visuals"), hash("Helicopters"));
	bot.esp.bradrdogos = Ini.ReadBool(hash("Visuals"), hash("Dogos"));
	bot.esp.bradrvehicles = Ini.ReadBool(hash("Visuals"), hash("Vehicles"));
	bot.esp.bradrturrets = Ini.ReadBool(hash("Visuals"), hash("Turrets"));
	bot.esp.bradrartillery = Ini.ReadBool(hash("Visuals"), hash("Artillery"));
	//Tracers
	bot.esp.bradartracers = Ini.ReadBool(hash("Visuals"), hash("Tracers"));
	menu->fadeTime = Ini.ReadFloat(hash("Visuals"), hash("Fade Time"));
	menu->fadeScale = Ini.ReadFloat(hash("Visuals"), hash("Fade Scale"));
	menu->beamWidth = Ini.ReadFloat(hash("Visuals"), hash("Beam Width"));
	menu->beamLength = Ini.ReadFloat(hash("Visuals"), hash("Beam Length"));
	menu->screwRadius = Ini.ReadFloat(hash("Visuals"), hash("Screw Radius"));
	menu->screwDist = Ini.ReadFloat(hash("Visuals"), hash("Screw Dist"));
	//Cheats
	local->unlimitedSlots = Ini.ReadBool(hash("Cheats"), hash("Unlimited Class Slots"));
	menu->frenderfovx = Ini.ReadFloat(hash("Cheats"), hash("Fov"));
	menu->nightmode = Ini.ReadBool(hash("Cheats"), hash("Night Mode"));
	bot.noflsh = Ini.ReadBool(hash("Cheats"), hash("Remove Flash"));
	bot.bfullbright = Ini.ReadBool(hash("Cheats"), hash("Full Bright"));
	menu->i32_Name = Ini.ReadBool(hash("Cheats"), hash("32 Name Patcher"));
	menu->flshname = Ini.ReadBool(hash("Cheats"), hash("Flash Name"));
	menu->addname = Ini.ReadBool(hash("Cheats"), hash("Advertise Menu"));
	menu->bForceInv = Ini.ReadBool(hash("Cheats"), hash("Force Invite"));
	menu->bClosedBypass = Ini.ReadBool(hash("Cheats"), hash("Bypass Closed Sessions"));
	menu->props = Ini.ReadFloat(hash("Cheats"), hash("Prop Size"));
	menu->bgunsound = Ini.ReadBool(hash("Cheats"), hash("Gun Sounds"));
	menu->smokec = Ini.ReadBool(hash("Cheats"), hash("Smoke Color"));
	menu->skyc = Ini.ReadBool(hash("Cheats"), hash("Sky Color"));
	menu->skyr = Ini.ReadBool(hash("Cheats"), hash("Sky Rotate"));
	//Settings
	menu->fahrenheit = Ini.ReadBool(hash("Settings"), hash("Celsius"));
	menu->temp1 = Ini.ReadBool(hash("Settings"), hash("Disable CPU"));
	menu->temp2 = Ini.ReadBool(hash("Settings"), hash("Disable RSX"));
	menu->fps = Ini.ReadBool(hash("Settings"), hash("Disable FPS"));
	menu->res = Ini.ReadBool(hash("Settings"), hash("Disable Resolution"));
	menu->disabledlc = Ini.ReadBool(hash("Settings"), hash("Disable DLC"));
	menu->benablecamos = Ini.ReadBool(hash("Settings"), hash("Enable DLC Camos"));
	menu->sping = Ini.ReadBool(hash("Settings"), hash("Spinning Weapons"));
	menu->engnsounds = Ini.ReadBool(hash("Settings"), hash("Disable Menu Sounds"));
	menu->btrickmode = Ini.ReadBool(hash("Settings"), hash("Trickshot Mode"));
	bot.scspeed = Ini.ReadFloat(hash("Settings"), hash("Scroll Speed"));
	menu->SMPing = Ini.ReadInt(hash("Settings"), hash("Search Session Max Ping"));
	//Server Info
	menu->serverinfo = Ini.ReadBool(hash("Server Info"), hash("Disable Server Info"));
	menu->host = Ini.ReadBool(hash("Server Info"), hash("Disable Host Name"));
	menu->map = Ini.ReadBool(hash("Server Info"), hash("Disable Map Name"));
	menu->game = Ini.ReadBool(hash("Server Info"), hash("Disable Game Type Name"));
	menu->ping = Ini.ReadBool(hash("Server Info"), hash("Disable Ping"));
	menu->ents = Ini.ReadBool(hash("Server Info"), hash("Disable Entitys"));
	menu->maxc = Ini.ReadBool(hash("Server Info"), hash("Disable Max Clients"));
	//Camo
	bot.camotype = Ini.ReadInt(hash("Camo"), hash("Camo Type"));
	menu->flagx = Ini.ReadInt(hash("Camo"), hash("Camo Spoofer"));
	menu->camocolor = Ini.ReadBool(hash("Camo"), hash("Enable Camo Color"));
	menu->Reflection = Ini.ReadFloat(hash("Camo"), hash("Reflection"));
	menu->normalheight = Ini.ReadFloat(hash("Camo"), hash("Normal Map Height"));
	menu->Emissive_Amo = Ini.ReadFloat(hash("Camo"), hash("Emissive"));
	menu->Gloss_Amount = Ini.ReadFloat(hash("Camo"), hash("Gloss"));
	menu->Layer1ScrollX = Ini.ReadFloat(hash("Camo"), hash("Animate Layer1 X"));
	menu->Layer1ScrollY = Ini.ReadFloat(hash("Camo"), hash("Animate Layer1 Y"));
	menu->Layer1Depth = Ini.ReadFloat(hash("Camo"), hash("Layer1 Depth"));
	menu->Layer1W = Ini.ReadFloat(hash("Camo"), hash("Layer1 Width"));
	menu->Layer1H = Ini.ReadFloat(hash("Camo"), hash("Layer1 Height"));
	menu->Layer1Alpha = Ini.ReadFloat(hash("Camo"), hash("Layer1 Alpha"));
	menu->Layer2ScrollX = Ini.ReadFloat(hash("Camo"), hash("Animate Layer2 X"));
	menu->Layer2ScrollY = Ini.ReadFloat(hash("Camo"), hash("Animate Layer2 Y"));
	menu->Layer3Scroll = Ini.ReadFloat(hash("Camo"), hash("Animate Layer3"));
	//Theme
	menu->bo2theme = Ini.ReadBool(hash("Theme"), hash("Custom BO2 Theme"));
	menu->msize = Ini.ReadInt(hash("Theme"), hash("Width Size"));
	menu->fade = Ini.ReadBool(hash("Theme"), hash("Enable Fade"));
	menu->lockcolor = Ini.ReadBool(hash("Theme"), hash("Lock Colors"));
	//Colors
	menu->en = Ini.ReadColor(hash("Theme"), hash("Enemy Color"));
	menu->fn = Ini.ReadColor(hash("Theme"), hash("Friendly Color"));
	menu->hitble = Ini.ReadColor(hash("Theme"), hash("Hittable Color"));
	menu->vis = Ini.ReadColor(hash("Theme"), hash("Visible Color"));
	menu->trcr = Ini.ReadColor(hash("Theme"), hash("Tracer Color"));
	menu->hb = Ini.ReadColor(hash("Theme"), hash("Shield Color"));
	menu->xh = Ini.ReadColor(hash("Theme"), hash("Crosshair Color"));
	menu->fc = Ini.ReadColor(hash("Theme"), hash("Fov Circle Color"));
	menu->skin = Ini.ReadColor(hash("Theme"), hash("Main Color"));
	menu->skin2 = Ini.ReadColor(hash("Theme"), hash("Secondary Color"));
	menu->skin3 = Ini.ReadColor(hash("Theme"), hash("Border Primary"));
	menu->skin4 = Ini.ReadColor(hash("Theme"), hash("Border Secondary"));
	menu->skin5 = Ini.ReadColor(hash("Theme"), hash("Border Tertiary"));
	menu->skin6 = Ini.ReadColor(hash("Theme"), hash("Border Quaternary"));
	menu->rgbac = Ini.ReadColor(hash("Theme"), hash("Camo Color"));
	//Rgba
	menu->en.Rainbow = Ini.ReadBool(hash("Theme"), hash("Enemy Color Rainbow"));
	menu->fn.Rainbow = Ini.ReadBool(hash("Theme"), hash("Friendly Color Rainbow"));
	menu->hitble.Rainbow = Ini.ReadBool(hash("Theme"), hash("Hittable Color Rainbow"));
	menu->vis.Rainbow = Ini.ReadBool(hash("Theme"), hash("Visible Color Rainbow"));
	menu->trcr.Rainbow = Ini.ReadBool(hash("Theme"), hash("Tracer Color Rainbow"));
	menu->hb.Rainbow = Ini.ReadBool(hash("Theme"), hash("Shield Color Rainbow"));
	menu->xh.Rainbow = Ini.ReadBool(hash("Theme"), hash("Crosshair Color Rainbow"));
	menu->fc.Rainbow = Ini.ReadBool(hash("Theme"), hash("Fov Circle Color Rainbow"));
	menu->skin3.Rainbow = Ini.ReadBool(hash("Theme"), hash("Border Primary Color Rainbow"));
	menu->skin4.Rainbow = Ini.ReadBool(hash("Theme"), hash("Border Secondary Color Rainbow"));
	menu->skin5.Rainbow = Ini.ReadBool(hash("Theme"), hash("Border Tertiary Color Rainbow"));
	menu->skin6.Rainbow = Ini.ReadBool(hash("Theme"), hash("Border Quaternary Color Rainbow"));
	menu->rgbac.Rainbow = Ini.ReadBool(hash("Theme"), hash("Camo Color Rainbow"));

	menu->menufade = Ini.ReadFloat(hash("Theme"), hash("Main Color Theme Rainbow Speed"));
	menu->en.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Enemy Color Rainbow Speed"));
	menu->fn.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Friendly Color Rainbow Speed"));
	menu->hitble.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Hittable Color Rainbow Speed"));
	menu->vis.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Visible Color Rainbow Speed"));
	menu->trcr.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Tracer Color Rainbow Speed"));
	menu->hb.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Shield Color Rainbow Speed"));
	menu->xh.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Crosshair Color Rainbow Speed"));
	menu->fc.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Fov Circle Color Rainbow Speed"));
	menu->rgbac.RainbowSpeed = Ini.ReadFloat(hash("Theme"), hash("Camo Color Rainbow Speed"));
	//End
	Ini.Free();
	char Filename[30];
	_sys_sprintf(Filename, encryptDecrypt(hash("$r!Bnoghfts`uhno!Ghmd!Mn`ede")).c_str(), fileName);
	UI_OpenToastPopup(0, encryptDecrypt(hash("uitlcrtq")).c_str(), encryptDecrypt(hash("Bnoghfts`uhno")).c_str(), Filename, 3000);
}

void SaveToIniFile(const char* fileName) {
	Ini.PrepareSave(fileName);
	Ini.WriteSection(hash("Aimbot"));
	Ini.WriteBool(hash("Player Aimbot"), bot.benable);
	Ini.WriteInt(hash("Aim Type"), bot.aimtype);
	Ini.WriteInt(hash("Key Type"), bot.keytype);
	Ini.WriteInt(hash("Tag Type"), bot.tagtype);
	Ini.WriteInt(hash("Bone Scan Strength"), bot.loop_number_autobone);
	Ini.WriteBool(hash("Fov Circle"), bot.bcircle);
	Ini.WriteFloat(hash("Fov Circle Scale"), bot.fovs);
	Ini.WriteFloat(hash("Smooth Snap Scale"), bot.snaps);
	Ini.WriteFloat(hash("ADS Zoom Scale"), bot.ads);
	Ini.WriteBool(hash("Visible"), bot.bvisible);
	Ini.WriteBool(hash("Autowall"), bot.bautowall);
	Ini.WriteBool(hash("FPS Saving"), menu->fpssaving);
	Ini.WriteBool(hash("Aim Lock"), bot.benablal);
	Ini.WriteBool(hash("Remove Spread"), bot.bnospread);
	Ini.WriteBool(hash("Remove Flinch"), bot.bnoflinch);
	Ini.WriteBool(hash("Remove Sway"), bot.bnosway);
	Ini.WriteBool(hash("Remove Bob"), bot.bnobob);
	Ini.WriteBool(hash("Remove Recoil"), bot.bnorec);
	Ini.WriteBool(hash("Remove Kick"), bot.bnokick);
	Ini.WriteBool(hash("Cancel Reload"), bot.cancelreload);
	Ini.WriteBool(hash("Auto Crouch"), bot.bautocrouch);
	Ini.WriteBool(hash("Lean"), bot.blean);
	Ini.WriteBool(hash("Air Stuck"), bot.bIsAirStuck);
	Ini.WriteBool(hash("Snake"), bot.snake_bot);
	Ini.WriteBool(hash("Lean"), bot.blean);
	Ini.WriteBool(hash("Autoshoot"), bot.bautoshoot);
	Ini.WriteSection(hash("Anti-Aim"));//Antiaim
	Ini.WriteBool(hash("Enable Antiaim"), bot.benableanti);
	Ini.WriteBool(hash("Third Person"), bot.bthirdp);
	Ini.WriteBool(hash("Unlock Angles"), bot.block3dpaa);
	Ini.WriteBool(hash("Advanced Options"), bot.baaadvanced);
	Ini.WriteInt(hash("Firing X"), bot.antitypeX[FIRING]);
	Ini.WriteInt(hash("Sprinting X"), bot.antitypeX[SPRINTING]);
	Ini.WriteInt(hash("Crouching X"), bot.antitypeX[CROUCHING]);
	Ini.WriteInt(hash("Standing X"), bot.antitypeX[STANDING]);
	Ini.WriteInt(hash("Moving X"), bot.antitypeX[MOVING]);
	Ini.WriteInt(hash("Snake X"), bot.antitypeX[SNAKE]);
	Ini.WriteInt(hash("Firing Y"), bot.antitypeY[FIRING]);
	Ini.WriteInt(hash("Sprinting Y"), bot.antitypeY[SPRINTING]);
	Ini.WriteInt(hash("Crouching Y"), bot.antitypeY[CROUCHING]);
	Ini.WriteInt(hash("Standing Y"), bot.antitypeY[STANDING]);
	Ini.WriteInt(hash("Moving Y"), bot.antitypeY[MOVING]);
	Ini.WriteInt(hash("Snake Y"), bot.antitypeY[SNAKE]);
	Ini.WriteFloat(hash("Custom Pitch"), bot.custompitchscale);
	Ini.WriteBool(hash("Riot Backwards"), bot.breversebot);
	Ini.WriteBool(hash("Simi-Up"), bot.blockup);
	Ini.WriteFloat(hash("Jitter X Scale"), bot.pitchscalex);
	Ini.WriteFloat(hash("Jitter Y Scale"), bot.pitchscaley);
	Ini.WriteFloat(hash("Spin Y Scale"), bot.spinscale);
	Ini.WriteFloat(hash("Fake Lag Scale"), bot.fakelagscale);
	Ini.WriteSection(hash("Visuals"));//Esp
	Ini.WriteBool(hash("Friendlys"), bot.esp.ballies);
	Ini.WriteBool(hash("Enemys"), bot.esp.baxis);
	Ini.WriteInt(hash("Bound"), bot.esp.bound);
	Ini.WriteInt(hash("Snaplines"), bot.esp.snaplines);
	Ini.WriteBool(hash("Names"), bot.esp.bnames);
	Ini.WriteBool(hash("Crosshair Compass"), bot.esp.bcompass);
	Ini.WriteBool(hash("Health Bar"), bot.esp.bhealthbar);
	Ini.WriteBool(hash("Sprint Meter"), bot.esp.sprintmeter);
	Ini.WriteBool(hash("Dynamic Crosshair"), bot.esp.bdynamic);
	Ini.WriteBool(hash("Custom Crosshair"), bot.customxh);
	Ini.WriteBool(hash("Custom Dynamic"), bot.customxhd);
	Ini.WriteFloat(hash("Pattern X"), bot.customw);
	Ini.WriteFloat(hash("Pattern Y"), bot.customh);
	Ini.WriteFloat(hash("Thickness"), bot.customt);
	Ini.WriteFloat(hash("Rotation"), bot.customr);
	Ini.WriteFloat(hash("Spin Speed"), bot.customrs);
	Ini.WriteBool(hash("Tracers"), bot.esp.btracers);
	Ini.WriteBool(hash("Client Health Bars"), bot.esp.clienthealth);
	Ini.WriteBool(hash("Target Info"), bot.esp.btargetinfo);
	Ini.WriteBool(hash("Proximity Warning"), bot.esp.bprox);
	Ini.WriteBool(hash("V-Angles"), bot.esp.bvangles);
	Ini.WriteBool(hash("Laser"), bot.blaser);
	Ini.WriteBool(hash("Enable Chams"), bot.esp.bchams);
	Ini.WriteBool(hash("Weapon Chams"), bot.esp.bweaponchams);
	Ini.WriteBool(hash("Chams On Me"), menu->renderchamsonme);
	Ini.WriteFloat(hash("Chams Intensity"), bot.chamsintensity);
	Ini.WriteBool(hash("Player Wallhack"), bot.esp.bwall);
	Ini.WriteBool(hash("Weapon Wallhack"), bot.esp.bwwall);
	Ini.WriteBool(hash("Entity Wallhack"), bot.esp.ebwall);
	Ini.WriteBool(hash("Enable World Ents"), bot.esp.benableworldents);
	Ini.WriteBool(hash("Weapons"), bot.esp.bweapsworld);
	Ini.WriteBool(hash("Weapon Items"), bot.esp.bpickupweaponsworld);
	Ini.WriteBool(hash("Grenades"), bot.esp.bnadesworld);
	Ini.WriteBool(hash("Scavenger Bags"), bot.esp.bpickupscavsworld);
	Ini.WriteBool(hash("Projectile Fuse Time"), bot.esp.benablenadefuse);
	Ini.WriteBool(hash("Projectile Tracers"), bot.esp.bnadetracers);
	Ini.WriteBool(hash("Enable Radar"), bot.esp.bradar);
	Ini.WriteBool(hash("Orbital VSAT"), bot.esp.bplayers);
	Ini.WriteFloat(hash("Compass Scale"), bot.esp.scale);
	Ini.WriteFloat(hash("Compass Size"), bot.esp.scalewh);
	Ini.WriteBool(hash("Weapon Items"), bot.esp.bradrpickupweaps);
	Ini.WriteBool(hash("Grenades"), bot.esp.bradrnades);
	Ini.WriteBool(hash("Scavenger Bags"), bot.esp.bradrpickupscavs);
	Ini.WriteBool(hash("Helicopters"), bot.esp.bradrhelis);
	Ini.WriteBool(hash("Dogos"), bot.esp.bradrdogos);
	Ini.WriteBool(hash("Vehicles"), bot.esp.bradrvehicles);
	Ini.WriteBool(hash("Turrets"), bot.esp.bradrturrets);
	Ini.WriteBool(hash("Artillery"), bot.esp.bradrartillery);
	Ini.WriteBool(hash("Tracers"), bot.esp.bradartracers);
	Ini.WriteFloat(hash("Fade Time"), menu->fadeTime);
	Ini.WriteFloat(hash("Fade Scale"), menu->fadeScale);
	Ini.WriteFloat(hash("Beam Width"), menu->beamWidth);
	Ini.WriteFloat(hash("Beam Length"), menu->beamLength);
	Ini.WriteFloat(hash("Screw Radius"), menu->screwRadius);
	Ini.WriteFloat(hash("Screw Dist"), menu->screwDist);
	Ini.WriteSection(hash("Cheats"));//Cheats
	Ini.WriteBool(hash("Unlimited Class Slots"), local->unlimitedSlots);
	Ini.WriteFloat(hash("Fov"), menu->frenderfovx);
	Ini.WriteBool(hash("Night Mode"), menu->nightmode);
	Ini.WriteBool(hash("Remove Flash"), bot.noflsh);
	Ini.WriteBool(hash("Full Bright"), bot.bfullbright);
	Ini.WriteBool(hash("32 Name Patcher"), menu->i32_Name);
	Ini.WriteBool(hash("Flash Name"), menu->flshname);
	Ini.WriteBool(hash("Advertise Menu"), menu->addname);
	Ini.WriteBool(hash("Force Invite"), menu->bForceInv);
	Ini.WriteBool(hash("Bypass Closed Sessions"), menu->bClosedBypass);
	Ini.WriteFloat(hash("Prop Size"), menu->props);
	Ini.WriteBool(hash("Gun Sounds"), menu->bgunsound);
	Ini.WriteBool(hash("Smoke Color"), menu->smokec);
	Ini.WriteBool(hash("Sky Color"), menu->skyc);
	Ini.WriteBool(hash("Sky Rotate"), menu->skyr);
	Ini.WriteSection(hash("Settings"));//Settings
	Ini.WriteBool(hash("Celsius"), menu->fahrenheit);
	Ini.WriteBool(hash("Disable CPU"), menu->temp1);
	Ini.WriteBool(hash("Disable RSX"), menu->temp2);
	Ini.WriteBool(hash("Disable FPS"), menu->fps);
	Ini.WriteBool(hash("Disable Resolution"), menu->res);
	Ini.WriteBool(hash("Disable DLC"), menu->disabledlc);
	Ini.WriteBool(hash("Enable DLC Camos"), menu->benablecamos);
	Ini.WriteBool(hash("Spinning Weapons"), menu->sping);
	Ini.WriteBool(hash("Disable Menu Sounds"), menu->engnsounds);
	Ini.WriteBool(hash("Trickshot Mode"), menu->btrickmode);
	Ini.WriteFloat(hash("Scroll Speed"), bot.scspeed);
	Ini.WriteInt(hash("Search Session Max Ping"), menu->SMPing);
	Ini.WriteSection(hash("Server Info"));//Server Info
	Ini.WriteBool(hash("Disable Server Info"), menu->serverinfo);
	Ini.WriteBool(hash("Disable Host Name"), menu->host);
	Ini.WriteBool(hash("Disable Map Name"), menu->map);
	Ini.WriteBool(hash("Disable Game Type Name"), menu->game);
	Ini.WriteBool(hash("Disable Entitys"), menu->ents);
	Ini.WriteBool(hash("Disable Max Clients"), menu->maxc);
	Ini.WriteSection(hash("Camo"));//Camo
	Ini.WriteInt(hash("Camo Type"), bot.camotype);
	Ini.WriteInt(hash("Camo Spoofer"), menu->flagx);
	Ini.WriteBool(hash("Enable Camo Color"), menu->camocolor);
	Ini.WriteFloat(hash("Reflection"), menu->Reflection);
	Ini.WriteFloat(hash("Normal Map Height"), menu->normalheight);
	Ini.WriteFloat(hash("Emissive"), menu->Emissive_Amo);
	Ini.WriteFloat(hash("Gloss"), menu->Gloss_Amount);
	Ini.WriteFloat(hash("Animate Layer1 X"), menu->Layer1ScrollX);
	Ini.WriteFloat(hash("Animate Layer1 Y"), menu->Layer1ScrollY);
	Ini.WriteFloat(hash("Layer1 Depth"), menu->Layer1Depth);
	Ini.WriteFloat(hash("Layer1 Width"), menu->Layer1W);
	Ini.WriteFloat(hash("Layer1 Height"), menu->Layer1H);
	Ini.WriteFloat(hash("Layer1 Alpha"), menu->Layer1Alpha);
	Ini.WriteFloat(hash("Animate Layer2 X"), menu->Layer2ScrollX);
	Ini.WriteFloat(hash("Animate Layer2 Y"), menu->Layer2ScrollY);
	Ini.WriteFloat(hash("Animate Layer3"), menu->Layer3Scroll);
	Ini.WriteSection(hash("Theme"));//Theme
	Ini.WriteBool(hash("Custom BO2 Theme"), menu->bo2theme);
	Ini.WriteInt(hash("Width Size"), menu->msize);
	Ini.WriteBool(hash("Enable Fade"), menu->fade);
	Ini.WriteBool(hash("Lock Colors"), menu->lockcolor);
	Ini.WriteColor(hash("Enemy Color"), menu->en);
	Ini.WriteColor(hash("Friendly Color"), menu->fn);
	Ini.WriteColor(hash("Hittable Color"), menu->hitble);
	Ini.WriteColor(hash("Visible Color"), menu->vis);
	Ini.WriteColor(hash("Tracer Color"), menu->trcr);
	Ini.WriteColor(hash("Shield Color"), menu->hb);
	Ini.WriteColor(hash("Crosshair Color"), menu->xh);
	Ini.WriteColor(hash("Fov Circle Color"), menu->fc);
	Ini.WriteColor(hash("Main Color"), menu->skin);
	Ini.WriteColor(hash("Secondary Color"), menu->skin2);
	Ini.WriteColor(hash("Border Primary"), menu->skin3);
	Ini.WriteColor(hash("Border Secondary"), menu->skin4);
	Ini.WriteColor(hash("Border Tertiary"), menu->skin5);
	Ini.WriteColor(hash("Border Quaternary"), menu->skin6);
	Ini.WriteColor(hash("Camo Color"), menu->rgbac);
	Ini.WriteBool(hash("Enemy Color Rainbow"), menu->en.Rainbow);
	Ini.WriteBool(hash("Friendly Color Rainbow"), menu->fn.Rainbow);
	Ini.WriteBool(hash("Hittable Color Rainbow"), menu->hitble.Rainbow);
	Ini.WriteBool(hash("Visible Color Rainbow"), menu->vis.Rainbow);
	Ini.WriteBool(hash("Tracer Color Rainbow"), menu->trcr.Rainbow);
	Ini.WriteBool(hash("Shield Color Rainbow"), menu->hb.Rainbow);
	Ini.WriteBool(hash("Crosshair Color Rainbow"), menu->xh.Rainbow);
	Ini.WriteBool(hash("Fov Circle Color Rainbow"), menu->fc.Rainbow);
	Ini.WriteBool(hash("Border Primary Color Rainbow"), menu->skin3.Rainbow);
	Ini.WriteBool(hash("Border Secondary Color Rainbow"), menu->skin4.Rainbow);
	Ini.WriteBool(hash("Border Tertiary Color Rainbow"), menu->skin5.Rainbow);
	Ini.WriteBool(hash("Border Quaternary Color Rainbow"), menu->skin6.Rainbow);
	Ini.WriteBool(hash("Camo Color Rainbow"), menu->rgbac.Rainbow);
	Ini.WriteFloat(hash("Main Color Theme Rainbow Speed"), menu->menufade);
	Ini.WriteFloat(hash("Enemy Color Rainbow Speed"), menu->en.RainbowSpeed);
	Ini.WriteFloat(hash("Friendly Color Rainbow Speed"), menu->fn.RainbowSpeed);
	Ini.WriteFloat(hash("Hittable Color Rainbow Speed"), menu->hitble.RainbowSpeed);
	Ini.WriteFloat(hash("Visible Color Rainbow Speed"), menu->vis.RainbowSpeed);
	Ini.WriteFloat(hash("Tracer Color Rainbow Speed"), menu->trcr.RainbowSpeed);
	Ini.WriteFloat(hash("Shield Color Rainbow Speed"), menu->hb.RainbowSpeed);
	Ini.WriteFloat(hash("Crosshair Color Rainbow Speed"), menu->xh.RainbowSpeed);
	Ini.WriteFloat(hash("Fov Circle Color Rainbow Speed"), menu->fc.RainbowSpeed);
	Ini.WriteFloat(hash("Camo Color Rainbow Speed"), menu->rgbac.RainbowSpeed);
	Ini.Save();
	char Filename[30];
	_sys_sprintf(Filename, encryptDecrypt(hash("$r!Bnoghfts`uhno!Ghmd!R`wde")).c_str(), fileName);
	UI_OpenToastPopup(0, encryptDecrypt(hash("uitlcrtq")).c_str(), encryptDecrypt(hash("Bnoghfts`uhno")).c_str(), Filename, 3000);
}