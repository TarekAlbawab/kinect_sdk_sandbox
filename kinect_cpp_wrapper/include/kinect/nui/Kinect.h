#pragma once

#include <memory>

#include <Windows.h>
#include <MSR_NuiApi.h>

#include "kinect\nui\ImageStream.h"
#include "kinect\nui\SkeletonEngine.h"

/// tr1��std�ɂ���
namespace std {
	using namespace std::tr1;
}

/// MS����SDK�̖��O���
namespace kinect {
	/// NUI(�J�����A�摜�A����)�̖��O���
	namespace nui {
		/// Kinect�̑S�̓I�ȓ���
		class Kinect
		{
		public:

			/// �C���X�^���X�̃|�C���^
            typedef std::shared_ptr< INuiInstance > NuiInstance;

			Kinect( int index = 0 );
			~Kinect();

			static int GetActiveCount();

			/**
			 * Kinect�̏�����
			 *
			 * @param	dwFlags	�������t���O
			 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX	�����f�[�^�ƃ��[�U�[���擾����
			 *	@arg	NUI_INITIALIZE_FLAG_USES_COLOR					�J�����摜���擾����
			 *	@arg	NUI_INITIALIZE_FLAG_USES_SKELETON				���i�ǐՂ��s��
			 *	@arg	NUI_INITIALIZE_FLAG_USES_DEPTH					�����f�[�^���擾����
			 */
			void Initialize( DWORD dwFlags );
			void Shutdown();

            void WaitAndUpdateAll();

			void SetAngle( LONG lAngleDegrees );
			LONG GetAngle() const;

			/**
			 * ����Kinect�̃C���X�^���X�C���f�b�N�X���擾����
			 * 
			 * @return 0����n�܂�C���X�^���X�̃C���f�b�N�X
			 */
            int GetInstanceIndex() const { return index_; }

			/**
			 * ����Kinect�̃J�����C���[�W���擾����
			 * 
			 * @return ImageStream�̎Q��
			 */
            ImageStream& VideoStream() { return video_; }

			/**
			 * ����Kinect�̋����C���[�W���擾����
			 * 
			 * @return ImageStream�̎Q��
			 */
			ImageStream& DepthStream() { return depth_; }

			/**
			 * ����Kinect�̃X�P���g���G���W�����擾����
			 * 
			 * @return SkeletonEngine�̎Q��
			 */
			SkeletonEngine& Skeleton() { return skeleton_; }

            static const LONG CAMERA_ELEVATION_MAXIMUM = NUI_CAMERA_ELEVATION_MAXIMUM;	///< �J�����̎�ӂ�ő�l
            static const LONG CAMERA_ELEVATION_MINIMUM = NUI_CAMERA_ELEVATION_MINIMUM;	///< �J�����̎�ӂ�ŏ��l

        private:

            NuiInstance Create( int index );

		private:

			NuiInstance instance_;			///< �C���X�^���X

            ImageStream video_;				///< �J�����C���[�W
            ImageStream depth_;				///< �����C���[�W
            SkeletonEngine  skeleton_;		///< ���i�g���b�L���O

            int index_;						///< ����Kinect�̃C���f�b�N�X
		};
	}
}
