
#pragma once

#include "value.h"

class CFileStream
{
public:
	CFileStream();
	~CFileStream();

private:
	FILE*	m_pFile;
	int		m_iFileSize;
	bool	m_bOpen;

public:
	bool Open(char* pFileName, char* pMode);
	bool Close();
	void Read(void* pData, int iSize);
	// 한 줄이 몇글자인진 알수없기 때문에 사이즈를 레퍼런스 인자로 받아서 
	// 함수가 사용된 곳에 반환해준다.
	void ReadLine(void* pData, int& iSize);
	void Write(void* pData, int iSize);
	void WriteLine(void* pData, int iSize);
};