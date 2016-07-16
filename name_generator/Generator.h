#pragma once

#include <vector>

enum GENERATE_CONDITION
{
	GENERATECONDITION_NONE = 0,
	GENERATECONDITION_1,
	GENERATECONDITION_2,
	GENERATECONDITION_3,
};

class Generator
{
public:
	Generator();

	~Generator();

	bool Load();

	std::wstring Generate(GENERATE_CONDITION condition);
	
	std::wstring GenerateRemoveLastestUsed(GENERATE_CONDITION condition);

	size_t GetInsertCharacterPosition(unsigned int i, GENERATE_CONDITION condition);

private:
	std::vector< std::vector<WCHAR> > m_Character;
		
	std::vector<std::wstring> m_Name;
};
