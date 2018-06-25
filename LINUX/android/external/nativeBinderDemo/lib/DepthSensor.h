#ifndef DEPTH_SENSOR_H
#define DEPTH_SENSOR_H

//#include	"ProcessThread.h"



namespace android {

//class ProcessThread;

const int DEPTH_POINT_WIDTH = 224;
const int DEPTH_POINT_HEIGTH = 172;


/*
struct DepthPoint
{
    float x;                 //!< X coordinate [meters]
    float y;                 //!< Y coordinate [meters]
    float z;                 //!< Z coordinate [meters]
    float noise;             //!< noise value [meters]
    short int grayValue;      //!< 16-bit gray value
    signed char depthConfidence; //!< value from 0 (invalid) to 255 (full confidence)
};
*/

//typedef struct
//{
//	struct DepthPoint data[224 * 172];
//}depth_frame_t;

class ProcessThread;

class DepthSensor
{
	public:
		//DepthSensor(){
//	mProcessThread = new ProcessThread(this);
//	mProcessThread->start();
		//};

 		DepthSensor();
    	virtual ~DepthSensor();

	private:
		std::list<char *> mDepthSensorQueue;
		ProcessThread * mProcessThread;
		

	public:
		void push_back(char * item);
		char * pop_front();

		bool empty();
		//void start();

};





}; // namespace android

#endif


