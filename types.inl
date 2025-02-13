#pragma once
#include <stdint.h>
#include <math.h>
#include <algorithm>

extern IAML* aml;
extern uintptr_t pUE4;
extern void* hUE4;
#define SYM(sym) (aml->GetSym(hUE4, sym))

typedef int8_t int8;
typedef uint8_t uint8;
typedef unsigned char uchar;
typedef uint8 byte;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef uintptr_t DWORD_PTR;

#define LOWORD(l) ((WORD) (((DWORD_PTR) (l)) & 0xffff))
#define HIWORD(l) ((WORD) ((((DWORD_PTR) (l)) >> 16) & 0xffff))
#define LOBYTE(w) ((BYTE) (((DWORD_PTR) (w)) & 0xff))
#define HIBYTE(w) ((BYTE) ((((DWORD_PTR) (w)) >> 8) & 0xff))

//手打(￣へ￣)
uintptr_t decodeADRL(uintptr_t addr){
	uintptr_t pc = addr; int op1 = *(int*)addr, op2 = *(int*)(addr + 4);
	return (pc & ~0xFFF) + (((((op1 >> 5) & 0x7FFFF) << 2) | (op1 >> 29) & 3) << 12) + ((op2 >> 10) & 0x3FFF);
}

#define STRU_PACKED_ALIGNED(n) __attribute__((packed)) __attribute__((aligned(n)))
#define STRU_ALIGNED(n) __attribute__((aligned(n)))
#define ASM __attribute__((optnone)) __attribute__((naked))
#define CSTYLE extern 
#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

typedef char16_t* FString;

void AsciiToGxtChar(const char* src, char16_t* dst){
	for(;*src;*dst++=*src++)
		;
	*dst=0;
}

void GxtCharToAscii(const char16_t* src, char* dst){
	for(;*src;*dst++=*src++)
		;
	*dst=0;
}

enum eSaveTypes{
	eCheckpointSave,
	eAutoSave,
	eTerminateSave,
	eExitSave,
	eOddjobSave,
	eStartMissionSave,
	eNormalSave
};

struct CompressedVector {
	int16 x, y, z;
};

struct CRect {
	// Init in flipped state
	float left      =  1000000.0F; // x1
	float top       = -1000000.0F; // y1
	float right     = -1000000.0F; // x2
	float bottom    =  1000000.0F; // y2
};

struct CRGBA{ //定义来自SilentPatch
	uint8 r, g, b, a;
	inline CRGBA() {}
	inline constexpr CRGBA(const CRGBA& in) : r(in.r), g(in.g), b(in.b), a(in.a){}
	inline constexpr CRGBA(const CRGBA& in, uint8 alpha) : r(in.r), g(in.g), b(in.b), a(alpha){}
	inline constexpr CRGBA(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255) : r(red), g(green), b(blue), a(alpha){}

	friend constexpr CRGBA Blend(const CRGBA& From, const CRGBA& To, double BlendVal){
		const double InvBlendVal = 1.0 - BlendVal;
		return CRGBA( uint8(To.r * BlendVal + From.r * InvBlendVal),
			uint8(To.g * BlendVal + From.g * InvBlendVal),
			uint8(To.b * BlendVal + From.b * InvBlendVal),
			uint8(To.a * BlendVal + From.a * InvBlendVal));
	}

	friend constexpr CRGBA BlendSqr(const CRGBA& From, const CRGBA& To, double BlendVal){
		const double InvBlendVal = 1.0 - BlendVal;
		return CRGBA( uint8(sqrt((To.r * To.r) * BlendVal + (From.r * From.r) * InvBlendVal)),
			uint8(sqrt((To.g * To.g) * BlendVal + (From.g * From.g) * InvBlendVal)),
			uint8(sqrt((To.b * To.b) * BlendVal + (From.b * From.b) * InvBlendVal)),
			uint8(sqrt((To.a * To.a) * BlendVal + (From.a * From.a) * InvBlendVal)));
	}
};
struct CVector{
	float x, y, z;
};
struct CVector2D{
	float x,y;
};

// UE的几个常用定义
struct FVector{
	float X, Y, Z;
};
struct FVector2D{
	float X, Y;
};
struct FVector4{
	float X,Y,Z,W;
};
struct FLinearColor{
	float R,G,B,A;
};

void CalcColorBadToGood(float value, float max, CRGBA& out){
	if(value <= max/4){
		value = value/max*4;
		out.r = 0xA0+(value*0x5F);
		out.g = 0;
		out.b = 0;
	}else if(value <= max/2){
		value = value/max*4-1;
		out.r = 0xFF;
		out.g = uint8(value*0xFF);
		out.b = 0;
	}else{
		value = std::min(value/max*2-1, 1.f);
		out.r = 0xFF-uint8(value*0xFF);
		out.g = 0xFF;
		out.b = 0;
	}
	out.a = 0xFF;
}