#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>

class Communication
{
public:
    Communication();

public:
    static const QString setReferenceEl(const int value);
    static const QString setWorkingEl(const int value);
    static const QString setIntputMode(const int value);
    static const QString setNumberOfEl(const int value);

    static const QString setTimer(const int value);
    static const QString getTime();

    static const QString setScanRateForReferenceChannelToIncreaseAtOddSteps(int value);
    static const QString setScanRateForReferenceElectrodeChannelToIncreaseAtEvenSteps(int value);
    static const QString setScanRateForWorkingElectrodeChannelToIncreaseAtOddSteps(int value);
    static const QString setScanRateForReferenceChannelToIncreaseAtEvenSteps(int value);

    static const QString setNoOfSteps(int value);

    static const QString run();
    static const QString stop();


};

#endif // COMMUNICATION_H
