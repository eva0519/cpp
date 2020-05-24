
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
	//파일이 이미 열려서 사용하고 있다면 다시 열지 못하게 한다.
	if (m_bOpen)
		return false;

	fopen_s(&m_pFile, pFileName, pMode);

	if (!m_pFile)
		return false;

	// 파일 커서를 가장 뒤로 이동시킨다.
	// fseek 함수는 파일 커서를 원하는 위치로 이동시킬 수 있는 함수이다.
	// 3번째 인자는 3종류가 있다.
	// SEEK_SET : 파일의 제일 처음을 의미한다.
	// SEET_CUR : 현재 가리키고 있는 파일 커서의 위치를 의미한다.
	// SEEK_END : 파일의 가장 마지막을 의미한다.
	// 2번째 인자인 offset 들어가는 바이트 수만큼 3번째 인자에서 지정한
	// 위치로부터 이동하게 된다.
	fseek(m_pFile, 0, SEEK_END);

	// ftell : 파일 커서의 위치를 얻어오는 함수이다. 위에서 파일 커서를
	// 가장 마지막으로 이동시켰기 때문에 ftell 을 이용해서 파일 커서의
	// 위치를 얻어오면 곧 파일 크기가 된다.
	m_iFileSize = ftell(m_pFile);

	// 파일 크기를 구한 후에 가장 앞으로 다시 이동시켜준다.
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
	// 파일이 열려있지 않은 상태라면 읽고 쓰기를 할 수 없다.
	if (!m_bOpen)
		return;

	fread(pData, iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* pData, int& iSize)
{
	if (!m_bOpen)
		return;

	// 1바이트(하나)씩 읽어올 변수
	char	cData;
	// void 포인터를 인자로 받기 때문에 역참조가 불가능하니 우회해서 넣어준다.
	// 형변환한 인자로 받은 데이터의 주소를 포인터로 가리키고 있기 때문에
	// 포인터변수 선언한 pChangeData 안에 데이터를 넣는다는건 
	// 즉 인자로 받은 데이터의 value(값)에 넣는다는 것이다.
	char* pChangeData = (char*)pData;
	// 1바이트씩 카운트하면서 인덱스로 사용할 변수
	iSize = 0;

	// feof 함수. end of file.
	// feof 함수는 파일 커서가 파일의 끝에 도달했는지를 체크한다.
	// 파일의 끝에 도달하지 않았을 경우 0을 리턴하고 끝일 경우
	// 0이 아닌 수를 리턴한다.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);

		if (cData == '\n')
			break;
		// 엔터를 만나면 굿바이
		// 단, 이런식으로 처리하려면 파일문서끝에 무조건 엔터를 넣어줘야 한다.
		// 그렇지 않으면 stage.cpp에서 마지막줄 마지막 배열 인덱스를
		// 대입하는 와중에 feof함수로 파일의 끝까지 읽어들이는 것은 이미 끝난 것이
		// 되므로 메모리 배열을 벗어나게 된다.

		pChangeData[iSize] = cData;
		// 1바이트 넣고 돌고 1바이트 넣고 돌고
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
	//위 두 식은 같다. 포인터연산이다.
	//pBuffer는 문자열 배열이고 구해놓은 iSize는 한 줄의 크기이므로
	//문자열 1바이트 크기 x iSize를 첫배열주소에서 더해준 것으로.
	//한줄의 끝에 주소를 역참조해서 \n value를 넣어준다는 뜻이다

	fwrite(pData, iSize + 1, 1, m_pFile);

	delete[]	pBuffer;
}
