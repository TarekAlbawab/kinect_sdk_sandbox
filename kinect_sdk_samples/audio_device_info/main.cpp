// �J�����摜��\������T���v��
#include <iostream>

// MSR_NuiApi.h�̑O��Windows.h���C���N���[�h����
#include <Windows.h>
#include <MSR_NuiApi.h>
#include <MSRKinectAudio.h>

#include "win32\DllLoader.h"

typedef HRESULT (WINAPI *GETKINECTDEVICEINFO)(PKINECT_AUDIO_INFO pDeviceInfo, int *piDeviceCount);

void main()
{
    try {
        HRESULT hr = ::CoInitialize( 0 );
        if ( hr != S_OK ) {
            throw win32::Win32Exception( hr );
        }

        // �C���|�[�g���C�u�������Ȃ��̂ŁADLL���璼�Ƀ��[�h����
        win32::DllLoader dll( "MSRKinectAudio.dll" );
        GETKINECTDEVICEINFO GetKinectDeviceInfo = dll.GetProcAddress<GETKINECTDEVICEINFO>( "GetKinectDeviceInfo" );

        KINECT_AUDIO_INFO DeviceInfo = { 0 };
        int DeviceCount = 0;
        hr = GetKinectDeviceInfo( &DeviceInfo, &DeviceCount );
        if ( hr != S_OK ) {
            throw win32::Win32Exception( hr );
        }

        std::wcout << "DeviceCount:" << DeviceCount << " " <<
                     "DeviceIndex:" << DeviceInfo.iDeviceIndex << " " <<
                     "DeviceName :" << DeviceInfo.szDeviceName << " " <<
                     "DeviceID   :" << DeviceInfo.szDeviceID << std::endl;
    }
    catch ( std::exception& ex ) {
        std::cout << ex.what() << std::endl;
    }
}
