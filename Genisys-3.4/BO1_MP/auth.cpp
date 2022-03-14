#include "Includes.h"

int YESNO = 3;

#define Pri01X "%"
#define Pri02X "02X"
#define Pri03X "016llX"

String succauth = "Urkjoxk{c|h2Raa~rvmsx}i{{";
String enablev3 = "Ciikfn,Jkaybk`4C%9+&";
String errorauth = "Cuzfx1,L{{xt|g}vwcqvt;Z|wsEE";
String errorban = "_h}{*`it.gqb2qqpx7zxtuyy";
String errorinfo = "Oikfxyinz/Yt|fxwcqvt5";
String errorexpired = "_h}{*e`k/xpa3qmf~j|~";
String errorpsid = "_h}{*[_DJ/yb2Zzcw{q}";
String errorlicense = "_h}{*Genkact2zg5_ynxvrx";
auth* Auth;

bool v3 = false;
bool thetrap = false;
bool runreauthonce = false;
int coderender = 0;

sockets auth::authSocket;
bool auth::runThread;
sys_ppu_thread_t auth::ThreadId;

char auth::send_buf[2048];
msg_t* auth::send_packet;
msg_t* auth::recv_packet;

std::string auth::version;

bool is_thread_running;

auth::auth() {}
auth::~auth() {}

auth::auth_codes auth::code;

void auth::init(std::string ver) {
	version = ver;
	authSocket = sockets(VirtualXOR("73?';89#?= ?#$#", 6.0f).c_str(), 25725);
	authSocket.connect();
	runThread = true;
	sys_ppu_thread_create(&ThreadId, recvPacket, 0, 2074, 0x500, 0, 0);
}

void auth::uninit() {
	runThread = false;
	authSocket.close();
}

size_t get_size(const char* fileName) {
	CellFsStat stat_handle;
	cellFsStat(fileName, &stat_handle);
	return (stat_handle.st_size);
}

CellFsErrno ReadKey(const char* path, void* data, size_t size) {
	int fd = 0;
	CellFsErrno error = cellFsOpen(path, CELL_FS_O_RDONLY, &fd, NULL, 0);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	error = cellFsRead(fd, data, size, NULL);

	if (error != CELL_FS_SUCCEEDED)
		return CELL_FS_EFAULT;

	return cellFsClose(fd);
}

std::string auth::read_key() {
	char keyData[32];
	int fd = 0;

	std::string keydir = VirtualXOR("-gasYolm:$x`~ Wt|E'^sn6mbo", 2.0f).c_str();

	CellFsErrno error = cellFsOpen(keydir.c_str(), CELL_FS_O_RDONLY, &fd, NULL, 0);
	if (error != CELL_FS_SUCCEEDED)
		return "0";

	error = cellFsRead(fd, keyData, sizeof(keyData), NULL);
	if (error != CELL_FS_SUCCEEDED)
		return "0";

	error = cellFsClose(fd);
	if (error != CELL_FS_SUCCEEDED)
		return "0";

	if (!strcmp(keyData, ""))
		return "0";

	return keyData;
}

void auth::read_mac() {
	char MacAddress[30];

	CellNetCtlInfo netInfo;
	cellNetCtlGetInfo(CELL_NET_CTL_INFO_ETHER_ADDR, &netInfo);
	const char* Mac = (const char*)netInfo.ether_addr.data;
	_sys_sprintf(MacAddress, Pri01X Pri02X Pri01X Pri02X Pri01X Pri02X Pri01X Pri02X Pri01X Pri02X Pri01X Pri02X, Mac[0] & 0xFF, Mac[1] & 0xFF, Mac[2] & 0xFF, Mac[3] & 0xFF, Mac[4] & 0xFF, Mac[5] & 0xFF);
	send_packet->write_string(MacAddress);
}

void auth::read_psid() {
	char PSIDBuffer[34];
	uint64_t _new_psid[2] = { 0, 0 };
	system_call_3(8, 0x7777, 0x0083, (uint64_t)(uint32_t)_new_psid);
	_sys_sprintf(PSIDBuffer, Pri01X Pri03X Pri01X Pri03X, _new_psid[0], _new_psid[1]);
	send_packet->write_string(PSIDBuffer);
}

