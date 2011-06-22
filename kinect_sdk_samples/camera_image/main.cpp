// �A�N�e�B�u��Kinect�̐����擾����T���v��
#include <iostream>

// MSR_NuiApi.h�̑O��Windows.h���C���N���[�h����
#include <Windows.h>
#include <MSR_NuiApi.h>

#include <opencv2/opencv.hpp>

#define ERROR_CHECK( ret )  \
    if ( ret != S_OK ) {    \
        std::cout << "failed " #ret " " << ret << std::endl;    \
        exit( 1 );          \
    }


void main()
{
    // ������
    ERROR_CHECK( ::NuiInitialize( NUI_INITIALIZE_FLAG_USES_COLOR ) );

    // �J�����n���h���̎擾
    HANDLE imageEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
    HANDLE streamHandle = 0;
    NUI_IMAGE_RESOLUTION resolution = NUI_IMAGE_RESOLUTION_640x480;
    ERROR_CHECK( ::NuiImageStreamOpen( NUI_IMAGE_TYPE_COLOR, resolution,
                    0, 2, imageEvent, &streamHandle ) );

    // ��ʃT�C�Y���擾
    DWORD x = 0, y = 0;
    ::NuiImageResolutionToSize( resolution, x, y );

    // OpenCV�̏����ݒ�
    char* windowName = "camera_image";
    ::cvNamedWindow( windowName );
    cv::Ptr< IplImage > videoImg = ::cvCreateImage( cvSize( x, y ), IPL_DEPTH_8U, 4 );

    // ���C�����[�v
    while ( 1 ) {
        // �f�[�^�̍X�V��҂�
        ::WaitForSingleObject( imageEvent, INFINITE );

        // �J�����f�[�^�̎擾
        CONST NUI_IMAGE_FRAME *imageFrame = 0;
        ERROR_CHECK( ::NuiImageStreamGetNextFrame( streamHandle, 0, &imageFrame ) );

        // �摜�f�[�^�̎擾
        KINECT_LOCKED_RECT rect;
        imageFrame->pFrameTexture->LockRect( 0, &rect, 0, 0 );

        // �f�[�^�̃R�s�[�ƕ\��
        memcpy( videoImg->imageData, (BYTE*)rect.pBits, videoImg->widthStep * videoImg->height );
        ::cvShowImage( windowName, videoImg );

        // �J�����f�[�^�̉��
        ERROR_CHECK( ::NuiImageStreamReleaseFrame( streamHandle, imageFrame ) );

        int key = ::cvWaitKey( 10 );
        if ( key == 'q' ) {
            break;
        }
    }

    // �I������
    NuiShutdown();

    ::cvDestroyAllWindows();
}
