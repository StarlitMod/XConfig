namespace ViceCity{
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
		FONT_BANK, FONT_STANDARD, FONT_HEADING
	};
	void (*PrintString)(float x, float y, char16_t* text, int*);
	void (*SetColor)(CRGBA& color);
	void (*SetDropShadowPosition)(int16 value);
	void (*SetFontStyle)(eFontStyle style);
	void (*SetJustifyOn)();
	void (*SetScale)(float x, float y);
	void (*SetWrapx)(float value);
	void _Init(){
		SET_TO(PrintString, SYM("_ZN8ViceCity5CFont11PrintStringEffPtPi"));
		SET_TO(SetColor, SYM("_ZN8ViceCity5CFont8SetColorE5CRGBA"));
		SET_TO(SetDropShadowPosition, SYM("_ZN8ViceCity5CFont21SetDropShadowPositionEs"));
		SET_TO(SetFontStyle, SYM("_ZN8ViceCity5CFont12SetFontStyleEs"));
		SET_TO(SetJustifyOn, SYM("_ZN8ViceCity5CFont12SetJustifyOnEv"));
		SET_TO(SetScale, SYM("_ZN8ViceCity5CFont8SetScaleEff"));
		SET_TO(SetWrapx, SYM("_ZN8ViceCity5CFont8SetWrapxEf"));
	}
}
namespace CGame{
	int* currArea;
	inline void _Init(){
		SET_TO(currArea, SYM("_ZN8ViceCity5CGame8currAreaE"));
	}
}
struct _CGarage{
	uint8 m_eGarageType;
	byte gap1[0xB7];
}; VALIDATE_SIZE(_CGarage, 0xB8);
namespace CGarage{
	bool (*IsPlayerOutsideGarage)(_CGarage* self);
	inline void _Init(){
		SET_TO(IsPlayerOutsideGarage, SYM("_ZN8ViceCity7CGarage21IsPlayerOutsideGarageEv"));
	}
}
namespace CGarages{
	_CGarage (*aGarages)[32];
	inline void _Init(){
		SET_TO(aGarages, SYM("_ZN8ViceCity8CGarages8aGaragesE"));
	}
}
namespace CHud{
	void (*SetHelpMessage)(const FString& text, bool quick, bool displayForever, bool addToBrief, int);
	inline void _Init(){
		SET_TO(SetHelpMessage, SYM("_ZN8ViceCity4CHud14SetHelpMessageERK7FStringbbbi"));
	}
}
namespace CMenuManager{
	bool *m_PrefsInvincibility;
	bool *m_PrefsCarInvincibility;
	inline void _Init(){
		SET_TO(m_PrefsInvincibility, SYM("_ZN8ViceCity12CMenuManager20m_PrefsInvincibilityE"));
		SET_TO(m_PrefsCarInvincibility, SYM("_ZN8ViceCity12CMenuManager23m_PrefsCarInvincibilityE"));
	}
}
namespace CPad{
	char16_t* *KeyBoardCheatString;
	uint32 *m_nCheatStringSize;
	void _Init(){
		SET_TO(KeyBoardCheatString, SYM("_ZN8ViceCity4CPad19KeyBoardCheatStringE"));
		SET_TO(m_nCheatStringSize, uintptr_t(KeyBoardCheatString) + sizeof(KeyBoardCheatString));
	}

