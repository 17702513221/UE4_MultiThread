 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_MULTITHREAD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MultiThread")
	TArray<uint32> PrimeNumbers;

	// ��ʱ�����
	FTimerHandle MyTimerHand;

	// ����FRunnable���߳�
	UFUNCTION(BlueprintCallable, Category = "MultiThread")
		void RunMultiThread();

	// �ر�FRunnable���̣߳����ػ�ը
	UFUNCTION(BlueprintCallable, Category = "MultiThread")
		void StopMultiThread();

	// int��size_t��С�Ƚ�
	UFUNCTION(BlueprintCallable, Category = "cao")
		bool Cao();

	// ����TaskGraphSysten
	UFUNCTION(BlueprintCallable, Category = "MultiThread")
		void StartTask();

	// ����Ƿ�����Task������
	UFUNCTION(BlueprintCallable, Category = "MultiThread")
		void VictoryCheckAllThreadsDone();
};
