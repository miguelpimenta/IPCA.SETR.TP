#include "backend.h"
#include <string>

Backend::Backend(QObject *parent, QQmlApplicationEngine *ptr) : QObject(parent)
{
    this->mEngine = ptr;

    this->mBlkLeft = mEngine->rootObjects().at(0)->findChild<QObject*>("bLeft");
    this->mBlkRight = mEngine->rootObjects().at(0)->findChild<QObject*>("bRight");
    this->mSpeedMarker = mEngine->rootObjects().at(0)->findChild<QObject*>("marker1");
    this->mRotationsMarker = mEngine->rootObjects().at(0)->findChild<QObject*>("marker2");
    this->mGearLighter = mEngine->rootObjects().at(0)->findChild<QObject*>("gear");
    this->mMarkerSpd = mEngine->rootObjects().at(0)->findChild<QObject*>("markerSpd");
    this->mMarkerRot = mEngine->rootObjects().at(0)->findChild<QObject*>("markerRot");
    this->mSpdLight = mEngine->rootObjects().at(0)->findChild<QObject*>("spdLight");
    this->mRotLight = mEngine->rootObjects().at(0)->findChild<QObject*>("rotLight");
    this->mWheel = mEngine->rootObjects().at(0)->findChild<QObject*>("wheel");
    this->mWheelRot = mEngine->rootObjects().at(0)->findChild<QObject*>("wheelRot");
    this->mTemper = mEngine->rootObjects().at(0)->findChild<QObject*>("temper");
    this->mBuzzer = mEngine->rootObjects().at(0)->findChild<QObject*>("buzzer");

    // Port Read
    this->mPort = new QSerialPort();
    this->mPort->setBaudRate(QSerialPort::Baud9600);
    this->mPort->setStopBits(QSerialPort::OneStop);
    this->mPort->setDataBits(QSerialPort::Data8);
    this->mPort->setParity(QSerialPort::NoParity);
    this->mPort->setFlowControl(QSerialPort::NoFlowControl);
    // PORT
    this->mPort->setPortName("COM10");
    connect(mPort, SIGNAL(readyRead()), this, SLOT(newData()));
    this->mPort->open(QSerialPort::ReadWrite);
}

void Backend::newData()
{
    if (mPort->canReadLine())
    {
        QByteArray data = mPort->readLine();
        qDebug() << data;

        // Blinkers
        if (data.contains("Blink"))
        {
            if (data.contains("BlinkAll"))
            {
                blinkAll((data.contains("On") ? true : false));
            }
            else if (data.contains("BlinkLeft"))
            {
                blinkLeft((data.contains("On") ? true : false));
            }
            else if (data.contains("BlinkRight"))
            {
                blinkRight((data.contains("On") ? true : false));
            }
        }

        // Gears
        if (data.contains("Gear"))
        {
            if (data.contains("0"))
            {
                gearSwitch(0);
            }
            else if (data.contains("1"))
            {
                if (data.contains("-1"))
                {
                    gearSwitch(-1);
                }
                else
                {
                    gearSwitch(1);
                }
            }
            else if (data.contains("2"))
            {
                gearSwitch(2);
            }
            else if (data.contains("3"))
            {
                gearSwitch(3);
            }
            else if (data.contains("4"))
            {
                gearSwitch(4);
            }
            else if (data.contains("5"))
            {
                gearSwitch(5);
            }
            else if (data.contains("6"))
            {
                gearSwitch(6);
            }
        }

        // Start/Stop
        if (data.contains("START!"))
        {
            engineState(true);
        }
        if (data.contains("STOP!"))
        {
            engineState(false);
        }

        // Speed
        if (data.contains("Speed:"))
        {
            QString speed = data;
            carSpeed(speed.split(":")[1].toInt());
        }

        // RPMs
        if (data.contains("RPM:"))
        {
            QString rpm = data;
            carRPMs(rpm.split(":")[1].toInt());
        }

        // Wheel
        if (data.contains("<") || data.contains(">"))
        {
            QString wheel = data;
            wheelState(data);
        }

        // Buzz
        buzz(data.contains("BUZZ") ? true : false);

        // Temp
        if (data.contains("TEMP:"))
        {
            QString temp = data;
            temperature(qRound(temp.split(":")[1].toFloat()));
        }
    }
}

// Buzzer
void Backend::buzz(bool state)
{
    mBuzzer->setProperty("visible", state);
}

// Temperature
void Backend::temperature(int temp)
{
    //qDebug() << temp;
    mTemper->setProperty("text", temp);
}

// RPMs
void Backend::carRPMs(int rpm)
{
    int val = qRound( ((float)260/(float)8000) * (float)rpm);
    if (val >= 0 && val <= 260)
    {
        mMarkerRot->setProperty("angle", val);
    }
}

// Speed
void Backend::carSpeed(int speed)
{
    int spd = qRound( ((float)260/(float)300) * (float)speed);
    if (spd >= 0 && spd <= 260)
    {
        mMarkerSpd->setProperty("angle", spd);
    }
}

// Driving Wheel
void Backend::wheelState(QString wheelPos)
{
    // Turn Right
    if (wheelPos.trimmed() == ">")
    {
        mWheelRot->setProperty("angle", 15);
    }
    else if (wheelPos.trimmed() == ">>")
    {
        mWheelRot->setProperty("angle", 30);
    }
    else if (wheelPos.trimmed() == ">>>")
    {
        mWheelRot->setProperty("angle", 45);
    }
    // Turn Left
    else if (wheelPos.trimmed() == "<")
    {
        mWheelRot->setProperty("angle", -15);
    }
    else if (wheelPos.trimmed() == "<<")
    {
        mWheelRot->setProperty("angle", -30);
    }
    else if (wheelPos.trimmed() == "<<<")
    {
        mWheelRot->setProperty("angle", -45);
    }
}

// Engine Start/Stop
void Backend::engineState(bool state)
{
    mSpdLight->setProperty("visible", state);
    mRotLight->setProperty("visible", state);
    if (!state)
    {
        mMarkerSpd->setProperty("angle", 0);
        mMarkerRot->setProperty("angle", 0);
    }
}

// Blink All
void Backend::blinkAll(bool state)
{
    mBlkLeft->setProperty("visible", (state ? true : false));
    mBlkRight->setProperty("visible", (state ? true : false));
}

// Blink Left
void Backend::blinkLeft(bool state)
{
    mBlkLeft->setProperty("visible", (state ? true : false));
    mBlkRight->setProperty("visible", false);
}

// Blink Right
void Backend::blinkRight(bool state)
{
    mBlkRight->setProperty("visible", (state ? true : false));
    mBlkLeft->setProperty("visible", false);
}

// Gears
void Backend::gearSwitch(int gear)
{
    switch (gear) {
    case -1:
        mGearLighter->setProperty("x", 780);
        break;
    case 0:
        mGearLighter->setProperty("x", 525);
        break;
    case 1:
        mGearLighter->setProperty("x", 555);
        break;
    case 2:
        mGearLighter->setProperty("x", 590);
        break;
    case 3:
        mGearLighter->setProperty("x", 625);
        break;
    case 4:
        mGearLighter->setProperty("x", 665);
        break;
    case 5:
        mGearLighter->setProperty("x", 700);
        break;
    case 6:
        mGearLighter->setProperty("x", 740);
        break;
    }
}


