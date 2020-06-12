#include "CoreMinimal.h"
#include "HAL/Runnable.h"

class FSimpleRunnable :public FRunnable
{
public:
	FSimpleRunnable();
	~FSimpleRunnable();

private:
	// ����ʵ�ֵļ���
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
};