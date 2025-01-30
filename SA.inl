namespace GTASA{
enum eModelID : uint16 {MODEL_PREDATOR = 430};
enum eDoors : uint32 {BONNET, BOOT, FRONT_LEFT_DOOR, FRONT_RIGHT_DOOR, REAR_LEFT_DOOR, REAR_RIGHT_DOOR, MAX_DOORS};
eDoors operator++(eDoors& i, int){i = (eDoors)((uint32)i + 1); return i;}
struct CVehicle{
	private: byte gap0[0x3A];
	public: eModelID m_nModelIndex;
}; VALIDATE_OFFSET(CVehicle, m_nModelIndex, 0x3A);
namespace CAchievement{
	bool *messagedAboutCheating;
	inline void _Init(){
		SET_TO(messagedAboutCheating, SYM("_ZN12CAchievement21messagedAboutCheatingE"));
	}
}
namespace CAutomobile{
	void (*CloseAllDoors)(CVehicle* self);
	bool (*IsDoorFullyOpen)(const CVehicle *self, eDoors DoorID);
	bool (*IsDoorMissing)(const CVehicle *self, eDoors DoorID);
	void (*OpenDoor)(CVehicle *self, void *pPed, int index, eDoors DoorID, float timeRatio, bool bPlaySoundSample);
	void _Init(){
		SET_TO(CloseAllDoors, SYM("_ZN11CAutomobile13CloseAllDoorsEv"));
		SET_TO(IsDoorFullyOpen, SYM("_ZNK11CAutomobile15IsDoorFullyOpenE6eDoors"));
		SET_TO(IsDoorMissing, SYM("_ZNK11CAutomobile13IsDoorMissingE6eDoors"));
		SET_TO(OpenDoor, SYM("_ZN11CAutomobile8OpenDoorEP4CPedi6eDoorsfb"));
	}
}
namespace CCheat{
	bool (*m_aCheatsActive)[105];
	bool *m_bHasPlayerCheated;
	char16_t* *m_CheatString;
	uint32 *m_nCheatStringSize; //这个实际上是前一个FString的长度成员
	void (*ScriptBypassCheat)();
	void (*TimeTravelCheat)();
	//void (*TogglePlayerInvincibility)();
	CVehicle* (*VehicleCheat)(int modelId, bool bSpawnAsPlayerRemoteControl, float);
	void (*WeaponCheat4)();

	void _Init(){
		SET_TO(m_aCheatsActive, SYM("_ZN6CCheat15m_aCheatsActiveE"));
		SET_TO(m_bHasPlayerCheated, SYM("_ZN6CCheat19m_bHasPlayerCheatedE"));
		SET_TO(m_CheatString, SYM("_ZN6CCheat13m_CheatStringE"));
		SET_TO(m_nCheatStringSize, uintptr_t(m_CheatString) + sizeof(m_CheatString));
		SET_TO(ScriptBypassCheat, SYM("_ZN6CCheat17ScriptBypassCheatEv"));
		SET_TO(TimeTravelCheat, SYM("_ZN6CCheat15TimeTravelCheatEv"));
		SET_TO(VehicleCheat, SYM("_ZN6CCheat12VehicleCheatEibf"));
		//SET_TO(TogglePlayerInvincibility, SYM("_ZN6CCheat25TogglePlayerInvincibilityEv"));
		SET_TO(WeaponCheat4, SYM("_ZN6CCheat12WeaponCheat4Ev"));
	}

	bool _TestCheat(const char* text, int size){
		if(*CCheat::m_nCheatStringSize < size+1) return false;
		char* pos1 = (char*)(*CCheat::m_CheatString + (*m_nCheatStringSize-size-1));
		const char* pos2 = text;
		while(true){
			if(*pos1 && (tolower(*pos1++) != tolower(*pos2++)))
				return false;
			pos1++;
			if(!*((char16_t*)pos1)){ //其实是个很蠢的对比方案，这也是宽字符恶心的地方
				*CCheat::m_nCheatStringSize = 0;
				(*CCheat::m_CheatString)[0] = 0;
				return true;
			}
		}
	}
}
enum eModelID : uint16;
enum AssocGroupId : uint32;
struct _CPed{
	private: byte gap0[0x3A];
	public: eModelID m_nModelIndex;
	private: byte gap3C[0x6A4];
	public: AssocGroupId m_nAnimGroup;
}; VALIDATE_OFFSET(_CPed, m_nAnimGroup, 0x6E0);
namespace CClothes{
	void (*RebuildPlayer)(_CPed* player, bool bIgnoreFatAndMuscle);
	inline void _Init(){
		SET_TO(RebuildPlayer, SYM("_ZN8CClothes13RebuildPlayerEP10CPlayerPedb"));
	}
}
namespace CDamageManager{
	int (*GetCarNodeIndexFromDoor)(eDoors DoorIndex);
	inline void _Init(){
		SET_TO(GetCarNodeIndexFromDoor, SYM("_ZN14CDamageManager23GetCarNodeIndexFromDoorE6eDoors"));
	}
}
struct CEntryExit {
	char    m_szName[8];
	CRect   m_recEntrance;
	float   m_fEntranceZ;
	float   m_fEntranceAngleRad;
	CVector m_vecExitPos;
	float   m_fExitAngle;
	union {
		struct {
			uint16 bUnknownInterior : 1;     // 0x1
			uint16 bUnknownPairing : 1;      // 0x2
			uint16 bCreateLinkedPair : 1;    // 0x4
			uint16 bRewardInterior : 1;      // 0x8
			uint16 bUsedRewardEntrance : 1;  // 0x10
			uint16 bCarsAndAircraft : 1;     // 0x20
			uint16 bBikesAndMotorcycles : 1; // 0x40
			uint16 bDisableOnFoot : 1;       // 0x80

			uint16 bAcceptNpcGroup : 1;      // 0x100
			uint16 bFoodDateFlag : 1;        // 0x200
			uint16 bUnknownBurglary : 1;     // 0x400
			uint16 bDisableExit : 1;         // 0x800
			uint16 bBurglaryAccess : 1;      // 0x1000
			uint16 bEnteredWithoutExit : 1;  // 0x2000
			uint16 bEnableAccess : 1;        // 0x4000
			uint16 bDeleteEnex : 1;          // 0x8000
		};
		uint16 m_nFlags;
	};
	uint8       m_nArea;
	uint8       m_nSkyColor;
	uint8       m_nTimeOn;
	uint8       m_nTimeOff;
	uint8       m_nNumberOfPeds;
	CEntryExit* m_pLink;
}; VALIDATE_SIZE(CEntryExit, 64);
template <class A, class B = A> struct CPool {
	B*     m_pObjects;
	uint8* m_byteMap;
	int32  m_nSize;
	int32  m_nFirstFree;
	bool   m_bOwnsAllocations;
	bool   m_bIsLocked; // Seemingly not used anywhere, only toggled on/off
};
typedef CPool<CEntryExit> CEntryExitsPool;
namespace CEntryExitManager{
	CEntryExitsPool* *mp_poolEntryExits;
	int (*FindNearestEntryExit)(const CVector2D& position, float range, int ignoreArea);
	void _Init(){
		SET_TO(mp_poolEntryExits, SYM("_ZN17CEntryExitManager17mp_poolEntryExitsE"));
		SET_TO(FindNearestEntryExit, SYM("_ZN17CEntryExitManager20FindNearestEntryExitERK9CVector2Dfi"));
	}
}
namespace CFont{
	enum eFontStyle : uint8 {
		FONT_GOTHIC, FONT_SUBTITLES, FONT_MENU, FONT_PRICEDOWN
	};
	enum class eFontAlignment : uint8 {
		ALIGN_UNDEFINED = 0xFF,
		ALIGN_CENTER = 0,
		ALIGN_LEFT,
		ALIGN_RIGHT
	};
	void (*PrintString)(float x, float y, char16_t* text);
	void (*SetColor)(CRGBA& color);
	void (*SetDropShadowPosition)(int16 value);
	void (*SetEdge)(int8 value);
	void (*SetFontStyle)(eFontStyle style);
	void (*SetJustify)(bool on);
	void (*SetOrientation)(eFontAlignment alignment);
	void (*SetScale)(float h);
	void (*SetWrapx)(float value);
	void _Init(){
		SET_TO(PrintString, SYM("_ZN5CFont11PrintStringEffPt"));
		SET_TO(SetColor, SYM("_ZN5CFont8SetColorE5CRGBA"));
		SET_TO(SetDropShadowPosition, SYM("_ZN5CFont21SetDropShadowPositionEa"));
		SET_TO(SetEdge, SYM("_ZN5CFont7SetEdgeEa"));
		SET_TO(SetFontStyle, SYM("_ZN5CFont12SetFontStyleEh"));
		SET_TO(SetJustify, SYM("_ZN5CFont10SetJustifyEh"));
		SET_TO(SetOrientation, SYM("_ZN5CFont14SetOrientationEh"));
		SET_TO(SetScale, SYM("_ZN5CFont8SetScaleEf"));
		SET_TO(SetWrapx, SYM("_ZN5CFont8SetWrapxEf"));
	}
}
namespace CGame{
	int* currArea;
	inline void _Init(){
		SET_TO(currArea, SYM("_ZN5CGame8currAreaE"));
	}
}
enum eGarageType : uint8 {
	SAFEHOUSE_SANTAMARIA = 17, GARAGE_HIDEOUT_TWO = 17,
	SAFEHOUSE_ROCKSHORE = 18,  GARAGE_HIDEOUT_THREE = 18,
}; using eGarageDoorState = uint8;
struct STRU_PACKED_ALIGNED(4) _CGarage{
	CVector Base;
	CVector2D Delta1;
	CVector2D Delta2;
	float CeilingZ;
	float Delta1Length;
	float Delta2Length;
	float MinX;
	float MaxX;
	float MinY;
	float MaxY;
	float Openness;
	uint32 TimeOfNextEvent;
	struct CVehicle *pCarToCollect;
	uchar Name[8];
	eGarageType Type;
	eGarageDoorState State;
	union {
		uint8 Flags;
		struct {
			uint8 bClosingEmpty : 1;
			uint8 bDeActivated : 1;
			uint8 bResprayHappened : 1;
			uint8 bRotatyDoor : 1;
			uint8 bInvertRotation : 1;
			uint8 bLeaveCameraAlone : 1;
			uint8 bShouldDoorsHaveCollision : 1;
			uint8 bFreeResprays : 1;
		};
	};
	eGarageType OriginalType;
	private: byte m_DoorAudioEntity[200];
}; VALIDATE_SIZE(_CGarage, 0x11C); VALIDATE_OFFSET(_CGarage, Type, 80);
namespace CGarage{
	bool (*IsPlayerOutsideGarage)(_CGarage* self);
	inline void _Init(){
		SET_TO(IsPlayerOutsideGarage, SYM("_ZN7CGarage21IsPlayerOutsideGarageEf"));
	}
}
namespace CGarages{
	_CGarage (*aGarages)[50];
	inline void _Init(){
		SET_TO(aGarages, SYM("_ZN8CGarages8aGaragesE"));
	}
}
namespace CHud{
	void (*SetHelpMessage)(const FString& text, bool quickMessage, bool permanent, bool addToBrief, uint32, int);
	inline void _Init(){
		SET_TO(SetHelpMessage, SYM("_ZN4CHud14SetHelpMessageERK7FStringbbbji"));
	}
}
enum eVehicleType {
	VEHICLE_TYPE_NONE = -1, VEHICLE_TYPE_CAR, VEHICLE_TYPE_MONSTERTRUCK,
	VEHICLE_TYPE_QUADBIKE, VEHICLE_TYPE_HELI, VEHICLE_TYPE_PLANE, VEHICLE_TYPE_BOAT, VEHICLE_TYPE_TRAIN,
	VEHICLE_TYPE_NOT_USED, VEHICLE_TYPE_FAKE_PLANE, VEHICLE_TYPE_BIKE, VEHICLE_TYPE_BMX, VEHICLE_TYPE_TRAILER
};
namespace CModelInfo{
	eVehicleType (*IsVehicleModelType)(int index);
	inline void _Init(){
		SET_TO(IsVehicleModelType, SYM("_ZN10CModelInfo18IsVehicleModelTypeEi"));
	}
}
struct _CPad{
	private: byte gap0[0x15A];
	public:  bool bDisablePlayerDuck;
	private: byte gap15B[0x25];
}(*Pads)[2]; VALIDATE_SIZE(_CPad, 0x180); VALIDATE_OFFSET(_CPad, bDisablePlayerDuck, 0x15A);
namespace CPad{
	uintptr_t GetCarGunFired;
	uintptr_t GetPedWalkLeftRight;
	uintptr_t GetPedWalkUpDown;
	inline void _Init(){
		SET_TO(Pads, SYM("Pads"));
		SET_TO(GetCarGunFired, SYM("_ZN4CPad14GetCarGunFiredEbbb"));
		SET_TO(GetPedWalkLeftRight, SYM("_ZN4CPad19GetPedWalkLeftRightEbi"));
		SET_TO(GetPedWalkUpDown, SYM("_ZN4CPad16GetPedWalkUpDownEbi"));
	}
}
namespace CPed{
	void (*DeleteRwObject)(_CPed* self);
	void (*SetModelIndex)(_CPed* self, uint32 modelIndex);
	inline void _Init(){
		SET_TO(DeleteRwObject, SYM("_ZN4CPed14DeleteRwObjectEv"));
		SET_TO(SetModelIndex, SYM("_ZN4CPed13SetModelIndexEj"));
	}
}
enum ePickupType : uint8 {
	PICKUP_NONE, PICKUP_IN_SHOP, PICKUP_ON_STREET, PICKUP_ONCE, PICKUP_ONCE_TIMEOUT, PICKUP_ONCE_TIMEOUT_SLOW,
	PICKUP_COLLECTABLE1, PICKUP_IN_SHOP_OUT_OF_STOCK, PICKUP_MONEY, PICKUP_MINE_INACTIVE , PICKUP_MINE_ARMED,
	PICKUP_NAUTICAL_MINE_INACTIVE, PICKUP_NAUTICAL_MINE_ARMED, PICKUP_FLOATINGPACKAGE, PICKUP_FLOATINGPACKAGE_FLOATING,
	PICKUP_ON_STREET_SLOW, PICKUP_ASSET_REVENUE, PICKUP_PROPERTY_LOCKED, PICKUP_PROPERTY_FORSALE,
	PICKUP_MONEY_DOESNTDISAPPEAR, PICKUP_SNAPSHOT, PICKUP_2P, PICKUP_ONCE_FOR_MISSION
};
struct STRU_PACKED_ALIGNED(4) CPickup{
	float            CurrentValue;
	struct CObject*  pObject;
	uint32           MonetaryValue;
	uint32           RegenerationTime;
	CompressedVector Coors;
	uint16           MoneyPerDay;
	int16            MI;
	int16            ReferenceIndex;
	ePickupType      Type;
	struct {
		uint8 State : 1; // waiting for regeneration
		uint8 bNoAmmo : 1;    // no ammo
		uint8 bHelpMessageDisplayed : 1;
		uint8 bIsPickupNearby : 1;
		uint8 TextIndex : 3; // see enum ePickupPropertyText
	} m_nFlags;
}; VALIDATE_SIZE(CPickup, 36);
namespace CPickups{
	CPickup (*aPickUps)[620];
	inline void _Init(){
		SET_TO(aPickUps, SYM("_ZN8CPickups8aPickUpsE"));
	}
}
namespace CPlayerPed{
	bool *bDebugPlayerInvincible;
	inline void _Init(){
		SET_TO(bDebugPlayerInvincible, SYM("_ZN10CPlayerPed22bDebugPlayerInvincibleE"));
	}
}
/*struct CZoneInfo{
	uint8 GangDensity[10];
  	uint8 DrugDealerCounter;
	CRGBA ZoneColor;
	struct{
		uint8 zonePopulationType : 5;
		uint8 radarMode : 2;
		uint8 noCops : 1;
		uint8 zonePopulationRace : 4;
	};
	auto GetSumOfGangDensity()const{
		uint32 sum = 0;
		for(uint8 i:GangDensity)
			sum += i;
		return sum;
	}
};
namespace CPopCycle{
	CZoneInfo* *m_pCurrZoneInfo;
	void _Init(){
		SET_TO(m_pCurrZoneInfo, SYM("_ZN9CPopCycle15m_pCurrZoneInfoE"));
	}
}*/
using eBlipColour = uint32;
enum eRadarSprite : int8 { RADAR_SPRITE_NONE };
using eBlipDisplay = uint8; using eBlipType = uint8; using eBlipAppearance = uint8;
struct tRadarTrace{
	eBlipColour  m_nColour;
	uint32       m_nEntityHandle;
	CVector      m_vPosition;
	uint16       m_nCounter;
	float        m_fSphereRadius;
	uint16       m_nBlipSize;
	CEntryExit*  m_pEntryExit;
	eRadarSprite m_nBlipSprite;
	bool         m_bBright : 1;              // It makes use of bright colors. Always set.
	bool         m_bTrackingBlip : 1;        // It is available.
	bool         m_bShortRange : 1;          // It doesn't show permanently on the radar.
	bool         m_bFriendly : 1;            // It is affected by BLIP_COLOUR_THREAT.
	bool         m_bBlipRemain : 1;          // It has the priority over the entity (it will still appear after the entity's deletion).
	bool         m_bBlipFade : 1;            // Possibly a leftover. Always unset (unused).
	uint8        m_nCoordBlipAppearance : 2; // see eBlipAppearance
	eBlipDisplay    m_nBlipDisplayFlag : 2;
	eBlipType       m_nBlipType : 4;
	eBlipAppearance m_nAppearance : 2;
}; VALIDATE_SIZE(tRadarTrace, 0x30);
namespace CRadar{
	tRadarTrace (*ms_RadarTrace)[250];
	int (*GetCustomWaypointArrayIndex)(void* self);
	inline void _Init(){
		SET_TO(ms_RadarTrace, SYM("_ZN6CRadar13ms_RadarTraceE"));
		SET_TO(GetCustomWaypointArrayIndex, SYM("_ZN6CRadar27GetCustomWaypointArrayIndexEv"));
	}
}
namespace CRunningScript{
	void (*SetCharCoordinates)(void* self, _CPed* ped, float posnX, float posnY, float posnZ, bool warpGang, bool offset);
	inline void _Init(){
		SET_TO(SetCharCoordinates, SYM("_ZN14CRunningScript18SetCharCoordinatesEP4CPedfffbb"));
	}
}
enum eStats : uint16 { STAT_MUSCLE = 23, STAT_TIMES_CHEATED = 137 };
namespace CStats{
	float (*GetStatValue)(eStats stat);
	void (*IncrementStat)(eStats stat, float value);
	void (*SetStatValue)(eStats stat, float value);
	inline void _Init(){
		SET_TO(GetStatValue, SYM("_ZN6CStats12GetStatValueEt"));
		SET_TO(IncrementStat, SYM("_ZN6CStats13IncrementStatEtf"));
		SET_TO(SetStatValue, SYM("_ZN6CStats12SetStatValueEtf"));
	}
}
enum eStreamingLoadState : uint8 {LOADSTATE_NOT_LOADED, LOADSTATE_LOADED, };
struct STRU_ALIGNED(4) CStreamingInfo{
	private: byte gap0[8];
	public:  short m_nextIndex, m_prevIndex;
	private: byte gapC;
 	public:  byte m_status;
}; VALIDATE_SIZE(CStreamingInfo, 16); VALIDATE_OFFSET(CStreamingInfo, m_status, 0xD); //DE的这个结构和原版不同
enum eStreamingFlags{STREAMING_GAME_REQUIRED = 0x2};
namespace CStreaming{
	CStreamingInfo (*ms_aInfoForModel)[26316];
	void (*RequestModel)(int modelId, eStreamingFlags flags, bool);
	void (*LoadAllRequestedModels)(bool); //逆天GSG工作室特有的无意义bool参数
	void (*SetModelIsDeletable)(int modelId);
	inline void _Init(){
		SET_TO(ms_aInfoForModel, SYM("_ZN10CStreaming16ms_aInfoForModelE"));
		SET_TO(RequestModel, SYM("_ZN10CStreaming12RequestModelEiib"));
		SET_TO(LoadAllRequestedModels, SYM("_ZN10CStreaming22LoadAllRequestedModelsEb"));
		SET_TO(SetModelIsDeletable, SYM("_ZN10CStreaming19SetModelIsDeletableEi"));
	}
}
namespace CTheScripts{
	//bool (*IsPlayerOnAMission)();
	byte (*ScriptSpace)[339000];
	inline void _Init(){
		//SET_TO(IsPlayerOnAMission, SYM("_ZN11CTheScripts18IsPlayerOnAMissionEv"));
		SET_TO(ScriptSpace, SYM("_ZN11CTheScripts11ScriptSpaceE"));
	}
}
namespace CTimer{
	float  *game_FPS;
	uint32 *m_snTimeInMilliseconds;
	float  *ms_fTimeScale;
	void _Init(){
		SET_TO(game_FPS, SYM("_ZN6CTimer8game_FPSE"));
		SET_TO(m_snTimeInMilliseconds, SYM("_ZN6CTimer22m_snTimeInMillisecondsE"));
		SET_TO(ms_fTimeScale, SYM("_ZN6CTimer13ms_fTimeScaleE"));
	}
}
struct _UGameterSettings;
namespace UGameterSettings{
	void (*OnLanguageSetEv)(_UGameterSettings* self);
	inline void _Init(){
		SET_TO(OnLanguageSetEv, SYM("_ZN16UGameterSettings13OnLanguageSetEv"));
	}
}
namespace UGTASingleton{
	_UGameterSettings* (*GetSettings)(bool ForceRefresh, bool bForceUpdateAudio, bool forceNoChanges);
	inline void _Init(){
		SET_TO(GetSettings, SYM("_ZN13UGTASingleton11GetSettingsEbbb"));
	}
}
namespace {
	int *AllowMissionReplay;
	//void (*AsciiToGxtChar)(const char* src, wchar_t* dst);
	_CPed* (*FindPlayerPed)(int playerId);
	CVehicle* (*FindPlayerVehicle)(int playerId, bool bIncludeRemote);
	uint32 (*OS_ScreenGetHeight)();
	uint32 (*OS_ScreenGetWidth)();
	bool (*SaveGameForPause)(eSaveTypes saveType, char* saveName);

	void _Init(){
		SET_TO(AllowMissionReplay, SYM("AllowMissionReplay"));
		//SET_TO(AsciiToGxtChar, SYM("_Z14AsciiToGxtCharPKcPt"));
		SET_TO(FindPlayerPed, SYM("_Z13FindPlayerPedi"));
		SET_TO(FindPlayerVehicle, SYM("_Z17FindPlayerVehicleib"));
		SET_TO(OS_ScreenGetHeight, SYM("_Z18OS_ScreenGetHeightv"));
		SET_TO(OS_ScreenGetWidth, SYM("_Z17OS_ScreenGetWidthv"));
		SET_TO(SaveGameForPause, SYM("_Z16SaveGameForPause10eSaveTypesPc"));
	}
}
bool OpenVehDoor(CVehicle* pVeh, eDoors DoorID, float timeRatio, bool bPlaySoundSample){
	eVehicleType type = CModelInfo::IsVehicleModelType(pVeh->m_nModelIndex);
	if(type == VEHICLE_TYPE_CAR || type == VEHICLE_TYPE_HELI || type == VEHICLE_TYPE_PLANE || type == VEHICLE_TYPE_MONSTERTRUCK){
		int nodeIdx = CDamageManager::GetCarNodeIndexFromDoor(DoorID);
		if(!CAutomobile::IsDoorMissing(pVeh, DoorID)
			&& *(int*)((uintptr_t)pVeh + 2384 + 4 * nodeIdx) != -1){
				CAutomobile::OpenDoor(pVeh, nullptr, nodeIdx, DoorID, timeRatio, true);
				return true;
			}
	}
	return false;
}


bool bRestoreDebuggingCheats, bIncreaseTimesCheated, bEnableTP, bShowFPS, bModernFonts, bEnableAutoSave, bSaveInInteriors, bFixMissingTextKey,
	bFixIconInSea, bColorZoneName, bFixBoatMovingHi, bFixMissingShootBtnForPredator; uint8 nLastPatchGetCarGunFired;
int nLastSavingTime, nSaveIntervalTime;
float fMaxFPSToCalcColor;

void RespondCheatActivited(bool activited){
	static char16_t* text = new char16_t[20];
	if(activited)AsciiToGxtChar("CHEAT1", text); //不能用字面量
	else AsciiToGxtChar("CHEAT8", text);
	CHud::SetHelpMessage(text, true, false, false, 0, 0);
	if(bIncreaseTimesCheated){
		*CAchievement::messagedAboutCheating = true; //没什么用，游戏内实现作弊反馈也有那我就写了
		*CCheat::m_bHasPlayerCheated = true;
		CStats::IncrementStat(STAT_TIMES_CHEATED, 1.f);
	}
}

DECL_HOOKv(CCheat__AddToCheatString, char LastPressedKey, bool p2){
	CCheat__AddToCheatString(LastPressedKey, p2);
	if(*CCheat::m_CheatString && *CCheat::m_nCheatStringSize){
		char buffer[31]={};
		char* pos3=buffer, *pos1 = (char*)*CCheat::m_CheatString;
		int len = 1;
		while(true){
			if(*pos1) *pos3++ = *pos1, len++;
			pos1++;
			if(len == *CCheat::m_nCheatStringSize)break;
		}
		logger->Info("CheatString %s", buffer);
		if(!bRestoreDebuggingCheats) return;
		static int nID;
		static bool bInputtedNum = false;
		if(isdigit(LastPressedKey))
			nID = 10 * nID + LastPressedKey - '0', bInputtedNum = true;
		else{
			if(toupper(LastPressedKey) == 'S' && bInputtedNum){
				auto type = CModelInfo::IsVehicleModelType(nID);
				if(type != VEHICLE_TYPE_NONE && type != VEHICLE_TYPE_TRAIN){ //VehicleCheat()没有实现刷火车，强制刷出会崩
					logger->Info("Spawn %d", nID);
					*CCheat::m_nCheatStringSize = 0;
					(*CCheat::m_CheatString)[0] = 0;
					if(CCheat::VehicleCheat(nID, false, 1.0))
						RespondCheatActivited(true);
				}
			}else if(toupper(LastPressedKey) == 'T' && bInputtedNum){
				// static float muscle = 200.f;
				_CPed* ped = FindPlayerPed(-1);
				if(ped){ //下面的部分基本算是几个opcode的重新实现（参考了KaizoM的脚本https://www.mixmods.com.br/2022/01/simple-skin-selector-ped-creator/）
					//if(nID) muscle = CStats::GetStatValue(STAT_MUSCLE), CStats::SetStatValue(STAT_MUSCLE, 200.f);
					//else CStats::SetStatValue(STAT_MUSCLE, muscle);
					//CClothes::RebuildPlayer(ped, false);
					CStreaming::RequestModel(nID, STREAMING_GAME_REQUIRED, false);
					CStreaming::LoadAllRequestedModels(false);
					if((*CStreaming::ms_aInfoForModel)[nID].m_status == LOADSTATE_LOADED){
						AssocGroupId ang = ped->m_nAnimGroup;
						CPed::DeleteRwObject(ped);
						ped->m_nModelIndex = (eModelID)-1;
						CPed::SetModelIndex(ped, nID);
						ped->m_nAnimGroup = ang;
						CStreaming::SetModelIsDeletable(nID);
						if(nID) (*Pads)[0].bDisablePlayerDuck = true; //DE的bug导致改变模型后下蹲崩溃，暂时解决办法是禁止蹲下
						else {										  //万一有脚本把这个值改回来了（某些任务）就坏事了
							(*Pads)[0].bDisablePlayerDuck = false;
							CClothes::RebuildPlayer(ped, false);
						}
						RespondCheatActivited(true);
					}
				}
			}
			nID = 0, bInputtedNum = false;
		}
		if(CCheat::_TestCheat("teleport", 8)){
			_CPed* ped = FindPlayerPed(-1);
			if(ped){
				int index = CRadar::GetCustomWaypointArrayIndex(nullptr); //实际上游戏中存在CRadar::GetWaypointBlipPos的函数，但是返回值不能用
				if(index != -1){ //这里确保目标有效
					CVector coord = (*CRadar::ms_RadarTrace)[index].m_vPosition;
					logger->Info("Target %f %f", coord.x, coord.y);
					//CColStore__RequestCollision(coord, 0);
					CRunningScript::SetCharCoordinates(nullptr, ped, coord.x, coord.y, -100.f, true, true); //TODO: 提前载入该区域
					RespondCheatActivited(true);
				}
			}
		}
		if(CCheat::_TestCheat("slamdoors", 9)){
			CVehicle* pVeh = FindPlayerVehicle(-1, false);
			if(pVeh){
				bool toOpen = false, bSuccessful = false;
				for(eDoors i = BONNET; i < MAX_DOORS; i++){
					if(!CAutomobile::IsDoorMissing(pVeh, i) && !CAutomobile::IsDoorFullyOpen(pVeh, i)){
						toOpen = true;
						break;
					}
				}
				if(toOpen){
					for(eDoors i = BONNET; i < MAX_DOORS; i++){
						if(OpenVehDoor(pVeh, i, 1.0, true))bSuccessful = true;
					}
					if(bSuccessful)RespondCheatActivited(true);
				} else {
					CAutomobile::CloseAllDoors(pVeh);
					OpenVehDoor(pVeh, BONNET, 0.0, true);
					OpenVehDoor(pVeh, BOOT, 0.0, true);
					RespondCheatActivited(false);
				}
			}
		}
		if(CCheat::_TestCheat("secretspyset", 12)){
			CCheat::WeaponCheat4();
			RespondCheatActivited(true);
		}
		if(CCheat::_TestCheat("timetraveler", 12)){
			CCheat::TimeTravelCheat();
			RespondCheatActivited(true);
		}
		if(CCheat::_TestCheat("freezeit", 8)){
			(*CCheat::m_aCheatsActive)[7]=!(*CCheat::m_aCheatsActive)[7];
			if(!(*CCheat::m_aCheatsActive)[7]) RespondCheatActivited(false);
			else RespondCheatActivited(true);
		}
		if(CCheat::_TestCheat("nopity", 6)){
			CCheat::ScriptBypassCheat();
			RespondCheatActivited(true);
		}
		if(CCheat::_TestCheat("truegod", 7)){
			*CPlayerPed::bDebugPlayerInvincible = !*CPlayerPed::bDebugPlayerInvincible;
			if(!*CPlayerPed::bDebugPlayerInvincible) RespondCheatActivited(false);
			else RespondCheatActivited(true);
		}
	}
}

DECL_HOOKv(CGame__Process){
	CGame__Process();
	static char szA[BUFSIZ]={};
	uint32 nScreenW = OS_ScreenGetWidth(), nScreenH = OS_ScreenGetHeight(); 
	float fPxX = float(nScreenW) / 1920.f, fPxY = float(nScreenH) / 1080.f;
	if(bShowFPS && CTimer::game_FPS && CTimer::ms_fTimeScale){
		memset(szA, 0, sizeof(szA));
		float fRealFPS = *CTimer::game_FPS * *CTimer::ms_fTimeScale;
		int n = sprintf(szA, "FPS: %05.2f", fRealFPS);
		if(n){
			char16_t* szW=new char16_t[n+2];
			AsciiToGxtChar(szA, szW);
			CRGBA color={};
			CalcColorBadToGood(fRealFPS, fMaxFPSToCalcColor, color);
  
			CFont::SetColor(color);
			CFont::SetDropShadowPosition(4);
			CFont::SetEdge(3);
			CFont::SetFontStyle(bModernFonts ? CFont::FONT_MENU : CFont::FONT_SUBTITLES);
			CFont::SetJustify(1);
			CFont::SetOrientation(CFont::eFontAlignment::ALIGN_LEFT);
			CFont::SetScale(1.3f);
			CFont::SetWrapx(1000.f);
			CFont::PrintString(fPxX * 32, fPxY * 8, szW);
			delete[] szW;
		}
	}
	if(bEnableAutoSave && CTimer::m_snTimeInMilliseconds){
		uint32 nTimeInMs = *CTimer::m_snTimeInMilliseconds;
		if(!nLastSavingTime) nLastSavingTime = nTimeInMs;
		else if(nTimeInMs - nLastSavingTime > nSaveIntervalTime){
			bool bPlayerIsInGarage = false;
			for(auto& gar : *CGarages::aGarages)
				if((1l<<gar.Type) & 0b1001111000000111111111000001110000000000000000 //省得去用很多的if-else
					&& !CGarage::IsPlayerOutsideGarage(&gar)){
					bPlayerIsInGarage = true;
					break;
				}
			if(!*AllowMissionReplay && !bPlayerIsInGarage && (bSaveInInteriors || !*CGame::currArea)){
				bool res = SaveGameForPause(eSaveTypes::eExitSave, nullptr);
				logger->Info("Autosave %s", res ? "completed" : "failed");
			} else logger->Info("Autosave skipped %d %d (%d %d)", !*AllowMissionReplay, !bPlayerIsInGarage, bSaveInInteriors, !*CGame::currArea);
			nLastSavingTime = nTimeInMs;
		}
	}
	if(bFixIconInSea){
		#define gfvar(n) *((float*)*CTheScripts::ScriptSpace + n)
		if(!int(gfvar(2944)) || !int(gfvar(2947)) || !int(gfvar(2978))){
			logger->Info("Repairing iconInSea glitch!");
			gfvar(2944) = -1969.27, gfvar(2947) = 316.0696, gfvar(2948) = 2441.002;
			for(CPickup& pickup : *CPickups::aPickUps){
				if(pickup.Type == PICKUP_NONE) continue;
				//logger->Info("Pickup %f %f %f", pickup.m_vecPos.x/8.f, pickup.m_vecPos.y/8.f, pickup.m_vecPos.z/8.f);
				if(pickup.Coors.x == 0 && int(pickup.Coors.y/8.f) == 282){
					pickup.Coors.x = -1969.27*8.f;
					break;
				}
			}
			for(tRadarTrace& blip : *CRadar::ms_RadarTrace){
				if(blip.m_nBlipSprite == RADAR_SPRITE_NONE) continue;
				//logger->Info("Blip %f %f %f", blip.m_vPosition.x, blip.m_vPosition.y, blip.m_vPosition.z);
				if(int(blip.m_vPosition.x) == 0 && int(blip.m_vPosition.y) == 282) blip.m_vPosition.x = -1969.27;
				else if(int(blip.m_vPosition.x) == 0 && int(blip.m_vPosition.y) == -1772) blip.m_vPosition.x = 316.0696;
				else if(int(blip.m_vPosition.x) == 0 && int(blip.m_vPosition.y) == 695) blip.m_vPosition.x = 2441.002;
			}
			int index = 0;
			for(auto& gar : *CGarages::aGarages){ //这是防止房子还没买就给解锁enex了（但未经测试）
				if(gar.Type == GARAGE_HIDEOUT_TWO && !gar.bDeActivated
					&& (index = CEntryExitManager::FindNearestEntryExit({316.0696, -1772.569}, 10.0, -1)))
					(*CEntryExitManager::mp_poolEntryExits)->m_pObjects[index].bEnableAccess = true;
				if(gar.Type == GARAGE_HIDEOUT_THREE && !gar.bDeActivated
					&& (index = CEntryExitManager::FindNearestEntryExit({2441.002, 695.1089}, 10.0, -1)))
					(*CEntryExitManager::mp_poolEntryExits)->m_pObjects[index].bEnableAccess = true;
			}
		}
	}
	if(bFixMissingShootBtnForPredator){
		CVehicle* veh = FindPlayerVehicle(-1, false);
		if(veh && veh->m_nModelIndex == MODEL_PREDATOR){
			if(nLastPatchGetCarGunFired != 1){
				logger->Info("Patching car gun");
				aml->Write8(CPad::GetCarGunFired+0x195, 0xB9);
				aml->Write8(CPad::GetCarGunFired+0x1E5, 0xB9);
				nLastPatchGetCarGunFired = 1;
			}
		}else{
			if(nLastPatchGetCarGunFired != 0){
				logger->Info("Unpatching car gun");
				aml->Write8(CPad::GetCarGunFired+0x195, 0x5D);
				aml->Write8(CPad::GetCarGunFired+0x1E5, 0x5D);
				nLastPatchGetCarGunFired = 0;
			}
		}
	}
	if(bFixMissingTextKey){
		static bool fixed;
		if(!fixed)
			UGameterSettings::OnLanguageSetEv(UGTASingleton::GetSettings(false, false, false)),
			fixed = true;
	}
	/*if(bFixBoatMovingHi){ //神奇UE之字符串指针在运行时初始化
		uintptr_t ms_vehicleDescs = SYM("_ZN17CVehicleModelInfo15ms_vehicleDescsE"),
			boatIds = *(uintptr_t*)(ms_vehicleDescs + 40);
		logger->Info("ms_vehicleDescs 0x%x  boatIds 0x%x", ms_vehicleDescs, boatIds);
		uintptr_t (*FName)(const char*, int, int);
		SET_TO(FName, SYM("_ZN5FNameC2EPKci9EFindName"));
		*(uintptr_t*)boatIds = FName("boat_moving", 11, 1);
		bFixBoatMovingHi = false;
	}*/
}
/*CRGBA* CalcZoneName(){
	if((*CPopCycle::m_pCurrZoneInfo)){
		CRGBA zoneColor=(*CPopCycle::m_pCurrZoneInfo)->ZoneColor;
		if(zoneColor.r || zoneColor.g || zoneColor.b){
			CRGBA c={};
			if(bColorZoneName){
				uint32 total = (*CPopCycle::m_pCurrZoneInfo)->GetSumOfGangDensity();
				float weight = std::min(3*total/120.f, 1.f), weight2 = 1-weight;
				c.r=sqrt(zoneColor.r*zoneColor.r*weight + zoneColor.g*zoneColor.g*weight2);
				c.g=sqrt(zoneColor.g*zoneColor.g*weight + zoneColor.b*zoneColor.b*weight2);
				c.b=sqrt(zoneColor.b*zoneColor.b*weight + zoneColor.a*zoneColor.a*weight2);
			}else{
				c.r=zoneColor.g;
				c.g=zoneColor.b;
				c.b=zoneColor.a;
			}
			return &c;
		}
	}
	return nullptr;
}

__attribute__((optnone))ASM_NAKED void CHud__DrawAreaName(){
	asm volatile(
		"PUSH {X0-X23, S0-S14}\n"
		"BL CalcZoneName\n"
		"MOV X24, X0\n"
		"POP {X0-X23, S0-S14}\n"

	);
}*/

void Init(){
	GTASA::_Init();
	UGameterSettings::_Init();
	UGTASingleton::_Init();
	CAchievement::_Init();
	CAutomobile::_Init();
	CCheat::_Init();
	CClothes::_Init();
	CDamageManager::_Init();
	CEntryExitManager::_Init();
	CFont::_Init();
	CGame::_Init();
	CGarage::_Init();
	CGarages::_Init();
	CHud::_Init();
	CModelInfo::_Init();
	CPad::_Init();
	CPed::_Init();
	CPickups::_Init();
	CPlayerPed::_Init();
	//CPopCycle::_Init();
	CRadar::_Init();
	CRunningScript::_Init();
	CStats::_Init();
	CStreaming::_Init();
	CTimer::_Init();
	CTheScripts::_Init();

	cfg->Bind("IdeasFrom", "", "About")->SetString("RusJJ, Silent, KaizoM");

	bEnableAutoSave = cfg->GetBool("Enabled", true, "AutoSave");
	ConfigEntry* entry = cfg->Bind("IntervalTime", 20, "AutoSave");
	if(entry->GetInt() < 10) entry->SetInt(10);
	nSaveIntervalTime = entry->GetInt() * 1000;
	bSaveInInteriors = cfg->GetBool("SaveInInteriors", false, "AutoSave");

	bRestoreDebuggingCheats = cfg->GetBool("RestoreDebuggingCheats", true, "Debugging");
	bIncreaseTimesCheated = cfg->GetBool("IncreaseTimesCheated", true, "Debugging");
	bModernFonts = cfg->GetBool("UseModernFonts", true, "Debugging");
	bShowFPS = cfg->GetBool("ShowFPS", true, "Debugging");
	fMaxFPSToCalcColor = cfg->GetFloat("MaxFPSToShowColor", 30.f, "Debugging");
	//bEnableTP = cfg->GetBool("TeleportCheatTRAVELER", true, "Debugging");

	bFixIconInSea = cfg->GetBool("FixRadarIconInSeaGlitch", true, "Gameplay");

	if(cfg->GetBool("SprintOnAnySurface", true, "Gameplay"))
		aml->Redirect(SYM("_ZN14SurfaceInfos_c12CantSprintOnEj"), uintptr_t(ret0));

	if(nVer == V1_72 && cfg->GetBool("PlaneExplodeDisappearFix", true, "Gameplay")){
		uintptr_t pBaseFunc = SYM("_ZN6CPlane9BlowUpCarEP7CEntityh");
		aml->Write32(pBaseFunc + 0xFC, 0x14000036);
		aml->PlaceNOP(pBaseFunc + 0x1E8);
	}

	bFixMissingTextKey = cfg->GetBool("FixMissingTextKey", true, "Visual");

	if(cfg->GetBool("AbleToSkipCredits", true, "SCMFixes")){
		uintptr_t pBaseFunc = SYM("_ZN14CRunningScript7ProcessEv");
		aml->Write32(pBaseFunc + 0x24, 0x36000300);
		aml->PlaceNOP(pBaseFunc + 0x28, 8);
	}

	if(cfg->GetBool("AllowAutoAimingOnRFMG", true, "Gameplay"))
		aml->Write32(SYM("_ZN10CPlayerPed22FindWeaponLockOnTargetEi")+0xD8, 0xD2C00409);

	if(nVer == V1_72 && cfg->GetBool("ClimbOnAnyVehicle", true, "Gameplay"))
		aml->Write32(SYM("_ZN16CTaskSimpleClimb20ScanToGrabSectorListER8CPtrListP4CPedR7CVectorRfRhbbb")+0x4A0, 0x17FFFF81);

	if(nVer == V1_72 && (bFixMissingShootBtnForPredator = cfg->GetBool("FixMissingShootBtnForPredator", true, "Gameplay")))
		aml->Write32(SYM("_ZN5CBoat14ProcessControlEv")+0x390, 0x52800021);

	// bFixBoatMovingHi = cfg->GetBool("BoatRotatingRadarFix", false, "Visual");

	if(nVer == V1_72 && (bColorZoneName = cfg->GetBool("ColouredZoneNames", true, "Visual")))
		aml->Write(SYM("_ZN4CHud12DrawAreaNameEv")+0x3E4, "\x6A\x31\x40\x39" "\x6B\x35\x40\x39" "\x69\x00\x00\xB5" "\x4A\x00\x00\xB5" "\x8B\x00\x00\xB4", 20);
	

	//aml->Write(SYM("_ZN8CPadBase18GetToggleCheatMenuEv")+0xC8, "\x60\x01\x80\x52" "\x21\x00\x80\x52" "\xE2\x03\x1F\x2A" "\x23\x00\x80\x52" "\xE1\x83\x1D\x94", 20);
	//HOOKBL(CHud__DrawAreaName, pBaseFunc+0x3F8);
	
	/*if(cfg->GetBool("NoRadioCuts", true, "Gameplay"))
		aml->Redirect(SYM("_Z14IsRemovedTracki"), (uintptr_t)ret0);*/

	HOOKSYM(CCheat__AddToCheatString, hUE4, "_ZN6CCheat16AddToCheatStringEcb");
	HOOKSYM(CGame__Process, hUE4, "_ZN5CGame7ProcessEv");
	//HOOKSYM(OnLostFocusPause, hUE4, "_ZN4AHUD16OnLostFocusPauseEb");

	cfg->Save(); // Will only save if something was changed
}
}