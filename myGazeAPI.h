/**
*
* @mainpage myGaze API Documentation
*
* The myGaze Software Development Kit ("SDK") provides an Application Interface ("API") for 
* communication between your customized software application and the myGaze eyetracking-server, 
* allowing you to create full-featured eye tracking applications that take advantage of the powerful 
* features offered by myGaze eye tracking device. Specifically, the SDK was designed for add eye 
* tracking technology into their own custom applications. Using the functions provided in the SDK 
* you can control VI myGaze eye tracking device and retrieve eye tracking data. The SDK delivery 
* a high level Interface which provides maximum speed and minimum latency for data transfer. 
* Additionally, the SDK supports a growing number of programming languages and environments 
* including, but not limited to, MATLAB, C/C++, C#, Visual Basic, and Python. Several example 
* programs are provided for helping you get started with your application development. 
*
*
* (C) Copyright 2013, Visual Interaction GmbH 
*
* All rights reserved. This work contains unpublished proprietary information of 
* Visual Interaction GmbH and is copy protected by law. It may not be disclosed 
* to third parties or copied or duplicated in any form, in whole or in part, 
* without the specific written permission of Visual Interaction GmbH
*
* @author Visual Interaction GmbH 
*
*/ 

/**
* @file myGazeAPI.h 
*
* @brief The file contains the prototype declaration for all supported functions and data 
* structs the customer needs to use to get access the myGaze eyetracking device. 
**/ 

#pragma once 

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#define DLLExport __declspec(dllexport) 


#define RET_SUCCESS													1
#define RET_DATA_INVALID											2
#define RET_CALIBRATION_ABORTED										3
#define RET_SERVER_IS_RUNNING										4

#define ERR_CONNECTION_REFUSED										100 
#define ERR_CONNECTION_NOT_ESTABLISHED								101 
#define ERR_CALIBRATION_NOT_AVAILABLE								102 
#define ERR_CALIBRATION_NOT_VALIDATED								103 
#define ERR_SERVER_NOT_RUNNING										104 
#define ERR_SERVER_NOT_RESPONDING									105 
#define ERR_PARAMETER_INVALID										112 
#define ERR_PARAMETER_CALIBRATION_INVALID							113 
#define ERR_CALIBRATION_TIMEOUT										114 
#define ERR_TRACKING_NOT_STABLE										115 
#define ERR_SOCKET_CREATE											121 
#define ERR_SOCKET_CONNECT											122 
#define ERR_SOCKET_BIND												123 
#define ERR_SOCKET_DELETE											124 
#define ERR_SERVER_NO_RESPONSE										131 
#define ERR_SERVER_VERSION_INVALID									132 
#define ERR_SERVER_VERSION_UNKNOWN									133 
#define ERR_FILE_ACCESS												171 
#define ERR_SOCKET_ERROR											181 
#define ERR_SERVER_NOT_READY										194 
#define ERR_SERVER_NOT_FOUND										201	
#define ERR_SERVER_PATH_NOT_FOUND									202	
#define ERR_SERVER_ACCESS_DENIED									203 
#define ERR_SERVER_ACCESS_INCOMPLETE								204 
#define ERR_SERVER_OUT_OF_MEMORY									205 
#define ERR_DEVICE_NOT_FOUND										211 
#define ERR_DEVICE_UNKNOWN											212 
#define ERR_DEVICE_CONNECTED_TO_WRONG_PORT							213 
#define ERR_FEATURE_NOT_LICENSED									250



/**
* @enum CalibrationStatusEnum
*
* @brief This enum provides information about the eyetracking-server calibration status. If the 
* device is not calibrated the eyetracking-server won't deliver valid gaze data. Use the function 
* "iV_Calibrate" to perform a calibration. 
*
* The enum contains the following information:
* unknownCalibrationStatus:			calibration status is unknown (i.e. if the connection is not established) 
* noCalibration:					the device is not calibrated and will not deliver valid gaze data 
* validCalibration:					the device is calibrated and will deliver valid gaze data 
* performingCalibration:			the device is currently performing a calibration 
*/ 
enum CalibrationStatusEnum 
{
	unknownCalibrationStatus = 0, 
	noCalibration = 1, 
	validCalibration = 2, 
	performingCalibration = 3 
};


