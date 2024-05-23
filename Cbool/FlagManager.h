#pragma once
#include <string>
#include <unordered_map>

/************************************************
* @file		FlagManager.h.
* @brief	フラグマネージャークラス.
* @author	崎田友輝.
**/
class CFlagManager final
{
public:
	// ハンドル.
	//	フラグの作成を失敗した場合は "std::uint〇〇_t" の数字を増やしてください.
	//	使えるフラグの数は以下の通りです.
	//	 | uint8_t	= 255個.
	//	 | uint16_t	= 65,535個.
	//	 | uint32_t	= 4,294,967,295個.
	//	 | uint64_t	= 18,446,744,073,709,551,615個.
	using Handle = std::uint16_t;

private:
	// 保存データ構造体.
	struct stSaveData {
		int			VectorNo;	// 配列の保存場所.
		int			BitNo;		// ビットの保存場所.
		std::string	Name;		// 名前.

		stSaveData()
			: stSaveData( 0, 0, "" )
		{}
		stSaveData( const int vNo, const int bNo, const std::string& name )
			: VectorNo	( vNo )
			, BitNo		( bNo )
			, Name		( name )
		{}
	} typedef SSaveData;

	// 保存データのマップ.
	using DataSave_map		= std::unordered_map<Handle, SSaveData>;

public:
	CFlagManager();
	~CFlagManager();

	// インスタンスの取得.
	static CFlagManager* GetInstance();

	// フラグの作成.
	//	名前の識別番号を返す.
	//	作成できなかった場合は "0" を返す.
	static Handle CreateFlag( const std::string& Name );
	// フラグの削除.
	static void DeleteFlag( const Handle& handle );

	// ビットを立てる.
	static void OnBitFlag( const Handle& handle );
	// ビットを下ろす.
	static void OffBitFlag( const Handle& handle );
	// ビットが立っているか.
	static bool IsBitFlag( const Handle& handle );

	// 名前の取得.
	static std::string GetName( const Handle& handle );
	// 名前を設定.
	static void SetName( const Handle& handle, const std::string& name );

private:
	std::vector<std::uint32_t>	m_FlagList;			// フラグリスト.
	DataSave_map				m_SaveDataList;		// 保存データリスト.
	std::vector<Handle>			m_DeleteHandleList;	// 削除して使用していないハンドルリスト.
	std::vector<unsigned int>	m_BitNum;			// ビットの保存個数.
	Handle						m_FlagNum;			// 保存したフラグ個数.
};
