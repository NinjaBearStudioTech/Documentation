#include "GameFramework/PluginLabsPlayerController.h"
#include "Components/NinjaInputManagerComponent.h"
#include "Interfaces/InputBufferInterface.h"

APluginLabsPlayerController::SetBufferState(bool bOpen)
{
    if (bOpen)
    {
        // Open the Input Buffer in the controller's Input Manager.
        IInputBufferInterface::Execute_OpenInputBuffer(InputManagerComponent);
    }
    else
    {
        // Close the Input Buffer in the controller's Input Manager.
        IInputBufferInterface::Execute_CloseInputBuffer(InputManagerComponent);
    }
}