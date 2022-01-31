#include "Includes.h"

bool ends_with(const std::string& text, const std::string& search)
{
	return (text.size() >= search.size() && text.substr(text.size() - search.size(), search.size()) == search);
}

std::vector<std::string> list_files(const std::string& directory_name, bool recursive)
{
	std::vector<std::string> files;

	std::string directory_name_ = directory_name;
	if (!ends_with(directory_name, "/"))
	{
		directory_name_.append("/");
	}

	int fd;
	if (cellFsOpendir(directory_name_.c_str(), &fd) != CELL_FS_OK) { return files; }

	uint64_t nread;
	CellFsDirent dent;

	while (cellFsReaddir(fd, &dent, &nread) == CELL_FS_OK)
	{
		if (nread == 0) { break; }

		if (dent.d_name[0] != '.')
		{
			struct CellFsStat st;
			auto file = directory_name_ + dent.d_name;

			if (cellFsStat(file.c_str(), &st) == CELL_FS_SUCCEEDED)
			{
				if ((st.st_mode & CELL_FS_S_IFDIR) != 0)
				{
					if (recursive)
					{
						auto sub_directory = list_files(file, recursive);
						for (auto& sub_file : sub_directory)
						{
							files.push_back(sub_file);
						}
					}
				}
				else
				{
					files.push_back(file);
				}
			}
		}
	}

	cellFsClosedir(fd);

	return files;
}

bool read_file(const std::string& file_name, void* data, size_t size)
{
	int fd = 0;
	uint64_t pos = 0;
	uint64_t nread = 0;

	cellFsChmod(file_name.c_str(), CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
	if (cellFsOpen(file_name.c_str(), 0, &fd, NULL, 0) == CELL_FS_SUCCEEDED)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		cellFsRead(fd, data, size, &nread);
		cellFsClose(fd);

		return true;
	}

	return false;
}

int64_t get_file_size(const std::string& file_name)
{
	struct CellFsStat s;

	if (cellFsStat(file_name.c_str(), &s) == CELL_FS_SUCCEEDED)
	{
		return static_cast<int64_t>(s.st_size);
	}

	return -1;
}

std::string read_file(const std::string& file_name)
{
	auto size = get_file_size(file_name);
	if (size != -1)
	{
		auto* data = new char[size + 1];
		read_file(file_name, data, size);

		std::string output;
		output.resize(size + 1);
		memcpy(const_cast<char*>(output.c_str()), data, static_cast<size_t>(size));
		return output;
	}

	return {};
}
bool read_lines(const std::string& file_name, std::vector<std::string>& buffer)
{
	std::string file_buffer = read_file(file_name);
	if (file_buffer.empty())
		return false;

	const char* pch;
	pch = strchr(file_buffer.c_str(), '\n');

	std::vector<int> positions;
	positions.push_back(0);
	while (pch != NULL)
	{
		positions.push_back(pch - file_buffer.c_str() + 1);
		pch = strchr(pch + 1, '\n');
	}

	for (int i = 0; i < positions.size(); i++)
	{
		buffer.push_back(file_buffer.substr(positions[i], positions[i + 1] - positions[i] - 1));
	}
} 

bool file_exists(const std::string& file_name)
{
	struct CellFsStat s;

	if (cellFsStat(file_name.c_str(), &s) == CELL_FS_SUCCEEDED)
	{
		return ((s.st_mode & CELL_FS_S_IFREG) != 0);
	}

	return false;
}

bool directory_exists(const std::string& directory_name)
{
	struct CellFsStat s;

	if (cellFsStat(directory_name.c_str(), &s) == CELL_FS_SUCCEEDED)
	{
		return ((s.st_mode & CELL_FS_S_IFDIR) != 0);
	}

	return false;
}

void create_directory(const std::string& directory_name)
{
	if (!directory_exists(directory_name.c_str()))
	{
		cellFsMkdir(directory_name.c_str(), 0777);
	}
}

std::vector<std::string> split(const std::string& text, char delimiter)
{
	std::vector<std::string> out;
	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = text.find(delimiter, pos)) != std::string::npos)
	{
		std::string substring(text.substr(prev_pos, pos - prev_pos));

		out.push_back(substring);

		prev_pos = ++pos;
	}

	out.push_back(text.substr(prev_pos, pos - prev_pos));
	return out;
}

bool write_file(const std::string& file_name, const void* data, size_t size)
{
	int fd = 0;
	uint64_t pos = 0, nwrite = 0;

	if (cellFsOpen(file_name.c_str(), CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, NULL, 0) == CELL_FS_SUCCEEDED)
	{
		cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
		cellFsWrite(fd, data, size, &nwrite);
		cellFsClose(fd);

		return true;
	}

	return false;
}

bool write_file(const std::string& file_name, const std::string& data)
{
	return write_file(file_name, data.c_str(), data.length());
}

int friends::friend_count;
int friends::friend_increment;
std::vector<friend_list> friends::sorted_friends;

