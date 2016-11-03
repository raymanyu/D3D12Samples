﻿//-------------------------------------------------------------------------------------------------
// File : asdxResMTN.h
// Desc : Project Asura Motion Data Loader.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <asdxResMotion.h>


namespace asdx {

//-------------------------------------------------------------------------------------------------
//! @brief      MTNファイルからモーションリソースを読込します.
//!
//! @param[in]      filename        ファイル名です.
//! @param[out]     pResult         リソースモーションの格納先です.
//! @retval true    読込に成功.
//! @retval false   読込に失敗.
//-------------------------------------------------------------------------------------------------
bool LoadResMotionFromMTN( const char16* filename, ResMotion* pResult );

//-------------------------------------------------------------------------------------------------
//! @brief      モーションリソースをMTNファイルに保存します.
//!
//! @param[in]      filename        ファイル名です.
//! @param[in]      pMotion         ファイルに保存するリソースモーションです.
//! @retval true    保存に成功.
//! @retval false   保存に失敗.
//-------------------------------------------------------------------------------------------------
bool SaveResMotionToMTN( const char16* filename, const ResMotion* pMotion );


} // namespace asdx