#include "Includes.h"

friends fr;

bool ends_with(const std::string& text, const std::string& search) {
	return (text.size() >= search.size() && text.substr(text.size() - search.size(), search.size()) == search);
}

std::vector<std::string> list_files(std::string directory_name, int _max, bool recursive) {
	std::vector<std::string> files;

	files.clear();

	std::string directory_name_;

	directory_name_.clear();

	int fd;
	if (cellFsOpendir(directory_name.c_str(), &fd) != CELL_FS_OK) { return files; }

	uint64_t nread;
	CellFsDirent dent;

	while (cellFsReaddir(fd, &dent, &nread) == CELL_FS_OK) {
		if (files.size() >= _max)
			break;

		if (nread == 0) { break; }

		if (dent.d_name[0] != '.') {
			struct CellFsStat st;
			directory_name_ = directory_name + dent.d_name;

			if (cellFsStat(directory_name_.c_str(), &st) == CELL_FS_SUCCEEDED) {
				if ((st.st_mode & CELL_FS_S_IFDIR) != 0) {
					if (recursive) {
						auto sub_directory = list_files(directory_name_.c_str(), _max, recursive);
						for (auto& sub_file : sub_directory) {
							files.push_back(sub_file);
						}
					}
				}
				else {
					files.push_back(directory_name_.c_str());
				}
			}
		}
	}

	cellFsClosedir(fd);

	return files;
}

bool read_file(const std::string& file_name, void* data, size_t size) {
	int fd = 0;
	uint64_t pos = 0;
	uint64_t nread = 0;

	cellFsChmod(file_name.c_str(), CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (cellFsOpen(file_name.c_str(), 0, &fd, NULL, 0) == CELL_FS_SUCCEEDED) {
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		cellFsRead(fd, data, size, &nread);
		cellFsClose(fd);

		return true;
	}

	return false;
}

int64_t get_file_size(const std::string& file_name) {
	struct CellFsStat s;

	if (cellFsStat(file_name.c_str(), &s) == CELL_FS_SUCCEEDED) {
		return static_cast<int64_t>(s.st_size);
	}

	return -1;
}

std::string read_file(const std::string& file_name) {
	auto size = get_file_size(file_name);
	if (size != -1) {
		auto* data = new char[size + 1];
		read_file(file_name, data, size);

		std::string output;
		output.clear();
		output.resize(size + 1);
		memcpy(const_cast<char*>(output.c_str()), data, static_cast<size_t>(size));
		return output;
	}

	return {};
}

bool read_lines(const std::string& file_name, std::vector<std::string>& buffer) {
	std::string file_buffer = read_file(file_name);
	if (file_buffer.empty())
		return false;

	const char* pch;
	pch = strchr(file_buffer.c_str(), '\n');

	std::vector<int> positions;
	positions.push_back(0);
	while (pch != NULL) {
		positions.push_back(pch - file_buffer.c_str() + 1);
		pch = strchr(pch + 1, '\n');
	}

	for (int i = 0; i < positions.size(); i++) {
		buffer.push_back(file_buffer.substr(positions[i], positions[i + 1] - positions[i] - 1));
	}

	positions.clear();
	file_buffer.clear();
}

bool file_exists(const std::string& file_name) {
	struct CellFsStat s;

	if (cellFsStat(file_name.c_str(), &s) == CELL_FS_SUCCEEDED) {
		return ((s.st_mode & CELL_FS_S_IFREG) != 0);
	}

	return false;
}

bool directory_exists(const std::string& directory_name) {
	struct CellFsStat s;

	if (cellFsStat(directory_name.c_str(), &s) == CELL_FS_SUCCEEDED) {
		return ((s.st_mode & CELL_FS_S_IFDIR) != 0);
	}

	return false;
}

void create_directory(const std::string& directory_name) {
	if (!directory_exists(directory_name.c_str())) {
		cellFsMkdir(directory_name.c_str(), 0777);
	}
}

std::vector<std::string> split(const std::string& text, char delimiter) {
	std::vector<std::string> out;
	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = text.find(delimiter, pos)) != std::string::npos) {
		std::string substring(text.substr(prev_pos, pos - prev_pos));

		out.push_back(substring);

		prev_pos = ++pos;
	}

	out.push_back(text.substr(prev_pos, pos - prev_pos));
	return out;
}

