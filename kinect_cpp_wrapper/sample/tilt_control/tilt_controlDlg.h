
// tilt_controlDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxcmn.h"


// Ctilt_controlDlg �_�C�A���O
class Ctilt_controlDlg : public CDialogEx
{
// �R���X�g���N�V����
public:
	Ctilt_controlDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^�[

// �_�C�A���O �f�[�^
	enum { IDD = IDD_TILT_CONTROL_DIALOG };

    enum {
        TIMER_ANGLE,
        TIMER_UPDATE,
    };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

private:

    kinect::nui::Kinect kinect_;

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CSliderCtrl m_sliderTilt;
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    int m_angle;
};
