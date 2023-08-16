//
// Powered by tapy.me/weikton
//

#include "../main.h"
#include "../game/RW/RenderWare.h"
#include "../game/game.h"
#include "../game/util.h"
#include "../util/armhook.h"

#include "../net/netgame.h"
#include "../gui/gui.h"
#include "../chatwindow.h"

extern CNetGame *pNetGame;
extern CGUI *pGUI;
extern CChatWindow *pChatWindow;

//void InstallWeiktonHook();

// 0042A774
// Телепорт по метке на карте ( Teleport from map in menu )
//int (*CRadar__SetCoordBlip)(int r0, float X, float Y, float Z, int r4, int r5, char* name);
//int CRadar__SetCoordBlip_hook(int r0, float X, float Y, float Z, int r4, int r5, char* name)
//{
//	if(pNetGame && !strncmp(name, "CODEWAY", 7))
//	{
//		float findZ = (( float (*)(float, float))(g_GTASAAdr + 0x42A774 + 1))(X, Y); // 2.01
//		findZ += 1.5f;
//
//		FLog("OnPlayerClickMap: %f, %f, %f", X, Y, Z);
//		RakNet::BitStream bsSend;
//
//		bsSend.Write(X);
//		bsSend.Write(Y);
//		bsSend.Write(findZ);
//
//		pNetGame->GetRakClient()->RPC(&RPC_MapMarker, &bsSend, HIGH_PRIORITY, RELIABLE, 0, false, UNASSIGNED_NETWORK_ID, nullptr);
//	}
//	return CRadar__SetCoordBlip(r0, X, Y, Z, r4, r5, name);
//}

// Включение паузы (отслеживание)
// 0096B514
void (*CTimer__StartUserPause)();
void CTimer__StartUserPause_hook()
{
//                process pause event
//	if (g_pJavaWrapper)
//	{
//		if (pKeyBoard)
//		{
//			if (pKeyBoard->IsNewKeyboard())
//				pKeyBoard->Close();
//		}
//	}

// 1.08	*(uint8_t*)(g_GTASAAdr + 0x8C9BA3) = 1;
	*(uint8_t*)(g_GTASAAdr + 0x96B514) = 1;
}

void (*CTimer__EndUserPause)();
void CTimer__EndUserPause_hook()
{
//                process resume event
//	if (g_pJavaWrapper)
//	{
//
//	}

// 1.08	*(uint8_t*)(g_GTASAAdr + 0x8C9BA3) = 0;
	*(uint8_t*)(g_GTASAAdr + 0x96B514) = 1;
}

void InstallWeiktonHook()
{
//                tapy.me/weikton
//                SetupGameHook = SetUpHook
//                  SetupGameHook(g_GTASAAdr + 0x442720, (uintptr_t)CRadar__SetCoordBlip_hook, (uintptr_t*)&CRadar__SetCoordBlip); //00442720
//	SetupGameHook(g_GTASAAdr + 0x4210C8, (uintptr_t)CTimer__StartUserPause_hook, (uintptr_t*)&CTimer__StartUserPause); //004210C8
//	SetupGameHook(g_GTASAAdr + 0x4210D8, (uintptr_t)CTimer__EndUserPause_hook, (uintptr_t*)&CTimer__EndUserPause); //004210D8
}