bool write_file(const std::string& file_name, const void* data, size_t size) {
	int fd = 0;
	uint64_t pos = 0, nwrite = 0;

	if (cellFsOpen(file_name.c_str(), CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, NULL, 0) == CELL_FS_SUCCEEDED) {
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		cellFsWrite(fd, data, size, &nwrite);
		cellFsClose(fd);
		return true;
	}

	return false;
}

bool write_file(const std::string& file_name, const std::string& data) {
	return write_file(file_name, data.c_str(), data.length());
}

String honkList[] = {
hash("Messing with the honk"),
hash("Honk?, get the bonk"),
hash("Bonk"), hash("Oooooooh yea you like my ASSets HUH?"),
hash("Fuck....."),
hash("Peace was never an option"),
hash("Im an agent of chaos"),
hash("wAckY BoNkErs!"),
hash("Ending skids with V3.4"),
hash("Can I use mod menu on chimken"),
hash("Grab a bonk load of my ASSets"),
hash("This isn't real"),
hash("Reality is a lie"),
hash("Crashing on memset"),
hash("You just got robloxed"),
hash("Hazy gay"),
hash("Hmmm you wish you had these ASSets bro"),
hash("Hmmmmmmm you want these ASSets HUH???"),
hash("Bruh moment"),
hash("Boof"),
hash("Developing Dexters excuse for a cheat"),
hash("Eat my ass"),
hash("Get stick bugged"),
hash("Go to horny jail"),
hash("Lupos is the fake Lupos"),
hash("About 12"),
hash("Red looking sus"),
hash("Hello, how are u, I'm unda da water"),
hash("1000% zoom = code go brrrrrrrr"),
hash("BOOOOONEZZZZzzzzz"),
hash("Blasts mods likes men"),
hash("Welcome to the get fucked update"),
hash("What the hell is even that"),
hash("Cocking Nora"),
hash("DEXCFW: Reselling pasted botnets"),
hash("Genisys clap Gaybab"),
hash("Wait your menu has 4 sides? it must be leeched"),
hash("Beetsd from beeietnam"),
hash("But can it handle 7zip"),
hash("That was a 0xFE moment"),
hash("Are you really hacking if you don't crash on memset"),
hash("PS3 video editor gang"),
"!IDA SKID"
};

bool delete_file(const std::string& file_name) {
	if (!file_exists(file_name))
		return false;
	else
		cellFsUnlink(file_name.c_str());
}

void friends::delete_friend(std::string user) {
	delete_file(FRIENDS_DIR + user + hash(".ini"));
	friends::read_friends();
	Mshit.id = Mshit.prev[Mshit.id - 1];
}

int read_npid(std::string name, SceNpId* npid)
{
	// BO1 NPWR01247
	// BO2 NPWR02059
	// BO3 NPWR08251
	int32_t ret, tmp;

	if (name.empty())
		return -1;

	SceNpOnlineId onlineId;
	memset(&onlineId, 0, sizeof(onlineId));
	strncpy(onlineId.data, name.c_str(), SCE_NET_NP_ONLINEID_MAX_LENGTH);

	SceNpId my_npid;
	ret = sceNpManagerGetNpId(&my_npid);
	if (ret < 0)
	{
		printf(hash("failed to get npid (0x%X)"), ret);
		return -1;
	}

	if (name == "")
		return -1;
	auto lookupTitleCtxId = sceNpLookupCreateTitleCtx((SceNpCommunicationId*)hash("NPWR02059"), &my_npid);

	int32_t transId = sceNpLookupCreateTransactionCtx(lookupTitleCtxId);

	ret = sceNpLookupNpIdAsync(transId, &onlineId, npid, 0, NULL);
	if (ret < 0)
	{
		printf(hash("failed to lookup npid (0x%X)\n"), ret);
		return -1;
	}
	int result;
	while (sceNpLookupPollAsync(transId, &result)) {
		cellSysutilCheckCallback();
		Sleep(500);
	}
	sceNpLookupDestroyTitleCtx(lookupTitleCtxId);
	sceNpLookupDestroyTransactionCtx(lookupTitleCtxId);

	if (npid->handle.data[0] == '\0')
	{
		printf(hash("invalid handle\n"));
		return -1;
	}
	npid->opt[4] = 'p';
	npid->opt[5] = 's';
	npid->opt[6] = '3';
	npid->reserved[0] = 1;

	return ret;
}

int friends::friend_count;
unsigned int friends::true_count;
int friends::friend_increment;

