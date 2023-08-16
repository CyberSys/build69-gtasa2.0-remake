//
// Powered by tapy.me/weikton
//
 
#pragma once

class CDebug
{
public:
	CDebug();
	~CDebug();

	void Render();
	void Process();

	void AddMessage(char* msg);
	void SpawnLocalPlayer();
                  void RenderWare();

private:
	uint32_t m_dwLastTick;
	std::vector<std::string> m_Messages;
};