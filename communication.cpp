#include "communication.h"

Communication::Communication()
{

}

const QString Communication::setReferenceEl(const int value)
{
    return QString("A(%1)").arg(value);
}

const QString Communication::setWorkingEl(const int value)
{
    return QString("B(%1)").arg(value);
}

const QString Communication::setIntputMode(const int value)
{
    return QString("C(%1)").arg(value);
}

const QString Communication::setNumberOfEl(const int value)
{
    return QString("D(%1)").arg(value);
}

const QString Communication::setTimer(const int value)
{
    return QString("E(%1)").arg(value);
}

const QString Communication::getTime()
{
    return QString("F()");
}

const QString Communication::setScanRateForReferenceChannelToIncreaseAtOddSteps(int value)
{
    return QString("G(%1)").arg(value);
}

const QString Communication::setScanRateForReferenceElectrodeChannelToIncreaseAtEvenSteps(int value)
{
    return QString("I(%1)").arg(value);
}

const QString Communication::setScanRateForWorkingElectrodeChannelToIncreaseAtOddSteps(int value)
{
    return QString("J(%1)").arg(value);
}

const QString Communication::setScanRateForReferenceChannelToIncreaseAtEvenSteps(int value)
{
    return QString("K(%1)").arg(value);
}

const QString Communication::setNoOfSteps(int value)
{
    return QString("L(%1)").arg(value);
}

const QString Communication::run()
{
    return QString("M()");
}

const QString Communication::stop()
{
    return QString("N()");
}
