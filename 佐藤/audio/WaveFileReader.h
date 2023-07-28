#pragma once

#if !defined( WAVE_FILE_READER__H )
#define WAVE_FILE_READER__H

#include"main.h"

#include <cstdio>
#include <cstring>
#include<tchar.h>

#include<xaudio2.h>

class WaveFileReader
{
public:
	// �R���X�g���N�^
	WaveFileReader()
		: m_pFile(NULL)
		, m_hasGotWaveFormat(false)
		, m_firstSampleOffset(-1)
		, m_dataChunkSize(0)
		, m_dataChunkSamples(0)
	{
	}
	// �f�X�g���N�^
	~WaveFileReader()
	{
		Close();
	}

	// �I�[�v��
	bool Open(const TCHAR* filename)
	{
		if (m_pFile) return false;
		if (_tfopen_s(&m_pFile, filename, _T("rb")) != 0) return false;
		return true;
	}

	// �t�H�[�}�b�g�����擾
	const WAVEFORMATEX* GetWaveFormat()
	{
		// �I�[�v���ς݂�
		if (!m_pFile) return NULL;

		if (!m_hasGotWaveFormat)
		{
			long offset = 12;

			while (1)
			{
				// �`�����N�擪�ֈړ�
				if (fseek(m_pFile, offset, SEEK_SET) != 0) break;

				// �`�����N�V�O�l�`����ǂݍ���
				char chunkSignature[4] = { 0 };
				std::size_t readChars = 0;
				while (readChars < 4)
				{
					std::size_t ret = fread(chunkSignature + readChars, sizeof(char), 4 - readChars, m_pFile);
					if (ret == 0) break;
					readChars += ret;
				}

				// �`�����N�T�C�Y��ǂݍ���
				uint32_t chunkSize = 0;
				if (fread(&chunkSize, sizeof(uint32_t), 1, m_pFile) == 0) break;

				// fmt �`�����N������������t�H�[�}�b�g����ǂݍ���
				if (strncmp(chunkSignature, "fmt ", 4) == 0)
				{
					std::size_t readSize = chunkSize < sizeof(WAVEFORMATEX) ? chunkSize : sizeof(WAVEFORMATEX);
					if (fread(&m_waveFormat, readSize, 1, m_pFile) == 0) break;

					// PCM �̂Ƃ��͈ꉞ cbSize �� 0 �ɂ��Ă��� (���������炵������)
					if (m_waveFormat.wFormatTag == WAVE_FORMAT_PCM) m_waveFormat.cbSize = 0;
					// �t�H�[�}�b�g���擾�ς�
					m_hasGotWaveFormat = true;
				}

				// data �`�����N������������I�t�Z�b�g�ƃT�C�Y���L��
				if (strncmp(chunkSignature, "data", 4) == 0)
				{
					m_firstSampleOffset = offset + 8;	// �V�O�l�`�� 4bytes �{ �T�C�Y 4bytes
					m_dataChunkSize = chunkSize;
				}

				// ���̃`�����N��
				offset += (static_cast<long>(chunkSize) + 8);
			}

			if (!m_hasGotWaveFormat) return NULL;	// �ǂ����ŃG���[���N���Ă����ƏE���Ȃ�����

			// �t�H�[�}�b�g��񂪎擾�ł����� data �`�����N���̃T���v�������v�Z
			m_dataChunkSamples = m_dataChunkSize / m_waveFormat.nBlockAlign;	// �K������؂��͂�
		}
		return &m_waveFormat;
	}

	// �T���v�������擾
	std::size_t GetSamples()
	{
		// �I�[�v���ς݂�
		if (!m_pFile) return 0;
		// �t�H�[�}�b�g�����擾���Ă��Ȃ���΂�����
		if (!m_hasGotWaveFormat) GetWaveFormat();

		return m_dataChunkSamples;
	}

	// ���f�[�^�ǂݍ���
	std::size_t ReadRaw(const std::size_t start, const std::size_t samples, void* buffer)
	{
		// �o�b�t�@�A�h���X���s���ł͂Ȃ���
		if (!buffer) return 0;	// �{���Ȃ� assert ���ׂ�
		// �I�[�v���ς݂�
		if (!m_pFile) return 0;
		// �t�H�[�}�b�g�����擾���Ă��Ȃ���΂�����
		if (!m_hasGotWaveFormat)
		{
			if (!GetWaveFormat()) return 0;
		}
		// �J�n�ʒu���I�[�o�[���Ă��Ȃ���
		if (start >= m_dataChunkSamples) return 0;

		// ���ۂɓǂݍ��ރT���v�������v�Z
		std::size_t actualSamples = start + samples > m_dataChunkSamples ? m_dataChunkSamples - start : samples;

		// �ǂݍ��݊J�n�ʒu�ֈړ�
		if (fseek(m_pFile, m_firstSampleOffset + start * m_waveFormat.nBlockAlign, SEEK_SET) != 0) return 0;
		// �ǂݍ���
		std::size_t readSamples = 0;
		while (readSamples < actualSamples)
		{
			std::size_t ret = fread(reinterpret_cast<uint8_t*>(buffer) + readSamples * m_waveFormat.nBlockAlign,
				m_waveFormat.nBlockAlign,
				actualSamples - readSamples,
				m_pFile);
			if (ret == 0) break;
			readSamples += ret;
		}

		return readSamples;
	}

	// ���K���ς݃f�[�^�ǂݍ���
	std::size_t ReadNormalized(const std::size_t start, const std::size_t samples, float* left, float* right)
	{
		// ���Ȃ��Ƃ� 1ch �Ԃ�͎w�肳��Ă��邩
		if (!left) return 0;	// �{���Ȃ� assert ���ׂ�
		// �I�[�v���ς݂�
		if (!m_pFile) return 0;
		// �t�H�[�}�b�g�����擾���Ă��Ȃ���΂�����
		if (!m_hasGotWaveFormat)
		{
			if (!GetWaveFormat()) return 0;
		}
		// �J�n�ʒu���I�[�o�[���Ă��Ȃ���
		if (start >= m_dataChunkSamples) return 0;

		// ���ۂɓǂݍ��ރT���v�������v�Z
		std::size_t actualSamples = start + samples > m_dataChunkSamples ? m_dataChunkSamples - start : samples;



		return 0;
	}

	// �N���[�Y
	void Close()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
			m_hasGotWaveFormat = false;
			m_firstSampleOffset = -1;
			m_dataChunkSize = 0;
			m_dataChunkSamples = 0;
		}
	}

private:
	// �t�@�C���n���h��
	FILE* m_pFile;
	// �t�H�[�}�b�g�����擾�ς݂�
	bool m_hasGotWaveFormat;
	// �t�H�[�}�b�g���
	WAVEFORMATEX m_waveFormat;
	// data �`�����N���擪�T���v���ւ̃I�t�Z�b�g
	long m_firstSampleOffset;
	// data �`�����N�T�C�Y
	std::size_t m_dataChunkSize;
	// data �`�����N���T���v����
	std::size_t m_dataChunkSamples;
};


#endif // !defined( WAVE_FILE_READER__H )