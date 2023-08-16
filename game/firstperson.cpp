//
// Ported by Weikton 22.07.23
//

#include "../main.h"
#include "game.h"
#include "firstperson.h"

#include "RW/RenderWare.h"
#include "..//gui/gui.h"
#include "..//vendor/imgui/imgui.h"

#include "..//chatwindow.h"
#include "..//keyboard.h"
#include "..//dialog.h"
#include "..//net/netgame.h"

extern CNetGame* pNetGame;
extern CGame *pGame;
extern CGUI *pGUI;
extern CKeyBoard *pKeyBoard;
extern CDialogWindow *pDialogWindow;

bool CFirstPersonCamera::m_bEnabled = false;
CFirstPersonCamera::CFirstPersonCamera()
{
	p_CamToggleTexture = (RwTexture*)LoadTextureFromDB("mobile", "cam-toggle");
}

CFirstPersonCamera::~CFirstPersonCamera()
{

}

extern CChatWindow* pChatWindow;
MATRIX4X4* RwMatrixMultiplyByVector(VECTOR* out, MATRIX4X4* a2, VECTOR* in);
void CFirstPersonCamera::ProcessCameraOnFoot(uintptr_t pCam, CPlayerPed* pPed)
{
                  // CRunningScript::ProcessCommands2300To2399 0x952C1E
                  // CRunningScript::ProcessCommands2300To2399 0x952C1F
	if (!m_bEnabled || *(uint8_t*)(g_GTASAAdr + 0x952C1E) || *(uint8_t*)(g_GTASAAdr + 0x952C1F))
	{
		return;
	}

	VECTOR* pVec = (VECTOR*)(pCam + 372);

	VECTOR vecOffset;
	vecOffset.X = 0.35f;
	vecOffset.Y = 0.1f;
	vecOffset.Z = 0.1f;
	
	VECTOR vecOut;
	//RwMatrixMultiplyByVector(&vecOut, &(pPed->m_HeadBoneMatrix), &vecOffset);

	if (vecOut.X != vecOut.X || vecOut.Y != vecOut.Y || vecOut.Z != vecOut.Z)
	{
		pPed->GetBonePosition(4, &vecOut);
	}
	if (vecOut.X != vecOut.X || vecOut.Y != vecOut.Y || vecOut.Z != vecOut.Z)
	{
		return;
	}

	pVec->X = vecOut.X;
	pVec->Y = vecOut.Y;
	pVec->Z = vecOut.Z;

                  // RwCameraSetNearClipPlane(RwCamera *,float)
                  // CCam::Process_FollowPedWithMouse(CVector const&,float,float,float)
	((RwCamera*(*)(RwCamera*, float))(g_GTASAAdr + 0x001D5AB8 + 1))(*(RwCamera**)(g_GTASAAdr + 0x9FC93C), 0.2f);
}

VECTOR vecAtSaved;
VECTOR vecUpSaved;
bool bsaved = false;

void CFirstPersonCamera::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

void CFirstPersonCamera::Render()
{
    CPlayerPed *pPlayerPed = pGame->FindPlayerPed();
    
    if(pNetGame->GetGameState() != GAMESTATE_CONNECTED) return;
    if(pDialogWindow->m_bIsActive || pKeyBoard->IsOpen()) return;
    
    ImGuiIO &io = ImGui::GetIO();
    
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0x00, 0x00, 0x00, 0x00).Value);
	
    ImGuiStyle style;
    style.FrameBorderSize = ImGui::GetStyle().FrameBorderSize;
    ImGui::GetStyle().FrameBorderSize = 0.0f;
    
    ImGui::Begin("Cam-Toggle", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
    
    ImVec2 vecButSize_c = ImVec2(ImGui::GetFontSize() * 3+5.0f, ImGui::GetFontSize() * 3);
    
    if(ImGui::ImageButton((ImTextureID)p_CamToggleTexture->raster, vecButSize_c))
    {
	if(!m_bEnabled) SetEnabled(true);
	else SetEnabled(false);
    }
    
    ImGui::SetWindowSize(ImVec2(-1, -1));

    ImVec2 dSize    = io.DisplaySize;
    ImVec2 winPos   = ImVec2(dSize.x - (dSize.x / 9), dSize.y / 5);

    ImGui::SetWindowPos(winPos);
    ImGui::End();
    
    ImGui::PopStyleColor(3);
    ImGui::GetStyle().FrameBorderSize = style.FrameBorderSize;
}

void CFirstPersonCamera::Toggle()
{
	m_bEnabled ^= 1;
}

bool CFirstPersonCamera::IsEnabled()
{
	return m_bEnabled;
}