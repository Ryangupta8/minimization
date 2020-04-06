#include "ros/ros.h"
#include "Trajectory.h"
#include <limits>
#include <iostream>
#include <fstream>
#include "minimization/WaypointList.h"

using namespace Eigen;
using namespace std;


void trajectory_cb(const minimization::WaypointList& msg)
{
	ROS_INFO("Subscribing to the trajectory publisher");
	// Get msg values and convert to Eigen
	double maxVel_x = msg.maxVelocity;
	double maxVel_y = msg.maxVelocity;
	double maxAcc_x = msg.maxAcceleration;
	double maxAcc_y = msg.maxAcceleration;
	double size = msg.list_size;
	
	VectorXd maxV(2); maxV << maxVel_x, maxVel_y;
	VectorXd maxA(2); maxA << maxAcc_x, maxAcc_y;

	VectorXd temp(2); 
	double x, y; 
	list<VectorXd> wps;

	std::cout << "size = " << size << std::endl;
	std::cout << "msg.wp_list.size() = " << msg.wp_list.size() << std::endl;
	for(int i=0; i < msg.list_size; ++i){
		cout << "loop" << std::endl;
		x = msg.wp_list[i].x;
		y = msg.wp_list[i].y;
		temp << x, y;
		wps.push_back(temp);
	}

	Trajectory trajectory(Path(wps, 0.1), maxV, maxA);
	// Prints out txts for the phase plane plot
	trajectory.outputPhasePlaneTrajectory();


	if(trajectory.isValid()) {
		// Duration of the trajectory
		double duration = trajectory.getDuration();
		std::cout << "Trajectory duration: " << duration << " s" << std::endl << std::endl;
		std::cout << "Time      Position                  Velocity" << std::endl;
		// Save our variables in text files
		std::ofstream file1("/home/ryangupta/min_ws/src/minimization/output/xt_pos_vel.txt");
		std::ofstream file2("/home/ryangupta/min_ws/src/minimization/output/yt_pos_vel.txt");
		std::ofstream file3("/home/ryangupta/min_ws/src/minimization/output/time.txt");
		for(double t = 0.0; t < duration; t += 0.1) {
			file3 << t << std::endl; // time.txt

			file1 << trajectory.getPosition(t)[0] << "    " << trajectory.getVelocity(t)[0] << std::endl; // xt_pos_vel.txt

			file2 << trajectory.getPosition(t)[1] << "    " << trajectory.getVelocity(t)[1] << std::endl; // yt_pos_vel.txt

			printf("%6.4f   %7.4f %7.4f   %7.4f %7.4f\n", t, trajectory.getPosition(t)[0], trajectory.getPosition(t)[1],
				trajectory.getVelocity(t)[0], trajectory.getVelocity(t)[1]);
		}
		printf("%6.4f   %7.4f %7.4f   %7.4f %7.4f\n", duration, trajectory.getPosition(duration)[0], trajectory.getPosition(duration)[1],
			trajectory.getVelocity(duration)[0], trajectory.getVelocity(duration)[1]);
		file3 << duration << std::endl; // time.txt
		file1 << trajectory.getPosition(duration)[0] << "    " << trajectory.getVelocity(duration)[0] << std::endl; // xt_pos_vel.txt
		file2 << trajectory.getPosition(duration)[1] << "    " << trajectory.getVelocity(duration)[1] << std::endl; // yt_pos_vel.txt

		file1.close();
		file2.close();
		file3.close();
	}
	else {
		std::cout << "Trajectory generation failed." << std::endl;
	}

	ROS_INFO("Trajectory generation complete");
}


int main(int argc, char **argv){

	ros::init(argc,argv,"trajectory_listener");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("/py_coverage/trajectory", 1000, trajectory_cb);

	ros::spin();

	return 0;
}