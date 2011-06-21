// ���S�̋�����\������T���v��
#include <iostream>
#include <sstream>

#include "kinect\nui\Kinect.h"
#include "kinect\nui\ImageFrame.h"

#include <opencv2/opencv.hpp>

void main()
{
    try {
        // NUI_INITIALIZE_FLAG_USES_DEPTH�̕\���̂��������킩���
        kinect::nui::Kinect kinect;
        kinect.Initialize( NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX );

        kinect::nui::ImageStream& depth = kinect.DepthStream();
        depth.Open( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_320x240 );

        // OpenCV�̏����ݒ�
        char* windowName = "depth_map";
        ::cvNamedWindow( windowName );
        cv::Ptr< IplImage > depthImg = ::cvCreateImage( cvSize(depth.Width(), depth.Height()), IPL_DEPTH_16U, 1 );

        while ( 1 ) {
            // �f�[�^�̍X�V��҂�
            kinect.WaitAndUpdateAll();

            // ���̃t���[���̃f�[�^���擾����(OpenNI���ۂ�)
            kinect::nui::DepthFrame depthMD( depth );

            // �f�[�^�̃R�s�[�ƕ\��
            memcpy( depthImg->imageData, (BYTE*)depthMD.Bits(), depthImg->widthStep * depthImg->height );

            ::cvShowImage( windowName, depthImg );

            int key = ::cvWaitKey( 10 );
            if ( key == 'q' ) {
                break;
            }
        }

        ::cvDestroyAllWindows();
    }
    catch ( std::exception& ex ) {
        std::cout << ex.what() << std::endl;
    }
}
