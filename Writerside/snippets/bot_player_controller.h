#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"

UCLASS()
class SAMPLEPROJECT_API ASamplePlayerController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()
    
public:

    virtual FGenericTeamId GetGenericTeamId() const override;
    
protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Team")
    uint8 TeamId = 1;
    
};