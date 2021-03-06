﻿//-------------------------------------------------------------------------------------------------
// File : asdxRef.h
// Desc : Reference Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <asdxTypedef.h>


namespace asdx {

///////////////////////////////////////////////////////////////////////////////////////////////////
// IReference interface
///////////////////////////////////////////////////////////////////////////////////////////////////
struct IReference
{
    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~IReference()
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを1つ増やします.
    //---------------------------------------------------------------------------------------------
    virtual void AddRef() const = 0;

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを1つ減らします.
    //---------------------------------------------------------------------------------------------
    virtual void Release() const = 0;

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを取得します.
    //!
    //! @return     参照カウントを返却します.
    //---------------------------------------------------------------------------------------------
    virtual s32 GetCount() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// RefBase class
///////////////////////////////////////////////////////////////////////////////////////////////////
class RefBase
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
    RefBase()
    : m_Count(0)
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    virtual ~RefBase()
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを１つ増やします.
    //---------------------------------------------------------------------------------------------
    void AddRef() const
    { ++m_Count; }

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを１つ減らします.
    //---------------------------------------------------------------------------------------------
    void Release() const
    {
        auto count = --m_Count;
        if (count == 0)
        { delete this; }
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを取得します.
    //!
    //! @return     参照カウントを返却します.
    //---------------------------------------------------------------------------------------------
    s32 GetCount() const
    { return m_Count; }

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    mutable s32 m_Count;    //!< 参照カウントです.

    //=============================================================================================
    // private methods.
    //=============================================================================================
    /* NOTHING */
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// RefPtr class
///////////////////////////////////////////////////////////////////////////////////////////////////
ASDX_TEMPLATE(T)
class RefPtr
{
    //=============================================================================================
    // list of friend classes and methods.
    //=============================================================================================
    ASDX_TEMPLATE(U) friend class RefPtr;

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
    RefPtr() ASDX_NOTHROW
    : m_pPtr( nullptr )
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //---------------------------------------------------------------------------------------------
    explicit RefPtr( nullptr_type ) ASDX_NOTHROW
    : m_pPtr( nullptr )
    { /* DO_NOTHING */ }

    //---------------------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //---------------------------------------------------------------------------------------------
    explicit RefPtr( T* pInterface ) ASDX_NOTHROW
    : m_pPtr( pInterface )
    { AddRef(); }

    //---------------------------------------------------------------------------------------------
    //! @brief      コピーコンストラクタです.
    //---------------------------------------------------------------------------------------------
    RefPtr( const RefPtr& value ) ASDX_NOTHROW
    : m_pPtr( value.m_pPtr )
    { AddRef(); }

    //---------------------------------------------------------------------------------------------
    //! @brief      ムーブコンストラクタです.
    //---------------------------------------------------------------------------------------------
    RefPtr( RefPtr&& value ) ASDX_NOTHROW
    : m_pPtr( nullptr )
    {
        if ( this != reinterpret_cast<RefPtr*>(&reinterpret_cast<u8&>(value)) )
        { Swap(value); }
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      引数付きコンストラクタです.
    //---------------------------------------------------------------------------------------------
    ASDX_TEMPLATE(U)
    explicit RefPtr( U* value ) ASDX_NOTHROW
    : m_pPtr( value )
    { AddRef(); }

    //---------------------------------------------------------------------------------------------
    //! @brief      デストラクタです.
    //---------------------------------------------------------------------------------------------
    ~RefPtr() ASDX_NOTHROW
    { Release(); }

    //---------------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //---------------------------------------------------------------------------------------------
    RefPtr& operator = ( T* value ) ASDX_NOTHROW
    {
        if ( m_pPtr != value )
        { RefPtr(value).Swap(*this); }
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //---------------------------------------------------------------------------------------------
    RefPtr& operator = ( const RefPtr& value ) ASDX_NOTHROW
    {
        if ( m_pPtr != value.m_pPtr )
        { RefPtr(value).Swap(*this); }
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      ムーブ代入演算子です.
    //---------------------------------------------------------------------------------------------
    RefPtr& operator = ( RefPtr&& value ) ASDX_NOTHROW
    {
        RefPtr(static_cast<RefPtr&&>(value)).Swap(*this);
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //---------------------------------------------------------------------------------------------
    ASDX_TEMPLATE(U)
    RefPtr& operator = ( U* value ) ASDX_NOTHROW
    {
        RefPtr(value).Swap(*this);
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //---------------------------------------------------------------------------------------------
    ASDX_TEMPLATE(U)
    RefPtr& operator = ( const RefPtr<U>& value ) ASDX_NOTHROW
    {
        RefPtr(value).Swap(*this);
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      ムーブ代入演算子です.
    //---------------------------------------------------------------------------------------------
    ASDX_TEMPLATE(U)
    RefPtr& operator = ( RefPtr<U>&& value ) ASDX_NOTHROW
    {
        RefPtr(static_cast<RefPtr&&>(value)).Swap(*this);
        return *this;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      代入演算子です.
    //---------------------------------------------------------------------------------------------
    RefPtr& operator = ( nullptr_type ) ASDX_NOTHROW
    {
        Release();
        return (*this);
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      アタッチします.
    //---------------------------------------------------------------------------------------------
    void Attach( T* value ) ASDX_NOTHROW
    {
        if ( m_pPtr != nullptr )
        { m_pPtr->Release(); }
        m_pPtr = value;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      デタッチします.
    //---------------------------------------------------------------------------------------------
    T* Detach() ASDX_NOTHROW
    {
        T* ptr = m_pPtr;
        m_pPtr = nullptr;
        return ptr;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      値を入れ替えます.
    //---------------------------------------------------------------------------------------------
    void Swap( RefPtr& value ) ASDX_NOTHROW
    {
        T* temp = m_pPtr;
        m_pPtr  = value.m_pPtr;
        value.m_pPtr = temp;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      値を入れ替えます.
    //---------------------------------------------------------------------------------------------
    void Swap( RefPtr&& value ) ASDX_NOTHROW
    {
        T* temp = m_pPtr;
        m_pPtr  = value.m_pPtr;
        value.m_pPtr = temp;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      ポインタを取得します.
    //---------------------------------------------------------------------------------------------
    T* GetPtr() const ASDX_NOTHROW
    { return m_pPtr; }

    //---------------------------------------------------------------------------------------------
    //! @brief      アドレスを取得します.
    //---------------------------------------------------------------------------------------------
    T* const* GetAddress() const ASDX_NOTHROW
    { return &m_pPtr; }

    //---------------------------------------------------------------------------------------------
    //! @brief      アドレスを取得します.
    //---------------------------------------------------------------------------------------------
    T** GetAddress() ASDX_NOTHROW
    { return &m_pPtr; }

    //---------------------------------------------------------------------------------------------
    //! @brief      リセットします.
    //---------------------------------------------------------------------------------------------
    void Reset() ASDX_NOTHROW
    { Release(); }

    //---------------------------------------------------------------------------------------------
    //! @brief      指定された値にコピーを行います.
    //---------------------------------------------------------------------------------------------
    void CopyTo( T** ptr ) ASDX_NOTHROW
    {
        AddRef();
        (*ptr) = m_pPtr;
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      アロー演算子です.
    //---------------------------------------------------------------------------------------------
    T* operator -> () const ASDX_NOTHROW
    { return m_pPtr; }

    //---------------------------------------------------------------------------------------------
    //! @brief      bool型へのキャストです.
    //---------------------------------------------------------------------------------------------
    operator bool () const ASDX_NOTHROW
    { return m_pPtr != nullptr; }

protected:
    //=============================================================================================
    // protected variables.
    //=============================================================================================
    T*  m_pPtr;     //!< 参照カウントインタフェースを実装するオブジェクトのポインタです.

    //=============================================================================================
    // protected methods.
    //=============================================================================================

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを増やします.
    //---------------------------------------------------------------------------------------------
    void AddRef()
    {
        if ( m_pPtr != nullptr )
        { m_pPtr->AddRef(); }
    }

    //---------------------------------------------------------------------------------------------
    //! @brief      参照カウントを減らします.
    //---------------------------------------------------------------------------------------------
    void Release()
    {
        T* ptr = m_pPtr;
        if ( ptr != nullptr )
        {
            m_pPtr = nullptr;
            ptr->Release();
        }
    }

private:
    //=============================================================================================
    // private variables.
    //=============================================================================================
    /* NOTHING */

    //=============================================================================================
    // private methods.
    //=============================================================================================
    /* NOTHING */
};

ASDX_TEMPLATE(T)
bool operator == ( const RefPtr<T>& value, const T* ptr )
{ return ( value.GetPtr() == ptr ); }

ASDX_TEMPLATE(T)
bool operator == ( const T* ptr, const RefPtr<T>& value )
{ return ( value.GetPtr() == ptr ); }

ASDX_TEMPLATE(T)
bool operator == ( const RefPtr<T>& a, const RefPtr<T>& b )
{ return a.GetPtr() == b.GetPtr(); }

ASDX_TEMPLATE2(T, U)
bool operator == ( const RefPtr<T>& a, const RefPtr<U>& b )
{ return a.GetPtr() == b.GetPtr(); }

ASDX_TEMPLATE(T)
bool operator != ( const RefPtr<T>& value, const T* ptr )
{ return ( value.GetPtr() != ptr ); }

ASDX_TEMPLATE(T)
bool operator != ( const T* ptr, const RefPtr<T>& value )
{ return ( value.GetPtr() != ptr ); }

ASDX_TEMPLATE(T)
bool operator != ( const RefPtr<T>& a, const RefPtr<T>& b )
{ return a.GetPtr() != b.GetPtr(); }

ASDX_TEMPLATE2(T, U)
bool operator != ( const RefPtr<T>& a, const RefPtr<U>& b )
{ return a.GetPtr() != b.GetPtr(); }

ASDX_TEMPLATE(T)
bool operator == ( const RefPtr<T>& value, nullptr_type )
{ return ( value.GetPtr() == nullptr ); }

ASDX_TEMPLATE(T)
bool operator == ( nullptr_type, const RefPtr<T>& value )
{ return ( value.GetPtr() == nullptr ); }

ASDX_TEMPLATE(T)
bool operator != ( const RefPtr<T>& value, nullptr_type )
{ return ( value.GetPtr() != nullptr ); }

ASDX_TEMPLATE(T)
bool operator != ( nullptr_type, const RefPtr<T>& value )
{ return ( value.GetPtr() != nullptr ); }


} // namespace asura