	bool _TestCheat(const char* text, int size){
		if(*CPad::m_nCheatStringSize < size+1) return false;
		char* pos1 = (char*)(*CPad::KeyBoardCheatString + (*m_nCheatStringSize-size-1));
		const char* pos2 = text;
		while(true){
			if(*pos1 && (tolower(*pos1++) != tolower(*pos2++)))
				return false;
			pos1++;
			if(!*((char16_t*)pos1)){
				*CPad::m_nCheatStringSize = 0;
				(*CPad::KeyBoardCheatString)[0] = 0;
				return true;
			}
		}
	}
}
struct _CPathFind;
_CPathFind *ThePaths;
namespace CPathFind{
	void (*SwitchRoadsOffInArea)(_CPathFind* self, float x1, float x2, float y1, float y2, float z1, float z2, bool disable);
	inline void _Init(){
		SET_TO(ThePaths, SYM("_ZN8ViceCity8ThePathsE"));
		SET_TO(SwitchRoadsOffInArea, SYM("_ZN8ViceCity9CPathFind20SwitchRoadsOffInAreaEffffffb"));
	}
}
struct _CRunningScript;
namespace CRunningScript{
	void (*UpdateCompareFlag)(_CRunningScript* self, bool flag);
	inline void _Init(){
		SET_TO(UpdateCompareFlag, SYM("_ZN8ViceCity14CRunningScript17UpdateCompareFlagEh"));
	}
}
namespace CTheScripts{
	byte (*ScriptSpace)[0x3F9A0];
	inline void _Init(){
		SET_TO(ScriptSpace, SYM("_ZN8ViceCity11CTheScripts11ScriptSpaceE"));
	}
}
namespace CTimer{
	uint32* m_snTimeInMilliseconds;
	inline void _Init(){
		SET_TO(m_snTimeInMilliseconds, SYM("_ZN8ViceCity6CTimer22m_snTimeInMillisecondsE"));
	}
}
namespace CTouchInterface{
	enum WidgetIDs : uint32 {WIDGET_PHONE = 26};
	bool (*IsReleased)(WidgetIDs WidgetID, FVector2D* pVecOut, int nFrameCount);
	inline void _Init(){
		SET_TO(IsReleased, SYM("_ZN8ViceCity15CTouchInterface10IsReleasedENS0_9WidgetIDsEP9FVector2Di"));
	}
}
enum PedState {PED_ANSWER_MOBILE = 36};
struct CPed{
	private: byte gap0[908];
	public: PedState m_nPedState;
}; VALIDATE_OFFSET(CPed, m_nPedState, 908);
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
	CPed* (*FindPlayerPed)();
	void (*InvincibilityCheat)();
	uint32 (*OS_ScreenGetHeight)();
	uint32 (*OS_ScreenGetWidth)();
	bool (*SaveGameForPause)(eSaveTypes saveType);
	void _Init(){
		SET_TO(AllowMissionReplay, SYM("_ZN8ViceCity18AllowMissionReplayE"));
		SET_TO(FindPlayerPed, SYM("_ZN8ViceCity13FindPlayerPedEv"));
		SET_TO(InvincibilityCheat, SYM("_ZN8ViceCity18InvincibilityCheatEv"));
		SET_TO(OS_ScreenGetHeight, SYM("_Z18OS_ScreenGetHeightv"));
		SET_TO(OS_ScreenGetWidth, SYM("_Z17OS_ScreenGetWidthv"));
		SET_TO(SaveGameForPause, SYM("_ZN8ViceCity16SaveGameForPauseEi"));
	}
}

bool bEnableAutoSave, bSaveInInteriors, bModernFonts, bSkipPhoneCall, bFixLLBridgesTraffic, bFixMissingTextKey,
	bSkipJustDown = false;
int nLastSavingTime, nSaveIntervalTime;
float fMaxFPSToCalcColor;

DECL_HOOKv(CGame__Process){
	CGame__Process();
	if(bEnableAutoSave && ViceCity::CTimer::m_snTimeInMilliseconds){
		uint32 nTimeInMs = *ViceCity::CTimer::m_snTimeInMilliseconds;
		if(!nLastSavingTime) nLastSavingTime = nTimeInMs;
		else if(nTimeInMs - nLastSavingTime > nSaveIntervalTime){
			bool bPlayerIsInGarage = false;
			for(auto& gar : *CGarages::aGarages)
				if((gar.m_eGarageType - 24 <= 8 || gar.m_eGarageType - 16 <= 2)
					&& !CGarage::IsPlayerOutsideGarage(&gar)){ //TODO：貌似不能用
					bPlayerIsInGarage = true;
					break;
				}
			if(!*ViceCity::AllowMissionReplay && !bPlayerIsInGarage && (bSaveInInteriors || !*CGame::currArea)){
				bool res = ViceCity::SaveGameForPause(eSaveTypes::eExitSave);
				logger->Info("Autosave %s", res ? "completed" : "failed");
			} else logger->Info("Autosave skipped %d %d (%d %d)", !*AllowMissionReplay, !bPlayerIsInGarage, bSaveInInteriors, !*CGame::currArea);
			nLastSavingTime = nTimeInMs;
		}
	}
	if(bSkipPhoneCall){
		CPed* pPed = ViceCity::FindPlayerPed();
		if(pPed && pPed->m_nPedState == PED_ANSWER_MOBILE){
			if(!bSkipJustDown && CTouchInterface::IsReleased(CTouchInterface::WIDGET_PHONE, nullptr, 2)) //TODO: 按过一次就永远返回true了？？
				bSkipJustDown = true;
		} else bSkipJustDown = false;
	}
	if(bFixMissingTextKey){
		static bool fixed;
		if(!fixed)
			UGameterSettings::OnLanguageSetEv(UGTASingleton::GetSettings(false, false, false)),
			fixed = true;
	}
	if(bFixLLBridgesTraffic){
		#define givar(n) *((int*)*CTheScripts::ScriptSpace + n)
		if(givar(541) && !givar(1239)){ //TODO：貌似不能用
			logger->Info("Fixing LLBridgeTraffic");
			CPathFind::SwitchRoadsOffInArea(ThePaths, -291.0, -287.0, 0.0, 208.0, 648.0, 35.0, false);
			CPathFind::SwitchRoadsOffInArea(ThePaths, -291.0, -287.0, 0.0, 208.0, 648.0, 35.0, false);
			CPathFind::SwitchRoadsOffInArea(ThePaths, -283.0, 372.0, 0.0, -137.0, 608.0, 35.0, false);
			givar(1239) = 2;
		}
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
		CFont::SetFontStyle(bModernFonts ? CFont::FONT_STANDARD : CFont::FONT_BANK);
		CFont::SetJustifyOn();
		CFont::SetScale(2.3*0.54f, 2.3f);  
		CFont::SetWrapx(1000.f);
		CFont::PrintString(fPxX * 32, fPxY * 8, szW, nullptr);
		delete[] szW;
	}
}

