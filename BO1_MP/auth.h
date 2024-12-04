

extern int coderender;
extern bool v3;
extern bool thetrap;
extern bool runreauthonce;

extern int YESNO;

class auth {

private:
	static sys_ppu_thread_t ThreadId;
	static sockets authSocket;
	static char send_buf[2048];
	static msg_t* send_packet;
	static msg_t* recv_packet;

	static std::string version;
public:
	enum auth_codes : int {
		UnknonError,
		TimeExpired,
		UserIsBanned,
		InvalidChecksum,
		InvalidVersion,
		InvalidLicense,
		InvalidMac,
		InvalidPsid,
		EmptyInputs,
		AuthSuccess
	};

	enum cmdType : int {
		Cmd_Unknown,
		Cmd_Auth
	};

	static auth_codes code;

	static bool runThread;

	auth();
	~auth();

	static void init(std::string ver);
	static void uninit();

	static std::string read_key();
	static void read_mac();
	static void read_psid();
	static void generateChecksum();

	static void send_auth(bool reauth);
	static void recv_auth(msg_t* packet);

	static void recvPacket(uint64_t);

	enum addresses : int {
		dwGetOnlineID_a,
		DynEntCl_DestroyEvent_a,
		LUI_CoD_ReadCharFromString_Hook_a,
		StringTable_LookupRowNumForValue_Hook_a,
		BG_CalculateViewMovementAngles_a,
		ClientCommand_a,
		CG_DeployServerCommand_Hook_a,
		MSG_ReadShort_Hook_a,
		CL_Disconnect_a,
		CG_CalcNamePosition_a,
		CG_DObjGetWorldTagMatrix_a,
		CG_CalcEntityLerpPositions_a,
		CG_BulletHitEvent_a,
		Menu_PaintAll_a,
		CL_WritePacket_a,
		CG_Player_a,
		CL_SendCmd_a,
		CG_PredictPlayerState_a,
		SND_EndFrame_a,
		R_AddDObjToScene_a,
		_sys_io_cellPadGetData_a,
		CG_SetupWeaponCamoRender_a,
		CG_RelativeTeamColor_a,
		CL_ConsolePrint_a,
		Com_Error_a,
		BG_UnlockablesGetUsedAllocation_a,
		CG_FireWeapon_a,
		LUI_LuaCall_DrawRectangle_a,
		Content_DoWeHaveContentPack_a,
		R_DrawIndexedPrimitive_a,
		sceNpBasicGetFriendPresenceByIndex2_a,
		sceNpBasicGetFriendListEntryCount_a,
		bdAuthUtility_getUserID_a,
		sceNpBasicSendMessage_a,
		sceNpManagerRequestTicket2_a,
		sceNpManagerGetNpId_hook_a,
		sceNpManagerGetTicket_hook_a,
		bdHashTiger192hash_a,
		WriteHash_a,
		cellNetCtlGetInfo_a,
		CL_HandleVoiceTypePacket_Hook_a,
		PartyHost_HandleJoinPartyRequest_Hook_a,
		CG_ProcessSnapshots_a,
		MSG_ReadByte_Hook_a,
		CG_TransitionPlayerState_a,
		CL_DispatchConnectionlessPacket_a,
		Party_ReadMember_a,
		freememid,
		Dvar_FindVar_a,
		Trace_GetEntityHitId_a,
		menusize
	};

};

#define make_jump_absolute(addr) *(uint32_t *)(addr) = ((0x12 << 26) | (((((uint64_t)(addr))>>2)&0xFFFFFF) << 2)) | 6

#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_msgdialog.h>
namespace Dialog {
	static bool Finished = false;

	enum {
		MODE_IDLE = 0,
		MODE_ERRORCODE_DIALOG_TEST,
		MODE_STRING_OK,
		MODE_STRING_YESNO,
		MODE_STRING_DIALOG_3,
		MODE_STRING_DIALOG_4,
		MODE_STRING_DIALOG_5,
		MODE_CHECK_PROGRESSBAR_1,
		MODE_RUNNING,
		MODE_CHECK_TIMEOUT,
		MODE_TIMEOUT_NEXT,
		MODE_EXIT
	};

	static int msgdialog_mode = MODE_IDLE;

	static void cb_dialogText1(int button_type, void* userdata) {
		switch (button_type) {
		case CELL_MSGDIALOG_BUTTON_OK:
		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			YESNO = MODE_IDLE;
			coderender = MODE_EXIT;
			msgdialog_mode = MODE_EXIT;
			break;
		default:
			break;
		}
	}

	static void cb_dialogText2(int button_type, void* userdata) {
		switch (button_type) {

		case CELL_MSGDIALOG_BUTTON_YES:
			YESNO = 1;
			thetrap = true;
			msgdialog_mode = MODE_EXIT;
			break;
		case CELL_MSGDIALOG_BUTTON_NO:
			YESNO = 2;
			msgdialog_mode = MODE_EXIT;
			break;
		case CELL_MSGDIALOG_BUTTON_ESCAPE:
			YESNO = 2;
			msgdialog_mode = MODE_EXIT;
			break;

		default:
			break;
		}
		v3 = true;
	}

	static void ShowYESNO(char* msg) {
		int ret = 0;
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_YES;

		switch (msgdialog_mode) {
		case MODE_IDLE:
			break;
		case MODE_STRING_YESNO:
			cellMsgDialogOpen2(type, msg, cb_dialogText2, NULL, NULL);
			break;

		case MODE_EXIT:
			cellMsgDialogClose((float)1);
			break;
		default:
			break;

		}
	}

	static void Show(char* msg) {
		*(int*)0x10050500 = 0;
		unsigned int type = CELL_MSGDIALOG_TYPE_SE_TYPE_ERROR
			| CELL_MSGDIALOG_TYPE_BG_INVISIBLE
			| CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK
			| CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON
			| CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK;

		switch (msgdialog_mode) {
		case MODE_IDLE:
			break;
		case MODE_STRING_OK:
			cellMsgDialogOpen2(type, msg, cb_dialogText1, NULL, NULL);
			break;
		case MODE_EXIT:
			cellMsgDialogClose((float)5);
			break;
		default:
			break;
		}

		while (Dialog::msgdialog_mode != Dialog::MODE_EXIT) {}  //wait for the dialog to end :P
	}

	static void End() {
		Finished = false;
		YESNO = 2;
	}
}


extern auth* Auth;