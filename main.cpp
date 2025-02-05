#include "mod/amlmod.h"
#include "mod/logger.h"
#include "mod/config.h"

//#include "include/Gloss.h"

MYMOD(com.starlit.xconfig, XConfig, 0.13, BengbuGuards)
static Config cfgLocal("XConfig");

Config* cfg = &cfgLocal;
uintptr_t pUE4;
void* hUE4;
#define SYM(sym) (aml->GetSym(hUE4, sym))
#include "types.inl"
#define ForceJump(addr) aml->PlaceB((addr), aml->GetBranchDest(addr))
//GHook (*GlossHookInternalImpl)(void *addr, GlossHookInternalCallback new_func, void *ret_addr, bool is_4_byte_hook, i_set mode);

enum {III=1,VC,SA}nGame;
enum {Netflex=1,Rockstar}nGameType;
enum VERSION{V1_72=1, V1_8X, UNKNOWN}nVer;

int ret0(int a, ...) { return 0; } // Generic

#include "III.inl"
#include "VC.inl"
#include "SA.inl"
namespace UGameterface{
	FString (*GetVersionString)();
	inline void _Init(){
		SET_TO(GetVersionString, SYM("_ZN12UGameterface16GetVersionStringEv"));
	}
}

extern "C" void OnModLoad()
{
	logger->SetTag("XConfig");
	
	pUE4 = aml->GetLib("libUE4.so");
	hUE4 = aml->GetLibHandle("libUE4.so");
	
	if(!pUE4){
		logger->Info("Can't find libUE4, unloading...");
		return;
	}
	//SETSYM_TO(GlossHookInternalImpl, aml->GetLibHandle("libAML.so"), "GlossHookInternal");
	cfg->Bind("Author", "", "About")->SetString("BengbuGuards, XMDS");
	cfg->Bind("Version", "", "About")->SetString("Beta-13");
	const char* szGame = aml->GetCurrentGame();
	logger->Info("Game %s", szGame);
	#define _stricmp strcasecmp
	if(!_stricmp(szGame, "com.netflix.NGP.GTASanAndreasDefinitiveEdition"))nGame=SA, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gtasa.de"))nGame=SA, nGameType=Rockstar;
	else if(!_stricmp(szGame, "com.netflix.NGP.GTAViceCityDefinitiveEdition"))nGame=VC, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gtavc.de"))nGame=VC, nGameType=Rockstar;
	else if(!_stricmp(szGame, "com.netflix.NGP.GTAIIIDefinitiveEdition"))nGame=III, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gta3.de"))nGame=III, nGameType=Rockstar;
	/*UGameterface::_Init();
	// 判断游戏版本，某些硬编码补丁只适用于1.72，否则闪退 TODO: 使用Pattern
	FString sVer = UGameterface::GetVersionString();
	char secChar = *((char*)sVer + 4);
	if(secChar == '7')nVer = V1_72;
	else if(secChar == '8')nVer = V1_8X;
	else nVer = UNKNOWN;*/
	nVer = V1_8X;

	if(nGame == SA)
		GTASA::Init();

	if(nGame == VC)
		ViceCity::Init();

	if(nGame == III)
		GTA3::Init();

	logger->Info("XConfig mod is loaded!");
	
}
