namespace GTA3{
enum eWeaponType : int32{
	WEAPONTYPE_UNARMED, WEAPONTYPE_BASEBALLBAT, WEAPONTYPE_COLT45, WEAPONTYPE_UZI, WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_AK47, WEAPONTYPE_M16, WEAPONTYPE_SNIPERRIFLE, WEAPONTYPE_ROCKETLAUNCHER, WEAPONTYPE_FLAMETHROWER,
	WEAPONTYPE_MOLOTOV, WEAPONTYPE_GRENADE, WEAPONTYPE_DETONATOR, WEAPONTYPE_HELICANNON, WEAPONTYPE_LAST_WEAPONTYPE,
	WEAPONTYPE_ARMOUR, WEAPONTYPE_RAMMEDBYCAR, WEAPONTYPE_RUNOVERBYCAR, WEAPONTYPE_EXPLOSION, WEAPONTYPE_UZI_DRIVEBY,
	WEAPONTYPE_DROWNING, WEAPONTYPE_FALL, WEAPONTYPE_UNIDENTIFIED,
	WEAPONTYPE_TOTALWEAPONS = WEAPONTYPE_LAST_WEAPONTYPE, WEAPONTYPE_TOTAL_INVENTORY_WEAPONS = 13,
};
namespace AGTAHud{
	uint32 (*m_aLastUpdatedFramesCount)[40];
	uint32* m_nLastUpdatedIndex;
	bool _Init(){
		if(nVer == V1_72){
			uintptr_t GGrassMovement = SYM("GGrassMovement");
			SET_TO(m_aLastUpdatedFramesCount, GGrassMovement + 80);
			SET_TO(m_nLastUpdatedIndex, uintptr_t(m_aLastUpdatedFramesCount) + sizeof(uint32[40]));
		} else if(nVer == V1_8X){
			uintptr_t AGTALightBase__LastTime = SYM("_ZN13AGTALightBase8LastTimeE");
			SET_TO(m_aLastUpdatedFramesCount, AGTALightBase__LastTime - 200);
			SET_TO(m_nLastUpdatedIndex, uintptr_t(m_aLastUpdatedFramesCount) + sizeof(uint32[40]));
		} else return false;
		return true;
	}
}
namespace CFont{
	enum eFontStyle{
		FONT_BANK, FONT_PAGER, FONT_HEADING
	};
	void (*PrintString)(float x, float y, char16_t* text, int*);
	void (*SetColor)(CRGBA& color);
	void (*SetDropShadowPosition)(int16 value);
	void (*SetFontStyle)(eFontStyle style);
	void (*SetJustifyOn)();
	void (*SetScale)(float x, float y);
	void (*SetWrapx)(float value);
	void _Init(){
		SET_TO(PrintString, SYM("_ZN4GTA35CFont11PrintStringEffPtPi"));
		SET_TO(SetColor, SYM("_ZN4GTA35CFont8SetColorE5CRGBA"));
		SET_TO(SetDropShadowPosition, SYM("_ZN4GTA35CFont21SetDropShadowPositionEs"));
		SET_TO(SetFontStyle, SYM("_ZN4GTA35CFont12SetFontStyleEs"));
		SET_TO(SetJustifyOn, SYM("_ZN4GTA35CFont12SetJustifyOnEv"));
		SET_TO(SetScale, SYM("_ZN4GTA35CFont8SetScaleEff"));
		SET_TO(SetWrapx, SYM("_ZN4GTA35CFont8SetWrapxEf"));
	}
}
struct CGangInfo{
	int32 m_nVehicleMI;
	int8 m_nPedModelOverride;
	eWeaponType m_Weapon1;
	eWeaponType m_Weapon2;
};
namespace CGangs{
	enum {GANG_MAFIA, GANG_TRIAD, GANG_DIABLOS, GANG_YAZUKA, GANG_YARDIE, GANG_COLUMB, GANG_HOODS, GANG_7, GANG_8, NUM_GANGS};
	CGangInfo (*Gang)[NUM_GANGS];
	inline void _Init(){
		SET_TO(Gang, SYM("_ZN4GTA36CGangs4GangE"));
	}
}
namespace CMenuManager{
	bool* m_PrefsInvincibility;
	inline void _Init(){
		SET_TO(m_PrefsInvincibility, SYM("_ZN4GTA312CMenuManager20m_PrefsInvincibilityE"));
	}
}
namespace CPad{
	wchar_t** KeyBoardCheatString;
	uint32* m_nCheatStringSize;
	void _Init(){
		SET_TO(KeyBoardCheatString, SYM("_ZN4GTA34CPad19KeyBoardCheatStringE"));
		SET_TO(m_nCheatStringSize, uintptr_t(KeyBoardCheatString) + sizeof(KeyBoardCheatString));
	}
}
namespace CTimer{
	uint32* m_snTimeInMilliseconds;
	inline void _Init(){
		SET_TO(m_snTimeInMilliseconds, SYM("_ZN4GTA36CTimer22m_snTimeInMillisecondsE"));
	}
}
struct _UGameterSettings;
namespace UGameterSettings{
	void (*OnLanguageSetEv)(_UGameterSettings* self);
	void _Init(){
		SET_TO(OnLanguageSetEv, SYM("_ZN16UGameterSettings13OnLanguageSetEv"));
	}
}
namespace UGTASingleton{
	_UGameterSettings* (*GetSettings)(bool ForceRefresh, bool bForceUpdateAudio, bool forceNoChanges);
	void _Init(){
		SET_TO(GetSettings, SYM("_ZN13UGTASingleton11GetSettingsEbbb"));
	}
}
namespace{
	int* AllowMissionReplay;
	//void (*AsciiToGxtChar)(const char* src, wchar_t* dst);
	uint32 (*OS_ScreenGetHeight)();
	uint32 (*OS_ScreenGetWidth)();
	bool (*SaveGameForPause)(eSaveTypes saveType);
	void _Init(){
		SET_TO(AllowMissionReplay, SYM("_ZN4GTA318AllowMissionReplayE"));
		//SET_TO(AsciiToGxtChar, SYM("_Z14AsciiToGxtCharPKcPt"));
		SET_TO(OS_ScreenGetHeight, SYM("_Z18OS_ScreenGetHeightv"));
		SET_TO(OS_ScreenGetWidth, SYM("_Z17OS_ScreenGetWidthv"));
		SET_TO(SaveGameForPause, SYM("_ZN4GTA316SaveGameForPauseEi"));
	}
}
struct CPed{
	private: byte gap0[556];
	uint32 bShakeFist : 1;
	uint32 bNoCriticalHits : 1;
	public:  uint32 bVehExitWillBeInstant : 1;
};
enum : int16{MI_SPEEDER = 142};
struct CVehicle{
	private: byte gap0[0x78];
	public: int16 m_modelIndex;
};VALIDATE_OFFSET(CVehicle, m_modelIndex, 0x78);
enum AssocGroupId : int32;enum AnimationId{ANIM_STD_CAR_SIT = 0x6F};

bool bEnableAutoSave, bModernFonts, bFixMissingTextKey;
int nLastSavingTime, nSaveIntervalTime;
float fMaxFPSToCalcColor;

DECL_HOOKv(CGame__Process){
	CGame__Process();
	if(bEnableAutoSave && GTA3::CTimer::m_snTimeInMilliseconds){
		uint32 nTimeInMs = *GTA3::CTimer::m_snTimeInMilliseconds;
		if(!nLastSavingTime) nLastSavingTime = nTimeInMs;
		else if(nTimeInMs - nLastSavingTime > nSaveIntervalTime){
			if(!*AllowMissionReplay){
				bool res = SaveGameForPause(eSaveTypes::eExitSave);
				logger->Info("Autosave %s", res ? "completed" : "failed");
			} else logger->Info("Autosave skipped %d", !*AllowMissionReplay);
			nLastSavingTime = nTimeInMs;
		}
	}
	if(bFixMissingTextKey){
		static bool fixed;
		if(!fixed)
			UGameterSettings::OnLanguageSetEv(UGTASingleton::GetSettings(false, false, false)),
			fixed = true;
	}
}
DECL_HOOKv(AGTAHUD__UpdatePerfHUD, bool showFPS, const FVector& coord, const FString& zoneName){
	AGTAHUD__UpdatePerfHUD(false, coord, zoneName);
	static char szA[BUFSIZ]={};
	uint32 nScreenW = OS_ScreenGetWidth(), nScreenH = OS_ScreenGetHeight(); 
	float fPxX = float(nScreenW) / 1920.f, fPxY = float(nScreenH) / 1080.f;
	memset(szA, 0, sizeof(szA));

	uint32 nFramesUpdated = (*AGTAHud::m_aLastUpdatedFramesCount)[*AGTAHud::m_nLastUpdatedIndex % 40],
	nFramesLastUpdated = (*AGTAHud::m_aLastUpdatedFramesCount)[(*AGTAHud::m_nLastUpdatedIndex - 1) % 40];
	float fRealFPS = 39000.f / (nFramesLastUpdated - nFramesUpdated);
	int n = sprintf(szA, "FPS: %05.2f", fRealFPS);
	if(n){
		char16_t* szW=new char16_t[n+2];
		AsciiToGxtChar(szA, szW);
		CRGBA color={};
		CalcColorBadToGood(fRealFPS, fMaxFPSToCalcColor, color);

		CFont::SetColor(color);
		CFont::SetDropShadowPosition(4);
		CFont::SetFontStyle(bModernFonts ? CFont::FONT_BANK : CFont::FONT_HEADING);
		CFont::SetJustifyOn();
		CFont::SetScale(2*0.54f, 2.f);
		CFont::SetWrapx(1000.f);
		CFont::PrintString(fPxX * 32, fPxY * 8, szW, nullptr);
		delete[] szW;
	}
}

DECL_HOOKv(CPad__AddToPCCheatString, void* self, char LastPressedKey, bool p3){
	CPad__AddToPCCheatString(self, LastPressedKey, p3);
	if(*CPad::KeyBoardCheatString && *CPad::m_nCheatStringSize){
		char buffer[31]={};
		char* pos3=buffer, *pos1 = (char*)*CPad::KeyBoardCheatString;
		int len = 1;
		while(true){
			if(*pos1) *pos3++ = *pos1, len++;
			pos1++;
			if(len == *CPad::m_nCheatStringSize)break;
		}
		logger->Info("CheatString %s", buffer);
	}
}
DECL_HOOK(int8, CRunningScript__ProcessCommands500To599, void* self, int command){
	int8 result = CRunningScript__ProcessCommands500To599(self, command);
	if(command == 567)
		if((*CGangs::Gang)[CGangs::GANG_MAFIA].m_Weapon2 == WEAPONTYPE_SHOTGUN)
			(*CGangs::Gang)[CGangs::GANG_MAFIA].m_Weapon2 = WEAPONTYPE_AK47;
	return result;
}

bool bSitInBoat = false; CPed* pInstance;
DECL_HOOKv(CPed__SetEnterCar_AllClear, CPed* self, CVehicle *car, uint32 doorNode, uint32 doorFlag){
	if(car->m_modelIndex == MI_SPEEDER){
		bSitInBoat = true, pInstance = self;
	}
	CPed__SetEnterCar_AllClear(self, car, doorNode, doorFlag);
}
DECL_HOOKp(CAnimManager__BlendAnimation, void *clump, AssocGroupId groupId, AnimationId animId, float delta){
	if(bSitInBoat)animId = ANIM_STD_CAR_SIT;
	void* ret = CAnimManager__BlendAnimation(clump, groupId, animId, delta);
	pInstance->bVehExitWillBeInstant = true;
	bSitInBoat = false;
	return ret;
}

void Init(){
	GTA3::_Init();
	UGameterSettings::_Init();
	UGTASingleton::_Init();
	bool bFPSShowAvailable = GTA3::AGTAHud::_Init();
	GTA3::CFont::_Init();
	GTA3::CGangs::_Init();
	GTA3::CMenuManager::_Init();
	GTA3::CPad::_Init();
	GTA3::CTimer::_Init();

	bEnableAutoSave = cfg->GetBool("Enabled", true, "AutoSave");
	ConfigEntry* entry = cfg->Bind("IntervalTime", 20, "AutoSave");
	if(entry->GetInt() < 10) entry->SetInt(10);
	nSaveIntervalTime = entry->GetInt() * 1000;

	if (bFPSShowAvailable){ //内存地址每个版本都不同
		if(cfg->GetBool("ShowFPS", true, "Debugging"))
			HOOKSYM(AGTAHUD__UpdatePerfHUD, hUE4, "_ZN7AGTAHUD13UpdatePerfHUDEbRK7FVectorRK7FString");
		bModernFonts = cfg->GetBool("UseModernFonts", true, "Debugging");
		fMaxFPSToCalcColor = cfg->GetFloat("MaxFPSToShowColor", 30.f, "Debugging");
	}

	/*https://cookieplmonster.github.io/2024/10/25/silentpatch-goes-open-source/#stealth-fbi-cars
	  https://github.com/CookiePLMonster/SilentPatch/blob/dev/SilentPatchIII/SilentPatchIII.cpp#L2456
	  https://github.com/halpz/re3/blob/master/src/control/CarCtrl.cpp#L345
	  Silent认为是测试版遗留，所以删除；re3只在注释中表明这一事实，未标FIX_BUGS*/
	if(cfg->GetBool("FixFBICarColor", true, "Visual")){
		uintptr_t pBaseFunc = SYM("_ZN4GTA38CCarCtrl20GenerateOneRandomCarEb");
		if(pBaseFunc == 0)pBaseFunc = SYM("_ZN4GTA38CCarCtrl20GenerateOneRandomCarEv");
		uintptr_t target = aml->PatternScan("BF AE 01 71", pBaseFunc, 0x1020); //CMP W21, #107
		if(target){
			target = aml->PatternScan("?? ?? FF 54", target, 20); //B.NE loc
			if(target){
				ForceJump(target); //B.NE改成B
			}
		}
	}
	bFixMissingTextKey = cfg->GetBool("FixMissingTextKey", true, "Visual");

	/*https://cookieplmonster.github.io/2024/10/25/silentpatch-goes-open-source/#boat-driving-animations
	  https://github.com/CookiePLMonster/SilentPatch/blob/dev/SilentPatchIII/SilentPatchIII.cpp#L2407
	  https://github.com/halpz/re3/blob/master/src/peds/PedAI.cpp#L3534
	  均修复
	if(cfg->GetBool("BoatSittingAnimFix", true, "Gameplay")){
		SET_TO(CAnimManager__BlendAnimation, SYM("_ZN4GTA312CAnimManager14BlendAnimationEP11AGTASKActorNS_12AssocGroupIdENS_11AnimationIdEf"));
		uintptr_t pBaseFunc = SYM("_ZN4GTA34CPed20SetEnterCar_AllClearEPNS_8CVehicleEjj");
		HOOK(CPed__SetEnterCar_AllClear, pBaseFunc);
		uintptr_t target = aml->PatternScan("42 0F 80 52", pBaseFunc, 0x400); //MOV W2, #122
		if(target){
			target = aml->PatternScan("?? ?? ?? 97", pBaseFunc, 20); //BL ...
			if(target){
				aml->PlaceBL(target, (uintptr_t)HookOf_CAnimManager__BlendAnimation);
			}
		}
	}*/

	if(cfg->GetBool("MafiaDontUseShotgun", false, "Gameplay"))
		HOOKSYM(CRunningScript__ProcessCommands500To599, hUE4, "_ZN4GTA314CRunningScript23ProcessCommands500To599Ei");

	HOOKSYM(CGame__Process, hUE4, "_ZN4GTA35CGame7ProcessEv");
	HOOKSYM(CPad__AddToPCCheatString, hUE4, "_ZN4GTA34CPad18AddToPCCheatStringEcb");

	cfg->Save(); // Will only save if something was changed
}
}