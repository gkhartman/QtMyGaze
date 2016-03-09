//MyGazeQT widget driver
//Written by Garret Hartman
//Qt5 addaptation of Jose Silva's MyGaze Connection Software

#include "mygazeqtwidget.h"
#include <QApplication>
#include "myGazeAPI.h"
#include <stdlib.h>
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <mygazeqtwidget.h>

//Begin main program procedure
int main(int argc, char *argv[]) {

    //create new QT application and widget then display
    QApplication a(argc, argv);
    MyGazeQTWidget w;
    w.show();
    return a.exec(); //return from main

}//end main


////////////////Jose's Code//////////////////////////////////
//#include "mygazehaptic.h"
//#include <QtWidgets/QApplication>
//#include  "QtWidgets\qapplication.h"
//#include "Eye.h"


//myGazeHaptic *window;
//CalibrationStruct Global_calibrationData;
//int Global_ret_calibrate;
//int Global_ret_validate;
//AccuracyStruct Global_accuracyData;
//QTextStream *out;
//int beginEyeTracker(int argc, _TCHAR* argv[]);

//int __stdcall SampleCallbackFunction(SampleStruct sampleData)

//{
//	window->notify(sampleData.leftEye.gazeX,sampleData.leftEye.gazeY);
//	QString xValue = QString::number(sampleData.leftEye.gazeX);
//	QString yValue = QString::number(sampleData.leftEye.gazeY);

//	out->operator<<( "X : "+xValue+ "      "+ " Y : " + yValue + "\n");

//	return 1;
//}

//int __stdcall EventCallbackFunction(EventStruct eventData)
//{
//	dtd::cout << "Fixation event - X: " << eventData.positionX << " Y: " << eventData.positionY << std::endl;
//	return 1;
//}

//void closeThePortals(){
//	iV_SetSampleCallback(NULL);
//	iV_SetEventCallback(NULL);
//	QString disconnect = QString::number(iV_Disconnect());

//	window->stringNotify("iV_Disconnect: " + disconnect);
//}

//void calibrateFunction(){


//		iV_SetupCalibration(&Global_calibrationData);

//		// start the calibration process
//		Global_ret_calibrate = iV_Calibrate();
//		if (Global_ret_calibrate == RET_SUCCESS)
//		{
//			qDebug() << "Calibration done successfully";

//			// start the validation process
//			Global_ret_validate = iV_Validate();
//			if (Global_ret_validate == RET_SUCCESS)
//			{
//				qDebug() << "Validation done successfully" ;

//				//  read out the accuracy values
//				if (iV_GetAccuracy(&Global_accuracyData) == RET_SUCCESS)
//				{
//					qDebug() << "AccuracyData - dev left X: " << Global_accuracyData.deviationLX << " dev left Y: " << Global_accuracyData.deviationLY;
//					getchar();
//				}

//			}
//			else
//			{
//				qDebug() << "Validation could not be finished: " << Global_ret_validate ;
//			}

//		}
//		else
//		{
//			if (Global_ret_calibrate == 101){
//				window->stringNotify("EyeTracker must be running in order to calibrate. Restart EyeTracker");
//			}
//			qDebug() << "Calibration could not be finished: " << Global_ret_calibrate ;
//		}


//}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return beginEyeTracker(argc, argv);


//}
//int beginEyeTracker(int argc, _TCHAR* argv[]){
//	QApplication a(argc, argv);
//	window = new myGazeHaptic();

//	AccuracyStruct accuracyData;
//	SystemInfoStruct systemInfoData;
//	CalibrationStruct calibrationData;

//	Global_accuracyData = accuracyData;
//	Global_calibrationData = calibrationData;


//	int ret_calibrate = 0;
//	int ret_validate = 0;
//	int ret_connect = 0;

//	Global_ret_calibrate = ret_calibrate;
//	Global_ret_validate = ret_validate;



//	window->stringNotify("Command line output from myGazeAPI Demo");
//	////open the file

//	QFile file("eyeTrackingValues.txt");
//	file.open(QIODevice::WriteOnly | QIODevice::Text);
//	out = new QTextStream(&file);



//	// ----------------------------------------------------------------------------
//	// ---- connect to myGaze eyetracking-server
//	// ----------------------------------------------------------------------------
//	ret_connect = iV_Connect();
//	if (ret_connect == RET_SUCCESS)
//	{
//		window->stringNotify("Connection to eyetracking-server was established successfully");
//	}
//	else
//	{
//		QString ret_connect_code = QString::number(ret_connect);
//		window->stringNotify("Connection could not be established: " + ret_connect_code);
//		getchar();
//		qDebug() << "sucessful termination";
//		return a.exec();
//	}


