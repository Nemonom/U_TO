// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine.h"

/**
 * 
 */
class U_TO2_API WaveMachine : public Machine
{
public:
	WaveMachine(UWorld* InputWorld);
	virtual ~WaveMachine();

private:
	void CreateProjectile();

protected:
	const float CreateTime{ 1.5f };
};
