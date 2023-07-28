#pragma once

#include"GameObject.h"

#include<string>
#include<thread>
#include<vector>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
//#include<thread>
//#include<cstdint>

#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

#include<xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include"WaveFileReader.h"


//#pragma comment(lib, "Mf.lib")
//#pragma comment(lib, "mfplat.lib")
//#pragma comment(lib, "Mfreadwrite.lib")
//#pragma comment(lib, "mfuuid.lib")

//#include<unordered_map>
//
//typedef struct {
//	const char* name;
//	IXAudio2SourceVoice* audio;
//}AudioData;

class Audio : public Component
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	/*static unordered_map<int, char*> mData;
	static int mIndex;*/

	IXAudio2SourceVoice*	m_SourceVoice{};
	BYTE*					m_SoundData{};

	int						m_Length{};
	int						m_PlayLength{};

	IMFSourceReader* mMFSourceReader{};
	IMFMediaType* mMFMediaType{};
	WAVEFORMATEX* mWaveFormat{};
	vector<BYTE> mMediaData;

	/*BYTE mBuffers[MAX_BUFFER_COUNT][STREAMING_BUFFER_SIZE]{};
	OVERLAPPED mOverlapped{};*/

	WaveFileReader mReader;

	vector<BYTE> mPrimary;
	vector<BYTE> mSecondary;

	size_t nextFirstSample = 0;
	size_t submitCount = 0;

	bool mStreaming{};
	bool mLoop{};

	void SetBuffer();
	string WStringToString(wstring oWString);

public:

	Audio();
	~Audio();

	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Update();
	void Uninit();

	void Load(const char *FileName);
	void Play(bool Loop = false);

	void LoadMP3(wstring file);
	void PlayMP3(bool loop = false);

	void LoadStreaming(wstring file);
	void PlayStreaming(bool loop = false);

};

