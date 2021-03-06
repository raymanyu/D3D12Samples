﻿//-------------------------------------------------------------------------------------------------
// File : asdxNeon.inl
// Desc : ARM NEON Wrapper Module.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------
#pragma once

#if ASDX_IS_NEON

namespace asdx {

///////////////////////////////////////////////////////////////////////////////////////////////////
// Simd class
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//      生成処理を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Create( f32 x, f32 y, f32 z, f32 w )
{
    f32 element = { x, y, z, w };
    return __vld1q_f32( element );
}

//-------------------------------------------------------------------------------------------------
//      X成分を設定します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
void Simd::SetX( b128& value, f32 x )
{ vsetq_lane_f32( x, value, 0 ); }

//-------------------------------------------------------------------------------------------------
//      Y成分を設定します.
//-------------------------------------------------------------------------------------------------
ASDX_INILNE
void Simd::SetY( b128& value, f32 y )
{ vsetq_lane_f32( y, value, 1 ); }

//-------------------------------------------------------------------------------------------------
//      Z成分を設定します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
void Simd::SetZ( b128& value, f32 z )
{ vsetq_lane_f32( z, value, 2 ); }

//-------------------------------------------------------------------------------------------------
//      W成分を設定します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
void Simd::SetW( b128& value, f32 w )
{ vsetq_lane_f32( w, value, 3 ); }

//-------------------------------------------------------------------------------------------------
//      X成分を取得します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
f32 Simd::GetX( const b128& value )
{ return vgetq_lane_f32( value, 0 ); }

//-------------------------------------------------------------------------------------------------
//      Y成分を取得します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
f32 Simd::GetY( const b128& value )
{ return vgetq_lane_f32( value, 1 ); }

//-------------------------------------------------------------------------------------------------
//      Z成分を取得します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
f32 Simd::GetZ( const b128& value )
{ return vgetq_lane_f32( value, 2 ); }

//-------------------------------------------------------------------------------------------------
//      W成分を取得します.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
f32 Simd::GetW( const b128& value )
{ return vgetq_lane_f32( value, 3 ); }

//-------------------------------------------------------------------------------------------------
//      加算計算を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Add( const b128& a, const b128& b )
{ return vaddq_f32( a, b ); }

//-------------------------------------------------------------------------------------------------
//      減算計算を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Sub( const b128& a, const b128& b )
{ return vsubq_f32( a, b ); }

//-------------------------------------------------------------------------------------------------
//      乗算計算を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Mul( const b128& a, const b128& b )
{ return vmulq_f32( a, b ); }

//-------------------------------------------------------------------------------------------------
//      除算計算を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Div( const b128& a, const b128& b )
{
    // TODO : 最適化.
    b128 rcp = vrecpeq_f32(b);
    return vmulq_f32( a, rcp );
}

//-------------------------------------------------------------------------------------------------
//      積和計算を行います.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Mad( const b128& a, const b128& b, const b128& c )
{ return vmlaq_f32( c, a, b ); }

//-------------------------------------------------------------------------------------------------
//      平方根を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Sqrt( const b128& value )
{
    // TODO : 最適化.
    b128 rcp = vrsqrtsq_f32( value );
    return vrecpeq_f32( rcp );
}

//-------------------------------------------------------------------------------------------------
//      逆数を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Rcp( const b128& value )
{ return vrecpeq_f32( value ); }

//-------------------------------------------------------------------------------------------------
//      平方根の逆数を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Rsqrt( const b128& value )
{ return vrsqrtsq_f32( value ); }

//-------------------------------------------------------------------------------------------------
//      負符号をつけた値を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Negate( const b128& value )
{ return vnegq_f32( value ); }

//-------------------------------------------------------------------------------------------------
//      絶対値を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Abs( const b128& value )
{ return vabsq_f32( value ); }

//-------------------------------------------------------------------------------------------------
//      最小値を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Min( const b128& a, const b128& b )
{ return vminq_f32( a, b ); }

//-------------------------------------------------------------------------------------------------
//      最大値を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Max( const b128& a, const b128& b )
{ return vmaxq_f32( a, b ); }

//-------------------------------------------------------------------------------------------------
//      内積を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Dp3( const b128& a, const b128& b )
{
    b128 tmp = vmulq_f32( a, b );
    b128 v1 = vget_low_f32( tmp );
    b128 v2 = vget_high_f32( tmp );
    v1 = vpadd_f32( v1, v1 );
    v2 = vdup_lane_f32( v2, 0 );
    v1 = vadd_f32( v1, v2 );
    return vcombine_f32( v1, v1 );
}

//-------------------------------------------------------------------------------------------------
//      内積を求めます.
//-------------------------------------------------------------------------------------------------
ASDX_INLINE
b128 Simd::Dp4( const b128& a, const b128& b )
{
    b128 tmp = vmulq_f32( a, b );
    b128 v1 = vget_low_f32( tmp );
    b128 v2 = vget_high_f32( tmp );
    v1 = vpadd_f32( v1, v1 );
    v2 = vpadd_f32( v2, v2 );
    v1 = vadd_f32( v1, v2 );
    return vcombine_f32( v1, v1 );
}

} // namespace asdx

#endif//ASDX_IS_NEON