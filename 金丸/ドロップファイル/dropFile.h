#pragma once
#include <list>
#include <filesystem> //������g���ꍇ�v���p�e�B��C++����W����C++17�ɐݒ肵�Ȃ��Ⴂ���Ȃ�

namespace fs = std::filesystem;

class DropFile
{
private:
    static HDROP m_Drop;
	static std::list<fs::path> m_fullPathNames;
	static void CopyFileToProjectFolder(fs::path filePath);
public:
	static void SetDrop(HDROP hDROP) { m_Drop = hDROP; }
	static void DropFileData();
};