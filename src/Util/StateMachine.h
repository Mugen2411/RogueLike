//! @file StateMachine.h
//! @note Copyright (c) Mugen_GameLab

#ifndef __MagicaRogue_StateMachine__
#define __MagicaRogue_StateMachine__

#include <unordered_map>

namespace magica_rogue
{
	/**********************************************************************//**
		@class		MRStateMachine
		@brief		ステートマシンを表現するクラス
	*//***********************************************************************/
	template<class T>
	class MRStateMachine
	{
	public:
		/**********************************************************************//**
			@brief			更新関数を追加する
			@param[in]		This					関数を実行する主体
			@return			なし
		*//***********************************************************************/
		MRStateMachine(T* This):m_pThis(This), m_frameOnState(0){}

		/**********************************************************************//**
			@brief			関数を追加する
			@param[in]		state				ステート
			@param[in]		updateFunc			更新関数ポインタ
			@param[in]		renderFunc			描画関数ポインタ
			@return			なし
		*//***********************************************************************/
		void Register(int state, void (T::* updateFunc)(void), void (T::* renderFunc)(void)const) {
			m_updateList[state] = updateFunc;
			m_renderList[state] = renderFunc;
		}

		/**********************************************************************//**
			@brief			更新
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Update() 
		{
			(m_pThis->*(m_updateList[m_aliveState]))();
			++m_frameOnState;
		}

		/**********************************************************************//**
			@brief			描画
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Render()const
		{
			(m_pThis->*(m_renderList.at(m_aliveState)))();
		}

		/**********************************************************************//**
			@brief			ステートの遷移
			@param[in]			state			遷移先のステート
			@return			なし
		*//***********************************************************************/
		void ChangeState(const int state) 
		{
			m_frameOnState = 0;
			m_prevState = m_aliveState;
			m_aliveState = state;
		}

		/**********************************************************************//**
			@brief			前のステートへ戻る
			@param			なし
			@return			なし
		*//***********************************************************************/
		void RestoreState()
		{
			int tmp = m_aliveState;
			m_aliveState = m_prevState;
			m_prevState = tmp;
		}
		/**********************************************************************//**
			@brief			ステートの取得
			@param			なし
			@return			ステート
		*//***********************************************************************/
		int GetState() const
		{
			return m_aliveState;
		}

		/**********************************************************************//**
			@brief			前のステートの取得
			@param			なし
			@return			前のステート
		*//***********************************************************************/
		int GetPrevState() const
		{
			return m_prevState;
		}

		/**********************************************************************//**
			@brief			経過フレームの取得
			@param			なし
			@return			経過フレーム
		*//***********************************************************************/
		int GetFrame() const
		{
			return m_frameOnState;
		}
	private:
		int m_aliveState;												//!< ステート
		int m_prevState;												//!< 前のステート
		T* m_pThis;														//!< 自身のポインタ
		int m_frameOnState;												//!< ステートの経過フレーム
		std::unordered_map<int, void (T::*)(void)> m_updateList;		//!< 更新関数のリスト
		std::unordered_map<int, void (T::*)(void)const> m_renderList;	//!< 描画関数のリスト
	};
}

#endif//__MagicaRogue_StateMachine__