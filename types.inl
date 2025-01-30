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


#define STRU_PACKED_ALIGNED(n) __attribute__((packed)) __attribute__((aligned(n)))
#define STRU_ALIGNED(n) __attribute__((aligned(n)))
#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset) \
	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

typedef char16_t* FString;

/*struct FString{
	char16_t* Data;
	int ArrayNum, ArrayMax;

	FString(char16_t* simpleIn){
		Data = simpleIn;
	}
	char16_t operator[](size_t index){
		return Data[index];
	}
}; VALIDATE_SIZE(FString, 16);
*/

/*template<typename T> class Ref{
	uintptr_t addr;
	const char* sym;
	uintptr_t offset = 0;
	bool useSymbol;
public:
	Ref(uintptr_t addr):addr(addr){ useSymbol=false; }
	Ref(const char* sym, uintptr_t offset=0):sym(sym),offset(offset){ useSymbol=true; }
	operator T&() const{
		return useSymbol ? *(T*)(SYM(sym)+offset) : *(T*)addr;
	}
};*/

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

template <typename... Args> inline void Call(uintptr_t address, Args... args) {
    reinterpret_cast<void(*)(Args...)>(address)(args...);
}

template <typename Ret, typename... Args> inline Ret CallAndReturn(uintptr_t address, Args... args) {
    return reinterpret_cast<Ret(*)(Args...)>(address)(args...);
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

struct CRGBA{
	uint8 r, g, b, a;
	CRGBA(){}
	CRGBA(const CRGBA& src):r(src.r),g(src.g),b(src.b),a(src.a){}
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

/*
struct CPed {};
struct CPlayerPed : CPed {};

struct CPlayerInfo{
  CPlayerPed *m_pPed;
  //...
};

struct MobileMenu
{
  uint8 gap0[32];
  char field_20[16];
  char field_30[16];
  uint8 gap40[40];
  int m_nTargetBlipIndex;
  short field_6C;
  uint8 gap6E[6];
  short field_74;
  char field_76;
};




MobileMenu *gMobileMenu;
tRadarTrace **CRadar__ms_RadarTrace;
CPlayerInfo **CWorld__Players;*/