/**
* @struct SystemInfoStruct
*
* @brief This struct provides information about the eyetracking-server 
* version as well as the API version in use. To update the "SystemInfoStruct" 
* use the function "iV_GetSystemInfo". 
*
* The struct contains the following information:
* samplerate:			sample rate of eye tracking device in use 
* iV_MajorVersion:		major version number of the connected eyetracking-server 
* iV_MinorVersion:		minor version number of the connected eyetracking-server 
* iV_Buildnumber:		build number of the connected eyetracking-server 
* API_MajorVersion:		major version number of the myGaze SDK in use 
* API_MinorVersion:		minor version number of the myGaze SDK in use 
* API_Buildnumber:		build number of the myGaze SDK in use 
* iV_ETDevice:			myGaze device ID 
*/ 
struct SystemInfoStruct
{
	int samplerate;					
	int iV_MajorVersion;			
	int iV_MinorVersion;			
	int iV_Buildnumber;				
	int API_MajorVersion;			
	int API_MinorVersion;			
	int API_Buildnumber;			
	enum ETDevice iV_ETDevice;		
};


/**
* @struct CalibrationPointStruct
*
* @brief This struct provides information about the position of calibration points. To update 
* information in "CalibrationPointStruct" use function "iV_GetCalibrationPoint". 
*
* The struct contains the following information:
* number:		number of calibration point 
* positionX:	horizontal position of calibration point [pixel] 
* positionY:	vertical position of calibration point [pixel] 
*/ 
struct CalibrationPointStruct
{
	int number;							
	int positionX;						
	int positionY;						
};


/**
* @struct EyeDataStruct
*
* @brief This struct provides numerical information about eye data. 
* "EyeDataStruct" is part of "SampleStruct". To update information 
* in "SampleStruct" use function "iV_GetSample" or set the sample 
* callback with "iV_SetSampleCallback". 
*
* The struct contains the following information:
* gazeX:			horizontal gaze position on screen [pixel] 
* gazeY:			vertical gaze position on screen [pixel] 
* diam:				pupil diameter [mm] 
* eyePositionX:		horizontal eye position relative to camera [mm] 
* eyePositionY: 	vertical eye position relative to camera [mm] 
* eyePositionZ:		distance eye to camera [mm] 
*/ 
struct EyeDataStruct
{
	double gazeX;					
	double gazeY;					
	double diam;					
	double eyePositionX;			
	double eyePositionY;			
	double eyePositionZ;			
};


/**
* @struct SampleStruct
*
* @brief This struct provides information about a gaze data samples. 
* The data describes the last gaze data sample that has been calculated. 
* It will be automatically updated when a new gaze data sample has been 
* calculated. To update information in "SampleStruct" use the function 
* "iV_GetSample" or set the sample callback with "iV_SetSampleCallback". 
* Note: Due to averaging binocular data the gaze values are similar for 
* both eyes. 
*
* The struct contains the following information:
* timestamp:		timestamp of current gaze data sample [microseconds] 
* leftEye:			stores information of the left eye (see EyeDataStruct for more information) 
* rightEye:			stores information of the right eye (see EyeDataStruct for more information) 
*/ 
struct SampleStruct
{
	long long timestamp;
	EyeDataStruct leftEye;
	EyeDataStruct rightEye;
};