//	// ----------------------------------------------------------------------------
//	// ---- read out system information
//	// ----------------------------------------------------------------------------
//	if (iV_GetSystemInfo(&systemInfoData) == RET_SUCCESS)
//	{
//		QString iV_MajorVersion = QString::number(systemInfoData.iV_MajorVersion);
//		QString iV_MinorVersion = QString::number(systemInfoData.iV_MinorVersion);
//		QString iV_Buildnumber = QString::number(systemInfoData.iV_Buildnumber);

//		window->stringNotify("SystemInfo eyetracking-server version: " + iV_MajorVersion + "." + iV_MinorVersion + "." + iV_Buildnumber);
//		//std::cout << "SystemInfo eyetracking-server version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;

//		QString API_MajorVersion = QString::number(systemInfoData.API_MajorVersion);
//		QString API_MinorVersion = QString::number(systemInfoData.API_MinorVersion);
//		QString API_Buildnumber = QString::number(systemInfoData.API_Buildnumber);

//		window->stringNotify("SystemInfo API version: " + API_MajorVersion + "."
//			+ API_MinorVersion + "." + API_Buildnumber);

//		//std::cout << "SystemInfo API version: " << systemInfoData.API_MajorVersion << "."<< systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;

//		QString samplerate = QString::number(systemInfoData.samplerate);
//		window->stringNotify("SystemInfo samplerate: " + samplerate);

//	}

//	// ----------------------------------------------------------------------------
//	// ---- start the calibration and validation process
//	// ----------------------------------------------------------------------------

//	// see the User Manual for detailed information due to setting up calibration
//	calibrationData.method = 5;
//	calibrationData.speed = 0;
//	calibrationData.displayDevice = 0;
//	calibrationData.targetShape = 2;
//	calibrationData.foregroundBrightness = 250;
//	calibrationData.backgroundBrightness = 230;
//	calibrationData.autoAccept = 1;
//	calibrationData.targetSize = 20;
//	calibrationData.visualization = 1;
//	strcpy(calibrationData.targetFilename, "");


//	//QObject::connect(window->getCalibrateButtonPointer(), &QPushButton::clicked, calibrateFunction);




//	// ----------------------------------------------------------------------------
//	// ---- accessing eye tracking data stream
//	// ----------------------------------------------------------------------------

//	// start monitoring tracking status
//	iV_ShowTrackingMonitor();


//	// define a callback function for gaze data samples

//	iV_SetSampleCallback(SampleCallbackFunction);

//	// define a callback function for fixation events
//	iV_SetEventCallback(EventCallbackFunction);

//	getchar();
//	getchar();

//	// disable callback function for receiving gaze data samples
//	//QObject::connect(window->getButtonPointer,SIGNAL(clicked()), iV_SetSampleCallback(NULL));
//	QObject::connect(window->getButtonPointer(), &QPushButton::clicked, closeThePortals);
//	// disable callback function for receiving fixation events




//	// ----------------------------------------------------------------------------
//	// ---- disconnect from myGaze eyetracking server
//	// ----------------------------------------------------------------------------



//	getchar();



//	qDebug() << "sucessful termination END";
//	return a.exec();
//}
//////////////////////////////////////////////////////////
////////////////Jose's Code//////////////////////////////////
//#include "mygazehaptic.h"
//#include <QtWidgets/QApplication>
//#include  "QtWidgets\qapplication.h"
//#include "Eye.h"


//myGazeHaptic *window;
//CalibrationStruct Global_calibrationData;
//int Global_ret_calibrate;
//int Global_ret_validate;
//AccuracyStruct Global_accuracyData;
//QTextStream *out;
//int beginEyeTracker(int argc, _TCHAR* argv[]);

//int __stdcall SampleCallbackFunction(SampleStruct sampleData)

//{
//	window->notify(sampleData.leftEye.gazeX,sampleData.leftEye.gazeY);
//	QString xValue = QString::number(sampleData.leftEye.gazeX);
//	QString yValue = QString::number(sampleData.leftEye.gazeY);

//	out->operator<<( "X : "+xValue+ "      "+ " Y : " + yValue + "\n");

//	return 1;
//}

//int __stdcall EventCallbackFunction(EventStruct eventData)
//{
//	dtd::cout << "Fixation event - X: " << eventData.positionX << " Y: " << eventData.positionY << std::endl;
//	return 1;
//}

