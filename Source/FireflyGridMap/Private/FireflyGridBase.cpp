// Copyright LazyGameStudio, Inc. All Rights Reserved.


#include "FireflyGridBase.h"

#include "FireflyGridMapBase.h"


UFireflyGridBase::UFireflyGridBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UFireflyGridBase::InitGrid(AFireflyGridMapBase* InGridMap, FVector InLocation, FFireflyGridCoordinate InCoordinate,
                                float InSize)
{
	GridMap = InGridMap;
	WorldLocation = InLocation;
	Coordinate = InCoordinate;
	Size = InSize;
}

TArray<UFireflyGridBase*> UFireflyGridBase::GetNeighbors()
{
	return TArray<UFireflyGridBase*>();
}

bool UFireflyGridBase::CanPassGrid(AActor* InActor) const
{
	if (PassFlag >= EGridPassFlag::Block)
	{
		return false;
	}
		
	//判断是否有其他棋子站在当前棋格上
	if (ActorsInGrid.Num() > 0 && InActor)
	{
		return ActorsInGrid.Contains(InActor) ? true : false;
	}

	return true;
}

void UFireflyGridBase::ScheduleGrid(AActor* InActor)
{
	if (InActor)
	{
		ActorsInGrid.AddUnique(InActor);
		//GridMap->ResetGridMaterial(this);
	}
}

void UFireflyGridBase::CancelScheduleGrid(AActor* InActor)
{
	if (InActor && ActorsInGrid.Contains(InActor))
	{
		ActorsInGrid.Remove(InActor);
		//GridMap->ResetGridMaterial(this);
	}
}

void UFireflyGridBase::EnterGrid(AActor* InActor)
{
	if (InActor)
	{
		ActorsInGrid.AddUnique(InActor);
		//GridMap->ResetGridMaterial(this);
	}
}

void UFireflyGridBase::LeaveGrid(AActor* InActor)
{
	if (InActor && ActorsInGrid.Contains(InActor))
	{
		ActorsInGrid.Remove(InActor);
		//GridMap->ResetGridMaterial(this);
	}
}