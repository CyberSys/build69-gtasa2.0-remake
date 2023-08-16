//
// Powered by tapy.me/weikton
//

#include "main.h"
#include "gui.h"
#include "game/game.h"
#include "net/netgame.h"
#include "game/RW/RenderWare.h"
#include "chatwindow.h"
#include "spawnscreen.h"
#include "playertags.h"
#include "dialog.h"
#include "keyboard.h"
#include "debug.h"
#include "settings.h"

extern CChatWindow *pChatWindow;
extern CSpawnScreen *pSpawnScreen;
extern CPlayerTags *pPlayerTags;
extern CDialogWindow *pDialogWindow;
extern CDebug *pDebug;
extern CSettings *pSettings;
extern CKeyBoard *pKeyBoard;
extern CNetGame *pNetGame;
extern CGame *pGame;

void ImGui_ImplRenderWare_RenderDrawData(ImDrawData* draw_data);
bool ImGui_ImplRenderWare_Init();
void ImGui_ImplRenderWare_NewFrame();
void ImGui_ImplRenderWare_ShutDown();

#define MULT_X	0.00052083333f	// 1/1920
#define MULT_Y	0.00092592592f 	// 1/1080

CGUI::CGUI()
{
	FLog("Initializing GUI..");

	// setup ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	ImGui_ImplRenderWare_Init();

	// scale
	m_vecScale.x = io.DisplaySize.x * MULT_X;
	m_vecScale.y = io.DisplaySize.y * MULT_Y;

	// font Size
	m_fFontSize = ScaleY( 30.0f );

	// mouse/touch
	m_bMousePressed = false;
	m_vecMousePos = ImVec2(0, 0);

	FLog("GUI | Scale factor: %f, %f Font size: %f", m_vecScale.x, m_vecScale.y, m_fFontSize);

	// setup style
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScrollbarSize = ScaleY(55.0f);
	style.WindowBorderSize = 0.0f;
	ImGui::StyleColorsDark();

	// load fonts
	char path[0xFF] = { 0 };
	sprintf(path, "%sSAMP/fonts/arial_bold.ttf", (const char*)(g_GTASAAdr+0x6D687C));

	// cp1251 ranges
	static const ImWchar ranges[] = 
	{
		0x0020, 0x0080,
		0x00A0, 0x00C0,
		0x0400, 0x0460,
		0x0490, 0x04A0,
		0x2010, 0x2040,
		0x20A0, 0x20B0,
		0x2110, 0x2130,
		0
	};
	
	FLog("GUI | Loading font: arial_bold.ttf");
	m_pFont = io.Fonts->AddFontFromFileTTF(path, m_fFontSize, nullptr, ranges);
	//FLog("GUI | ImFont pointer = 0x%X", m_pFont);
}

/*
                                    ImGui::Begin("###logo", nullptr,
					 ImGuiWindowFlags_NoTitleBar |
					 ImGuiWindowFlags_NoMove |
					 ImGuiWindowFlags_NoResize |
					 ImGuiWindowFlags_NoScrollbar |
					 ImGuiWindowFlags_NoSavedSettings);

		ImGui::Image((ImTextureID)texture, ImVec2(128,128));

		ImGui::SetWindowPos(ImVec2(1400, 540));
		ImGui::End();
*/

CGUI::~CGUI()
{
	ImGui_ImplRenderWare_ShutDown();
	ImGui::DestroyContext();
}

void CGUI::PresetsApply()
{
                  FLog("Calling CGUI::PresetsApply..");
                  FLog("Calling was terminated, by reason: status off");
}