Detour sceNpBasicGetFriendPresenceByIndex2Detour;
int sceNpBasicGetFriendPresenceByIndexC(uint32_t index, SceNpUserInfo* user, SceNpBasicPresenceDetails2* pres, uint32_t options) 
{
	sceNpBasicGetFriendPresenceByIndex2Detour.Stub(index, user, pres, options);

	if (strcmp(user->userId.handle.data, "") == 0)
	{
		strcpy((char*)user->userId.handle.data, friends::sorted_friends[friends::friend_increment].name.c_str());
		strcpy((char*)user->userId.opt, friends::sorted_friends[friends::friend_increment].npid.c_str());
		strcpy((char*)pres->status, "Genisys Friend System User");
		user->userId.reserved[0] = 1;
		pres->state = 2;
		friends::friend_increment++;
		
		if (friends::friend_increment >= friends::friend_count)
			friends::friend_increment = 0;
	}
	pres->state = 2;
}

Detour sceNpBasicGetFriendListEntryCountDetour;
int sceNpBasicGetFriendListEntryC(uint32_t* count) {
	friends::read_friends(friends::sorted_friends);
	uint32_t iCount = 0;
	friends::friend_count = friends::sorted_friends.size();
	int ret = sceNpBasicGetFriendListEntryCount(&iCount);
	if (ret < 0) {
		printf("err");
	}
	*count = iCount + friends::friend_count;
	return 0;
}

void friends::read_friends(std::vector<friend_list>& list)
{
	sorted_friends.clear();

	create_directory(FRIENDS_SUB_DIR);
	create_directory(FRIENDS_DIR);

	std::vector<std::string> files = list_files(FRIENDS_DIR, false);

	for (auto& file : files)
	{
		auto permission = cellFsChmod(file.c_str(), CELL_FS_S_IRWXU | CELL_FS_S_IRWXG | CELL_FS_S_IRWXO);
		if (permission != 0)
			printf("perm: 0x%X\n", permission);

		std::vector<std::string> buffer;
		if (!ends_with(file, ".gfs"))
			continue;

		read_lines(file, buffer);
		if (buffer.size() == 0)
			continue;

		friend_list friends = friend_list();

		friends::parse_info(buffer, friends);

		list.push_back(friends);
	}
}

void friends::write_friend(std::string user, std::string npid)
{
	int status;
	sceNpManagerGetStatus(&status);

	if (user.empty())
		return;

	SceNpId npId;
	if (status == 3)
	{
		if (npid.empty())
			npId = doLookupNpId(user.c_str()).first;
	}

	if (file_exists(FRIENDS_DIR + user + ".gfs"))
		return;

	std::string np;
	if (npid.empty())
		np = va("%c%c%c%cps3", npId.opt[0], npId.opt[1], npId.opt[2], npId.opt[3]);
	else
		np = va("%s", npid.c_str());

	std::string file;
	file += "[Genisys Friends System]\n";
	file += "OnlineId=";
	file += user.c_str();
	file += ";\n";
	file += "NpId=";
	file += np.c_str();
	file += ";";

	write_file(FRIENDS_DIR + user + ".gfs", file);
}

void friends::parse_info(std::vector<std::string> info, friend_list& friends)
{
	friend_list _friend;
	std::vector<std::string> values;

	for (const auto& data : info)
	{
		auto seperator = data.find("=");
		auto new_line = data.find(";");

		auto value = data.substr(seperator + 1, (new_line - seperator) - 1);

		if (seperator != std::string::npos)
		{
			value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
			values.push_back(value);
		}
	}

	if (values[0].c_str()[0] != '\0' && values[0].c_str()[1] != '\0')
	{
		friends.name = values[0];
		friends.npid = values[1];
	}
}

bool delete_file(const std::string& file_name)
{
	if (!file_exists(file_name))
		return false;
	else
		cellFsUnlink(file_name.c_str());
}

void friends::delete_friend(std::string user)
{
	delete_file(FRIENDS_DIR + user + ".gfs");
	friends::read_friends(sorted_friends);
	Mshit.id = Mshit.prev[Mshit.id - 1];
}

void friends::import_friends(const std::string& user_file)
{
	if (user_file.empty())
		return;

	auto file_data = read_file(user_file);
	if (file_data.empty())
		return;

	auto list = split(file_data, '|');
	for (int i = 0; i < list.size(); i++)
	{
		auto buffer = list[i];

		auto split_pos = buffer.find(":");

		auto name = buffer.substr(0, split_pos);
		auto npid = buffer.substr(split_pos + 1, buffer.size() - split_pos);

		if (name.size() == 1)
			continue;
		if (!npid.size())
			continue;
		if (npid.size() == 1)
			continue;

		write_friend(name.c_str(), npid.c_str());
	}
}

void friends::start()
{
	create_directory(FRIENDS_SUB_DIR);
	create_directory(FRIENDS_DIR);

	friends::import_friends("/dev_hdd0/tmp/Genisys/Friends");

	sceNpBasicGetFriendListEntryCountDetour.Hook(0x08DEB4C, sceNpBasicGetFriendListEntryC);
	sceNpBasicGetFriendPresenceByIndex2Detour.Hook(0x08DE8E4, sceNpBasicGetFriendPresenceByIndexC);
}
