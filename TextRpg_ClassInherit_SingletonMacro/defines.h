
#pragma once

// 매크로 기능은 반드시 한줄에 정의가 되어야 한다.
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p) if (p) { delete[] p; p = NULL; }

// 싱글톤 매크로
// 끝에 \를 붙이면 한줄로 인식한다. 마지막에는 붙이지않는다.
// 아래 부분이 그대로 인자를 받은 부분만 변경되어 사용된 코드에 가서 붙는다.
#define DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_pInst;\
public:\
	static Type* GetInst()\
	{\
		if(!m_pInst)\
		m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:\
	Type();\
	~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_pInst = NULL;

#define GET_SINGLE(Type)	Type::GetInst()
#define DESTROY_SINGLE(Type)	Type::DestroyInst()

// ; 주의