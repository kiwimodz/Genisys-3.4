#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <sstream>
#include <np.h>
#include <cctype>
#include <devstation/System.h>
#include <devstation/Math.h>
#include <Vector.h>
#include <Detour.h>
#pragma comment(lib, "net_stub")
#pragma comment(lib, "netctl_stub")

#include <sys/socket.h>
#include <netdb.h>
#include <CellPad.h>
#include <cell/sysmodule.h>
#include <pthread.h>
#include <Structures.h>
#include <Msg.h>
#include <aimassist_mp.h>
#include <cheats_mp.h>
#include <Functions.h>
#include <ini.h>
#include <console.h>
#include <menu.h>
#include <visuals_mp.h>
#include <NpId.h>
#include <trampoline.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sockets.h"
#include <prx.h>
#include "auth.h"

#define TOC 0x0D67E98