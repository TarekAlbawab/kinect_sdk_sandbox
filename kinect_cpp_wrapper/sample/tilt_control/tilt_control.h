
// tilt_control.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// Ctilt_controlApp:
// ���̃N���X�̎����ɂ��ẮAtilt_control.cpp ���Q�Ƃ��Ă��������B
//

class Ctilt_controlApp : public CWinApp
{
public:
	Ctilt_controlApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern Ctilt_controlApp theApp;