#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include<iostream>


using namespace std;


template<typename T1, typename T2>
constexpr auto SHA256_ROTL(T1 a, T2 b) { return ((a << (32 - b)) | (a >> b)); }
template<typename T1, typename T2>
constexpr auto SHA256_SR(T1 a, T2 b) { return ((a >> b)); }


template<typename T1, typename T2, typename T3>
constexpr auto SHA256_Ch(T1 x, T2 y, T3 z) { return ((x&y) ^ ((~x)&z)); }
template<typename T1, typename T2, typename T3>
constexpr auto SHA256_Maj(T1 x, T2 y, T3 z) { return ((x & y) ^ (x & z) ^ (y & z)); }
template<typename T1>
constexpr auto SHA256_E0(T1 x) { return SHA256_ROTL(x, 2) ^ SHA256_ROTL(x, 13) ^ SHA256_ROTL(x, 22); }
template<typename T1>
constexpr auto SHA256_E1(T1 x) { return SHA256_ROTL(x, 6) ^ SHA256_ROTL(x, 11) ^ SHA256_ROTL(x, 25); }
template<typename T1>
constexpr auto SHA256_O0(T1 x) { return SHA256_SR(x, 3) ^ SHA256_ROTL(x, 18) ^ SHA256_ROTL(x, 7); }
template<typename T1>
constexpr auto SHA256_O1(T1 x) { return SHA256_ROTL(x, 17) ^ SHA256_ROTL(x, 19) ^ SHA256_SR(x, 10); }


extern char* StrSHA256(const char* str, long long length, char* sha256) {
	char * pp, *ppend;
	unsigned int a, b, c, d, e, f, g, h, h1, h2, h3, h4, h5, h6, h7, h0, w[64];
	unsigned int L;
	h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
	h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;
	unsigned int k[64] = {
			0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
			0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
			0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
			0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
			0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
			0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
			0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
	};
	if (length % 64 >= 56)
		L = length + (128 - length % 64);
	else
		L = length + (64 - length % 64);
	if (!(pp = (char *)malloc((unsigned long)L)))
		return 0;
	int i = 0;
	for (i = 0; i < length; i++) {
		pp[i + 3 - 2 * (i % 4)] = str[i];
		if (i >= 64) {
			pp[i + 3 - 2 * (i % 4)] = str[i];
		}
	}
	for (i = length; i < L; i++)
		if (i == length)
			pp[i + 3 - 2 * (i % 4)] = 128;
		else
			pp[i + 3 - 2 * (i % 4)] = 0;

	*((long*)(pp + L - 4)) = length << 3;
	*((long*)(pp + L - 8)) = length >> 29;

	ppend = pp + L;
	for (; pp < ppend; pp += 64) {
		for (i = 0; i < 16; i++) {
			w[i] = ((long*)pp)[i];
		}
		for (i = 16; i < 64; i++) {
			w[i] = (SHA256_O1(w[i - 2]) + w[i - 7] + SHA256_O0(w[i - 15]) + w[i - 16]);
		}
		a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
		for (i = 0; i < 64; i++) {
			unsigned int temp1 = h + SHA256_E1(e) + SHA256_Ch(e, f, g) + k[i] + w[i];
			unsigned int temp2 = SHA256_E0(a) + SHA256_Maj(a, b, c);
			h = g, g = f, f = e;
			e = d + temp1;
			d = c, c = b, b = a;
			a = temp1 + temp2;
		}
		h0 += a, h1 += b, h2 += c, h3 += d;
		h4 += e, h5 += f, h6 += g, h7 += h;
	};
	sprintf(sha256, "%08X%08X%08X%08X%08X%08X%08X%08X", h0, h1, h2, h3, h4, h5, h6, h7);
	
	return sha256;
}


int myhash(const char* text)
{
	char sha256[65];
	//puts(StrSHA256(text, strlen(text), sha256));
	StrSHA256(text, strlen(text), sha256);

	//cout << sha256 << endl;
	int num = 0, j=1;
	for (char i : sha256)
	{
		num = num + (int)i*j++;
	}

	return num;
}

