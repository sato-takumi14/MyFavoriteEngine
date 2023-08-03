#include "main.h"
#include "dropFile.h"

#include <list>
#include <string>

HDROP DropFile::m_Drop{};
std::list<fs::path> DropFile::m_fullPathNames;


void DropFile::DropFileData()
{
    UINT count = 0;
    UINT length = 0;
    wchar_t* fullPathName = nullptr;

    // �h���b�O���ꂽ�t�@�C�������擾
    count = DragQueryFile(m_Drop, 0xFFFFFFFF, NULL, 0);

    // �t�@�C�����Ń��[�v
    for (int i = 0; i < static_cast<int>(count); i++)
    {
        // �t���p�X�̒������擾(NULL�I�[���܂܂�)
        length = DragQueryFile(m_Drop, i, NULL, 0);

        // �t���p�X���󂯎��ϐ���������(NULL�I�[���܂�)
        fullPathName = new wchar_t[length + 1];
        wmemset(fullPathName, L'\0', length + 1);

        // �t���p�X���擾
        DragQueryFile(m_Drop, i, reinterpret_cast<LPSTR>(fullPathName), length + 1);

        //������wchar_t*�^����const char*�ɕϊ����Ȃ��ƂȂ����o�O��
        const char* fullPathNameChar = reinterpret_cast<const char*>(fullPathName);

       
        m_fullPathNames.push_back(fullPathNameChar);

        // �ϐ��̉��
        delete[] fullPathName;

    }

    for (auto filePath : m_fullPathNames) {

        CopyFileToProjectFolder(filePath);

    }
    m_fullPathNames.clear(); // ���X�g�̃N���A

}

void DropFile::CopyFileToProjectFolder(fs::path filePath)
{
    // �v���W�F�N�g�̃��[�g�f�B���N�g�����擾
    //�����Ƀv���W�F�N�g�t�H���_�܂ł̃p�X���i�[����Ă���
    fs::path projectRoot = fs::current_path();

    // "asset\\texture"�t�H���_�̑��΃p�X��ݒ�
    //�v���W�F�N�g�t�H���_����ۑ��������ꏊ�ւ̃p�X���i�[����Ă���
    fs::path relativeFolderPath = L"asset\\texture";

    // �v���W�F�N�g�t�H���_�ɃR�s�[���邽�߂̃t�@�C���p�X���쐬
    fs::path destinationPath = projectRoot / relativeFolderPath / fs::path(filePath).filename();

    try {
        // �t�@�C�����R�s�[����
        //�����Ńt�@�C�����R�s�[���Ďw��̃p�X�̃t�H���_�Ɋi�[���Ă���
        fs::copy_file(filePath, destinationPath, fs::copy_options::overwrite_existing);
    }
    catch (const fs::filesystem_error& ex) {
        if (!fs::is_regular_file(filePath))
        {
           assert(fs::exists(filePath));
           assert(fs::exists(destinationPath));

          //�����p�X�ł͂Ȃ��A�V���{���b�N�����N�^�n�[�h�����N�ł��Ȃ��̂ŁA�����ł͂Ȃ�
           assert(!fs::equivalent(filePath, destinationPath));
        }
    }
}
