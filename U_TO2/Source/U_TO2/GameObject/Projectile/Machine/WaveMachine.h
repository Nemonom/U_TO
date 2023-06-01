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
	WaveMachine();
	virtual ~WaveMachine();

	virtual void Tick(float DeltaTime) override;

protected:
	const float m_Maxtime{ 1.5f };
	float m_Ctime{ 0.f };
};
