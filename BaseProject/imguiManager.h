#pragma once

class  ImguiManager
{
private:
	static char m_Buffer[1024];
public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();
};