/**
* @struct SampleStruct32
*
* @brief This struct provides information about a gaze data samples. 
* The data describes the last gaze data sample that has been calculated. 
* It will be automatically updated when a new gaze data sample has been 
* calculated. To update information in "SampleStruct32" use the function 
* "iV_GetSample32". 
* Note: Due to averaging binocular data the gaze values are similar for 
* both eyes. 
*
* The struct contains the following information: 
* timestamp:		timestamp of current gaze data sample [microseconds] 
* leftEye:			stores information of the left eye (see EyeDataStruct for more information) 
* rightEye:			stores information of the right eye (see EyeDataStruct for more information) 
*/ 
struct SampleStruct32 
{
	long long timestamp;
	EyeDataStruct leftEye;
	EyeDataStruct rightEye;
};


/**
* @struct EventStruct
*
* @brief This struct provides information about the last eye event that has 
* been calculated. It will be updated when a new event has been calculated. 
* To update information in "EventStruct" use function "iV_GetEvent" or set 
* the event callback with with "iV_SetEventCallback". 
*
* The struct contains the following information:
* eventType:	type of eye event, 'F' for fixation (only fixations are supported) 
* eye:			related eye, 'l' for left eye, 'r' for right eye
* startTime: 	start time of the event [microseconds] 
* endTime: 		end time of the event [microseconds] 
* duration: 	duration of the event [microseconds] 
* positionX:	horizontal position of the fixation event [pixel] 
* positionY:	vertical position of the fixation event [pixel] 
*/ 
struct EventStruct
{
	char eventType;						
	char eye;							
	long long startTime;				
	long long endTime;					
	long long duration;					
	double positionX;					
	double positionY;					
};


/**
* @struct EventStruct32
*
* @brief This struct provides information about the last eye event that has 
* been calculated. It will be updated when a new event has been calculated. 
* To update information in "EventStruct32" use function "iV_GetEvent32". 
*
* The struct contains the following information:
* startTime: 	start time of the event [microseconds] 
* endTime: 		end time of the event [microseconds] 
* duration: 	duration of the event [microseconds] 
* positionX:	horizontal position of the fixation event [pixel] 
* positionY:	vertical position of the fixation event [pixel] 
* eventType:	type of eye event, 'F' for fixation (only fixations are supported) 
* eye:			related eye, 'l' for left eye, 'r' for right eye
*/ 
struct EventStruct32
{
	double startTime;					
	double endTime;						
	double duration;					
	double positionX;					
	double positionY;					
	char eventType;						
	char eye;							
};


/**
* @struct AccuracyStruct
*
* @brief This struct provides information about the last valid validation. 
* Therefore a valid validation must be done before the AccuracyStruct can be 
* updated. To update information in "AccuracyStruct" use function "iV_GetAccuracy". 
* Note: In this version the accuracy data is similar for both eyes. 
*
* The struct contains the following information:
* deviationLX:	horizontal calculated deviation for left eye [degree]
* deviationLY:	vertical calculated deviation for left eye [degree]
* deviationRX:	horizontal calculated deviation for right eye [degree]
* deviationRY:	vertical calculated deviation for right eye [degree]
*/ 
struct AccuracyStruct
{
	double deviationLX; 
	double deviationLY;	
	double deviationRX;	
	double deviationRY;	
};


/**
* @struct CalibrationStruct
*
* @brief Use this struct to customize the calibration and validation behavior. 
* To set calibration parameters with "CalibrationStruct" use function 
* "iV_SetupCalibration" before a calibration or validation has been started. 
*
* The struct contains the following information: 
* method:				select calibration method [0: calibration free, 1: 1 point calibration, 5: 5 point calibration (default: 5) ] 
* visualization:		not supported 
* displayDevice:		set display device [0: primary device (default), 1: secondary device] 
* speed:				set calibration/validation speed for each calibration point [0: slow (default), 1: fast] 
* autoAccept:			set calibration/validation acceptance behavior for each point [0: manual by space hit, 1: automatic (default)] 
* foregroundBrightness:	set calibration/validation target brightness [0..255] (default: 250) 
* backgroundBrightness:	set calibration/validation background brightness [0..255] (default: 220) 
* targetShape:			set calibration/validation target shape [IMAGE = 0, CIRCLE1 = 1, CIRCLE2 = 2 (default), CROSS = 3] 
* targetSize:			set calibration/validation target size (default: 20 pixels) 
* targetFilename: 		select custom calibration/validation target [.bmp, .jpg, .png] (only if targetShape = 0) 
*/ 
struct CalibrationStruct
{
	int method;	
	int visualization;	
	int displayDevice;	
	int speed;	
	int autoAccept;	
	int foregroundBrightness;
	int backgroundBrightness;
	int targetShape;
	int targetSize;	
	char targetFilename[256];
};