Detour sceNpBasicGetFriendPresenceByIndex2Detour;
int friends::sceNpBasicGetFriendPresenceByIndexC(uint32_t index, SceNpUserInfo* user, SceNpBasicPresenceDetails2* pres, uint32_t options)
{
	auto ret = sceNpBasicGetFriendPresenceByIndex2Detour.Stub(index, user, pres, options);

	if (strcmp(user->userId.handle.data, "") == 0)
	{
		auto* _friend = (friend_list*)(0x260F4B0 + (index * 0x108));
		strcpy((char*)user->userId.handle.data, _friend->name);
		strcpy((char*)user->userId.opt, _friend->npid);

		user->userId.reserved[0] = 1;
		pres->state = 1;
		friend_increment++;

		if (friend_increment >= friend_count)
			friend_increment = 0;
	}
	pres->state = 2;
}

Detour sceNpBasicGetFriendListEntryCountDetour;
int sceNpBasicGetFriendListEntryC(uint32_t* count) {
	int ret = sceNpBasicGetFriendListEntryCount(&friends::true_count);
	if (ret < 0) {
		printf("err");
	}
	friends::read_friends();
	friends::friend_increment = friends::true_count;
	*count = friends::true_count + friends::friend_count;
	return 0;
}

void friends::read_friends()
{
	create_directory(FRIENDS_SUB_DIR);
	create_directory(FRIENDS_DIR);

	int max_ = 100;
	int value = max_ - friends::true_count;
	int friend_count = 0;
	int max_friends = friends::true_count;

	Ini.Init(va(hash("%s/%s"), FRIENDS_DIR, hash("Friends.ini")));

	while (true)
	{
		auto section_id = va(hash("%i.gen"), friend_count);
		if (!Ini.GetSection(section_id))
			break;

		char name[16], npid[8];
		Ini.ReadString(section_id, hash("name"), name);
		Ini.ReadString(section_id, hash("npid"), npid);

		auto* _friend = (friend_list*)(0x260F4B0 + (max_friends++ * 0x108));
		memset(_friend, 0, sizeof(friend_list));

		strcpy(_friend->name, name);
		strncpy(_friend->npid, npid, 7);

		friend_count++;
	}

	Ini.Free();

	friends::friend_count = friend_count - 1;
}


void friends::write_friend(std::string user, std::string npid)
{
	static int friend_count = 0;

	int status;
	sceNpManagerGetStatus(&status);

	if (user.empty())
		return;

	if (status == 3)
	{
		if (user.empty())
			return;
		if (npid.empty())
			return;

		Ini.WriteSection(va(hash("%i.gen"), friend_count++));
		Ini.WriteString(hash("name"), user.c_str());
		Ini.WriteString(hash("npid"), npid.c_str());
	}
}

void friends::import_friends(const std::string& user_file)
{
	Ini.PrepareFriendsSave(va(hash("%s/%s"), FRIENDS_DIR, hash("Friends.ini")));

	if (user_file.empty())
		return;

	auto file_data = read_file(user_file);
	if (file_data.empty())
		return;

	std::string name;
	std::string npid;

	auto list = split(file_data, '|');
	for (int i = 0; i < list.size(); i++)
	{
		auto buffer = list[i];

		auto split_pos = buffer.find(":");
		if (split_pos == std::string::npos)
			continue;

		if (name.size() == 1)
			continue;

		if (npid.size() == 1)
			continue;

		name = buffer.substr(0, split_pos);
		npid = buffer.substr(split_pos + 1, buffer.size() - split_pos);

		write_friend(name.data(), npid.data());
	}

	Ini.Save();
}

void friends::start()
{
	create_directory(FRIENDS_SUB_DIR);
	create_directory(FRIENDS_DIR);
	
	sceNpBasicGetFriendListEntryCountDetour.Hook(0x08DEB4C, sceNpBasicGetFriendListEntryC);
	sceNpBasicGetFriendPresenceByIndex2Detour.Hook(0x08DE8E4, sceNpBasicGetFriendPresenceByIndexC);

	import_friends(hash("/dev_hdd0/tmp/Genisys/Friends"));
	UI_OpenToastPopup(0, encryptDecrypt(hash("life_counter_alive")).c_str(), VirtualXOR(hash("Initializing"), 8).c_str(), hash("Fake Friends Initialized"), 5000);
}

