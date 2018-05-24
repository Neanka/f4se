#pragma once

struct perkData
{
	bool			isEligible;
	bool			isAllowable; // for GetIsSex checks
	bool			isHighLevel;
	int				filterFlag;
	int				reqlevel;
	std::string		reqs;
	std::string		SWFPath;
};

const std::string compareops[6] = {"=","!=","&gt;","&gt;=","&lt;","&lt;="};

struct AvailablePerk
{
	BGSPerk*		Perk;
	int				Level;
	int				NumRanks;
	BSFixedString	ranksInfo;
};

enum SPECIAL
{
	StrengthID = 706,
	PerceptionID,
	EnduranceID,
	CharismaID,
	IntelligenceID,
	AgilityID,
	LuckID,
	ExperienceID
};

enum SPECIALPerks
{
	StrengthPerkID = 0xd9784,
	PerceptionPerkID = 0xd9789,
	EndurancePerkID = 0xd978E,
	CharismaPerkID = 0xd9793,
	IntelligencePerkID = 0xd9798,
	AgilityPerkID = 0xd979d,
	LuckPerkID = 0xd97a2
};

enum PerkTypes
{
	type_default = 0,
	type_strtrain,
	type_pertrain,
	type_endtrain,
	type_chatrain,
	type_inttrain,
	type_agitrain,
	type_lcktrain,
	type_intensetraining,
	type_cancel
};

enum filterFlags
{
	filterFlag_elig = 1,
	filterFlag_notelig = 2,
	filterFlag_highlvl = 4,
	filterFlag_S = 8,
	filterFlag_P = 16,
	filterFlag_E = 32,
	filterFlag_C = 64,
	filterFlag_I = 128,
	filterFlag_A = 256,
	filterFlag_L = 512,
	filterFlag_NonSpecial = 1024,
	filterFlag_Other = 2048
};

