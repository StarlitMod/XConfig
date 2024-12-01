#include "mod/amlmod.h"
#include "mod/logger.h"
#include "mod/config.h"

MYMOD(com.starlit.xconfig, XConfig, 0.10, BengbuGuards)
static Config cfgLocal("XConfig");

Config* cfg = &cfgLocal;
uintptr_t pUE4;
void* hUE4;
#define SYM(sym) (aml->GetSym(hUE4, sym))
#include "types.inl"
enum {III=1,VC,SA}nGame;
enum {Netflex=1,Rockstar}nGameType;

int ret0(int a, ...) { return 0; } // Generic

#include "III.inl"
#include "VC.inl"
#include "SA.inl"


extern "C" void OnModLoad()
{
	logger->SetTag("XConfig");
	
	pUE4 = aml->GetLib("libUE4.so");
	hUE4 = aml->GetLibHandle("libUE4.so");
	
	if(!pUE4){
		logger->Info("Can't find libUE4, unloading...");
		return;
	}
	cfg->Bind("Author", "", "About")->SetString("BengbuGuards, XMDS");
	cfg->Bind("Version", "", "About")->SetString("Beta 10");
	const char* szGame = aml->GetCurrentGame();
	logger->Info("Game %s", szGame);
	#define _stricmp strcasecmp
	if(!_stricmp(szGame, "com.netflix.NGP.GTASanAndreasDefinitiveEdition"))nGame=SA, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gtasa.de"))nGame=SA, nGameType=Rockstar;
	else if(!_stricmp(szGame, "com.netflix.NGP.GTAViceCityDefinitiveEdition"))nGame=VC, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gtavc.de"))nGame=VC, nGameType=Rockstar;
	else if(!_stricmp(szGame, "com.netflix.NGP.GTAIIIDefinitiveEdition"))nGame=III, nGameType=Netflex;
	else if(!_stricmp(szGame, "com.rockstargames.gta3.de"))nGame=III, nGameType=Rockstar;

	if(nGame == SA)
		GTASA::Init();

	if(nGame == VC)
		ViceCity::Init();

	if(nGame == III)
		GTA3::Init();

	logger->Info("XConfig mod is loaded!");
	
}
