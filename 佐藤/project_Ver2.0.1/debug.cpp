
#include"main.h"
#include"input.h"
#include "debug.h"

#include<fstream>

int Debug::m_IntAdd = 1;
float Debug::m_FloatAdd = 1.0f;
float Debug::m_SetFloat = 0.01f;
bool Debug::m_RightFlag = false;
bool Debug::m_LeftFlag = false;
unordered_map<string, HoldData> Debug::m_DebugData;

void Debug::Update()
{

#if _DEBUG

	if (Input::GetKeyPress(VK_RIGHT)) {
		m_RightFlag = true;
		m_FloatAdd += m_SetFloat;
	}
	else {
		if (m_RightFlag) {
			m_RightFlag = false;
			cdbg << m_FloatAdd << endl;
		}
	}

	if (Input::GetKeyPress(VK_LEFT)) {
		m_LeftFlag = true;
		m_FloatAdd -= m_SetFloat;
	}
	else {
		if (m_LeftFlag) {
			m_LeftFlag = false;
			cdbg << m_FloatAdd << endl;
		}
	}

#endif // _DEBUG

}

void Debug::Uninit()
{

#if _DEBUG

	if (m_DebugData.size() == 0)return;

	fstream file;
	file.open("asset\\debug.txt", ios::out);

	for (auto& hold : m_DebugData) {

		DebugData data{};

		data.newline1 = '\n';
		data.newline2 = '\n';
		data.newline3 = '\n';
		data.newline4 = '\n';
		data.newline5 = '\n';

		{
			auto size = hold.second.tag.size();
			if (size < 30) {
				char_traits<char>::copy(data.tag, hold.second.tag.c_str(), size + 1);
			}
		}
		{
			auto size = hold.second.function.size();
			if (size < 100) {
				char_traits<char>::copy(data.function, hold.second.function.c_str(), size + 1);
			}
		}
		{
			auto size = hold.second.variable.size();
			if (size < 256) {
				char_traits<char>::copy(data.variable, hold.second.variable.c_str(), size + 1);
			}
		}
		{
			snprintf(data.data, sizeof(data.data), "%f", hold.second.data);
		}

		file.write((char*)&data, sizeof(DebugData));

		//cdbg << "tag:" << data.tag << " function:" << data.function << " data:" << data.data << endl;

	}

	file.close();

	m_DebugData.clear();

#endif // _DEBUG

}

void Debug::Position(Vector3 pos)
{
	cdbg << "Pos：x " << pos.x << " y " << pos.y << " z " << pos.z << endl;
}

void Debug::Rotation(Vector3 rot)
{
	cdbg << "Rot：x " << rot.x << " y " << rot.y << " z " << rot.z << endl;
}

void Debug::Scale(Vector3 scale)
{
	cdbg << "Scale：x " << scale.x << " y " << scale.y << " z " << scale.z << endl;
}

void Debug::MothodName(const char name[], string tag)
{
	cdbg << "タグ：" << tag << " 関数名：" << name << endl;
}

void Debug::DestroyAlert(string tag)
{
	cdbg << tag << "：消去" << endl;
}

void Debug::Adjustment(float* target)
{
	if (Input::GetKeyPress(VK_UP)) {
		*target += m_FloatAdd;
	}
	if (Input::GetKeyPress(VK_DOWN)) {
		*target -= m_FloatAdd;
	}

	/*if (Input::GetKeyPress(VK_RIGHT)) {
		m_FloatAdd += 0.1f;
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		m_FloatAdd -= 0.1f;
	}*/

	cdbg << "float:" << *target << endl;
}

void Debug::Adjustment(int* target)
{
	if (Input::GetKeyPress(VK_UP)) {
		*target += m_IntAdd;
	}
	if (Input::GetKeyPress(VK_DOWN)) {
		*target -= m_IntAdd;
	}

	if (Input::GetKeyPress(VK_RIGHT)) {
		m_IntAdd += 1;
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		m_IntAdd -= 1;
	}

	cdbg << "int:" << *target << endl;
}

void Debug::Adjustment(float* target, const char function[], string tag, string variable)
{
	if (Input::GetKeyPress(VK_UP)) {
		*target += m_FloatAdd;
	}
	if (Input::GetKeyPress(VK_DOWN)) {
		*target -= m_FloatAdd;
	}

	bool flag = false;

	for (auto& hold : m_DebugData) {

		if (hold.second.tag == tag &&
			hold.second.function == (char*)function) {
			hold.second.data = *target;
			flag = true;

			/*cdbg << "tag:" << hold.second.tag <<
				" function:" << hold.second.function <<
				" variable:" << hold.second.variable <<
				" data:" << hold.second.data << endl;*/

			break;
		}

	}

	if (!flag) {
		m_DebugData[tag] = { tag,(char*)function,variable, *target };
		
		/*cdbg << "tag:" << m_DebugData[tag].tag <<
			" function:" << m_DebugData[tag].function <<
			" variable:"<< m_DebugData[tag].variable <<
			" data:" << m_DebugData[tag].data << endl;*/
	}

}

void Debug::Adjustment(int* target, const char function[], string tag, string variable)
{
	if (Input::GetKeyPress(VK_UP)) {
		*target += m_IntAdd;
	}
	if (Input::GetKeyPress(VK_DOWN)) {
		*target -= m_IntAdd;
	}

	if (Input::GetKeyPress(VK_RIGHT)) {
		m_IntAdd += 1;
	}
	if (Input::GetKeyPress(VK_LEFT)) {
		m_IntAdd -= 1;
	}

	bool flag = false;

	for (auto& hold : m_DebugData) {

		if (hold.second.tag == tag &&
			hold.second.function == (char*)function) {
			hold.second.data = (float)*target;
			flag = true;

			/*cdbg << "tag:" << hold.second.tag <<
				" function:" << hold.second.function <<
				" variable:" << hold.second.variable <<
				" data:" << hold.second.data << endl;*/

			break;
		}

	}

	if (!flag) {
		m_DebugData[tag] = { tag,(char*)function,variable,(float)*target};
		
		/*cdbg << "tag:" << m_DebugData[tag].tag <<
			" function:" << m_DebugData[tag].function <<
			" variable:" << m_DebugData[tag].variable <<
			" data:" << m_DebugData[tag].data << endl;*/
	}

}
