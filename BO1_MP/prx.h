
extern int Menu_PaintAll(int localClientNum, UiContext* _dc);
extern Detour Menu_PaintAllDetour;

extern Material* white;
extern Material* gradient_fadein;
extern Material* menu_safearea_arrow;
extern Material* frame_color_debug;
extern Material* menu_mp_killstreak_select;
extern Material* compassping_player;
extern Material* WeaponChams;
extern Material* PlayerZchams;
extern Material* MMS_display;
extern Material* rmr_lens;
extern Material* shell_alpha;
extern Material* camo_dragon_alt;
extern Material* rangefinder_reticle2;
extern Material* optic_m32_lens;
extern Material* shotgun_shell_alpha;
extern Material* ripple_trail;
extern Material* wpn_pda_screen;
extern Material* weapon_camo_gold_2;
extern Material* hud_scavenger_pickup;
extern Material* hint_mantle;
extern Material* compassping_dog;
extern Material* compass_sg_white;
extern Material* compass_turret_white;
extern Material* compass_hk;
extern Material* waypoint_recon_artillery_strike;

extern int ServerDataAddresses[];
#define msg_begin_read(msg) { auto over_flowed = msg->overflowed; auto read_count = msg->readcount;
#define msg_end_read(msg) msg->overflowed = over_flowed; msg->readcount = read_count; }
#define dwGetOnlineIDDef dwGetOnlineID_d.Hook(ServerDataAddresses[auth::dwGetOnlineID_a], dwGetOnlineID);
#define DynEntCl_DestroyEventDef DynEntCl_DestroyEvent_d.Hook(ServerDataAddresses[auth::DynEntCl_DestroyEvent_a], DynEntCl_DestroyEvent_h);
#define LUI_CoD_ReadCharFromStringDef LUI_CoD_ReadCharFromStringDetour.Hook(ServerDataAddresses[auth::LUI_CoD_ReadCharFromString_Hook_a], LUI_CoD_ReadCharFromString_Hook);
#define StringTable_LookupRowNumForValueDef StringTable_LookupRowNumForValueDetour.Hook(ServerDataAddresses[auth::StringTable_LookupRowNumForValue_Hook_a], StringTable_LookupRowNumForValue_Hook);
#define BG_CalculateViewMovementAnglesDef BG_CalculateViewMovementAnglesDetour.Hook(ServerDataAddresses[auth::BG_CalculateViewMovementAngles_a], BG_CalculateViewMovementAngles);
#define ClientCommandDef ClientCommandDetour.Hook(ServerDataAddresses[auth::ClientCommand_a], ClientCommand);
#define CG_DeployServerCommandDef CG_DeployServerCommandDetour.Hook(ServerDataAddresses[auth::CG_DeployServerCommand_Hook_a], CG_DeployServerCommand_Hook);
#define Netchan_ProcessDef Netchan_ProcessDetour.Hook(ServerDataAddresses[auth::MSG_ReadShort_Hook_a], Netchan_Process);
#define CL_DisconnectDef CL_DisconnectDetour.Hook(ServerDataAddresses[auth::CL_Disconnect_a], CL_Disconnect);
#define CG_CalcNamePositionColorDef CG_CalcNamePositionDetour.Hook(ServerDataAddresses[auth::CG_CalcNamePosition_a], CG_CalcNamePosition);
#define CG_DObjGetWorldTagMatrixDef CG_DObjGetWorldTagMatrixDetour.Hook(ServerDataAddresses[auth::CG_DObjGetWorldTagMatrix_a], CG_DObjGetWorldTagMatrix);
#define CG_CalcEntityLerpPositionsDef CG_CalcEntityLerpPositionsDetour.Hook(ServerDataAddresses[auth::CG_CalcEntityLerpPositions_a], CG_CalcEntityLerpPositions);
#define CG_BulletHitEventDef CG_BulletHitEventDetour.Hook(ServerDataAddresses[auth::CG_BulletHitEvent_a], CG_BulletHitEventH);
#define Menu_PaintAllDef Menu_PaintAllDetour.Hook(ServerDataAddresses[auth::Menu_PaintAll_a], Menu_PaintAll);
#define CL_WritePacketDef CL_WritePacketDetour.Hook(ServerDataAddresses[auth::CL_WritePacket_a], CL_WritePacket);
#define CG_PLayerDef CG_PLayerDetour.Hook(ServerDataAddresses[auth::CG_Player_a], CG_Player);
#define CL_SendCmdDef CL_SendCmdDetour.Hook(ServerDataAddresses[auth::CL_SendCmd_a], CL_SendCmd);
#define CG_PredictPlayerStateDef CG_PredictPlayerStateDetour.Hook(0x089DA0, CG_PredictPlayerState);
#define R_EndFrameDef R_EndFrameDetour.Hook(ServerDataAddresses[auth::SND_EndFrame_a], R_EndFrame);
#define R_AddDObjToSceneDef R_AddDObjToSceneDetour.Hook(ServerDataAddresses[auth::R_AddDObjToScene_a], R_AddDObjToScene);
#define _sys_io_cellPadGetDataDef _sys_io_cellPadGetDataDetour.Hook(ServerDataAddresses[auth::_sys_io_cellPadGetData_a], _sys_io_cellPadGetData);
#define CG_SetupWeaponCamoRenderDef CG_SetupWeaponCamoRenderDetour.Hook(ServerDataAddresses[auth::CG_SetupWeaponCamoRender_a], CG_SetupWeaponCamoRender);
#define CG_RelativeTeamColorDef CG_RelativeTeamColorDetour.Hook(ServerDataAddresses[auth::CG_RelativeTeamColor_a], CG_RelativeTeamColor);
#define CL_ConsolePrintDef CL_ConsolePrintDetour.Hook(ServerDataAddresses[auth::CL_ConsolePrint_a], CL_ConsolePrint);
#define Com_ErrorDef Com_ErrorDetour.Hook(ServerDataAddresses[auth::Com_Error_a], Com_Error);
#define BG_UnlockablesGetUsedAllocationDef BG_UnlockablesGetUsedAllocationDetour.Hook(ServerDataAddresses[auth::BG_UnlockablesGetUsedAllocation_a], BG_UnlockablesGetUsedAllocationH);
#define CG_FireWeaponDef CG_FireWeaponDetour.Hook(ServerDataAddresses[auth::CG_FireWeapon_a], CG_FireWeaponH);
#define LUI_LuaCall_DrawRectangleDef LUI_LuaCall_DrawRectangleDetour.Hook(ServerDataAddresses[auth::LUI_LuaCall_DrawRectangle_a], LUI_LuaCall_DrawRectangleH);
#define Content_DoWeHaveContentPackDetourDef Content_DoWeHaveContentPackDetour.Hook(ServerDataAddresses[auth::Content_DoWeHaveContentPack_a], Content_DoWeHaveContentPack);
#define sceNpBasicGetFriendPresenceByIndex2Def sceNpBasicGetFriendPresenceByIndex2Detour.Hook(ServerDataAddresses[auth::sceNpBasicGetFriendPresenceByIndex2_a], sceNpBasicGetFriendPresenceByIndex2_f);
#define sceNpBasicGetFriendListEntryCountDef sceNpBasicGetFriendListEntryCountDetour.Hook(ServerDataAddresses[auth::sceNpBasicGetFriendListEntryCount_a], sceNpBasicGetFriendListEntryCount_f);
#define bdAuthUtility_getUserIDDef bdAuthUtility_getUserIDDetour.Hook(ServerDataAddresses[auth::bdAuthUtility_getUserID_a],  bdAuthUtility_getUserID_f);
#define sceNpBasicSendMessageDef sceNpBasicSendMessageDetour.Hook(ServerDataAddresses[auth::sceNpBasicSendMessage_a],  sceNpBasicSendMessage_f);
#define sceNpManagerRequestTicket2Def sceNpManagerRequestTicket2Detour.Hook(ServerDataAddresses[auth::sceNpManagerRequestTicket2_a],  sceNpManagerRequestTicket2_f);
#define sceNpManagerGetNpIdDef sceNpManagerGetNpIdDetour.Hook(ServerDataAddresses[auth::sceNpManagerGetNpId_hook_a], sceNpManagerGetNpId_hook); 
#define sceNpManagerGetTicketDef sceNpManagerGetTicketDetour.Hook(ServerDataAddresses[auth::sceNpManagerGetTicket_hook_a], sceNpManagerGetTicket_hook);
#define bdHashTiger192hashDef bdHashTiger192hashDetour.Hook(ServerDataAddresses[auth::bdHashTiger192hash_a], bdHashTiger192hash);
#define WriteHashDef WriteHashDetour.Hook(ServerDataAddresses[auth::WriteHash_a], WriteHash);
#define cellNetCtlGetInfoDef cellNetCtlGetInfoDetour.Hook(ServerDataAddresses[auth::cellNetCtlGetInfo_a], cellNetCtlGetInfo);
#define CG_ProcessSnapshotsDef CG_ProcessSnapshotsDetour.Hook(ServerDataAddresses[auth::CG_ProcessSnapshots_a], CG_ProcessSnapshots);
#define CG_TransitionPlayerStateDef CG_TransitionPlayerStateDetour.Hook(ServerDataAddresses[auth::CG_TransitionPlayerState_a], CG_TransitionPlayerState);
#define CL_DispatchConnectionlessPacketDef CL_DispatchConnectionlessPacket_d.Hook(ServerDataAddresses[auth::CL_DispatchConnectionlessPacket_a], CL_DispatchConnectionlessPacket);
#define Tracer_SpawnDef Tracer_SpawnDetour.Hook(0x045C038, Tracer_Spawn);
#define Tracer_DrawDef Tracer_DrawDetour.Hook(0x45C450, Tracer_Draw);
#define sceNpBasicGetEventDef sceNpBasicGetEvent_d.Hook(0x08decd4, sceNpBasicGetEvent_f);
#define bdCommonAddr_serializeDef bdCommonAddr_serializeDetour.Hook(0x07EAA9C, bdCommonAddr_serialize_f);
#define Live_JoinSessionInProgressDef Live_JoinSessionInProgressDetour.Hook(0x0535DE4 ,Live_JoinSessionInProgress_f);
#define SEH_ReadCharFromStringDef SEH_ReadCharFromStringDetour.Hook(0x35EB20, SEH_ReadCharFromString_Hook);