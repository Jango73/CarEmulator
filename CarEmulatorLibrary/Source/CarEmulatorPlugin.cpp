
// Qt
#include <qqml.h>

// Application
#include "CarEmulatorPlugin.h"
#include "CCar.h"
#include "CCarAI.h"

//-------------------------------------------------------------------------------------------------

using namespace CarEmulator;

//-------------------------------------------------------------------------------------------------

void CarEmulatorPlugin::registerTypes(const char *uri)
{
    // @uri CarEmulator
    qmlRegisterType<CCar>(uri, 1, 0, "Car");
    qmlRegisterType<CCarAI>(uri, 1, 0, "AICar");
}
