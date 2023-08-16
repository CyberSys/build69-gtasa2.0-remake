//
// Powered by tapy.me/weikton
//
 
#include "main.h"
#include "game/game.h"
#include "gui/gui.h"
#include "debug.h"
#include "util/armhook.h"

extern CGame *pGame;
extern CGUI *pGUI;

CDebug::CDebug()
{
	m_dwLastTick = GetTickCount();
}

CDebug::~CDebug()
{

}

uintptr_t (*TextureDatabaseRuntime_GetDatabase)(char *dbname);
uintptr_t TextureDatabaseRuntime_GetDatabase_hook(char *dbname)
{
	FLog("TextureDatabaseRuntime_GetDatabase: %s", dbname);
	return TextureDatabaseRuntime_GetDatabase(dbname);
}

void CDebug::AddMessage(char* msg)
{
	std::string str(msg);
	m_Messages.push_back(str);
}

void CDebug::Render()
{
	ImGui::Begin("Debug",  nullptr, ImGuiWindowFlags_NoSavedSettings);
	for(auto str : m_Messages)
	{
		ImGui::Text("%s", str.c_str());
	}

	ImGui::SetScrollHereY();

	ImGui::End();
}

void CDebug::Process()
{

}

void CDebug::SpawnLocalPlayer()
{
	FLog("CDebug: SpawnLocalPlayer");
	CCamera *pGameCamera = pGame->GetCamera();
	pGameCamera->Restore();
	pGameCamera->SetBehindPlayer();

	pGame->SetWorldTime(12, 0);
}

void CDebug::RenderWare()
{
	char szStr[256];
	char szStrPr[256];
	char szStrMem[256];
	char szStrPos[256];
	char szStrFPS[256];
	ImVec2 pos;
	ImVec2 pos2;
	                  uint32_t msUsed = *(uint32_t*)(g_GTASAAdr + 0x00792B74); // 00792B74 _ZN10CStreaming13ms_memoryUsedE
	                  uint32_t msAvailable = *(uint32_t*)(g_GTASAAdr + 0x00685FA0); // 00685FA0 _ZN10CStreaming18ms_memoryAvailableE
		float percentUsed = ((float)msUsed/(float)msAvailable)*100;
		snprintf(&szStrMem[0], 256, "Memory: %.1f/%.1f (%.1f %%)",
				 (float)msUsed/ (1024*1024),
				 (float)msAvailable / (1024*1024),
				 percentUsed
				 );
		pos = ImVec2(pGUI->ScaleX(40.0f), pGUI->ScaleY(1080.0f - pGUI->GetFontSize() * 10));

		pGUI->RenderText(pos, (ImU32)0xFFFFFFFF, true, &szStrMem[0]);

		if (pGame->FindPlayerPed()->m_pPed)
		{
                                                      MATRIX4X4 matFromPlayer;
                                                      CPlayerPed *pLocalPlayerPed = pGame->FindPlayerPed();
                                                      pLocalPlayerPed->GetMatrix(&matFromPlayer);

			snprintf(&szStrPos[0], 256, "Position: %.4f, %.4f, %.4f", matFromPlayer.pos.X, matFromPlayer.pos.Y, matFromPlayer.pos.Z);
			pos = ImVec2(pGUI->ScaleX(40.0f), pGUI->ScaleY(1080.0f - pGUI->GetFontSize() * 8));
			pGUI->RenderText(pos, (ImU32)0xFFFFFFFF, true, &szStrPos[0]);

	                                    //snprintf(&szStr[0], 256, "Streamed Peds: %d, Streamed Vehicles: %d", uiStreamedPeds, uiStreamedVehicles);
		                  //pos = ImVec2(pGUI->ScaleX(40.0f), pGUI->ScaleY(1080.0f - pGUI->GetFontSize() * 12));
	                                    //pGUI->RenderText(pos, (ImU32)0xFFFFFFFF, true, &szStr[0]);

	                                    snprintf(&szStrPr[0], 256, "tapy.me/weikton");
		                  pos = ImVec2(pGUI->ScaleX(40.0f), pGUI->ScaleY(1080.0f - pGUI->GetFontSize() * 6));
	                                    pGUI->RenderText(pos, (ImU32)0xFF00FFFF, true, &szStrPr[0]);

		                  //float* pFPS = (float*)(g_GTASAAdr + 0x6AABB0);
		                  snprintf(&szStrFPS[0], 256, "GTA: 2.01 | CLIENT: 3.02 (RELEASE)");
		                  pos2 = ImVec2(pGUI->ScaleX(40.0f), pGUI->ScaleY(1080.0f - pGUI->GetFontSize() * 4));
	                                    pGUI->RenderText(pos2, (ImU32)0xFFFFFFFF, true, &szStrFPS[0]);
		}
}