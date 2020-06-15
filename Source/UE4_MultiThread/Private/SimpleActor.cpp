#include "SimpleActor.h"
#include "SimpleRunnable.h"
#include "TimerManager.h"

namespace SimpleTaskGraph
{
	FGraphEventArray SimpleTask_CompletionEvents; // ���ڱ������������
	int Number = 0; // Ҫ��ӡ����������0��ʼ

	// Are all tasks complete?
	bool TasksAreComplete()
	{
		for (int32 Index = 0; Index < SimpleTask_CompletionEvents.Num(); Index++)
		{
			if (!SimpleTask_CompletionEvents[Index]->IsComplete())
			{
				return false;
			}
		}
		return true;
	}

	// ��ӡ��һ������
	int GetNextInt()
	{
		FPlatformProcess::Sleep(0.1);
		Number++;
		UE_LOG(LogTemp, Warning, TEXT("SimpleTask %d"), Number);
		return Number;
	}

	// Each task thread
	class SimpleTask
	{
	public:
		SimpleTask() {}

		// ��ȡ��������֣���ʱû�õ�
		static const TCHAR* GetTaskName()
		{
			return TEXT("SimpleTask");
		}

		//////////////////////////////////////////////////////////////////////////
		// ��Ҫʵ�ֵķ�����û����Щ����뱨����ʱû�õ�
		FORCEINLINE static TStatId GetStatId()
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(SimpleTask, STATGROUP_TaskGraphTasks);
		}
		static ESubsequentsMode::Type GetSubsequentsMode()
		{
			return ESubsequentsMode::TrackSubsequents;
		}
		static ENamedThreads::Type GetDesiredThread()
		{
			return ENamedThreads::AnyThread;
		}
		//////////////////////////////////////////////////////////////////////////

		// Main function: DO Task!
		void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
		{
			GetNextInt();
		}
	};

	// ʹ�������ռ�SimpleTaskGraph�������������������ͼ
	void GetInts(const uint32 TotalToGet)
	{
		for (uint32 i = 0; i < TotalToGet; i++)
		{
			// ��һ�������ȴ����е�������ɣ�Ȼ���ٽ�����һ������
			// ��һ�������ٷ�Wiki��NULL���������Բ�����˳��ִ��
			SimpleTask_CompletionEvents.Add(TGraphTask<SimpleTask>::CreateTask(
				&SimpleTask_CompletionEvents, ENamedThreads::GameThread).ConstructAndDispatchWhenReady());
		}
	}
}

// Sets default values
ASimpleActor::ASimpleActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASimpleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimpleActor::RunSimpleRunnable()
{
	FSimpleRunnable::JoyInit();
}

void ASimpleActor::StopSimpleRunnable()
{
	FSimpleRunnable::Shutdown();
}

void ASimpleActor::StartTask(int TotalToGet)
{
	SimpleTaskGraph::GetInts(TotalToGet);
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ASimpleActor::CheckAllTasksDone, 1, true);
}

void ASimpleActor::CheckAllTasksDone()
{
	if (SimpleTaskGraph::TasksAreComplete())
	{
		GetWorldTimerManager().ClearTimer(MyTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("TaskGraph Done!"));
	}
}