//void closeThePortals(){
//	iV_SetSampleCallback(NULL);
//	iV_SetEventCallback(NULL);
//	QString disconnect = QString::number(iV_Disconnect());

//	window->stringNotify("iV_Disconnect: " + disconnect);
//}

//void calibrateFunction(){


//		iV_SetupCalibration(&Global_calibrationData);

//		// start the calibration process
//		Global_ret_calibrate = iV_Calibrate();
//		if (Global_ret_calibrate == RET_SUCCESS)
//		{
//			qDebug() << "Calibration done successfully";

//			// start the validation process
//			Global_ret_validate = iV_Validate();
//			if (Global_ret_validate == RET_SUCCESS)
//			{
//				qDebug() << "Validation done successfully" ;

//				//  read out the accuracy values
//				if (iV_GetAccuracy(&Global_accuracyData) == RET_SUCCESS)
//				{
//					qDebug() << "AccuracyData - dev left X: " << Global_accuracyData.deviationLX << " dev left Y: " << Global_accuracyData.deviationLY;
//					getchar();
//				}

//			}
//			else
//			{
//				qDebug() << "Validation could not be finished: " << Global_ret_validate ;
//			}

//		}
//		else
//		{
//			if (Global_ret_calibrate == 101){
//				window->stringNotify("EyeTracker must be running in order to calibrate. Restart EyeTracker");
//			}
//			qDebug() << "Calibration could not be finished: " << Global_ret_calibrate ;
//		}


//}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return beginEyeTracker(argc, argv);


//}
//int beginEyeTracker(int argc, _TCHAR* argv[]){
//	QApplication a(argc, argv);
//	window = new myGazeHaptic();

//	AccuracyStruct accuracyData;
//	SystemInfoStruct systemInfoData;
//	CalibrationStruct calibrationData;

//	Global_accuracyData = accuracyData;
//	Global_calibrationData = calibrationData;


//	int ret_calibrate = 0;
//	int ret_validate = 0;
//	int ret_connect = 0;

//	Global_ret_calibrate = ret_calibrate;
//	Global_ret_validate = ret_validate;



//	window->stringNotify("Command line output from myGazeAPI Demo");
//	////open the file

//	QFile file("eyeTrackingValues.txt");
//	file.open(QIODevice::WriteOnly | QIODevice::Text);
//	out = new QTextStream(&file);



//	// ----------------------------------------------------------------------------
//	// ---- connect to myGaze eyetracking-server
//	// ----------------------------------------------------------------------------
//	ret_connect = iV_Connect();
//	if (ret_connect == RET_SUCCESS)
//	{
//		window->stringNotify("Connection to eyetracking-server was established successfully");
//	}
//	else
//	{
//		QString ret_connect_code = QString::number(ret_connect);
//		window->stringNotify("Connection could not be established: " + ret_connect_code);
//		getchar();
//		qDebug() << "sucessful termination";
//		return a.exec();
//	}


//	// ----------------------------------------------------------------------------
//	// ---- read out system information
//	// ----------------------------------------------------------------------------
//	if (iV_GetSystemInfo(&systemInfoData) == RET_SUCCESS)
//	{
//		QString iV_MajorVersion = QString::number(systemInfoData.iV_MajorVersion);
//		QString iV_MinorVersion = QString::number(systemInfoData.iV_MinorVersion);
//		QString iV_Buildnumber = QString::number(systemInfoData.iV_Buildnumber);

//		window->stringNotify("SystemInfo eyetracking-server version: " + iV_MajorVersion + "." + iV_MinorVersion + "." + iV_Buildnumber);
//		//std::cout << "SystemInfo eyetracking-server version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;

//		QString API_MajorVersion = QString::number(systemInfoData.API_MajorVersion);
//		QString API_MinorVersion = QString::number(systemInfoData.API_MinorVersion);
//		QString API_Buildnumber = QString::number(systemInfoData.API_Buildnumber);

//		window->stringNotify("SystemInfo API version: " + API_MajorVersion + "."
//			+ API_MinorVersion + "." + API_Buildnumber);

//		//std::cout << "SystemInfo API version: " << systemInfoData.API_MajorVersion << "."<< systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;

//		QString samplerate = QString::number(systemInfoData.samplerate);
//		window->stringNotify("SystemInfo samplerate: " + samplerate);

//	}

//	// ----------------------------------------------------------------------------
//	// ---- start the calibration and validation process
//	// ----------------------------------------------------------------------------