/**
* @struct MonitorAttachedGeometryStruct
*
* @brief Use this struct to customize myGaze geometry. (see chapter 'Monitor Attached Geometry' 
* in the myGaze SDK Manual). For setting up the myGaze geometry parameters with 
* "MonitorAttachedGeometryStruct" use function "iV_SetupMonitorAttachedGeometry". 
*
* The struct contains the following information:
* setupName:			name of the profile 
* stimX:				horizontal stimulus calibration size [mm] 
* stimY:				vertical stimulus calibration size [mm] 
* redStimDistHeight:	vertical distance myGaze to stimulus screen [mm] 
* redStimDistDepth:		horizontal distance myGaze to stimulus screen [mm] 
* redInclAngle:			myGaze inclination angle [degree] 
*/ 
struct MonitorAttachedGeometryStruct
{
	char setupName[256];
	int stimX;
	int stimY;
	int redStimDistHeight;
	int redStimDistDepth;
	int redInclAngle;
};



/**
* @struct ImageStruct
*
* @brief Use this struct to get raw tracking monitor image (format: RGB 24bpp) with 
* "iV_GetTrackingMonitor", or set the tracking monitor callback with "iV_SetTrackingMonitorCallback". 
*
* The struct contains the following information: 
* imageHeight:		vertical size of the image [pixel] 
* imageWidth:		horizontal size of the image [pixel] 
* imageSize:		image data size [bytes] 
* imageBuffer:		pointer to image data 
*/ 
struct ImageStruct
{
	int imageHeight;
	int imageWidth;
	int imageSize;
	char* imageBuffer;
};


/**
* @struct DateStruct 
*
* @brief Use this struct to get the license due date of the device. Use the 
* function "iV_GetLicenseDueDate" to update the "DateStruct". 
*
* The struct contains the following information:
* day:			day of license expiration 
* month:		month of license expiration 
* year:			year of license expiration 
*/ 
struct DateStruct
{
	int day;
	int month;
	int year;
};



typedef int (CALLBACK *pDLLSetSample)(struct SampleStruct sampleData);
typedef int (CALLBACK *pDLLSetEvent)(struct EventStruct eventData);
typedef int (CALLBACK *pDLLSetTrackingMonitor)(struct ImageStruct trackingMonitor);



/**
* @brief	Aborts a calibration or validation if they are in progress. iV_Calibrate or 
*			iV_Validate function will return with RET_CALIBRATION_ABORTED. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CALIBRATION_NOT_AVAILABLE			- calibration or validation not in progress 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
**/ 
DLLExport int __stdcall iV_AbortCalibration();


/**
* @brief	Accepts a calibration or validation point if the calibration or validation is in progress. 
*			The participant needs to be tracked and has to fixate the calibration or validation point. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CALIBRATION_NOT_AVAILABLE			- calibration or validation not in progress 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/ 
DLLExport int __stdcall iV_AcceptCalibrationPoint();


/**
* @brief 	Starts a calibration procedure. To proceed the participant needs to be tracked and 
*			has to fixate the calibration point. Depending on the calibration settings (which can 
*			be changed using "iV_SetupCalibration") the user can accept the calibration points 
*			manually (by pressing SPACE) or abort the calibration (by pressing ESC). If the 
*			calibration will be visualized the function won't return until the calibration has 
*			been finished (will be closed automatically) or aborted (ESC). 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_CALIBRATION_ABORTED					- calibration was aborted during progress 
* @return	ERR_CALIBRATION_TIMEOUT					- calibration was aborted automatically 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
* @return	ERR_PARAMETER_CALIBRATION_INVALID		- eye tracking device required for this calibration method is not connected
**/
DLLExport int __stdcall iV_Calibrate();


