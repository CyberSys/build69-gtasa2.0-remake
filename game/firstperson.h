#pragma once
#include "font.h"
#include <string>

//
// Ported by Weikton 22.07.23
//

class CFirstPersonCamera
{	
	static bool m_bEnabled;
public:
	CFirstPersonCamera();
	~CFirstPersonCamera();

	void Render();
	static void ProcessCameraOnFoot(uintptr_t pCam, CPlayerPed* pPed);
	static void SetEnabled(bool bEnabled);
	static void Toggle();

	static bool IsEnabled();

private:
	RwTexture* p_CamToggleTexture = nullptr;
};