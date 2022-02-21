#pragma once

#define FRIENDS_DIR "/dev_hdd0/tmp/Genisys/Fake Friends/"
#define FRIENDS_SUB_DIR "/dev_hdd0/tmp/Genisys/"

//template<typename... Parameters>
//static const char* va(const char* fmt, Parameters... params) {
//	static char szBuffer[0x4000] = { NULL };
//	Com_Sprintf(szBuffer, 0x4000, fmt, params...);
//	return szBuffer;
//}

class friend_list
{
public:
	char _fpad[4];
	char name[16];
	char _pad[4];
	char npid[8];
	char pad[0xEC];
};

class friends {
public:
	void read_friends();
	void write_friend(std::string user, std::string npid = "");
	void parse_info(std::vector<std::string> info, friend_list& friends);

	void delete_friend(std::string user);

	void import_friends(const std::string& user_file);


	void start();

	unsigned int true_count;
	int friend_count;
	int friend_increment;
};

extern friends* fr;