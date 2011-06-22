// ���S�̋�����\������T���v��
#include <iostream>
#include <sstream>

#include "kinect\nui\Kinect.h"
#include "kinect\nui\ImageFrame.h"

#include <opencv2/opencv.hpp>

void main()
{
    try {
        kinect::nui::Kinect kinect;
        kinect.Initialize( NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH );

        kinect::nui::ImageStream& video = kinect.VideoStream();
        video.Open( NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480 );

        kinect::nui::ImageStream& depth = kinect.DepthStream();
        depth.Open( NUI_IMAGE_TYPE_DEPTH, NUI_IMAGE_RESOLUTION_640x480 );

        // OpenCV�̏����ݒ�
        char* windowName = "depth";
        ::cvNamedWindow( windowName );
        cv::Ptr< IplImage > videoImg = ::cvCreateImage( cvSize(video.Width(), video.Height()), IPL_DEPTH_8U, 4 );

        // �`��p�t�H���g�̍쐬
        CvFont font;
        ::cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 10);

        while ( 1 ) {
            // �f�[�^�̍X�V��҂�
            kinect.WaitAndUpdateAll();

            // ���̃t���[���̃f�[�^���擾����(OpenNI���ۂ�)
            kinect::nui::ImageFrame imageMD( video );
            kinect::nui::DepthFrame depthMD( depth );

            // �f�[�^�̃R�s�[�ƕ\��
            memcpy( videoImg->imageData, (BYTE*)imageMD.Bits(), videoImg->widthStep * videoImg->height );

            // ���S�ɂ��镨�̂܂ł̋����𑪂��ĕ\������
            CvPoint point = cvPoint( depthMD.Width() / 2, depthMD.Height() / 2);
            ::cvCircle( videoImg, point, 10, cvScalar(0, 0, 0), -1 );

            std::stringstream ss;
            ss << depthMD( point.x, point.y ) << "mm";
            ::cvPutText( videoImg, ss.str().c_str(), point, &font, cvScalar(0, 0, 255) );

            ::cvShowImage( windowName, videoImg );

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
