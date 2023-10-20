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
		MRStateMachine(T* This):m_pThis(This){}

		/**********************************************************************//**
			@brief			更新関数を追加する
			@param[in]		ID					ステートと対応するID
			@param[in]		func				更新関数ポインタ
			@return			なし
		*//***********************************************************************/
		void UpdateRegister(int state, void (T::* func)(void)) {
			m_updateList[state] = func;
		}

		/**********************************************************************//**
			@brief			描画関数を追加する
			@param[in]		ID					ステートと対応するID
			@param[in]		func				更新関数ポインタ
			@return			なし
		*//***********************************************************************/
		void RenderRegister(int state, void (T::* func)(void)const) {
			m_renderList[state] = func;
		}

		/**********************************************************************//**
			@brief			更新
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Update() 
		{
			(m_pThis->*(m_updateList[m_state]))();
		}

		/**********************************************************************//**
			@brief			描画
			@param			なし
			@return			なし
		*//***********************************************************************/
		void Render()const
		{
			(m_pThis->*(m_renderList.at(m_state)))();
		}

		/**********************************************************************//**
			@brief			ステートの遷移
			@param[in]			state			遷移先のステート
			@return			なし
		*//***********************************************************************/
		void ChangeState(const int state) 
		{
			m_state = state;
		}
	private:
		int m_state;													//!< ステート
		T* m_pThis;														//!< 自身のポインタ
		std::unordered_map<int, void (T::*)(void)> m_updateList;
		std::unordered_map<int, void (T::*)(void)const> m_renderList;
	};
}

#endif//__MagicaRogue_StateMachine__