
#include "main.h"
#include "audio.h"

IXAudio2*				Audio::m_Xaudio = NULL;
IXAudio2MasteringVoice*	Audio::m_MasteringVoice = NULL;

void Audio::SetBuffer()
{
	nextFirstSample = 0;
	submitCount = 0;

	// プライマリバッファ
	std::vector< BYTE > primary(mWaveFormat->nAvgBytesPerSec * 3);
	mPrimary = primary;

	if (nextFirstSample < mReader.GetSamples())
	{
		std::size_t readSamples = mReader.ReadRaw(nextFirstSample, mWaveFormat->nSamplesPerSec * 3, &(mPrimary[0]));
		if (readSamples > 0)
		{
			XAUDIO2_BUFFER bufferDesc = { 0 };
			bufferDesc.Flags = nextFirstSample + readSamples >= mReader.GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
			bufferDesc.AudioBytes = readSamples * mWaveFormat->nBlockAlign;
			bufferDesc.pAudioData = &(mPrimary[0]);

			m_SourceVoice->SubmitSourceBuffer(&bufferDesc);

			/*_tprintf_s(_T("Read: 0･･･%u-----%u･･･%u\n"),
				nextFirstSample, nextFirstSample + readSamples - 1, mReader.GetSamples() - 1);*/

			nextFirstSample += readSamples;
			++submitCount;
		}
	}

	// セカンダリバッファ
	std::vector< BYTE > secondary(mWaveFormat->nAvgBytesPerSec * 3);
	mSecondary = secondary;
}

string Audio::WStringToString(wstring oWString)
{
	// wstring → SJIS
	int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str()
		, -1, (char*)NULL, 0, NULL, NULL);

	// バッファの取得
	CHAR* cpMultiByte = new CHAR[iBufferSize];

	// wstring → SJIS
	WideCharToMultiByte(CP_OEMCP, 0, oWString.c_str(), -1, cpMultiByte
		, iBufferSize, NULL, NULL);

	// stringの生成
	std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

	// バッファの破棄
	delete[] cpMultiByte;

	// 変換結果を返す
	return(oRet);
}

Audio::Audio()
{
}

Audio::~Audio()
{
	/*if (m_SourceVoice  != nullptr) {
		m_SourceVoice->Stop();
		m_SourceVoice->DestroyVoice();
	}
	if (m_SoundData) delete[] m_SoundData;*/
	
}

void Audio::InitMaster()
{
	// COM初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);

	// XAudio生成
	XAudio2Create(&m_Xaudio, 0);

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);

}

void Audio::UninitMaster()
{
	MFShutdown();

	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}

void Audio::Load(const char *FileName)
{

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)FileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		m_SoundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)m_SoundData, buflen);


		m_Length = readlen;
		m_PlayLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// サウンドソース生成
	m_Xaudio->CreateSourceVoice(&m_SourceVoice, &wfx);
	assert(m_SourceVoice);
}

void Audio::Update()
{

	if (mStreaming) {

		XAUDIO2_VOICE_STATE state;
		m_SourceVoice->GetState(&state);

		if (state.BuffersQueued == 0 && nextFirstSample >= mReader.GetSamples())
		{
			// すべて再生し終わっている
			//break;
			if (mLoop) {
				SetBuffer();
				m_SourceVoice->Start();
			}
		}
		else if (state.BuffersQueued < 2 && nextFirstSample < mReader.GetSamples())
		{
			// キューにバッファを追加
			std::vector< BYTE >& buffer = submitCount & 1 ? mSecondary : mPrimary;

			std::size_t readSamples = mReader.ReadRaw(nextFirstSample, mWaveFormat->nSamplesPerSec * 3, &(buffer[0]));
			if (readSamples > 0)
			{
				XAUDIO2_BUFFER bufferDesc = { 0 };
				bufferDesc.Flags = nextFirstSample + readSamples >= mReader.GetSamples() ? XAUDIO2_END_OF_STREAM : 0;
				bufferDesc.AudioBytes = readSamples * mWaveFormat->nBlockAlign;
				bufferDesc.pAudioData = &(buffer[0]);

				m_SourceVoice->SubmitSourceBuffer(&bufferDesc);

				nextFirstSample += readSamples;
				++submitCount;
			}
		}

	}
}

