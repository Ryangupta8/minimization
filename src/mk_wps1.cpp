#include <iostream>
#include <cstdio>
#include <Eigen/Core>
#include <Trajectory.h>
#include <Path.h>
#include <fstream>


int main() {
	std::list<Eigen::VectorXd> waypoints;
	Eigen::VectorXd waypoint(2);
	waypoint << 3.0, 3.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, 1.0;
	waypoints.push_back(waypoint);
	waypoint << 3.0, -2.0;
	waypoints.push_back(waypoint);
	waypoint << 1.0, -2.0;
	waypoints.push_back(waypoint);
	waypoint << 1.0, 1.0;
	waypoints.push_back(waypoint);
	waypoint << 1.0, 3.0;
	waypoints.push_back(waypoint);
	waypoint << -2.0, 3.0;
	waypoints.push_back(waypoint);
	waypoint << -2.0, 1.0;
	waypoints.push_back(waypoint);
	waypoint << -2.0, -2.0;
	waypoints.push_back(waypoint);

	Eigen::VectorXd maxAcceleration(2);
	maxAcceleration << 1.0, 1.0;
	Eigen::VectorXd maxVelocity(2);
	maxVelocity << 0.45, 0.45;

	Trajectory trajectory(Path(waypoints, 0.1), maxVelocity, maxAcceleration);
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

	// std::string s;
	// std::cin >> s;
}