/**
* @brief	Changes the position of a calibration point. This has to be done before the calibration 
*			process will be started. The parameter number refers to the used calibration method. 
* 
* @param	number									- selected calibration point
* @param	positionX								- new X position on screen
* @param	positionY								- new Y position on screen
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
* @return	ERR_SERVER_NO_RESPONSE					- no response from eyetracking-server; check calibration name / identifier
**/ 
DLLExport int __stdcall iV_ChangeCalibrationPoint(int number, int positionX, int positionY);


/**
* @brief	Establishes a connection to myGaze eyetracking-server. "iV_Connect" will 
*			not return until connection has been established. If no connection 
*			can be established the function will return after three seconds 
*			(or if set different by "iV_SetConnectionTimeout"). 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_SERVER_NOT_FOUND					- no eyetracking-server detected 
* @return	ERR_SERVER_PATH_NOT_FOUND				- no eyetracking-server detected 
* @return	ERR_SERVER_OUT_OF_MEMORY				- eyetracking-server could not be started 
* @return	ERR_SERVER_NOT_RUNNING					- eyetracking-server is not running 
* @return	ERR_SOCKET_BIND							- another process is blocking the communication 
* @return	ERR_CONNECTION_REFUSED 					- failed to establish connection 
**/ 
DLLExport int __stdcall iV_Connect();


/**
* @brief	Wakes up and enables the eyetracking-server from suspend mode to continue processing 
*			gaze data. The application can be set to suspend mode by calling "iV_PauseEyetracking" 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/ 
DLLExport int __stdcall iV_ContinueEyetracking();


/**
* @brief 	Deletes the myGaze geometry setup with the given name. It is not possible 
*			to delete geometry profiles if it is currently in use. (see chapter 
*			'Monitor Attached Geometry' in the myGaze SDK Manual) 
*
* @param	setupName								- name of the geometry setup which will be deleted 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_DeleteMonitorAttachedGeometry(char setupName[256]);


/**
* @brief 	Disables a CPU high performance mode to allow the CPU to reduce the performance. 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_DisableProcessorHighPerformanceMode();


/**
* @brief	Disconnects from eyetracking-server. After this function has been 
*			called no other function can communication with the eyetracking-server. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_SOCKET_DELETE						- failed to delete sockets 
**/ 
DLLExport int __stdcall iV_Disconnect();


/**
* @brief 	Enables a CPU high performance mode to prevent the CPU from reducing the performance. 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_EnableProcessorHighPerformanceMode();


/**
* @brief 	Updates "accuracyData" struct with validated accuracy results. Before 
*			accuracy data is accessible the accuracy needs to be validated with 
*			"iV_Validate". 
*
* @param	accuracyData							- see reference information for "AccuracyStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID	 					- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_CALIBRATION_NOT_AVAILABLE 			- system is not calibrated
* @return	ERR_CALIBRATION_NOT_VALIDATED			- system is not validated
**/
DLLExport int __stdcall iV_GetAccuracy(struct AccuracyStruct *accuracyData);


/**
* @brief 	Updates "imageData" struct with drawn accuracy results. Before 
*			accuracy data is accessible the accuracy needs to be validated with 
*			"iV_Validate". 
*
* @param	imageData								- see reference information for "ImageStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID	 					- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_CALIBRATION_NOT_AVAILABLE 			- system is not calibrated
* @return	ERR_CALIBRATION_NOT_VALIDATED			- system is not validated
**/
DLLExport int __stdcall iV_GetAccuracyImage(struct ImageStruct *imageData);


