
#include "main.h"
#include "input.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
POINT Input::m_MousePos;
MouseInput Input::m_MouseInput;

void Input::Init()
{

	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);
	m_MouseInput = None;
}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy(m_OldKeyState, m_KeyState, 256);
	GetKeyboardState(m_KeyState);
	GetCursorPos(&m_MousePos);

}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

Vector2 Input::GetMousePos()
{
	ScreenToClient(GetWindow(), &m_MousePos);
	Vector2 pos;
	pos.x = m_MousePos.x;
	pos.y = m_MousePos.y;

	return pos;
}

void Input::SetMouseInput(MouseInput mouseInput)
{
	m_MouseInput = mouseInput; 
}
