#include "stdafx.h"

#include "Str.h"
#include "XMLParser.h"

#include "Generator.h"

#include <algorithm>

Generator::Generator()
{
	srand(NULL);
}

Generator::~Generator()
{

}

bool Generator::Load()
{
	std::wstring file_name = _T(".\\Data\\Name.xml");
	light::XMLParser reader;
	if( false == reader.read_file(file_name))
		return false;

	if( false == reader.execute(_T("/List")) )
		return false;

	if( false == reader.bind_elem(_T("Info")) )
		return false;

	std::wstring Name;
	if( false == reader.bind_attrib(_T("Name"), Name) )
		return false;

	while( reader.next() )
	{	
		m_Name.push_back(Name);

		for(std::wstring::iterator it = Name.begin(); it != Name.end(); ++it)
		{
			size_t at = it - Name.begin();
			if(m_Character.size() < at + 1)
			{
				m_Character.resize(at + 1);
			}

			std::vector<WCHAR>::iterator vector_Character_It =  find(m_Character[at].begin(), m_Character[at].end(), *it);
			if(m_Character[at].end() == vector_Character_It)
			{
				m_Character[at].push_back(*it);
			}
		}
	}
	return true;
}

std::wstring Generator::Generate(GENERATE_CONDITION condition)
{
	if(condition == GENERATECONDITION_NONE)
		return m_Name[rand() % m_Name.size()];

	std::wstring strName;	
	for(unsigned int i = 0; i < m_Character.size(); ++i)
	{
		std::vector<WCHAR>& _vector_Character = m_Character[GetInsertCharacterPosition(i, condition)];

		WCHAR ch = _vector_Character[rand() % _vector_Character.size()];

		strName += ch;
	}
	return strName;
}

std::wstring Generator::GenerateRemoveLastestUsed(GENERATE_CONDITION condition)
{
	if(condition == GENERATECONDITION_NONE)
		return m_Name[rand() % m_Name.size()];

	static std::vector< std::vector<WCHAR> > vector_LastestUsedCharacter(m_Character.size()); //다른 함수에서 접근 불가능하게 하기 위해 static 멤버 변수로 선언.

	std::wstring strName;	
	for(unsigned int i = 0; i < m_Character.size(); ++i)
	{
		std::vector<WCHAR>& _vector_Character = m_Character[GetInsertCharacterPosition(i, condition)];
		WCHAR ch;
		do
		{
			ch = _vector_Character[rand() % _vector_Character.size()];
		}
		while(vector_LastestUsedCharacter[i].end() != find(vector_LastestUsedCharacter[i].begin(), vector_LastestUsedCharacter[i].end(), ch));

		vector_LastestUsedCharacter[i].push_back(ch);

		if(4 <= vector_LastestUsedCharacter[i].size())
		{
			vector_LastestUsedCharacter[i].erase(vector_LastestUsedCharacter[i].begin());
		}

		strName += ch;
	}
	return strName;
}

size_t Generator::GetInsertCharacterPosition(unsigned int i, GENERATE_CONDITION Condition)
{
	if(Condition == GENERATECONDITION_1)
		return rand() % m_Character.size();
	else if(Condition == GENERATECONDITION_2)
		return i == 0 ? 0 : rand() % i + 1;
	else if(Condition == GENERATECONDITION_3)
		return i;

	return 0;
}
