#include <vector>

#include "kinect/nui/Kinect.h"

#include "win32/Win32Exception.h"

namespace kinect {
	namespace nui {
		/**
		 * �R���X�g���N�^
		 *
		 * @param	index	��������Kinect�C���X�^���X�̃C���f�b�N�X
		 */
		Kinect::Kinect( int index /*= 0*/ )
            : instance_( Create( index ) )
            , video_( instance_ )
            , depth_( instance_ )
            , skeleton_( instance_ )
            , index_( index )
		{
		}

		/**
		 * �f�X�g���N�^
		 */
		Kinect::~Kinect()
		{
			Shutdown();
		}

		/**
		 * �C���X�^���X�𐶐�����
		 *
		 * @param	index	��������Kinect�C���X�^���X�̃C���f�b�N�X
		 */
        Kinect::NuiInstance Kinect::Create( int index )
        {
			INuiInstance* instance = 0;
			HRESULT ret = ::MSR_NuiCreateInstanceByIndex( index, &instance );
			if ( ret != S_OK ) {
				throw win32::Win32Exception( ret );
			}

			return NuiInstance( instance, ::MSR_NuiDestroyInstance );
        }

		/**
		 * �A�N�e�B�u��Kinect�̐����擾����
		 *
		 * @return	�A�N�e�B�u��Kinect�̐�
		 */
		/*static*/ int Kinect::GetActiveCount()
		{
			int count = 0;
			HRESULT ret = ::MSR_NUIGetDeviceCount( &count );
			if ( ret != S_OK ) {
				throw win32::Win32Exception( ret );
			}

			return count;
		}

		/**
		 * Kinect�̏�����
		 *
		 * @param	dwFlags	�������t���O
		 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX	�����ƃ��[�U�[���擾����
		 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX	�����ƃ��[�U�[���擾����
		 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX	�����ƃ��[�U�[���擾����
		 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX	�����ƃ��[�U�[���擾����
		 */
		void Kinect::Initialize( DWORD dwFlags )
		{
			HRESULT ret = instance_->NuiInitialize( dwFlags );
			if ( ret != S_OK ) {
				throw win32::Win32Exception( ret );
			}
		}

		void Kinect::Shutdown()
		{
			instance_->NuiShutdown();
		}

        void Kinect::WaitAndUpdateAll()
        {
            std::vector< HANDLE >   handle;
            if ( VideoStream().hStream_ != 0 ) {
                handle.push_back( VideoStream().event_.get() );
            }

            if ( DepthStream().hStream_ != 0 ) {
                handle.push_back( DepthStream().event_.get() );
            }

            if ( Skeleton().IsEnabled() ) {
                handle.push_back( Skeleton().event_.get() );
            }

            DWORD ret = ::WaitForMultipleObjects( handle.size(), &handle[0], TRUE, INFINITE );
            if ( ret == WAIT_FAILED ) {
                throw win32::Win32Exception( ::GetLastError() );
            }
        }

		void Kinect::SetAngle( LONG lAngleDegrees )
		{
			HRESULT ret = instance_->NuiCameraElevationSetAngle( lAngleDegrees );
			if ( ret != S_OK ) {
				throw win32::Win32Exception( ret );
			}
		}

		LONG Kinect::GetAngle() const
		{
			LONG angle = 0;
			HRESULT ret = instance_->NuiCameraElevationGetAngle( &angle );
			//if ( ret != S_OK ) {
			//	throw win32::Win32Exception( ret );
			//}

			return angle;
		}
	}
}