/**
* @brief	Updates "calibrationData" information stored which are currently selected. 
*
* @param	calibrationData							- see reference information for "CalibrationStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetCalibrationParameter(struct CalibrationStruct *calibrationData);


/**
* @brief 	Updates "calibrationPoint" information from requested calibration point 
*
* @param	calibrationPointNumber					- requested calibration point 
* @param	calibrationPoint						- see reference information for "CalibrationPointStruct"
*
* @return	RET_SUCCESS 							- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_GetCalibrationPoint(int calibrationPointNumber, struct CalibrationPointStruct *calibrationPoint);


/**
* @brief	Updates "calibrationStatus" information. The client needs to be connected 
*			to the eyetracking-server. 
*
* @param	calibrationStatus						- see reference information for "CalibrationStatusEnum"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID	 					- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetCalibrationStatus(enum CalibrationStatusEnum *calibrationStatus);


/**
* @brief 	Gets the currently loaded geometry. (see chapter 'Monitor Attached Mode' in the myGaze SDK Manual) 
*
* @param	monitorAttachedGeometry 				- the data of the requested profile 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
**/
DLLExport int __stdcall iV_GetCurrentMonitorAttachedGeometry(struct MonitorAttachedGeometryStruct *monitorAttachedGeometry);


/**
* @brief 	Provides the current eye tracker timestamp. 
*
* @param	currentTimestamp						- provided time stamp 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetCurrentTimestamp(long long *currentTimestamp);


/**
* @brief 	Updates "eventDataSample" with current event data. 
*
* @param	eventDataSample							- see reference information for "EventStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetEvent(struct EventStruct *eventDataSample);


/**
* @brief 	Updates "eventDataSample" with current event data. 
*
* @param	eventDataSample							- see reference information for "EventStruct32"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetEvent32(struct EventStruct32 *eventDataSample);


/**
* @brief 	Gets the device specific feature key. 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetFeatureKey(long long *featureKey);


/**
* @brief 	Gets all available profiles by name. They will be written comma separated 
*			in the char buffer. The user meeds to be sure that the buffer is not smaller 
*			than the needed buffer length. (see chapter 'Monitor Attached Geometry' 
*			in the myGaze SDK Manual) 
*
* @param	maxSize 								- the length of the string profileNames 
* @param	profileNames 							- an empty string where all profile names will be copied to 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_GetGeometryProfiles(int maxSize, char *profileNames);


/**
* @brief 	Gets the system license due date. The license will not expire if the 
*			license is set to 00.00.0000 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetLicenseDueDate(struct DateStruct *licenseDueDate);


/**
* @brief 	Gets the geometry data of a requested profile without selecting them. 
*			(see chapter 'Monitor Attached Mode' in the myGaze SDK Manual) 
*
* @param	profileName 							- the name of the requested profile 
* @param	monitorAttachedGeometry 				- the data of the requested profile 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_GetMonitorAttachedGeometry(char profileName[256], struct MonitorAttachedGeometryStruct *monitorAttachedGeometry);


/**
* @brief 	Updates "rawDataSample" with current eye tracking data sample. 
*
* @param	rawDataSample							- see reference information for "GazeDataSampleStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetSample(struct SampleStruct *rawDataSample);


/**
* @brief 	Updates "rawDataSample" with current eye tracking data sample. 
*
* @param	rawDataSample							- see reference information for "SampleStruct32"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetSample32(struct SampleStruct32 *rawDataSample);


/**
* @brief	Updated the serial number information of the connected device 
*
* @param	serialNumber							- the serial number of the requested device  
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetSerialNumber(char serialNumber[64]);


/**
* @brief	Updates "systemInfoData" struct with current system information. 
*
* @param	systemInfoData							- see reference information for "SystemInfoStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_DATA_INVALID						- no new data available
**/
DLLExport int __stdcall iV_GetSystemInfo(struct SystemInfoStruct *systemInfoData);


