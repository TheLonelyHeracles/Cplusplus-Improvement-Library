/*
 * bit-operation header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-7-12
 */

#ifndef __BIT_OPERATION_H__
#define __BIT_OPERATION_H__

#include <cassert>

inline int _1(int i) { assert(i < 32); return 1 << i; }
inline int _7(int i) { assert(i < 32); return (1 << i) - 1; }
inline long long _1L(int i) { assert(i < 64); return 1LL << i; }
inline long long _7L(int i) { assert(i < 64); return (1LL << i) - 1; }

// inverse function of _1(i) or _1L(i), put in _1(i) or _1L(i) returns i
template<typename T> inline int i_1(T x) {
	assert((x & x - 1) == 0);
	int ret = 0;
	for (int i = sizeof(T) << 2; i; i >>= 1) if (x >> i) { ret += i; x >>= i; }
	return ret;
}

template<typename T> inline T lowbit(T x) { return x & -x; }
template<typename T> inline bool testbit(T x, int i) { return (bool)(x & (T(1) << i)); }
template<typename T> inline bool setbit(T& x, int i) { return (x & (T(1) << i)) ? false : (x |= (T(1) << i), true); }
template<typename T> inline bool resetbit(T& x, int i) { return (x & (T(1) << i)) ? (x &= ~(T(1) << i), true) : false; }

template<typename T>
inline int cntbit(T x) {
	int len = sizeof(T) << 3;
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) + (x & 0x5555555555555555);
	x = ((x & 0xcccccccccccccccc) >> 2) + (x & 0x3333333333333333);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) + (x & 0x0f0f0f0f0f0f0f0f);
	if (len >= 16) x = ((x & 0xff00ff00ff00ff00) >> 8) + (x & 0x00ff00ff00ff00ff);
	if (len >= 32) x = ((x & 0xffff0000ffff0000) >> 16) + (x & 0x0000ffff0000ffff);
	if (len >= 64) x = ((x & 0xffffffff00000000) >> 32) + (x & 0x00000000ffffffff);
	return x;
}

template<typename T>
inline T reversebit(T x) {
	int len = sizeof(T) << 3;
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1);
	x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4);
	if (len >= 16) x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8);
	if (len >= 32) x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
	if (len >= 64) x = ((x & 0xffffffff00000000) >> 32) | ((x & 0x00000000ffffffff) << 32);
	return x;
}


// cntbit and reversebit specialized for int, long long
inline int cntbit(int x) {
	x = ((x & 0xaaaaaaaa) >> 1) + (x & 0x55555555);
	x = ((x & 0xcccccccc) >> 2) + (x & 0x33333333);
	x = ((x & 0xf0f0f0f0) >> 4) + (x & 0x0f0f0f0f);
	x = ((x & 0xff00ff00) >> 8) + (x & 0x00ff00ff);
	x = ((x & 0xffff0000) >> 16) + (x & 0x0000ffff);
	return x;
}
inline int cntbit(long long x) {
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) + (x & 0x5555555555555555);
	x = ((x & 0xcccccccccccccccc) >> 2) + (x & 0x3333333333333333);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) + (x & 0x0f0f0f0f0f0f0f0f);
	x = ((x & 0xff00ff00ff00ff00) >> 8) + (x & 0x00ff00ff00ff00ff);
	x = ((x & 0xffff0000ffff0000) >> 16) + (x & 0x0000ffff0000ffff);
	x = ((x & 0xffffffff00000000) >> 32) + (x & 0x00000000ffffffff);
	return int(x);
}
inline int reversebit(int x) {
	x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
	x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
	x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
	x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
	x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
	return x;
}
inline long long reversebit(long long x) {
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1);
	x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4);
	x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8);
	x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
	x = ((x & 0xffffffff00000000) >> 32) | ((x & 0x00000000ffffffff) << 32);
	return x;
}



/* eof */
#endif