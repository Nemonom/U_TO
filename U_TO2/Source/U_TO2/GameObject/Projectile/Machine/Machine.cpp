// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine.h"

Machine::Machine(UWorld* InputWorld)
{
	World = InputWorld;
}

Machine::~Machine()
{
}

void Machine::Tick(float DeltaTime)
{
}

void Machine::SetPos(const FVector& Pos)
{
	BasePos = Pos;
}