/**
* @brief 	Updates "imageData" with current tracking monitor image 
*
* @param	imageData								- see reference information for "ImageStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_GetTrackingMonitor(struct ImageStruct *imageData);


/**
* @brief	Checks if connection to myGaze eyetracking-server is still established	
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
**/ 
DLLExport int __stdcall iV_IsConnected();


/**
* @brief	Checks if the participant will be tracked proper. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_TRACKING_NOT_STABLE					- tracking is not stable 
**/ 
DLLExport int __stdcall iV_IsTrackingStable(); 


/**
* @brief 	Loads a previously saved calibration. A calibration has to be saved by using 
*			"iV_SaveCalibration". The calibration will be stored persistently and is 
*			available after a restart of the server and/or client. 
*
* @param	name									- calibration name / identifier 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_LoadCalibration(char name[256]);


/**
* @brief	Suspend the eyetracking-server and disable calculation of gaze data. The application 
*			can be reactivated by calling "iV_ContinueEyetracking" 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/ 
DLLExport int __stdcall iV_PauseEyetracking();


/**
* @brief	Disconnects and closes myGaze eyetracking-server. After this function has been 
*			called no other function or application can communication with the eyetracking-server. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_SOCKET_DELETE						- failed to delete sockets 
**/ 
DLLExport int __stdcall iV_Quit();


/**
* @brief	Resets all calibration points to it's default position. 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
**/ 
DLLExport int __stdcall iV_ResetCalibrationPoints();


/**
* @brief 	Stores a calibration with a custom ID. To be able to store a calibration 
*			it is needed to be perform a previously a successfully calibration. The 
*			calibration will be stored persistently and is available after a restart 
*			of the server and/or client. 
*
* @param	name									- calibration name / identifier 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_CALIBRATION_NOT_AVAILABLE 			- system is not calibrated
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SaveCalibration(char name[256]);


/**
* @brief 	A customized timeout how long "iV_Connect" tries to connect to myGaze eyetracking-server 
*
* @param	time									- the time [sec] iV_Connect is waiting for myGaze eyetracking-server  
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid 
**/
DLLExport int __stdcall iV_SetConnectionTimeout(int time);


/**
* @brief 	Selects a predefined geometry profile. (see chapter 'Monitor Attached Mode' 
*			in the myGaze SDK Manual) 
*
* @param	profileName								- name of the selected profile which should be selected 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetGeometryProfile(char* profileName);


/**
* @brief 	Sets a callback functions for the event data. The function will be called 
*			if a real-time detected fixation has been started or ended. To disable the callback 
*			call the function with the parameter NULL. 
*			Important note: Algorithms with high processor usage and long calculation time 
*			shouldn't run within this callback due to a higher probability of data loss
*
* @param	pEventCallbackFunction					- pointer to EventCallbackFunction
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetEventCallback(pDLLSetEvent pEventCallbackFunction); 


/**
* @brief 	Defines the detection parameter for online fixation detection algorithm. 
*
* @param	minDuration								- minimum fixation duration [ms] 
*			maxDispersion							- maximum dispersion [pixel] 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetEventDetectionParameter(int minDuration, int maxDispersion);


/**
* @brief	Sets the customer license. If provided license is wrong "iV_Connect" refuses to connect. 
*
* @param	licenseKey								- provided license key 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid 
**/ 
DLLExport int __stdcall iV_SetLicense(const char* licenseKey);


