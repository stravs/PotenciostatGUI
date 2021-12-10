#include "cyclicvoltametry.h"

#include <QtMath>
#include <QDebug>

CyclicVoltametry::CyclicVoltametry()
{
    m_upperVoltage = 1;
    m_lowerVoltage = -1;
    m_numberOfCycles = 1;
    m_scanRate = 100;
    m_timeStep = 25;
    m_initW = 22500;
    m_initR = 22606;
    m_Rslope = 1.5040E4;

    m_nrScans = 2 * m_numberOfCycles + 1;
    m_nrSteps1 = 1000000*(m_upperVoltage)/(m_scanRate*m_timeStep*2);
    m_nrSteps2 = 1000000*(m_upperVoltage-m_lowerVoltage)/(m_scanRate*m_timeStep*2);
    m_nrSteps3 = m_nrSteps2-m_nrSteps1;
    m_stepHeightAbs = qFabs((m_upperVoltage-m_lowerVoltage)*m_Rslope)/m_nrSteps2;
    qDebug() << "step size " << m_stepHeightAbs;

    m_nrDataPoints = 2*m_numberOfCycles*(m_nrSteps2+2);

    for (int i=1; i<m_numberOfCycles; i++)
    {
        m_stepR[i*2]=m_stepHeightAbs;
        m_stepR[i*2+1]=(-1)*m_stepHeightAbs;
        m_nrSteps[i*2]=m_nrSteps2;
        m_nrSteps[i*2+1]=m_nrSteps2;
    }

    m_stepR[1]=(-1)*m_stepHeightAbs;;
    m_nrSteps[1]=m_nrSteps1;
    m_nrSteps[m_nrScans]=m_nrSteps3;

    m_scanRunning = false;
    m_lastIndex = 0;

}

void CyclicVoltametry::setup()
{
    m_dataPointCounter = 0;
    m_scanCounter = 0;

    send(Communication::setReferenceEl(m_initR));
    send(Communication::setWorkingEl(m_initW));
    send(Communication::setNumberOfEl(3));
    send(Communication::setIntputMode(1));

    qDebug() << "setup finished";
}

void CyclicVoltametry::scan()
{
    m_scanCounter++;

    if(m_scanCounter > m_nrScans)
    {
        qDebug() << "konc";
    }
    else
    {
        send(Communication::setScanRateForReferenceChannelToIncreaseAtOddSteps(m_stepR[m_scanCounter]));
        send(Communication::setScanRateForReferenceElectrodeChannelToIncreaseAtEvenSteps(m_stepR[m_scanCounter]));
        send(Communication::setNoOfSteps(m_nrSteps[m_scanCounter]));
        send(Communication::run());
        m_scanRunning = true;
    }
}

void CyclicVoltametry::prcessData(QByteArray &data)
{
    if(data[2] == 'm')
        scan();
    else if(data[2] == 'M')
        qDebug() << "M";

}

void CyclicVoltametry::start()
{
    setup();
    for(auto i=0; i < m_nrScans; i++)
    {
        scan();
    }
}

bool CyclicVoltametry::send(QString text)
{
    qDebug() << text;
    return true;
}