void CGUI::Render()
{
	if(pGame)
	{
		if(pGame->IsGameLoaded())
		{
			if(pGame->IsGamePaused())
			{
				return;
			}
		}
	}

	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplRenderWare_NewFrame();
	ImGui::NewFrame();
	PresetsApply();

	if(pPlayerTags) pPlayerTags->Render();
	if(pChatWindow) pChatWindow->Render();
	if(pSpawnScreen) pSpawnScreen->Render();
	if(pDialogWindow) pDialogWindow->Render();
	if(pKeyBoard) pKeyBoard->Render();
                  if(pNetGame && !pDialogWindow->m_bIsActive) pDebug->RenderWare();

	if(pNetGame && !pDialogWindow->m_bIsActive) {
		ImVec2 vecButSize = ImVec2(ImGui::GetFontSize() * 3.8, ImGui::GetFontSize() * 2.5);

		ImGui::SetNextWindowPos(ImVec2(2.0f, (io.DisplaySize.y / 3) - (vecButSize.x / 2) + io.DisplaySize.y / 30));
		//ImGui::SetNextWindowBgAlpha(0.3f);
		ImGui::Begin("###keys", nullptr,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings |
			//ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_AlwaysAutoResize);

		// проеряем нажатие toggle-кнопки, меняем её текст
		if (ImGui::Button(m_bKeysStatus ? "<<" : ">>", vecButSize))
		{
			// меняем состояние кнопки
			m_bKeysStatus = !m_bKeysStatus;
		}
		ImGui::SameLine();

		// если нажали на Alt
		if (ImGui::Button("Alt", vecButSize))
		{
			//pNetGame->GetPlayerPool()->GetLocalPlayer()->GetPlayerPed()->
			LocalPlayerKeys.bKeys[ePadKeys::KEY_WALK] = true;
		}
                                    ImGui::SameLine();

		if(pNetGame)
		{
			CVehiclePool *pVehiclePool = pNetGame->GetVehiclePool();
			if(pVehiclePool)
			{
				VEHICLEID ClosetVehicleID = pVehiclePool->FindNearestToLocalPlayerPed();
				if(ClosetVehicleID < MAX_VEHICLES && pVehiclePool->GetSlotState(ClosetVehicleID))
				{
					CVehicle* pVehicle = pVehiclePool->GetAt(ClosetVehicleID);
					if(pVehicle)
					{
						if(pVehicle->GetDistanceFromLocalPlayerPed() < 4.0f)
						{
							if (ImGui::Button("G", vecButSize))
							{
								CPlayerPool *pPlayerPool;
								CLocalPlayer *pLocalPlayer;

								if(pNetGame)
								{
									pPlayerPool = pNetGame->GetPlayerPool();
									if(pPlayerPool)
									{
										pLocalPlayer = pPlayerPool->GetLocalPlayer();
										if(pLocalPlayer)
										{
											pLocalPlayer->HandlePassengerEntry();
										}
									}
								}
							}
							ImGui::SameLine();
						}
					}
				}
			}
		}

		// если кнопку переключили в раскрытое состояние, рендерим остальные кнопки
		if(m_bKeysStatus) {
		ImGui::SameLine();
		if (ImGui::Button("H", vecButSize)) LocalPlayerKeys.bKeys[ePadKeys::KEY_CTRL_BACK] = true;
		ImGui::SameLine();
		if (ImGui::Button("Y", vecButSize)) LocalPlayerKeys.bKeys[ePadKeys::KEY_YES] = true;
		ImGui::SameLine();
		if (ImGui::Button("N", vecButSize)) LocalPlayerKeys.bKeys[ePadKeys::KEY_NO] = true;
		}

		ImGui::End();
	}


	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplRenderWare_RenderDrawData(ImGui::GetDrawData());

	if(m_bNeedClearMousePos)
	{
		io.MousePos = ImVec2(-1, -1);
		m_bNeedClearMousePos = false;
	}
}

bool CGUI::OnTouchEvent(int type, bool multi, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();

	if(pGame)
	{
		if(pGame->IsGameLoaded())
		{
			if(pGame->IsGamePaused())
			{
				return true;
			}
		}
	}

	if(pKeyBoard)
	{
		if(!pKeyBoard->OnTouchEvent(type, multi, x, y)) 
		{
			return false;
		}
	}

	if(pChatWindow)
	{
		if(!pChatWindow->OnTouchEvent(type, multi, x, y)) {
			return false;
		}
	}

	switch(type)
	{
		case TOUCH_PUSH:
		io.MousePos = ImVec2(x, y);
		io.MouseDown[0] = true;
		break;

		case TOUCH_POP:
		io.MouseDown[0] = false;
		m_bNeedClearMousePos = true;
		break;

		case TOUCH_MOVE:
		io.MousePos = ImVec2(x, y);
		break;
	}

	return true;
}

void CGUI::RenderVersion()
{
	//ImVec2 _ImVec2 = ImVec2(ScaleX(10), ScaleY(5));
	//RenderText(_ImVec2, ImColor(255, 255, 255, 255), false, "", nullptr);
}

void CGUI::RenderRakNetStatistics()
{
	// nothing
}

void CGUI::RenderText(ImVec2& posCur, ImU32 col, bool bOutline, const char* text_begin, const char* text_end)
{
	int iOffset = 2.0f;

	if(bOutline)
	{
		posCur.x -= iOffset;
		ImGui::GetOverlayDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x += iOffset;
		// right 
		posCur.x += iOffset;
		ImGui::GetOverlayDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x -= iOffset;
		// above
		posCur.y -= iOffset;
		ImGui::GetOverlayDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y += iOffset;
		// below
		posCur.y += iOffset;
		ImGui::GetOverlayDrawList()->AddText(posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y -= iOffset;
	}

	ImGui::GetOverlayDrawList()->AddText(posCur, col, text_begin, text_end);
}

void CGUI::RenderBGText(float fontSize, ImVec2& posCur, ImU32 col, bool bOutline, const char* text_begin, const char* text_end)
{
	int iOffset = 2;

	if(bOutline)
	{
		posCur.x -= iOffset;
		ImGui::GetBackgroundDrawList()->AddText(GetFont(), fontSize, posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x += iOffset;
		// right 
		posCur.x += iOffset;
		ImGui::GetBackgroundDrawList()->AddText(GetFont(), fontSize, posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.x -= iOffset;
		// above
		posCur.y -= iOffset;
		ImGui::GetBackgroundDrawList()->AddText(GetFont(), fontSize, posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y += iOffset;
		// below
		posCur.y += iOffset;
		ImGui::GetBackgroundDrawList()->AddText(GetFont(), fontSize, posCur, ImColor(IM_COL32_BLACK), text_begin, text_end);
		posCur.y -= iOffset;
	}

	ImGui::GetBackgroundDrawList()->AddText(GetFont(), fontSize, posCur, col, text_begin, text_end);
}