/**
* @brief 	Sets a callback functions for the sample data. The function will be called 
*			if the myGaze eyetracking-server has calculated a new data sample. To disable 
*			the callback call the function with the parameter NULL. 
*			Important note: Algorithms with high processor usage and long calculation time 
*			shouldn't run within this callback due to a higher probability of data loss
*
* @param	pSampleCallbackFunction					- pointer to SampleCallbackFunction 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetSampleCallback(pDLLSetSample pSampleCallbackFunction); 


/**
* @brief 	Sets a callback functions for receiving the tracking monitor image. The function 
*			will be called if the myGaze SDK has calculated a tracking monitor image. The 
*			image format is RGB 24bpp. To disable the callback call the function with the parameter NULL. 
*			Important note: Algorithms with high processor usage and long calculation time 
*			shouldn't run within this callback due to a higher probability of data loss
*
* @param	pTrackingMonitorCallbackFunction		- pointer to TrackingMonitorCallbackFunction
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetTrackingMonitorCallback(pDLLSetTrackingMonitor pTrackingMonitorCallbackFunction);


/**
* @brief 	Sets the calibration and validation visualization parameter. 
*
* @param	calibrationData							- see reference information for "CalibrationStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
* @return	ERR_PARAMETER_CALIBRATION_NVALID 		- calibration method is invalid
**/
DLLExport int __stdcall iV_SetupCalibration(struct CalibrationStruct *calibrationData);


/**
* @brief 	Defines the myGaze monitor attached geometry. (see chapter 'Monitor Attached Mode' in the myGaze SDK Manual) 
*
* @param	monitorAttachedGeometry					- see reference information for "MonitorAttachedGeometryStruct"
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	ERR_PARAMETER_INVALID 					- parameter is invalid
**/
DLLExport int __stdcall iV_SetupMonitorAttachedGeometry(struct MonitorAttachedGeometryStruct *monitorAttachedGeometry);


/**
* @brief 	The validated accuracy results will be visualized in a dialog window. Before the 
*			image can be drawn the calibration needs to be performed with "iV_Calibrate" and 
*			validated with "iV_Validate". 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
* @return	RET_CALIBRATION_ABORTED					- validation was aborted during progress 
* @return	ERR_CALIBRATION_TIMEOUT					- validation was aborted automatically 
**/
DLLExport int __stdcall iV_ShowAccuracyMonitor();


/**
* @brief 	Visualizes myGaze tracking monitor in a dialog window. It shows the position of the 
*			participant related to the myGaze eyetracking device and indicates (using arrows) 
*			if the participant is not positioned in the center of the tracking head box. 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled
* @return	RET_DATA_INVALID						- no new data available
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established
**/
DLLExport int __stdcall iV_ShowTrackingMonitor(); 


/**
* @brief	Starts the myGaze eyetracking-server. The connection needs 
*			to be established separately using "iV_Connect". 
* 
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_SERVER_IS_RUNNING					- eyetracking-server is already running 
* @return	ERR_SERVER_NOT_FOUND					- failed to start myGaze eyetracking-server  
* @return	ERR_WRONG_CAMERA						- failed to start myGaze eyetracking-server 
* @return	ERR_CAMERA_NOT_FOUND					- could not detected any accessible device 
* @return	ERR_WRONG_CAMERA_PORT					- USB port not sufficient to access the device 
**/ 
DLLExport int __stdcall iV_Start();


/**
* @brief 	Starts a validation procedure. To proceed the participant needs to be tracked and 
*			has to fixate the validation point. Depending on the validation settings (which can 
*			be changed using "iV_SetupCalibration") the user can accept the validation points 
*			manually (by pressing SPACE or calling "iV_AcceptCalibrationPoint") or abort the 
*			calibration (by pressing ESC or calling "iV_AbortCalibration"). If the validation 
*			will be visualized by the API ("CalibrationStruct::visualization" is set to "1") 
*			the function won't return until the validation has been finished (closed automatically) 
*			or aborted (ESC). 
*
* @return	RET_SUCCESS								- intended functionality has been fulfilled 
* @return	RET_CALIBRATION_ABORTED					- validation was aborted during progress 
* @return	ERR_CONNECTION_NOT_ESTABLISHED			- no connection established 
* @return	ERR_CALIBRATION_NOT_AVAILABLE 			- system is not calibrated
* @return	ERR_CALIBRATION_TIMEOUT					- validation was aborted automatically due to a timeout 
**/
DLLExport int __stdcall iV_Validate();




