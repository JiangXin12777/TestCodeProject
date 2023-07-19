// Copyright Epic Games, Inc. All Rights Reserved.

#include "MVVM_Test.h"

#define LOCTEXT_NAMESPACE "FMVVM_TestModule"

void FMVVM_TestModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMVVM_TestModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMVVM_TestModule, MVVM_Test)