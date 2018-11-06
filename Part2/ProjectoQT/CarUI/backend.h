#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QSerialPort>
#include <QDebug>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr, QQmlApplicationEngine *ptr = nullptr);

signals:

public slots:
    //void incrementRotation();
    void newData();
    void blinkAll(bool state);
    void blinkLeft(bool state);
    void blinkRight(bool state);
    void gearSwitch(int gear);
    void engineState(bool state);
    void carSpeed(int speed);
    void carRPMs(int rpm);
    void wheelState(QString wheelPos);
    void buzz(bool state);
    void temperature(int temp);

private:
    QQmlApplicationEngine *mEngine;
    QObject *mBlkLeft;
    QObject *mBlkRight;
    QObject *mSpeedMarker;
    QObject *mRotationsMarker;
    QObject *mGearLighter;
    QObject *mMarkerSpd;
    QObject *mMarkerRot;
    QObject *mSpdLight;
    QObject *mRotLight;
    QObject *mWheel;
    QObject *mWheelRot;
    QObject *mBuzzer;
    QObject *mTemper;

    QSerialPort *mPort;
};

#endif // BACKEND_H
