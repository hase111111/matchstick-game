#include"Looper.h"
#include"Keyboard.h"

Looper::Looper()
{
}

bool Looper::loop()
{
	//���͂��擾
	Keyboard::getIns()->update();

	//�V�[���̃X�^�b�N�̈�ԏ�����s
	if (m_sceneMgr.updateTopScene() == false) { return false; }
	m_sceneMgr.drawTopScene();

	//fps�𐧌䂷�邽�߂̊֐�
	m_fps.wait();
	//m_fps.draw();

	//�S�����̐��s��,�V�[���`�F���W���s��
	m_sceneMgr.sceneChangeExecute();

	return true;
}