void Audio::Uninit()
{
	cdbg << "AudioUninit" << endl;

	m_SourceVoice->Stop();
	m_SourceVoice->DestroyVoice();

	CoTaskMemFree(mWaveFormat);
	if (mMFMediaType) mMFMediaType->Release();
	if (mMFSourceReader) mMFSourceReader->Release();

	delete[] m_SoundData;
}

void Audio::Play(bool Loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();


	// バッファ設定
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = m_Length;
	bufinfo.pAudioData = m_SoundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = m_PlayLength;

	// ループ設定
	if (Loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = m_PlayLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

/*
	float outputMatrix[4] = { 0.0f , 0.0f, 1.0f , 0.0f };
	m_SourceVoice->SetOutputMatrix(m_MasteringVoice, 2, 2, outputMatrix);
	//m_SourceVoice->SetVolume(0.1f);
*/


	// 再生
	m_SourceVoice->Start();

}

void Audio::LoadMP3(wstring file)
{
	MFCreateSourceReaderFromURL(file.c_str(), NULL, &mMFSourceReader);

	MFCreateMediaType(&mMFMediaType);
	mMFMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	mMFMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	mMFSourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mMFMediaType);

	mMFMediaType->Release();
	mMFMediaType = nullptr;
	mMFSourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mMFMediaType);

	MFCreateWaveFormatExFromMFMediaType(mMFMediaType, &mWaveFormat, nullptr);

	while (true) {

		IMFSample* sample{};
		DWORD dwStreamFlags{ 0 };
		mMFSourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &dwStreamFlags, nullptr, &sample);

		if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
			break;
		}

		IMFMediaBuffer* MediaBuffer{};
		sample->ConvertToContiguousBuffer(&MediaBuffer);

		BYTE* buffer{};
		DWORD length{};
		MediaBuffer->Lock(&buffer, nullptr, &length);

		mMediaData.resize(mMediaData.size() + length);
		memcpy(mMediaData.data() + mMediaData.size() - length, buffer, length);

		MediaBuffer->Unlock();

		MediaBuffer->Release();
		sample->Release();

	}

	m_Xaudio->CreateSourceVoice(&m_SourceVoice, mWaveFormat);
}

void Audio::PlayMP3(bool loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	XAUDIO2_BUFFER buffer{ 0 };

	buffer.pAudioData = mMediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(mMediaData.size());

	if (loop) {
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	m_SourceVoice->SubmitSourceBuffer(&buffer, NULL);

	m_SourceVoice->Start(0);
}

void Audio::LoadStreaming(wstring file)
{
	LoadMP3(file);
	mReader.Open(WStringToString(file).c_str());
	SetBuffer();
}

void Audio::PlayStreaming(bool loop)
{
	m_SourceVoice->Stop();
	m_SourceVoice->FlushSourceBuffers();

	m_SourceVoice->Start(0);

	mStreaming = true;
	mLoop = loop;
}

//void Audio::LoadMP3(string file)
//{
//	while (true)
//	{
//		IMFSample* pMFSample{ nullptr };
//		DWORD dwStreamFlags{ 0 };
//		mMFSourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &dwStreamFlags, nullptr, &pMFSample);
//
//		if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
//		{
//			break;
//		}
//
//		IMFMediaBuffer* pMFMediaBuffer{ nullptr };
//		pMFSample->ConvertToContiguousBuffer(&pMFMediaBuffer);
//
//		BYTE* pBuffer{ nullptr };
//		DWORD cbCurrentLength{ 0 };
//		pMFMediaBuffer->Lock(&pBuffer, nullptr, &cbCurrentLength);
//
//		mediaData.resize(mediaData.size() + cbCurrentLength);
//		memcpy(mediaData.data() + mediaData.size() - cbCurrentLength, pBuffer, cbCurrentLength);
//
//		pMFMediaBuffer->Unlock();
//
//		pMFMediaBuffer->Release();
//		pMFSample->Release();
//	}
//}
//
//void Audio::PlayMP3()
//{
//	IXAudio2SourceVoice* pSourceVoice{ nullptr };
//	m_Xaudio->CreateSourceVoice(&pSourceVoice, mWaveFormat);
//
//	XAUDIO2_BUFFER buffer{ 0 };
//	buffer.pAudioData = mediaData.data();
//	buffer.Flags = XAUDIO2_END_OF_STREAM;
//	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(mediaData.size());
//	pSourceVoice->SubmitSourceBuffer(&buffer);
//}



