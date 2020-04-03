#include "ros/ros.h"
#include "Trajectory.h"
#include <limits>
#include <iostream>
#include <fstream>
#include "minimization/Trajectorymsg.h"

using namespace Eigen;
using namespace std;


void trajectory_cb(const minimization::Trajectorymsg& msg)
{
	ROS_INFO("Subscribing to the trajectory publisher");
	// Get msg values and convert to Eigen
	double maxVel_x = msg.maxVelocity.data[0];
	double maxVel_y = msg.maxVelocity.data[1];
	double maxAcc_x = msg.maxAcceleration.data[0];
	double maxAcc_y = msg.maxAcceleration.data[1];
	
	VectorXd maxV; maxV << maxVel_x, maxVel_y;
	VectorXd maxA; maxA << maxAcc_x, maxAcc_y;

	VectorXd temp; double x, y; list<VectorXd> wps;
	for(int i=0; i < msg.waypoints_x.layout.dim[0].size; ++i){
		x = msg.waypoints_x.data[i];
		y = msg.waypoints_y.data[i];
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
		std::ofstream file1("~/min_ws/src/minimization/output/xt_pos_vel.txt");
		std::ofstream file2("~/min_ws/src/minimization/output/yt_pos_vel.txt");
		std::ofstream file3("~/min_ws/src/minimization/output/time.txt");
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