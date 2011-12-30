#pragma once 

#include <Windows.h>

#include <mmsystem.h>
#pragma comment( lib, "winmm.lib" )

#include <vector>

class WaveAudio
{
public:

    WaveAudio()
    {
    }

    virtual ~WaveAudio()
    {
        waveOutPause( hWaveOut );

        for ( size_t i = 0; i < waveHeaders_.size(); ++i ) {
            delete[] waveHeaders_[i].lpData;
        }
    }

    void Initialize( int nSampleRate, int nBitsPerSample, int nChannels, int audioBufferCount = 100 )
    {
        audioBufferCount_ = audioBufferCount;
        audioBufferNextIndex_ = 0;

        // WAVE�f�[�^�̐ݒ�
        WAVEFORMATEX wf;
        wf.wFormatTag = 0x0001; // PCM
        wf.nChannels = nChannels;
        wf.nSamplesPerSec = nSampleRate;
        wf.wBitsPerSample = nBitsPerSample;
        wf.nBlockAlign = wf.wBitsPerSample * wf.nChannels / 8;
        wf.nAvgBytesPerSec = wf.nBlockAlign * wf.nSamplesPerSec;

        MMRESULT mmRes = ::waveOutOpen( &hWaveOut, WAVE_MAPPER, &wf, NULL, NULL, CALLBACK_NULL );
        if ( mmRes != MMSYSERR_NOERROR ) {
            throw std::runtime_error( "waveOutOpen failed\n" );
        }

        // �����f�[�^�p�̃o�b�t�@�̍쐬�Ə�����
        waveHeaders_.resize( audioBufferCount_ );
        memset( &waveHeaders_[0], 0, sizeof(WAVEHDR) * waveHeaders_.size() );

        for ( size_t i = 0; i < waveHeaders_.size(); ++i ) {
            waveHeaders_[i].lpData = new char[MAX_BUFFER_SIZE];
            waveHeaders_[i].dwUser = i;
            waveHeaders_[i].dwFlags = WHDR_DONE;
        }
    }

    void Output( const void* buffer, DWORD length )
    {
        // �o�b�t�@�̎擾
        WAVEHDR* pHeader = &waveHeaders_[audioBufferNextIndex_];
        if ( (pHeader->dwFlags & WHDR_DONE) == 0 ) {
            return;
        }

        // WAVE�w�b�_�̃N���[���A�b�v
        MMRESULT mmRes = ::waveOutUnprepareHeader( hWaveOut, pHeader, sizeof(WAVEHDR) );
        if ( mmRes != MMSYSERR_NOERROR ) {
        }

        // WAVE�f�[�^�̎擾
        pHeader->dwBufferLength = length;
        pHeader->dwFlags = 0;
        memcpy( pHeader->lpData, buffer, pHeader->dwBufferLength );

        // WAVE�w�b�_�̏�����
        mmRes = ::waveOutPrepareHeader( hWaveOut, pHeader, sizeof(WAVEHDR) );
        if ( mmRes != MMSYSERR_NOERROR ) {
            return;
        }

        // WAVE�f�[�^���o�̓L���[�ɓ����
        mmRes = ::waveOutWrite( hWaveOut, pHeader, sizeof(WAVEHDR) );
        if ( mmRes != MMSYSERR_NOERROR ) {
            return;
        }

        // ���̃o�b�t�@�C���f�b�N�X
        audioBufferNextIndex_ = (audioBufferNextIndex_ + 1) % audioBufferCount_;
    }

private:

    WaveAudio( const WaveAudio& rhs );
    WaveAudio& operator = ( const WaveAudio& rhs );

private:

    static const int MAX_BUFFER_SIZE = 2 * 1024 * 1024;

    HWAVEOUT hWaveOut;
    std::vector<WAVEHDR>        waveHeaders_;

    int audioBufferCount_;
    int audioBufferNextIndex_;
};
