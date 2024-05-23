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

// �C���X�^���X�̎擾.
CFlagManager* CFlagManager::GetInstance()
{
	static std::unique_ptr<CFlagManager> pInstance = std::make_unique<CFlagManager>();
	return pInstance.get();
}

// �t���O�̍쐬.
CFlagManager::Handle CFlagManager::CreateFlag( const std::string& Name )
{
	CFlagManager* pI = GetInstance();

	// �S�Ẵt���O���g�p���Ă��邩.
	if ( pI->m_FlagNum == std::pow( 2, sizeof( Handle ) * 8 ) - 1 ) {
		MessageBox( NULL, TEXT( "�t���O�̍쐬�Ɏ��s���܂����B\nHandle�̃T�C�Y��傫�����Ă��������B\n���ڂ�����FlagManager.h���m�F���Ă��������B" ), TEXT( "�t���O�̍쐬���s" ), MB_OK );
		return 0;
	}

	// �폜�����n���h�����ė��p����.
	if ( pI->m_DeleteHandleList.size() != 0 ) {
		const Handle handle = pI->m_DeleteHandleList.back();
		pI->m_DeleteHandleList.pop_back();
		return handle;
	}

	// �V�����n���h�����쐬����.
	const int Size = static_cast<int>( pI->m_FlagList.size() );
	for ( int i = 0; i < Size + 1; i++ ) {
		// �V�����z��Ȃ�쐬����.
		if ( i == Size ) {
			pI->m_FlagList.push_back( 0 );
			pI->m_BitNum.push_back( 0 );
		}
		// �r�b�g�S�Ďg�p���Ă��邽�ߎ��̔z����m�F����.
		if ( pI->m_BitNum[i] == sizeof( pI->m_FlagList[0] ) * 8 ) continue;

		// �ۑ�����r�b�g�̏ꏊ��ۑ�.
		const Handle handle = pI->m_FlagNum;
		pI->m_SaveDataList[handle] = SSaveData( i, pI->m_BitNum[i], Name );

		// �ۑ���������ǉ�.
		pI->m_BitNum[i]++;
		pI->m_FlagNum++;

		// �n���h����Ԃ�.
		return handle;
	}
	return 0;	// ��O��Ԃ�.
}

// �t���O�̍폜.
void CFlagManager::DeleteFlag( const Handle & handle )
{
	CFlagManager* pI = GetInstance();

	// �폜�����n���h����ۑ�.
	pI->m_DeleteHandleList.push_back( handle );

	// �폜����r�b�g�̏�����.
	OffBitFlag( handle );
	pI->m_SaveDataList[handle].Name = "";
}

// �r�b�g�𗧂Ă�.
void CFlagManager::OnBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	pI->m_FlagList[SaveList.VectorNo] |= ( 1 << SaveList.BitNo );
}

// �r�b�g�����낷.
void CFlagManager::OffBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	pI->m_FlagList[SaveList.VectorNo] &= ~( 1 << SaveList.BitNo );
}

// �r�b�g�������Ă��邩.
bool CFlagManager::IsBitFlag( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	const SSaveData& SaveList = pI->m_SaveDataList[handle];
	return pI->m_FlagList[SaveList.VectorNo] & ( 1 << SaveList.BitNo );
}

// ���O�̎擾.
std::string CFlagManager::GetName( const Handle& handle )
{
	CFlagManager* pI = GetInstance();

	return pI->m_SaveDataList[handle].Name;
}

// ���O��ݒ�.
void CFlagManager::SetName( const Handle& handle, const std::string & name )
{
	CFlagManager* pI = GetInstance();

	pI->m_SaveDataList[handle].Name = name;
}