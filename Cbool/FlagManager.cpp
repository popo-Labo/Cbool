#include "FlagManager.h"
#include <memory>
#include <Windows.h>

CFlagManager::CFlagManager()
	: m_FlagList			()
	, m_SaveDataList		()
	, m_DeleteHandleList	()
	, m_BitNum				()
	, m_FlagNum				()
{
}

CFlagManager::~CFlagManager()
{
}

// インスタンスの取得.
CFlagManager* CFlagManager::GetInstance()
{
	static std::unique_ptr<CFlagManager> pInstance = std::make_unique<CFlagManager>();
	return pInstance.get();
}

// フラグの作成.
CFlagManager::Handle CFlagManager::CreateFlag( const std::string& Name )
{
	CFlagManager* pI = GetInstance();

	// 全てのフラグを使用しているか.
	if ( pI->m_FlagNum == std::pow( 2, sizeof( Handle ) * 8 ) - 1 ) {
		MessageBox( NULL, TEXT( "フラグの作成に失敗しました。\nHandleのサイズを大きくしてください。\n※詳しくはFlagManager.hを確認してください。" ), TEXT( "フラグの作成失敗" ), MB_OK );
		return 0;
	}

	// 削除したハンドルを再利用する.
	if ( pI->m_DeleteHandleList.size() != 0 ) {
		const Handle handle = pI->m_DeleteHandleList.back();
		pI->m_DeleteHandleList.pop_back();
		return handle;
	}

	// 新しくハンドルを作成する.
	const int Size = static_cast<int>( pI->m_FlagList.size() );
	for ( int i = 0; i < Size + 1; i++ ) {
		// 新しい配列なら作成する.
		if ( i == Size ) {
			pI->m_FlagList.push_back( 0 );
			pI->m_BitNum.push_back( 0 );
		}
		// ビット全て使用しているため次の配列を確認する.
		if ( pI->m_BitNum[i] == sizeof( pI->m_FlagList[0] ) * 8 ) continue;

		// 保存するビットの場所を保存.
		const Handle handle = pI->m_FlagNum;
		pI->m_SaveDataList[handle] = SSaveData( i, pI->m_BitNum[i], Name );

		// 保存した個数を追加.
		pI->m_BitNum[i]++;
		pI->m_FlagNum++;

		// ハンドルを返す.
		return handle;
	}
	return 0;	// 例外を返す.
}

// フラグの削除.
void CFlagManager::DeleteFlag( const Handle & handle )
{
	CFlagManager* pI = GetInstance();

	// 削除したハンドルを保存.
	pI->m_DeleteHandleList.push_back( handle );

	// 削除するビットの初期化.
	OffBitFlag( handle );
	pI->m_SaveDataList[handle].Name = "";
}

// ビットを立てる.
void CFlagManager::OnBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	pI->m_FlagList[SaveList.VectorNo] |= ( 1 << SaveList.BitNo );
}

// ビットを下ろす.
void CFlagManager::OffBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	pI->m_FlagList[SaveList.VectorNo] &= ~( 1 << SaveList.BitNo );
}

// ビットが立っているか.
bool CFlagManager::IsBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	return pI->m_FlagList[SaveList.VectorNo] & ( 1 << SaveList.BitNo );
}

// 名前の取得.
std::string CFlagManager::GetName( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	return pI->m_SaveDataList[handle].Name;
}

// 名前を設定.
void CFlagManager::SetName( const Handle& handle, const std::string & name )
{
	CFlagManager* pI = GetInstance();

	pI->m_SaveDataList[handle].Name = name;
}