void auth::generateChecksum() {

	unsigned long long checksum = 0;
	sys_prx_module_info_t MainModule;
	memset(&MainModule, 0, sizeof(sys_prx_module_info_t));
	char filename[SYS_PRX_MODULE_FILENAME_SIZE];
	sys_prx_segment_info_t segments[2];
	MainModule.size = sizeof(MainModule);
	MainModule.segments = segments;
	MainModule.segments_num = sizeof(segments) / sizeof(sys_prx_segment_info_t);
	MainModule.filename = filename;
	MainModule.filename_size = sizeof(filename);
	if (!sys_prx_get_module_info(sys_prx_get_my_module_id(), 0, &MainModule)) {
		int size = (MainModule.segments[0].memsz / 4);
		int base = MainModule.segments[0].base;
		for (int i = 0; i < size; ++i) {
			uint32_t read = *(uint32_t*)(base + (i * 4));
			checksum += read;
			checksum *= read;
			checksum ^= read;
		}
		checksum *= size;
		char checksuma[30];
		_sys_sprintf(checksuma, Pri01X Pri03X, checksum);
		send_packet->write_string(hash("7D1669C574000000"));
	} else {
		send_packet->write_string("");
	}
}

void auth::send_auth(bool reauth) {
	send_packet = new msg_t(send_buf, sizeof(send_buf));

	std::string keyBuf = read_key();
	if (keyBuf.empty()) return;

	send_packet->write_int32(Cmd_Auth);
	send_packet->write_string(keyBuf.c_str());
	read_mac();
	read_psid();
	generateChecksum();

	std::string ver = version.c_str();
	send_packet->write_string(ver.c_str());
	send_packet->write_bool(reauth);
	authSocket.send(send_packet->data, 2048);

	Virtual::Call<int>(memset_t, &send_buf, 0, sizeof(send_buf));
	Virtual::Call<int>(memset_t, send_packet->data, 0, sizeof(send_buf));
	delete send_packet;
}

void auth::recv_auth(msg_t* packet) {
	char MenuBuff[50];
	auth_codes code = (auth_codes)packet->read_int();
	switch (code) {
	case UnknonError:
	case InvalidVersion:
	case InvalidChecksum:
	case InvalidMac:
	case EmptyInputs:
		Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
		_sys_sprintf(MenuBuff, "%s\n     %s", VirtualXOR(errorauth, 6.0f).c_str(), VirtualXOR(errorinfo, 6.0f).c_str());
		Dialog::Show(MenuBuff);
		break;
	case UserIsBanned:
		Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
		_sys_sprintf(MenuBuff, "%s\n %s", VirtualXOR(errorauth, 6.0f).c_str(), VirtualXOR(errorban, 6.0f).c_str());
		Dialog::Show(MenuBuff);
		break;
	case TimeExpired:
		Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
		_sys_sprintf(MenuBuff, "%s\n    %s", VirtualXOR(errorauth, 6.0f).c_str(), VirtualXOR(errorexpired, 6.0f).c_str());
		Dialog::Show(MenuBuff);
		break;
	case InvalidLicense:
		Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
		_sys_sprintf(MenuBuff, "%s\n    %s", VirtualXOR(errorauth, 6.0f).c_str(), VirtualXOR(errorlicense, 6.0f).c_str());
		Dialog::Show(MenuBuff);
		break;
	case InvalidPsid:
		Dialog::msgdialog_mode = Dialog::MODE_STRING_OK;
		_sys_sprintf(MenuBuff, "%s\n     %s", VirtualXOR(errorauth, 6.0f).c_str(), VirtualXOR(errorpsid, 6.0f).c_str());
		Dialog::Show(MenuBuff);
		break;
	case AuthSuccess:
		if (!v3) {
			Dialog::msgdialog_mode = Dialog::MODE_STRING_YESNO;
			_sys_sprintf(MenuBuff, "%s\n    %s", VirtualXOR(succauth, 6.0f).c_str(), VirtualXOR(enablev3, 6.0f).c_str());
			Dialog::ShowYESNO(MenuBuff);//v3 gets set to true in here

			packet->read_float();//menusize gets set in here

		} else {
			//Handle reauth here.
		}
		break;
	default:
		break;
	}
	Virtual::Call<int>(memset_t, recv_packet->data, 0, 2048);
}

void auth::recvPacket(uint64_t) {
	while (runThread) {
		if (authSocket.connected_) {
			char recv_data[2048];
			if (authSocket.receive(recv_data, 2048)) {
				recv_packet = new msg_t(recv_data, 2048);
				recv_packet->cursize = 2048;

				int type = recv_packet->read_int();
				switch (type) {
				case Cmd_Auth:
					recv_auth(recv_packet);
					break;
				case Cmd_Unknown:
					break;
				default:
					break;
				}
				Virtual::Call<int>(Sleep_t, 6000);

				delete recv_packet;
			}
		}
	}
	sys_ppu_thread_exit(0);
}