DECL_HOOKv(CPad__AddToPCCheatString, void* self, char LastPressedKey, bool doCheatTest){
	CPad__AddToPCCheatString(self, LastPressedKey, doCheatTest);
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
		if(CPad::_TestCheat("truegod", 7)){
			static char16_t* text = new char16_t[20];
			InvincibilityCheat();
			if(*CMenuManager::m_PrefsInvincibility)
				AsciiToGxtChar("CHEAT1", text);
			else AsciiToGxtChar("CHEAT8", text);
			*CMenuManager::m_PrefsCarInvincibility = *CMenuManager::m_PrefsInvincibility;
			CHud::SetHelpMessage(text, false, false, false, 0);
		}
	}
}

DECL_HOOK(int8, CRunningScript__ProcessCommands900To999, _CRunningScript* self, int command){
	int8 result = CRunningScript__ProcessCommands900To999(self, command);
	if(command == 978 && bSkipJustDown) CRunningScript::UpdateCompareFlag(self, true);
	return result;
}

void Init(){
	ViceCity::_Init();
	UGameterSettings::_Init();
	UGTASingleton::_Init();
	bool bFPSShowAvailable = ViceCity::AGTAHud::_Init();
	ViceCity::CFont::_Init();
	ViceCity::CGame::_Init();
	ViceCity::CGarage::_Init();
	ViceCity::CGarages::_Init();
	ViceCity::CHud::_Init();
	ViceCity::CMenuManager::_Init();
	ViceCity::CPad::_Init();
	ViceCity::CPathFind::_Init();
	ViceCity::CRunningScript::_Init();
	ViceCity::CTimer::_Init();
	ViceCity::CTheScripts::_Init();
	ViceCity::CTouchInterface::_Init();

	cfg->Bind("IdeasFrom", "", "About")->SetString("GTAForums/Jack, GTAForums/Marsi4eg");

	bEnableAutoSave = cfg->GetBool("Enabled", true, "AutoSave");
	ConfigEntry* entry = cfg->Bind("IntervalTime", 20, "AutoSave");
	if(entry->GetInt() < 10) entry->SetInt(10);
	nSaveIntervalTime = entry->GetInt() * 1000;
	bSaveInInteriors = cfg->GetBool("SaveInInteriors", true, "AutoSave");

	if (bFPSShowAvailable){ //内存地址每个版本都不同
		if(cfg->GetBool("ShowFPS", true, "Debugging"))
			HOOKSYM(AGTAHUD__UpdatePerfHUD, hUE4, "_ZN7AGTAHUD13UpdatePerfHUDEbRK7FVectorRK7FString");
		bModernFonts = cfg->GetBool("UseModernFonts", true, "Debugging");
		fMaxFPSToCalcColor = cfg->GetFloat("MaxFPSToShowColor", 30.f, "Debugging");
	}

	if(cfg->GetBool("AllowAutoAimingOnMG", true, "Gameplay")){
		aml->PlaceNOP(SYM("_ZN8ViceCity10CPlayerPed22FindWeaponLockOnTargetEi")+0xD8, 2);
		uintptr_t ProcessPlayerWeapon_Internal = SYM("_ZN8ViceCity10CPlayerPed28ProcessPlayerWeapon_InternalEv");
		aml->PlaceNOP(ProcessPlayerWeapon_Internal+0xA28, 2);
		aml->PlaceNOP(ProcessPlayerWeapon_Internal+0xE08, 2);
		aml->PlaceNOP(ProcessPlayerWeapon_Internal+0xF98, 2); // TODO: NOP
		aml->PlaceNOP(ProcessPlayerWeapon_Internal+0x1658, 2);
		aml->PlaceNOP(ProcessPlayerWeapon_Internal+0x1C04, 2);
	}

	if((bSkipPhoneCall = cfg->GetBool("AbleToSkipTelephoneCall", true, "Gameplay")))
		HOOKSYM(CRunningScript__ProcessCommands900To999, hUE4, "_ZN8ViceCity14CRunningScript23ProcessCommands900To999Ei");
	bFixMissingTextKey = cfg->GetBool("FixMissingTextKey", true, "Visual");
	bFixLLBridgesTraffic = cfg->GetBool("FixLeafLinksBridgesTraffic", true, "Gameplay");

	HOOKSYM(CGame__Process, hUE4, "_ZN8ViceCity5CGame7ProcessEv");
	HOOKSYM(CPad__AddToPCCheatString, hUE4, "_ZN8ViceCity4CPad18AddToPCCheatStringEcb");
	
	cfg->Save(); // Will only save if something was changed
}
}