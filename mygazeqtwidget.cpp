//mygazeqtwidget.cpp
//Written By Garret Hartman
//Implements the MyGazeQt Widget to provide the Qt interface for the MyGaze Eyetracker

#include "mygazeqtwidget.h"
#include "ui_mygazeqtwidget.h"
#include <QApplication>
#include "myGazeAPI.h"
#include <stdlib.h>
#include <iostream>
#include "tchar.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QMessageBox>
#include <QDebug>
#include <QLCDNumber>
#include <thread>
#include <QThread>
#include <Windows.h>

//create new struct variables for calibration, accuracy, and system info data sets
CalibrationStruct calibrationData;
AccuracyStruct accuracyData;
SystemInfoStruct systemInfoData;

// Create and define values for device status identifiers
// which will be later checked against defined status constants
// in the myGazeAPI in order to determine the devices state
int ret_calibrate = 0;
int ret_validate = 0;
int ret_connect = 0;

double sLeftEyeX = 0;
double sLeftEyeY = 0;
double sRightEyeX = 0;
double sRightEyeY = 0;
double eLeftEyeX = 0;
double eLeftEyeY = 0;
double eRightEyeX = 0;
double eRightEyeY = 0;

//MyGaze Widget UI Setup Constructor
MyGazeQTWidget::MyGazeQTWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MyGazeQTWidget) {
    ui->setupUi(this);
}

//MyGaze Widget Destructor
MyGazeQTWidget::~MyGazeQTWidget() {
    delete ui;
}

//Connection Button Clicked -> initiate eyetracker hardware connection
void MyGazeQTWidget::on_connectButton_clicked() {

    //start connection process using button text to indicate connection status
    ui->connectButton->setText("Connecting...");
    ui->connectButton->setEnabled(false);
    connectEyetracker();

    //start calibration process
    //ui->connectButton->setText("Calibrating...");
    //if(ret_connect == RET_SUCCESS) {
    //    calibrateEyetracker();
    //}

    //update button text to connected or reset if connection or calibration fails
    if(ret_connect == RET_SUCCESS ) {
        ui->connectButton->setText("Connected");
        ui->startSessionButton->setEnabled(true);
    }
    else {
        ui->connectButton->setText("Connect");
        ui->connectButton->setEnabled(true);
    }
}

//static callback function to refresh sample data
int MyGazeQTWidget::sampleCallbackFunction(SampleStruct sampleData) {

    sLeftEyeX = sampleData.leftEye.gazeX;
    sLeftEyeY = sampleData.leftEye.gazeY;
    sRightEyeX = sampleData.rightEye.gazeX;
    sRightEyeY = sampleData.rightEye.gazeY;

    //log left and right eye sample coordinates
    qDebug() << "Left eye X: " << sampleData.leftEye.gazeX << " Left eye Y: " << sampleData.leftEye.gazeY << "\n";
    qDebug() << "Right eye X: " << sampleData.rightEye.gazeX << " Right eye Y: " << sampleData.rightEye.gazeY<< "\n";
    return 1; //returns successful operation status
}

//static callback function to refresh event data
int MyGazeQTWidget::eventCallbackFunction(EventStruct eventData)
{
    qDebug() << "Fixation event - X: " << eventData.positionX << " Y: " << eventData.positionY << "\n"; //log event data
    return 1; //returns successful operation status
}

//Starts an eyetracking session and logs data to file
void MyGazeQTWidget::on_startSessionButton_clicked() {
    iV_ShowTrackingMonitor(); 	 //start tracking monitor window
    SampleStruct currentSample;   //create a SampleStruct to store sample data
    EventStruct currentEvent;	 //create an EventStruct to store event data
    iV_GetSample(&currentSample); //get the sample data and store in currentSample
    iV_GetEvent(&currentEvent);   //get the event data and store in currentEvent

    pDLLSetSample setSample = &MyGazeQTWidget::sampleCallbackFunction;
    pDLLSetEvent setEvent = &MyGazeQTWidget::eventCallbackFunction;

    iV_SetSampleCallback(setSample); // pass sample callback function into setup function
    iV_SetEventCallback(setEvent); //pass event callback function into setup function
}

