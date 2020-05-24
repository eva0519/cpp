
#include "FileStream.h"



CFileStream::CFileStream():
	m_pFile(NULL),
	m_iFileSize(0),
	m_bOpen(false)
{
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(char* pFileName, char* pMode)
{
	//������ �̹� ������ ����ϰ� �ִٸ� �ٽ� ���� ���ϰ� �Ѵ�.
	if (m_bOpen)
		return false;

	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	// ���� Ŀ���� ���� �ڷ� �̵���Ų��.
	// fseek �Լ��� ���� Ŀ���� ���ϴ� ��ġ�� �̵���ų �� �ִ� �Լ��̴�.
	// 3��° ���ڴ� 3������ �ִ�.
	// SEEK_SET : ������ ���� ó���� �ǹ��Ѵ�.
	// SEET_CUR : ���� ����Ű�� �ִ� ���� Ŀ���� ��ġ�� �ǹ��Ѵ�.
	// SEEK_END : ������ ���� �������� �ǹ��Ѵ�.
	// 2��° ������ offset ���� ����Ʈ ����ŭ 3��° ���ڿ��� ������
	// ��ġ�κ��� �̵��ϰ� �ȴ�.
	fseek(m_pFile, 0, SEEK_END);

	// ftell : ���� Ŀ���� ��ġ�� ������ �Լ��̴�. ������ ���� Ŀ����
	// ���� ���������� �̵����ױ� ������ ftell �� �̿��ؼ� ���� Ŀ����
	// ��ġ�� ������ �� ���� ũ�Ⱑ �ȴ�.
	m_iFileSize = ftell(m_pFile);

	// ���� ũ�⸦ ���� �Ŀ� ���� ������ �ٽ� �̵������ش�.
	fseek(m_pFile, 0, SEEK_SET);

	m_bOpen = true;

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen)
		return false;

	m_bOpen = false;
	fclose(m_pFile);
	m_pFile = NULL;
	m_iFileSize = 0;

	return true;
}

void CFileStream::Read(void* pData, int iSize)
{
	// ������ �������� ���� ���¶�� �а� ���⸦ �� �� ����.
	if (!m_bOpen)
		return;

	fread(pData, iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* pData, int& iSize)
{
	if (!m_bOpen)
		return;

	// 1����Ʈ(�ϳ�)�� �о�� ����
	char	cData;
	// void �����͸� ���ڷ� �ޱ� ������ �������� �Ұ����ϴ� ��ȸ�ؼ� �־��ش�.
	// ����ȯ�� ���ڷ� ���� �������� �ּҸ� �����ͷ� ����Ű�� �ֱ� ������
	// �����ͺ��� ������ pChangeData �ȿ� �����͸� �ִ´ٴ°� 
	// �� ���ڷ� ���� �������� value(��)�� �ִ´ٴ� ���̴�.
	char* pChangeData = (char*)pData;
	// 1����Ʈ�� ī��Ʈ�ϸ鼭 �ε����� ����� ����
	iSize = 0;

	// feof �Լ�. end of file.
	// feof �Լ��� ���� Ŀ���� ������ ���� �����ߴ����� üũ�Ѵ�.
	// ������ ���� �������� �ʾ��� ��� 0�� �����ϰ� ���� ���
	// 0�� �ƴ� ���� �����Ѵ�.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);

		if (cData == '\n')
			break;
		// ���͸� ������ �¹���
		// ��, �̷������� ó���Ϸ��� ���Ϲ������� ������ ���͸� �־���� �Ѵ�.
		// �׷��� ������ stage.cpp���� �������� ������ �迭 �ε�����
		// �����ϴ� ���߿� feof�Լ��� ������ ������ �о���̴� ���� �̹� ���� ����
		// �ǹǷ� �޸� �迭�� ����� �ȴ�.

		pChangeData[iSize] = cData;
		// 1����Ʈ �ְ� ���� 1����Ʈ �ְ� ����
		++iSize;
	}
}

void CFileStream::Write(void* pData, int iSize)
{
	if (!m_bOpen)
		return;

	fwrite(pData, iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* pData, int iSize)
{
	if (!m_bOpen)
		return;

	char* pBuffer = new char[iSize + 1];

	*(pBuffer + iSize) = '\n';
	//pBuffer[iSize] = '\n';
	//�� �� ���� ����. �����Ϳ����̴�.
	//pBuffer�� ���ڿ� �迭�̰� ���س��� iSize�� �� ���� ũ���̹Ƿ�
	//���ڿ� 1����Ʈ ũ�� x iSize�� ù�迭�ּҿ��� ������ ������.
	//������ ���� �ּҸ� �������ؼ� \n value�� �־��شٴ� ���̴�

	fwrite(pData, iSize + 1, 1, m_pFile);

	delete[]	pBuffer;
}
