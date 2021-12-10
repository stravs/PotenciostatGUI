#ifndef CYCLICVOLTAMETRY_H
#define CYCLICVOLTAMETRY_H

#include <QObject>

#include "communication.h"


class CyclicVoltametry
{
public:
    CyclicVoltametry();

    void setup();
    void scan();
    void prcessData(QByteArray& data);
    void start();


private:
    float m_upperVoltage;
    float m_lowerVoltage;
    int m_numberOfCycles;
    int m_scanRate;
    int m_timeStep;
    float m_Rslope;

    int m_initW;
    int m_initR;

    int m_nrScans;
    int m_nrSteps1;
    int m_nrSteps2;
    int m_nrSteps3;
    int m_stepHeightAbs;
    int m_stepR[100];
    int m_nrSteps[100];
    int m_nrDataPoints;

    QList<float> m_Vw;    //Potential in volts
    QList<float> m_IuA;   //Electrode current in uA
    QList<int> m_dWe;   //Working electrode as set
    QList<int> m_dRe;   //Reference electrode as set
    QList<int> m_dADC;   //ADC value
    QList<int> m_Ts;   //Time step
    QList<int> m_Ni;   //Index of point in scan

    int m_dataPointCounter;
    int m_scanCounter;
    bool m_scanRunning;
    int m_lastIndex;

    bool send(QString text);

};

#endif // CYCLICVOLTAMETRY_H
