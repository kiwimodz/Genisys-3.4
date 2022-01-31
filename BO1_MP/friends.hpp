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
	std::string name;
	std::string npid;
};

class friends
{
public:
	static void read_friends(std::vector<friend_list>& list);
	static void write_friend(std::string user, std::string npid = "");
	static void parse_info(std::vector<std::string> info, friend_list& friends);

	static void delete_friend(std::string user);

	static void import_friends(const std::string& user_file);


	static void start();

	static std::vector<friend_list> sorted_friends;
	static int friend_count;
	static int friend_increment;
};