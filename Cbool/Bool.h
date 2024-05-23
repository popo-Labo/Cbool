#pragma once
#include <string>
#include "FlagManager.h"

/************************************************
* @file		Bool.h.
* @brief	�I���W�i��bool�N���X.
* @author	��c�F�P.
**/
class CBool final
{
public:
	void operator=( const bool Flag );
	void operator=( const char* sFlag );
	void operator=( const int iFlag );
	bool operator==( const bool Flag );

public:
	CBool( bool Flag = false, std::string Name = "" );
	~CBool();

	// bool�̏�Ԃ𕶎���Ŏ擾.
	inline std::string ToString() {
		return CFlagManager::IsBitFlag( m_Handle ) == true ? "true" : "false";
	};

	// bool�^�Ŏ擾.
	inline bool Get() {
		return CFlagManager::IsBitFlag( m_Handle );
	}

	// ���O���擾.
	inline std::string GetName() {
		return CFlagManager::GetName( m_Handle );
	};
	// ���O�̐ݒ�.
	inline void SetName( std::string Name ) {
		CFlagManager::SetName( m_Handle, Name );
	};

private:
	CFlagManager::Handle m_Handle; // �n���h��.
};
