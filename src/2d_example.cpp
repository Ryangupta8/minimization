#include <iostream>
#include <cstdio>
#include <Eigen/Core>
#include <Trajectory.h>
#include <Path.h>
#include <fstream>


/*
2D Example: Want the robot to follow the path:
----------------------
3 Finish wp8     wp7 | 
2       wp5      wp6 |
1       wp4      wp3 | 
0 Start  wp1     wp2 |
---------0--1--2--3---
*/

int main() {
	std::list<Eigen::VectorXd> waypoints;
	Eigen::VectorXd waypoint(2);
	waypoint << 0.0, 0.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, 0.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, 1.0;
	waypoints.push_back(waypoint);
	waypoint << 0.0, 1.0;
	waypoints.push_back(waypoint);
	waypoint << 0.0, 2.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, 2.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, 3.0;
	waypoints.push_back(waypoint);
	waypoint << 0.0, 3.0;
	waypoints.push_back(waypoint);

	Eigen::VectorXd maxAcceleration(2);
	maxAcceleration << 1.0, 1.0;
	Eigen::VectorXd maxVelocity(2);
	maxVelocity << 0.22, 0.22;

	Trajectory trajectory(Path(waypoints, 0.1), maxVelocity, maxAcceleration);
	// Prints out txts for the phase plane plot
	trajectory.outputPhasePlaneTrajectory();


	if(trajectory.isValid()) {
		// Duration of the trajectory
		double duration = trajectory.getDuration();
		std::cout << "Trajectory duration: " << duration << " s" << std::endl << std::endl;
		std::cout << "Time      Position                  Velocity" << std::endl;
		// Save our variables in text files
		std::ofstream file1("xt_pos_vel.txt");
		std::ofstream file2("yt_pos_vel.txt");
		std::ofstream file3("time.txt");
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

	// std::string s;
	// std::cin >> s;
}