//	// see the User Manual for detailed information due to setting up calibration
//	calibrationData.method = 5;
//	calibrationData.speed = 0;
//	calibrationData.displayDevice = 0;
//	calibrationData.targetShape = 2;
//	calibrationData.foregroundBrightness = 250;
//	calibrationData.backgroundBrightness = 230;
//	calibrationData.autoAccept = 1;
//	calibrationData.targetSize = 20;
//	calibrationData.visualization = 1;
//	strcpy(calibrationData.targetFilename, "");


//	//QObject::connect(window->getCalibrateButtonPointer(), &QPushButton::clicked, calibrateFunction);




//	// ----------------------------------------------------------------------------
//	// ---- accessing eye tracking data stream
//	// ----------------------------------------------------------------------------

//	// start monitoring tracking status
//	iV_ShowTrackingMonitor();


//	// define a callback function for gaze data samples

//	iV_SetSampleCallback(SampleCallbackFunction);

//	// define a callback function for fixation events
//	iV_SetEventCallback(EventCallbackFunction);

//	getchar();
//	getchar();

//	// disable callback function for receiving gaze data samples
//	//QObject::connect(window->getButtonPointer,SIGNAL(clicked()), iV_SetSampleCallback(NULL));
//	QObject::connect(window->getButtonPointer(), &QPushButton::clicked, closeThePortals);
//	// disable callback function for receiving fixation events




//	// ----------------------------------------------------------------------------
//	// ---- disconnect from myGaze eyetracking server
//	// ----------------------------------------------------------------------------



//	getchar();



//	qDebug() << "sucessful termination END";
//	return a.exec();
//}
//////////////////////////////////////////////////////////
////////////////Jose's Code//////////////////////////////////
//#include "mygazehaptic.h"
//#include <QtWidgets/QApplication>
//#include  "QtWidgets\qapplication.h"
//#include "Eye.h"


//myGazeHaptic *window;
//CalibrationStruct Global_calibrationData;
//int Global_ret_calibrate;
//int Global_ret_validate;
//AccuracyStruct Global_accuracyData;
//QTextStream *out;
//int beginEyeTracker(int argc, _TCHAR* argv[]);

//int __stdcall SampleCallbackFunction(SampleStruct sampleData)

//{
//	window->notify(sampleData.leftEye.gazeX,sampleData.leftEye.gazeY);
//	QString xValue = QString::number(sampleData.leftEye.gazeX);
//	QString yValue = QString::number(sampleData.leftEye.gazeY);

//	out->operator<<( "X : "+xValue+ "      "+ " Y : " + yValue + "\n");

//	return 1;
//}

//int __stdcall EventCallbackFunction(EventStruct eventData)
//{
//	dtd::cout << "Fixation event - X: " << eventData.positionX << " Y: " << eventData.positionY << std::endl;
//	return 1;
//}

//void closeThePortals(){
//	iV_SetSampleCallback(NULL);
//	iV_SetEventCallback(NULL);
//	QString disconnect = QString::number(iV_Disconnect());

//	window->stringNotify("iV_Disconnect: " + disconnect);
//}

//void calibrateFunction(){


//		iV_SetupCalibration(&Global_calibrationData);

//		// start the calibration process
//		Global_ret_calibrate = iV_Calibrate();
//		if (Global_ret_calibrate == RET_SUCCESS)
//		{
//			qDebug() << "Calibration done successfully";

//			// start the validation process
//			Global_ret_validate = iV_Validate();
//			if (Global_ret_validate == RET_SUCCESS)
//			{
//				qDebug() << "Validation done successfully" ;

//				//  read out the accuracy values
//				if (iV_GetAccuracy(&Global_accuracyData) == RET_SUCCESS)
//				{
//					qDebug() << "AccuracyData - dev left X: " << Global_accuracyData.deviationLX << " dev left Y: " << Global_accuracyData.deviationLY;
//					getchar();
//				}

//			}
//			else
//			{
//				qDebug() << "Validation could not be finished: " << Global_ret_validate ;
//			}

//		}
//		else
//		{
//			if (Global_ret_calibrate == 101){
//				window->stringNotify("EyeTracker must be running in order to calibrate. Restart EyeTracker");
//			}
//			qDebug() << "Calibration could not be finished: " << Global_ret_calibrate ;
//		}


//}
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return beginEyeTracker(argc, argv);


//}
//int beginEyeTracker(int argc, _TCHAR* argv[]){
//	QApplication a(argc, argv);
//	window = new myGazeHaptic();

//	AccuracyStruct accuracyData;
//	SystemInfoStruct systemInfoData;
//	CalibrationStruct calibrationData;

