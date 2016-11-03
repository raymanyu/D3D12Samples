﻿//-------------------------------------------------------------------------------------------------
// File : asdxTarget.h
// Desc : Render Target Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <asdxDevice.h>


namespace asdx {

///////////////////////////////////////////////////////////////////////////////////////////////////
// ColorTarget class
///////////////////////////////////////////////////////////////////////////////////////////////////
class ColorTarget : NonCopyable
{
    //=============================================================================================
    // list of friend classes and methods.
    //=============================================================================================
    /* NOTHING */

public:
    //=============================================================================================
    // public variables.
    //=============================================================================================
    /* NOTHING */

    //=============================================================================================
    // public methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    ColorTarget();

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~ColorTarget();

    //---------------------------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      device      デバイスです.
    //! @param[in]      width       横幅です.
    //! @param[in]      height      縦幅です.
    //! @param[in]      format      フォーマットです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //---------------------------------------------------------------------------------------------
    bool Init( Device& device, u32 width, u32 height, DXGI_FORMAT format );

    //---------------------------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      device      デバイスです.
    //! @param[in]      pSwapChain  スワップチェインです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //---------------------------------------------------------------------------------------------
    bool Init( Device& device, IDXGISwapChain* pSwapChain, u32 backBufferIndex );

    //---------------------------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //---------------------------------------------------------------------------------------------
    void Term();

    //---------------------------------------------------------------------------------------------
    //! @brief      リソースを取得します.
    //---------------------------------------------------------------------------------------------
    ID3D12Resource* GetResource() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      レンダーターゲットビューを取得します.
    //---------------------------------------------------------------------------------------------
    const DescHandle& GetRTV() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      シェーダリソースビューを取得します.
    //---------------------------------------------------------------------------------------------
    const DescHandle& GetSRV() const;

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    RefPtr<ID3D12Resource>  m_Resource;     //!< リソースです.
    DescHandle              m_RTV;          //!< レンダーターゲットビューです.
    DescHandle              m_SRV;          //!< シェーダリソースビューです.

    //=============================================================================================
    // private methods.
    //=============================================================================================
    /* NOTHING */
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// DepthTarget class
///////////////////////////////////////////////////////////////////////////////////////////////////
class DepthTarget : NonCopyable
{
    //=============================================================================================
    // list of friend classes and methods.
    //=============================================================================================
    /* NOTHING */

public:
    //=============================================================================================
    // public variables.
    //=============================================================================================
    /* NOTHING */

    //=============================================================================================
    // public methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    DepthTarget();

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~DepthTarget();

    //---------------------------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //!
    //! @param[in]      device      デバイスです.
    //! @param[in]      width       横幅です.
    //! @param[in]      height      縦幅です.
    //! @param[in]      format      フォーマットです.
    //! @retval true    初期化に成功.
    //! @retval false   初期化に失敗.
    //---------------------------------------------------------------------------------------------
    bool Init( Device& device, u32 width, u32 height, DXGI_FORMAT format );

    //---------------------------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //---------------------------------------------------------------------------------------------
    void Term();

    //---------------------------------------------------------------------------------------------
    //! @brief      リソースを取得します.
    //---------------------------------------------------------------------------------------------
    ID3D12Resource* GetResource() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      深度ステンシルビューを取得します.
    //---------------------------------------------------------------------------------------------
    const DescHandle& GetDSV() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      シェーダリソースビューを取得します.
    //---------------------------------------------------------------------------------------------
    const DescHandle& GetSRV() const;

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    RefPtr<ID3D12Resource>  m_Resource;     //!< リソースです.
    DescHandle              m_DSV;          //!< 深度ステンシルビューです.
    DescHandle              m_SRV;          //!< シェーダリソースビューです.

    //=============================================================================================
    // private metods.
    //=============================================================================================
    /* NOTHING */
};

} // namespace asdx