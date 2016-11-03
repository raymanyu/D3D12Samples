﻿//-------------------------------------------------------------------------------------------------
// File : asdxDevice.h
// Desc : Device Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <asdxRef.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <asdxDescHeap.h>


namespace asdx {

///////////////////////////////////////////////////////////////////////////////////////////////////
// DESCRIPTOR_COUNT structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct DESCRIPTOR_COUNT
{
    u32 Buffer;     //!< バッファ(CBV, SRV, UAV) の数です.
    u32 Sampler;    //!< サンプラーの数です.
    u32 RTV;        //!< レンダーターゲットビューの数です.
    u32 DSV;        //!< 深度ステンシルビューの数です.

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    DESCRIPTOR_COUNT()
    : Buffer ( 0 )
    , Sampler( 0 )
    , RTV    ( 0 )
    , DSV    ( 0 )
    { /* DO_NOTHING */ }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// DEVICE_DESC structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct DEVICE_DESC
{
    D3D_FEATURE_LEVEL   FeatureLevel;   //!< 機能レベルです.
    DESCRIPTOR_COUNT    CountDesc;      //!< ディスクリプター数の設定です.

    //---------------------------------------------------------------------------------------------
    //! @brief      コンストラクタです.
    //---------------------------------------------------------------------------------------------
    DEVICE_DESC()
    : FeatureLevel( D3D_FEATURE_LEVEL_11_0 )
    {
        CountDesc.Buffer  = 0;
        CountDesc.Sampler = 0;
        CountDesc.RTV     = 0;
        CountDesc.DSV     = 0;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// Device class
///////////////////////////////////////////////////////////////////////////////////////////////////
class Device : NonCopyable
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
    Device();

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    ~Device();

    //---------------------------------------------------------------------------------------------
    //! @brief      初期化処理を行います.
    //---------------------------------------------------------------------------------------------
    bool Init( DEVICE_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      終了処理を行います.
    //---------------------------------------------------------------------------------------------
    void Term();

    //---------------------------------------------------------------------------------------------
    //! @brief      デバイスを取得します.
    //---------------------------------------------------------------------------------------------
    ID3D12Device* GetDevice() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      ファクトリを取得します.
    //---------------------------------------------------------------------------------------------
    IDXGIFactory4* GetFactory() const;

    //---------------------------------------------------------------------------------------------
    //! @brief      スワップチェインを生成します.
    //---------------------------------------------------------------------------------------------
    bool CreateSwapChain( 
        ID3D12CommandQueue*     pQueue,
        DXGI_SWAP_CHAIN_DESC*   pDesc,
        IDXGISwapChain3**       ppSwapChain );

    //---------------------------------------------------------------------------------------------
    //! @brief      定数バッファビューを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateCBV( D3D12_CONSTANT_BUFFER_VIEW_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      シェーダリソースビューを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateSRV( ID3D12Resource* pResource, D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      アンオーダードアクセスビューを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateUAV( 
        ID3D12Resource*                   pResource,
        ID3D12Resource*                   pCounterResource, 
        D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      サンプラーを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateSmp( D3D12_SAMPLER_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      深度ステンシルビューを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateDSV( ID3D12Resource* pResource, D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      レンダーターゲットビューを生成します.
    //---------------------------------------------------------------------------------------------
    DescHandle CreateRTV( ID3D12Resource* pResource, D3D12_RENDER_TARGET_VIEW_DESC* pDesc );

    //---------------------------------------------------------------------------------------------
    //! @brief      アロー演算子です.
    //---------------------------------------------------------------------------------------------
    ID3D12Device* operator -> () const;

    //---------------------------------------------------------------------------------------------
    //! @brief      ディスクリプタヒープ設定コマンドを生成します.
    //---------------------------------------------------------------------------------------------
    void MakeSetDescHeapCmd( ID3D12GraphicsCommandList* pCmd );

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    RefPtr<ID3D12Device>    m_Device;
    RefPtr<IDXGIFactory4>   m_Factory;
    DESCRIPTOR_COUNT        m_OffsetCount;
    DescHeap                m_HeapBuffer;
    DescHeap                m_HeapSmp;
    DescHeap                m_HeapRTV;
    DescHeap                m_HeapDSV;

    //=============================================================================================
    // private methods.
    //=============================================================================================
    /* NOTHING */
};

} // namespace asdx