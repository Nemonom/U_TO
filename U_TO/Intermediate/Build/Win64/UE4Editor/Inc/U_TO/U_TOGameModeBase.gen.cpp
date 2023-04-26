// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "U_TO/U_TOGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeU_TOGameModeBase() {}
// Cross Module References
	U_TO_API UClass* Z_Construct_UClass_AU_TOGameModeBase_NoRegister();
	U_TO_API UClass* Z_Construct_UClass_AU_TOGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_U_TO();
// End Cross Module References
	void AU_TOGameModeBase::StaticRegisterNativesAU_TOGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_AU_TOGameModeBase_NoRegister()
	{
		return AU_TOGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_AU_TOGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AU_TOGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_U_TO,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AU_TOGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "U_TOGameModeBase.h" },
		{ "ModuleRelativePath", "U_TOGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AU_TOGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AU_TOGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AU_TOGameModeBase_Statics::ClassParams = {
		&AU_TOGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_AU_TOGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AU_TOGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AU_TOGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AU_TOGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AU_TOGameModeBase, 1748978227);
	template<> U_TO_API UClass* StaticClass<AU_TOGameModeBase>()
	{
		return AU_TOGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AU_TOGameModeBase(Z_Construct_UClass_AU_TOGameModeBase, &AU_TOGameModeBase::StaticClass, TEXT("/Script/U_TO"), TEXT("AU_TOGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AU_TOGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
