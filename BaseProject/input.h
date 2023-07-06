#pragma once
enum MouseInput
{
	None,
	LButtonDown,
	MButtonDown,
	RButtonDown,
	LButtonUp,
	MButtonUp,
	RButtonUp,
};


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_MousePos;
	static MouseInput m_MouseInput;
public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress(BYTE KeyCode);
	static bool GetKeyTrigger(BYTE KeyCode);
	static Vector2 GetMousePos();
	static void SetMouseInput(MouseInput mouseInput);

};