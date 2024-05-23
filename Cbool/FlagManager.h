#pragma once
#include <string>
#include <unordered_map>

/************************************************
* @file		FlagManager.h.
* @brief	�t���O�}�l�[�W���[�N���X.
* @author	��c�F�P.
**/
class CFlagManager final
{
public:
	// �n���h��.
	//	�t���O�̍쐬�����s�����ꍇ�� "std::uint�Z�Z_t" �̐����𑝂₵�Ă�������.
	//	�g����t���O�̐��͈ȉ��̒ʂ�ł�.
	//	 | uint8_t	= 255��.
	//	 | uint16_t	= 65,535��.
	//	 | uint32_t	= 4,294,967,295��.
	//	 | uint64_t	= 18,446,744,073,709,551,615��.
	using Handle = std::uint16_t;

private:
	// �ۑ��f�[�^�\����.
	struct stSaveData {
		int			VectorNo;	// �z��̕ۑ��ꏊ.
		int			BitNo;		// �r�b�g�̕ۑ��ꏊ.
		std::string	Name;		// ���O.

		stSaveData()
			: stSaveData( 0, 0, "" )
		{}
		stSaveData( const int vNo, const int bNo, const std::string& name )
			: VectorNo	( vNo )
			, BitNo		( bNo )
			, Name		( name )
		{}
	} typedef SSaveData;

	// �ۑ��f�[�^�̃}�b�v.
	using DataSave_map		= std::unordered_map<Handle, SSaveData>;

public:
	CFlagManager();
	~CFlagManager();

	// �C���X�^���X�̎擾.
	static CFlagManager* GetInstance();

	// �t���O�̍쐬.
	//	���O�̎��ʔԍ���Ԃ�.
	//	�쐬�ł��Ȃ������ꍇ�� "0" ��Ԃ�.
	static Handle CreateFlag( const std::string& Name );
	// �t���O�̍폜.
	static void DeleteFlag( const Handle& handle );

	// �r�b�g�𗧂Ă�.
	static void OnBitFlag( const Handle& handle );
	// �r�b�g�����낷.
	static void OffBitFlag( const Handle& handle );
	// �r�b�g�������Ă��邩.
	static bool IsBitFlag( const Handle& handle );

	// ���O�̎擾.
	static std::string GetName( const Handle& handle );
	// ���O��ݒ�.
	static void SetName( const Handle& handle, const std::string& name );

private:
	std::vector<std::uint32_t>	m_FlagList;			// �t���O���X�g.
	DataSave_map				m_SaveDataList;		// �ۑ��f�[�^���X�g.
	std::vector<Handle>			m_DeleteHandleList;	// �폜���Ďg�p���Ă��Ȃ��n���h�����X�g.
	std::vector<unsigned int>	m_BitNum;			// �r�b�g�̕ۑ���.
	Handle						m_FlagNum;			// �ۑ������t���O��.
};