//Open settings pannel (calibration data, toggle switches for different output)
void MyGazeQTWidget::on_settingsButton_clicked() {
    //TODO
}

//In progress: Sets up calibration of the eyetracking device and validates the calibration data
void MyGazeQTWidget::calibrateEyetracker() {
    iV_SetupCalibration(&calibrationData);
    ret_calibrate = iV_Calibrate(); //get calibration status
    if (ret_calibrate == RET_SUCCESS) {
        qDebug() << "Calibration done successfully"; //update debug log
        ret_validate = iV_Validate(); //validate calibration data
        if (ret_validate == RET_SUCCESS) {
            //  read out the accuracy values
            if (iV_GetAccuracy(&accuracyData) == RET_SUCCESS) {
                qDebug() << "AccuracyData - dev left X: " << accuracyData.deviationLX << " dev left Y: " << accuracyData.deviationLY;
            }
        }
        else {
            qDebug() << "Validation could not be finished: " << ret_validate ;
            displayErrorMessageBox();
            return;
        }
    }
    else {
        qDebug() << "Calibration could not be finished: " << ret_calibrate ; //write status to debug log
        displayErrorMessageBox();
        return;
    }
}

//Connects MyGaze EyeTracker to the MyGaze Server and returns int status
void MyGazeQTWidget::connectEyetracker() {
    iV_Start();

    //Connect to the eye tracking server and print the outcome to console
    ret_connect = iV_Connect();
    if(ret_connect == RET_SUCCESS) {
        qDebug() << "Eyetracker Connected"; //write connection status to debug log
    }
    else {
        qDebug() << "Eyetracker Could Not Be Connected";
        displayErrorMessageBox();
    }
}

//Displays a messagebox with appropiate error message
void MyGazeQTWidget::displayErrorMessageBox() {
    QMessageBox *msgBox = new QMessageBox();

    if(ret_connect == ERR_CONNECTION_NOT_ESTABLISHED) {
        msgBox->setText("Connection Error: Connection to eye tracking hardware was not established.");
    }
    else if (ret_connect == ERR_CONNECTION_REFUSED) {
        msgBox->setText("Connection Error: Connection to Eye Tracker Was Refused");
    }
    else if(ret_connect == ERR_SERVER_NOT_RUNNING || ret_connect == ERR_SERVER_NOT_RESPONDING){
        msgBox->setText("Connection Error: MyGaze server not running or not responding");
    }
    else if (ret_calibrate == ERR_CONNECTION_NOT_ESTABLISHED) {
        msgBox->setText("Calibration Error: Connection to eye tracking hardware was not established.");
    }
    else if(ret_calibrate == ERR_CALIBRATION_TIMEOUT) {
        msgBox->setText("Calibration Error: Calibration has timed out. Please make sure Eye Tracker is stable and try again");
    }
    else if(ret_calibrate == ERR_CALIBRATION_NOT_AVAILABLE) {
        msgBox->setText("Calibration Error: Calibration data not found or not available");
    }
    else if(ret_calibrate == ERR_CALIBRATION_NOT_VALIDATED) {
        msgBox->setText("Calibration Error: Calibration could not be validated.");
    }
    else if(ret_calibrate == ERR_SERVER_NOT_FOUND) {
        msgBox->setText("Calibration Error: MyGaze Server not found.");
    }
    else if(ret_calibrate == ERR_SERVER_NOT_RUNNING || ret_calibrate == ERR_SERVER_NOT_RESPONDING) {
        msgBox->setText("Calibration Error: MyGaze Server not running or not responding");
    }
    else {
        msgBox->setText("Undefined Error: Please check Eye Tracker connection and server software");
    }
    msgBox->exec();
}

void MyGazeQTWidget::on_quitButton_clicked() {
    iV_Disconnect(); //disconnect hardware from server
    QApplication::quit(); //quit qt application
}
