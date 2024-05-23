#pragma once
#include <string>
#include "FlagManager.h"

/************************************************
* @file		Bool.h.
* @brief	オリジナルboolクラス.
* @author	崎田友輝.
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

	// boolの状態を文字列で取得.
	inline std::string ToString() {
		return CFlagManager::IsBitFlag( m_Handle ) == true ? "true" : "false";
	};

	// bool型で取得.
	inline bool Get() {
		return CFlagManager::IsBitFlag( m_Handle );
	}

	// 名前を取得.
	inline std::string GetName() {
		return CFlagManager::GetName( m_Handle );
	};
	// 名前の設定.
	inline void SetName( std::string Name ) {
		CFlagManager::SetName( m_Handle, Name );
	};

private:
	CFlagManager::Handle m_Handle; // ハンドル.
};
