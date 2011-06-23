// ���S�̋�����\������T���v��
#include <iostream>
#include <sstream>

#include "kinect\nui\Kinect.h"
#include "kinect\nui\ImageFrame.h"

#include <opencv2/opencv.hpp>

const char* FACE_CASCADE_PATH = "C:/OpenCV2.2/data/haarcascades/haarcascade_frontalface_alt.xml";

void main()
{
    try {
        kinect::nui::Kinect kinect;
        kinect.Initialize( NUI_INITIALIZE_FLAG_USES_COLOR | NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX | NUI_INITIALIZE_FLAG_USES_SKELETON );

        kinect::nui::ImageStream& video = kinect.VideoStream();
        video.Open( NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480 );

        kinect::nui::ImageStream& depth = kinect.DepthStream();
        depth.Open( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_320x240 );

        // OpenCV�̏����ݒ�
        char* windowName = "player";
        ::cvNamedWindow( windowName );
        cv::Ptr< IplImage > videoImg = ::cvCreateImage( cvSize(video.Width(), video.Height()), IPL_DEPTH_8U, 4 );

        // �摜��ǂݍ����Kinect�ɂ��킹�ĕϊ�����
        cv::Ptr< IplImage > face = ::cvLoadImage( "lena.jpg" );
        cv::Ptr< IplImage > faceImg = ::cvCreateImage( cvSize(face->width, face->height), IPL_DEPTH_8U, 4 );
        ::cvCvtColor( face, faceImg, CV_RGB2RGBA ); 

        // ���o��̃��[�h
        CvHaarClassifierCascade* faceCascade = (CvHaarClassifierCascade*)::cvLoad( FACE_CASCADE_PATH, 0, 0, 0 );
        if( !faceCascade ) {
            throw std::runtime_error("error : cvLoad");
        }

        // �猟�o�p�̃X�g���[�W
        CvMemStorage* storage = ::cvCreateMemStorage();
        bool isDetected = true;

        // �O��̌��o����
        DWORD prevTime = ::GetTickCount();

        while ( 1 ) {
            // �f�[�^�̍X�V��҂��āA���̃t���[�����擾����
            kinect.WaitAndUpdateAll();
            kinect::nui::VideoFrame videoMD( video );

            // �f�[�^�̃R�s�[
            memcpy( videoImg->imageData, (BYTE*)videoMD.Bits(), videoImg->widthStep * videoImg->height );

            // ��̌��o
            if (isDetected) {
                // ���[�^���񂵂�����Ƃ�����̂ŁA1�b�Ɉ��
                if ( (::GetTickCount() - prevTime) > 1000 ) {
                    prevTime = ::GetTickCount();

                    // ��̌��o
                    cvClearMemStorage(storage);
                    CvSeq* faces = ::cvHaarDetectObjects( videoImg, faceCascade, storage );
                    for ( int i = 0; i < faces->total; ++i ) {
                        // ���o�������W�̎擾
                        CvRect rect = *(CvRect*)::cvGetSeqElem( faces, i );

                        // ���o������ɉ摜��\��t����
                        ::cvSetImageROI( videoImg, rect );
                        cv::Ptr< IplImage >  resizeImg = ::cvCreateImage( cvSize( rect.width, rect.height), faceImg->depth, faceImg->nChannels );
                        ::cvResize( faceImg, resizeImg );
                        ::cvCopy( resizeImg, videoImg );
                        ::cvResetImageROI( videoImg );

                        // ���S�_�ƁA�\���̈���O���������Ƃ��̍��W
                        POINT c = { rect.x + (rect.width / 2), rect.y + (rect.height / 2) };
                        RECT place[] = {
                            { 0, 0, video.Width(), video.Height() / 3 },
                            { 0, video.Height() / 3, video.Width(), video.Height() / 3 * 2 },
                            { 0, video.Height() / 3 * 2, video.Width(), video.Height() },
                        };

                        // ��̈ʒu�ɂ���āAKinect�̎�𓮂���
                        // ��1/3�ɂ���΁A��ɓ�����
                        LONG angle = kinect.GetAngle();
                        if ( ::PtInRect( &place[0], c ) ) {
                            angle += 5;
                            if ( angle < kinect.CAMERA_ELEVATION_MAXIMUM ) {
                                kinect.SetAngle( angle );
                            }
                        }
                        // ��1/3�ɂ���΁A�������Ȃ�
                        else if ( ::PtInRect( &place[1], c ) ) {
                        }
                        // ��1/3�ɂ���΁A���ɓ�����
                        else if ( ::PtInRect( &place[2], c ) ) {
                            angle -= 5;
                            if ( angle > kinect.CAMERA_ELEVATION_MINIMUM ) {
                                kinect.SetAngle( angle );
                            }
                        }
                    }
                }
            }

            ::cvShowImage( windowName, videoImg );

            int key = ::cvWaitKey( 10 );
            if ( key == 'q' ) {
                break;
            }
            else if (key == 'd') {
                isDetected = !isDetected;
            }
        }

        ::cvDestroyAllWindows();
    }
    catch ( std::exception& ex ) {
        std::cout << ex.what() << std::endl;
    }
}
