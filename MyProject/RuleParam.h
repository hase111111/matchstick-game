#pragma once
#include<string>

class RuleParam final
{
public:
	const static std::string WHICH_RULE;

	const static int STATE_BASIC;
	const static int STATE_MOD_5;
	const static int STATE_SLEF;
	const static int STATE_SAIHAI;
	const static int STATE_SENRYAKU;
	const static int STATE_OTHER;

private:
	//���̂���点�Ȃ�
	RuleParam() = delete;
};