enum Functions
{
	kFunction_GetWantBlocking = 0,
	kFunction_GetDistance = 1,
	kFunction_GetLocked = 5,
	kFunction_GetPos = 6,
	kFunction_GetAngle = 8,
	kFunction_GetStartingPos = 10,
	kFunction_GetStartingAngle = 11,
	kFunction_GetSecondsPassed = 12,
	kFunction_GetValue = 14,
	kFunction_GetCurrentTime = 18,
	kFunction_GetScale = 24,
	kFunction_IsMoving = 25,
	kFunction_IsTurning = 26,
	kFunction_GetLineOfSight = 27,
	kFunction_GetInSameCell = 32,
	kFunction_GetDisabled = 35,
	kFunction_MenuMode = 36,
	kFunction_GetDisease = 39,
	kFunction_GetClothingValue = 41,
	kFunction_SameFaction = 42,
	kFunction_SameRace = 43,
	kFunction_SameSex = 44,
	kFunction_GetDetected = 45,
	kFunction_GetDead = 46,
	kFunction_GetItemCount = 47,
	kFunction_GetGold = 48,
	kFunction_GetSleeping = 49,
	kFunction_GetTalkedToPC = 50,
	kFunction_GetQuestRunning = 56,
	kFunction_GetStage = 58,
	kFunction_GetStageDone = 59,
	kFunction_GetFactionRankDifference = 60,
	kFunction_GetAlarmed = 61,
	kFunction_IsRaining = 62,
	kFunction_GetAttacked = 63,
	kFunction_GetIsCreature = 64,
	kFunction_GetLockLevel = 65,
	kFunction_GetShouldAttack = 66,
	kFunction_GetInCell = 67,
	kFunction_GetIsClass = 68,
	kFunction_GetIsRace = 69,
	kFunction_GetIsSex = 70,
	kFunction_GetInFaction = 71,
	kFunction_GetIsID = 72,
	kFunction_GetFactionRank = 73,
	kFunction_GetGlobalValue = 74,
	kFunction_IsSnowing = 75,
	kFunction_GetRandomPercent = 77,
	kFunction_WouldBeStealing = 79,
	kFunction_GetLevel = 80,
	kFunction_IsRotating = 81,
	kFunction_GetDeadCount = 84,
	kFunction_GetIsAlerted = 91,
	kFunction_GetPlayerControlsDisabled = 98,
	kFunction_GetHeadingAngle = 99,
	kFunction_IsWeaponMagicOut = 101,
	kFunction_IsTorchOut = 102,
	kFunction_IsShieldOut = 103,
	kFunction_IsFacingUp = 106,
	kFunction_GetKnockedState = 107,
	kFunction_GetWeaponAnimType = 108,
	kFunction_IsWeaponSkillType = 109,
	kFunction_GetCurrentAIPackage = 110,
	kFunction_IsWaiting = 111,
	kFunction_IsIdlePlaying = 112,
	kFunction_IsIntimidatedbyPlayer = 116,
	kFunction_IsPlayerInRegion = 117,
	kFunction_GetActorAggroRadiusViolated = 118,
	kFunction_GetCrime = 122,
	kFunction_IsGreetingPlayer = 123,
	kFunction_IsGuard = 125,
	kFunction_HasBeenEaten = 127,
	kFunction_GetStaminaPercentage = 128,
	kFunction_HasBeenRead = 129,
	kFunction_GetDying = 130,
	kFunction_GetSceneActionPercent = 131,
	kFunction_WouldRefuseCommand = 132,
	kFunction_SameFactionAsPC = 133,
	kFunction_SameRaceAsPC = 134,
	kFunction_SameSexAsPC = 135,
	kFunction_GetIsReference = 136,
	kFunction_IsTalking = 141,
	kFunction_GetComponentCount = 142,
	kFunction_GetCurrentAIProcedure = 143,
	kFunction_GetTrespassWarningLevel = 144,
	kFunction_IsTrespassing = 145,
	kFunction_IsInMyOwnedCell = 146,
	kFunction_GetWindSpeed = 147,
	kFunction_GetCurrentWeatherPercent = 148,
	kFunction_GetIsCurrentWeather = 149,
	kFunction_IsContinuingPackagePCNear = 150,
	kFunction_GetIsCrimeFaction = 152,
	kFunction_CanHaveFlames = 153,
	kFunction_HasFlames = 154,
	kFunction_GetOpenState = 157,
	kFunction_GetSitting = 159,
	kFunction_GetIsCurrentPackage = 161,
	kFunction_IsCurrentFurnitureRef = 162,
	kFunction_IsCurrentFurnitureObj = 163,
	kFunction_GetDayOfWeek = 170,
	kFunction_GetTalkedToPCParam = 172,
	kFunction_IsPCSleeping = 175,
	kFunction_IsPCAMurderer = 176,
	kFunction_HasSameEditorLocationAsRef = 180,
	kFunction_HasSameEditorLocationAsRefAlias = 181,
	kFunction_GetEquipped = 182,
	kFunction_IsSwimming = 185,
	kFunction_GetAmountSoldStolen = 190,
	kFunction_GetIgnoreCrime = 192,
	kFunction_GetPCExpelled = 193,
	kFunction_GetPCFactionMurder = 195,
	kFunction_GetPCEnemyofFaction = 197,
	kFunction_GetPCFactionAttack = 199,
	kFunction_GetDestroyed = 203,
	kFunction_HasMagicEffect = 214,
	kFunction_GetDefaultOpen = 215,
	kFunction_IsSpellTarget = 223,
	kFunction_GetVATSMode = 224,
	kFunction_GetPersuasionNumber = 225,
	kFunction_GetVampireFeed = 226,
	kFunction_GetCannibal = 227,
	kFunction_GetIsClassDefault = 228,
	kFunction_GetClassDefaultMatch = 229,
	kFunction_GetInCellParam = 230,
	kFunction_GetPlayerDialogueInput = 231,
	kFunction_GetVatsTargetHeight = 235,
	kFunction_GetIsGhost = 237,
	kFunction_GetUnconscious = 242,
	kFunction_GetRestrained = 244,
	kFunction_GetIsUsedItem = 246,
	kFunction_GetIsUsedItemType = 247,
	kFunction_IsScenePlaying = 248,
	kFunction_IsInDialogueWithPlayer = 249,
	kFunction_GetLocationCleared = 250,
	kFunction_GetIsPlayableRace = 254,
	kFunction_GetOffersServicesNow = 255,
	kFunction_HasAssociationType = 258,
	kFunction_HasFamilyRelationship = 259,
	kFunction_HasParentRelationship = 261,
	kFunction_IsWarningAbout = 262,
	kFunction_IsWeaponOut = 263,
	kFunction_HasSpell = 264,
	kFunction_IsTimePassing = 265,
	kFunction_IsPleasant = 266,
	kFunction_IsCloudy = 267,
	kFunction_IsSmallBump = 274,
	kFunction_GetBaseValue = 277,
	kFunction_IsOwner = 278,
	kFunction_IsCellOwner = 280,
	kFunction_IsHorseStolen = 282,
	kFunction_IsLeftUp = 285,
	kFunction_IsSneaking = 286,
	kFunction_IsRunning = 287,
	kFunction_GetFriendHit = 288,
	kFunction_IsInCombat = 289,
	kFunction_IsInInterior = 300,
	kFunction_IsWaterObject = 304,
	kFunction_GetPlayerAction = 305,
	kFunction_IsActorUsingATorch = 306,
	kFunction_IsXBox = 309,
	kFunction_GetInWorldspace = 310,
	kFunction_GetPCMiscStat = 312,
	kFunction_GetPairedAnimation = 313,
	kFunction_IsActorAVictim = 314,
	kFunction_GetTotalPersuasionNumber = 315,
	kFunction_GetIdleDoneOnce = 318,
	kFunction_GetNoRumors = 320,
	kFunction_GetCombatState = 323,
	kFunction_GetWithinPackageLocation = 325,
	kFunction_IsRidingMount = 327,
	kFunction_IsFleeing = 329,
	kFunction_IsInDangerousWater = 332,
	kFunction_GetIgnoreFriendlyHits = 338,
	kFunction_IsPlayersLastRiddenMount = 339,
	kFunction_IsActor = 353,
	kFunction_IsEssential = 354,
	kFunction_IsPlayerMovingIntoNewSpace = 358,
	kFunction_GetInCurrentLocation = 359,
	kFunction_GetInCurrentLocationAlias = 360,
	kFunction_GetTimeDead = 361,
	kFunction_HasLinkedRef = 362,
	kFunction_IsChild = 365,
	kFunction_GetStolenItemValueNoCrime = 366,
	kFunction_GetLastPlayerAction = 367,
	kFunction_IsPlayerActionActive = 368,
	kFunction_IsTalkingActivatorActor = 370,
	kFunction_IsInList = 372,
	kFunction_GetStolenItemValue = 373,
	kFunction_GetCrimeGoldViolent = 375,
	kFunction_GetCrimeGoldNonviolent = 376,
	kFunction_IsOwnedBy = 378,
	kFunction_GetCommandDistance = 380,
	kFunction_GetCommandLocationDistance = 381,
	kFunction_GetHitLocation = 390,
	kFunction_IsPC1stPerson = 391,
	kFunction_GetCauseofDeath = 396,
	kFunction_IsLimbGone = 397,
	kFunction_IsWeaponInList = 398,
	kFunction_IsBribedbyPlayer = 402,
	kFunction_GetRelationshipRank = 403,
	kFunction_GetVATSValue = 407,
	kFunction_IsKiller = 408,
	kFunction_IsKillerObject = 409,
	kFunction_GetFactionCombatReaction = 410,
	kFunction_Exists = 414,
	kFunction_GetGroupMemberCount = 415,
	kFunction_GetGroupTargetCount = 416,
	kFunction_GetIsVoiceType = 426,
	kFunction_GetPlantedExplosive = 427,
	kFunction_IsScenePackageRunning = 429,
	kFunction_GetHealthPercentage = 430,
	kFunction_GetIsObjectType = 432,
	kFunction_PlayerVisualDetection = 434,
	kFunction_PlayerAudioDetection = 435,
	kFunction_GetIsCreatureType = 437,
	kFunction_HasKey = 438,
	kFunction_IsFurnitureEntryType = 439,
	kFunction_GetInCurrentLocationFormList = 444,
	kFunction_GetInZone = 445,
	kFunction_GetVelocity = 446,
	kFunction_GetGraphVariableFloat = 447,
	kFunction_HasPerk = 448,
	kFunction_GetFactionRelation = 449,
	kFunction_IsLastIdlePlayed = 450,
	kFunction_GetPlayerTeammate = 453,
	kFunction_GetPlayerTeammateCount = 454,
	kFunction_GetActorCrimePlayerEnemy = 458,
	kFunction_GetCrimeGold = 459,
	kFunction_IsPlayerGrabbedRef = 463,
	kFunction_GetKeywordItemCount = 465,
	kFunction_GetDestructionStage = 470,
	kFunction_GetIsAlignment = 473,
	kFunction_IsProtected = 476,
	kFunction_GetThreatRatio = 477,
	kFunction_GetIsUsedItemEquipType = 479,
	kFunction_GetPlayerActivated = 483,
	kFunction_GetFullyEnabledActorsInHigh = 485,
	kFunction_IsCarryable = 487,
	kFunction_GetConcussed = 488,
	kFunction_GetMapMarkerVisible = 491,
	kFunction_PlayerKnows = 493,
	kFunction_GetPermanentValue = 494,
	kFunction_GetKillingBlowLimb = 495,
	kFunction_CanPayCrimeGold = 497,
	kFunction_GetDaysInJail = 499,
	kFunction_EPAlchemyGetMakingPoison = 500,
	kFunction_EPAlchemyEffectHasKeyword = 501,
	kFunction_GetAllowWorldInteractions = 503,
	kFunction_DialogueGetAv = 506,
	kFunction_DialogueHasPerk = 507,
	kFunction_GetLastHitCritical = 508,
	kFunction_DialogueGetItemCount = 510,
	kFunction_LastCrippledCondition = 511,
	kFunction_HasSharedPowerGrid = 512,
	kFunction_IsCombatTarget = 513,
	kFunction_GetVATSRightAreaFree = 515,
	kFunction_GetVATSLeftAreaFree = 516,
	kFunction_GetVATSBackAreaFree = 517,
	kFunction_GetVATSFrontAreaFree = 518,
	kFunction_GetIsLockBroken = 519,
	kFunction_IsPS3 = 520,
	kFunction_IsWindowsPC = 521,
	kFunction_GetVATSRightTargetVisible = 522,
	kFunction_GetVATSLeftTargetVisible = 523,
	kFunction_GetVATSBackTargetVisible = 524,
	kFunction_GetVATSFrontTargetVisible = 525,
	kFunction_IsInCriticalStage = 528,
	kFunction_GetXPForNextLevel = 530,
	kFunction_GetInfamy = 533,
	kFunction_GetInfamyViolent = 534,
	kFunction_GetInfamyNonViolent = 535,
	kFunction_GetTypeCommandPerforming = 536,
	kFunction_GetQuestCompleted = 543,
	kFunction_GetSpeechChallengeSuccessLevel = 544,
	kFunction_IsGoreDisabled = 547,
	kFunction_IsSceneActionComplete = 550,
	kFunction_GetSpellUsageNum = 552,
	kFunction_GetActorsInHigh = 554,
	kFunction_HasLoaded3D = 555,
	kFunction_HasKeyword = 560,
	kFunction_HasRefType = 561,
	kFunction_LocationHasKeyword = 562,
	kFunction_LocationHasRefType = 563,
	kFunction_GetIsEditorLocation = 565,
	kFunction_GetIsAliasRef = 566,
	kFunction_GetIsEditorLocationAlias = 567,
	kFunction_IsSprinting = 568,
	kFunction_IsBlocking = 569,
	kFunction_HasEquippedSpell = 570,
	kFunction_GetCurrentCastingType = 571,
	kFunction_GetCurrentDeliveryType = 572,
	kFunction_GetAttackState = 574,
	kFunction_GetEventData = 576,
	kFunction_IsCloserToAThanB = 577,
	kFunction_LevelMinusPCLevel = 578,
	kFunction_IsBleedingOut = 580,
	kFunction_GetRelativeAngle = 584,
	kFunction_GetMovementDirection = 589,
	kFunction_IsInScene = 590,
	kFunction_GetRefTypeDeadCount = 591,
	kFunction_GetRefTypeAliveCount = 592,
	kFunction_GetIsFlying = 594,
	kFunction_IsCurrentSpell = 595,
	kFunction_SpellHasKeyword = 596,
	kFunction_GetEquippedItemType = 597,
	kFunction_GetLocationAliasCleared = 598,
	kFunction_GetLocationAliasRefTypeDeadCount = 600,
	kFunction_GetLocationAliasRefTypeAliveCount = 601,
	kFunction_IsWardState = 602,
	kFunction_IsInSameCurrentLocationAsRef = 603,
	kFunction_IsInSameCurrentLocationAsRefAlias = 604,
	kFunction_LocationAliasIsLocation = 605,
	kFunction_GetKeywordDataForLocation = 606,
	kFunction_GetKeywordDataForAlias = 608,
	kFunction_LocationAliasHasKeyword = 610,
	kFunction_IsNullPackageData = 611,
	kFunction_GetNumericPackageData = 612,
	kFunction_IsPlayerRadioOn = 613,
	kFunction_GetPlayerRadioFrequency = 614,
	kFunction_GetHighestRelationshipRank = 615,
	kFunction_GetLowestRelationshipRank = 616,
	kFunction_HasAssociationTypeAny = 617,
	kFunction_HasFamilyRelationshipAny = 618,
	kFunction_GetPathingTargetOffset = 619,
	kFunction_GetPathingTargetAngleOffset = 620,
	kFunction_GetPathingTargetSpeed = 621,
	kFunction_GetPathingTargetSpeedAngle = 622,
	kFunction_GetMovementSpeed = 623,
	kFunction_GetInContainer = 624,
	kFunction_IsLocationLoaded = 625,
	kFunction_IsLocationAliasLoaded = 626,
	kFunction_IsDualCasting = 627,
	kFunction_GetVMQuestVariable = 629,
	kFunction_GetCombatAudioDetection = 630,
	kFunction_GetCombatVisualDetection = 631,
	kFunction_IsCasting = 632,
	kFunction_GetFlyingState = 633,
	kFunction_IsInFavorState = 635,
	kFunction_HasTwoHandedWeaponEquipped = 636,
	kFunction_IsFurnitureExitType = 637,
	kFunction_IsInFriendStatewithPlayer = 638,
	kFunction_GetWithinDistance = 639,
	kFunction_GetValuePercent = 640,
	kFunction_IsUnique = 641,
	kFunction_GetLastBumpDirection = 642,
	kFunction_GetInfoChallangeSuccess = 644,
	kFunction_GetIsInjured = 645,
	kFunction_GetIsCrashLandRequest = 646,
	kFunction_GetIsHastyLandRequest = 647,
	kFunction_IsLinkedTo = 650,
	kFunction_GetKeywordDataForCurrentLocation = 651,
	kFunction_GetInSharedCrimeFaction = 652,
	kFunction_GetBribeSuccess = 654,
	kFunction_GetIntimidateSuccess = 655,
	kFunction_GetArrestedState = 656,
	kFunction_GetArrestingActor = 657,
	kFunction_HasVMScript = 659,
	kFunction_GetVMScriptVariable = 660,
	kFunction_GetWorkshopResourceDamage = 661,
	kFunction_HasValidRumorTopic = 664,
	kFunction_IsAttacking = 672,
	kFunction_IsPowerAttacking = 673,
	kFunction_IsLastHostileActor = 674,
	kFunction_GetGraphVariableInt = 675,
	kFunction_ShouldAttackKill = 678,
	kFunction_GetActivationHeight = 680,
	kFunction_WornHasKeyword = 682,
	kFunction_GetPathingCurrentSpeed = 683,
	kFunction_GetPathingCurrentSpeedAngle = 684,
	kFunction_GetWorkshopObjectCount = 691,
	kFunction_EPMagic_SpellHasKeyword = 693,
	kFunction_GetNoBleedoutRecovery = 694,
	kFunction_EPMagic_SpellHasSkill = 696,
	kFunction_IsAttackType = 697,
	kFunction_IsAllowedToFly = 698,
	kFunction_HasMagicEffectKeyword = 699,
	kFunction_IsCommandedActor = 700,
	kFunction_IsStaggered = 701,
	kFunction_IsRecoiling = 702,
	kFunction_HasScopeWeaponEquipped = 703,
	kFunction_IsPathing = 704,
	kFunction_GetShouldHelp = 705,
	kFunction_HasBoundWeaponEquipped = 706,
	kFunction_GetCombatTargetHasKeyword = 707,
	kFunction_GetCombatGroupMemberCount = 709,
	kFunction_IsIgnoringCombat = 710,
	kFunction_GetLightLevel = 711,
	kFunction_SpellHasCastingPerk = 713,
	kFunction_IsBeingRidden = 714,
	kFunction_IsUndead = 715,
	kFunction_GetRealHoursPassed = 716,
	kFunction_IsUnlockedDoor = 718,
	kFunction_IsHostileToActor = 719,
	kFunction_GetTargetHeight = 720,
	kFunction_IsPoison = 721,
	kFunction_WornApparelHasKeywordCount = 722,
	kFunction_GetItemHealthPercent = 723,
	kFunction_EffectWasDualCast = 724,
	kFunction_GetKnockStateEnum = 725,
	kFunction_DoesNotExist = 726,
	kFunction_GetPlayerWalkAwayFromDialogueScene = 728,
	kFunction_GetActorStance = 729,
	kFunction_CanProduceForWorkshop = 734,
	kFunction_CanFlyHere = 735,
	kFunction_EPIsDamageType = 736,
	kFunction_GetActorGunState = 738,
	kFunction_GetVoiceLineLength = 739,
	kFunction_ObjectTemplateItem_HasKeyword = 741,
	kFunction_ObjectTemplateItem_HasUniqueKeyword = 742,
	kFunction_ObjectTemplateItem_GetLevel = 743,
	kFunction_MovementIdleMatches = 744,
	kFunction_GetActionData = 745,
	kFunction_GetActionDataShort = 746,
	kFunction_GetActionDataByte = 747,
	kFunction_GetActionDataFlag = 748,
	kFunction_ModdedItemHasKeyword = 749,
	kFunction_GetAngryWithPlayer = 750,
	kFunction_IsCameraUnderWater = 751,
	kFunction_IsActorRefOwner = 753,
	kFunction_HasActorRefOwner = 754,
	kFunction_GetLoadedAmmoCount = 756,
	kFunction_IsTimeSpanSunrise = 757,
	kFunction_IsTimeSpanMorning = 758,
	kFunction_IsTimeSpanAfternoon = 759,
	kFunction_IsTimeSpanEvening = 760,
	kFunction_IsTimeSpanSunset = 761,
	kFunction_IsTimeSpanNight = 762,
	kFunction_IsTimeSpanMidnight = 763,
	kFunction_IsTimeSpanAnyDay = 764,
	kFunction_IsTimeSpanAnyNight = 765,
	kFunction_CurrentFurnitureHasKeyword = 766,
	kFunction_GetWeaponEquipIndex = 767,
	kFunction_IsOverEncumbered = 769,
	kFunction_IsPackageRequestingBlockedIdles = 770,
	kFunction_GetActionDataInt = 771,
	kFunction_GetVATSRightMinusLeftAreaFree = 772,
	kFunction_GetInIronSights = 773,
	kFunction_GetActorStaggerDirection = 774,
	kFunction_GetActorStaggerMagnitude = 775,
	kFunction_WornCoversBipedSlot = 776,
	kFunction_GetInventoryValue = 777,
	kFunction_IsPlayerInConversation = 778,
	kFunction_IsInDialogueCamera = 779,
	kFunction_IsMyDialogueTargetPlayer = 780,
	kFunction_IsMyDialogueTargetActor = 781,
	kFunction_GetMyDialogueTargetDistance = 782,
	kFunction_IsSeatOccupied = 783,
	kFunction_IsPlayerRiding = 784,
	kFunction_IsTryingEventCamera = 785,
	kFunction_UseLeftSideCamera = 786,
	kFunction_GetNoteType = 787,
	kFunction_LocationHasPlayerOwnedWorkshop = 788,
	kFunction_IsStartingAction = 789,
	kFunction_IsMidAction = 790,
	kFunction_IsWeaponChargeAttack = 791,
	kFunction_IsInWorkshopMode = 792,
	kFunction_IsWeaponChargingHoldAttack = 793,
	kFunction_IsEncounterAbovePlayerLevel = 794,
	kFunction_IsMeleeAttacking = 795,
	kFunction_GetVATSQueuedTargetsUnique = 796,
	kFunction_GetCurrentLocationCleared = 797,
	kFunction_IsPowered = 798,
	kFunction_GetTransmitterDistance = 799,
	kFunction_GetCameraPlaybackTime = 800,
	kFunction_IsInWater = 801,
	kFunction_GetWithinActivateDistance = 802,
	kFunction_IsUnderWater = 803,
	kFunction_IsInSameSpace = 804,
	kFunction_LocationAllowsReset = 805,
	kFunction_GetVATSBackRightAreaFree = 806,
	kFunction_GetVATSBackLeftAreaFree = 807,
	kFunction_GetVATSBackRightTargetVisible = 808,
	kFunction_GetVATSBackLeftTargetVisible = 809,
	kFunction_GetVATSTargetLimbVisible = 810,
	kFunction_IsPlayerListening = 811,
	kFunction_GetPathingRequestedQuickTurn = 812,
	kFunction_EPIsCalculatingBaseDamage = 813,
	kFunction_GetReanimating = 814,
	kFunction_IsInRobotWorkbench = 817
};

enum CompareOperators {
	kCompareOp_Equal = 0,
	kCompareOp_NotEqual,
	kCompareOp_Greater,
	kCompareOp_GreaterEqual,
	kCompareOp_Less,
	kCompareOp_LessEqual
};