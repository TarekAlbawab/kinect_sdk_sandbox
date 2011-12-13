using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using Microsoft.Research.Kinect.Nui;
using System.Runtime.InteropServices;

namespace CameraImage
{
    // �A�v���P�[�V�����ŗL�̏������L�q
    partial class Form1
    {
        private Runtime runtime;

        // ������
        private void xnInitialize()
        {
<<<<<<< HEAD
            // ランタイムの初期化 ... (1)
            runtime = Runtime.Kinects[0];
=======
            // �����^�C���̏����� ... (1)
            runtime = new Runtime();
>>>>>>> wpf_sample
            runtime.Initialize( RuntimeOptions.UseColor );

            // �r�f�I�A�f�v�X�X�g���[���̍쐬
            runtime.VideoStream.Open( ImageStreamType.Video, 2, ImageResolution.Resolution640x480, ImageType.Color );
        }

        // �`��
        private void xnDraw()
        {
            // �r�f�I�C���[�W�̍X�V��҂��A�摜�f�[�^���擾���� ... (4)
            var video = runtime.VideoStream.GetNextFrame( 0 );
            if ( video == null ) {
                return;
            }

            // �摜�̍쐬 ... (5)
            lock ( this ) {
                // �������ݗp�̃r�b�g�}�b�v�f�[�^���쐬(32bit bitmap)
                Rectangle rect = new Rectangle( 0, 0, bitmap.Width, bitmap.Height );
                BitmapData data = bitmap.LockBits( rect, ImageLockMode.WriteOnly,
                                        System.Drawing.Imaging.PixelFormat.Format32bppRgb );
                Marshal.Copy( video.Image.Bits, 0, data.Scan0, video.Image.Bits.Length );
                bitmap.UnlockBits( data );
            }
        }

        // �L�[�C�x���g
        private void xnKeyDown( Keys key )
        {
        }
    }
}