//	Global_accuracyData = accuracyData;
//	Global_calibrationData = calibrationData;


//	int ret_calibrate = 0;
//	int ret_validate = 0;
//	int ret_connect = 0;

//	Global_ret_calibrate = ret_calibrate;
//	Global_ret_validate = ret_validate;



//	window->stringNotify("Command line output from myGazeAPI Demo");
//	////open the file

//	QFile file("eyeTrackingValues.txt");
//	file.open(QIODevice::WriteOnly | QIODevice::Text);
//	out = new QTextStream(&file);



//	// ----------------------------------------------------------------------------
//	// ---- connect to myGaze eyetracking-server
//	// ----------------------------------------------------------------------------
//	ret_connect = iV_Connect();
//	if (ret_connect == RET_SUCCESS)
//	{
//		window->stringNotify("Connection to eyetracking-server was established successfully");
//	}
//	else
//	{
//		QString ret_connect_code = QString::number(ret_connect);
//		window->stringNotify("Connection could not be established: " + ret_connect_code);
//		getchar();
//		qDebug() << "sucessful termination";
//		return a.exec();
//	}


//	// ----------------------------------------------------------------------------
//	// ---- read out system information
//	// ----------------------------------------------------------------------------
//	if (iV_GetSystemInfo(&systemInfoData) == RET_SUCCESS)
//	{
//		QString iV_MajorVersion = QString::number(systemInfoData.iV_MajorVersion);
//		QString iV_MinorVersion = QString::number(systemInfoData.iV_MinorVersion);
//		QString iV_Buildnumber = QString::number(systemInfoData.iV_Buildnumber);

//		window->stringNotify("SystemInfo eyetracking-server version: " + iV_MajorVersion + "." + iV_MinorVersion + "." + iV_Buildnumber);
//		//std::cout << "SystemInfo eyetracking-server version: " << systemInfoData.iV_MajorVersion << "." << systemInfoData.iV_MinorVersion << "." << systemInfoData.iV_Buildnumber << std::endl;

//		QString API_MajorVersion = QString::number(systemInfoData.API_MajorVersion);
//		QString API_MinorVersion = QString::number(systemInfoData.API_MinorVersion);
//		QString API_Buildnumber = QString::number(systemInfoData.API_Buildnumber);

//		window->stringNotify("SystemInfo API version: " + API_MajorVersion + "."
//			+ API_MinorVersion + "." + API_Buildnumber);

//		//std::cout << "SystemInfo API version: " << systemInfoData.API_MajorVersion << "."<< systemInfoData.API_MinorVersion << "." << systemInfoData.API_Buildnumber << std::endl;

//		QString samplerate = QString::number(systemInfoData.samplerate);
//		window->stringNotify("SystemInfo samplerate: " + samplerate);

//	}

//	// ----------------------------------------------------------------------------
//	// ---- start the calibration and validation process
//	// ----------------------------------------------------------------------------

//	// see the User Manual for detailed information due to setting up calibration
//	calibrationData.method = 5;
//	calibrationData.speed = 0;
//	calibrationData.displayDevice = 0;
//	calibrationData.targetShape = 2;
//	calibrationData.foregroundBrightness = 250;
//	calibrationData.backgroundBrightness = 230;
//	calibrationData.autoAccept = 1;
//	calibrationData.targetSize = 20;
//	calibrationData.visualization = 1;
//	strcpy(calibrationData.targetFilename, "");


//	//QObject::connect(window->getCalibrateButtonPointer(), &QPushButton::clicked, calibrateFunction);




//	// ----------------------------------------------------------------------------
//	// ---- accessing eye tracking data stream
//	// ----------------------------------------------------------------------------

//	// start monitoring tracking status
//	iV_ShowTrackingMonitor();


//	// define a callback function for gaze data samples

//	iV_SetSampleCallback(SampleCallbackFunction);

//	// define a callback function for fixation events
//	iV_SetEventCallback(EventCallbackFunction);

//	getchar();
//	getchar();

//	// disable callback function for receiving gaze data samples
//	//QObject::connect(window->getButtonPointer,SIGNAL(clicked()), iV_SetSampleCallback(NULL));
//	QObject::connect(window->getButtonPointer(), &QPushButton::clicked, closeThePortals);
//	// disable callback function for receiving fixation events




//	// ----------------------------------------------------------------------------
//	// ---- disconnect from myGaze eyetracking server
//	// ----------------------------------------------------------------------------



//	getchar();



//	qDebug() << "sucessful termination END";
//	return a.exec();
//}
//////////////////////////////////////////////////////////
