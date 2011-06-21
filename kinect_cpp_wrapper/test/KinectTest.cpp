#include "gtest\gtest.h"
#include "kinect\nui\Kinect.h"

//#define ANGLE_TEST

// �C���X�^���X�̐���
TEST( KinectTest, CreateInstance )
{
	kinect::nui::Kinect kinect;
}

// �A�N�e�B�u��Kinect���̎擾
TEST( KinectTest, GetActiveCount )
{
	EXPECT_EQ( 1, kinect::nui::Kinect::GetActiveCount() );
}

// �f�o�C�X�̏�����
TEST( KinectTest, Initialize )
{
	kinect::nui::Kinect kinect;
	kinect.Initialize( NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX );
}

// �������Ȃ��̃V���b�g�_�E��
TEST( KinectTest, NonInitializeShutDown )
{
	kinect::nui::Kinect kinect;
	kinect.Shutdown();
}

// ��ӂ�
TEST( KinectTest, CameraElevationAngle )
{
	// SetAngle �̂��Ƃɏ����҂��Ȃ��ƁAGetAngle�ŃG���[�ɂȂ�
	const int SLEEP_TIME = 1000;

#ifdef ANGLE_TEST
	kinect::nui::Kinect kinect;
	kinect.Initialize( NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX );

	// Set��Get�̒l�͑��������
	kinect.SetAngle( NUI_CAMERA_ELEVATION_MAXIMUM );
	::Sleep( SLEEP_TIME );
	EXPECT_EQ( NUI_CAMERA_ELEVATION_MAXIMUM, kinect.GetAngle() );

	kinect.SetAngle( NUI_CAMERA_ELEVATION_MINIMUM );
	::Sleep( SLEEP_TIME );
	EXPECT_EQ( NUI_CAMERA_ELEVATION_MINIMUM, kinect.GetAngle() );

	kinect.SetAngle( 0 );
	::Sleep( SLEEP_TIME );
	EXPECT_EQ( 0, kinect.GetAngle() );
#endif
}
