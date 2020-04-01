
%%% Code for Plotting from Example.cpp
% trajectory = importdata('Example_phasePlaneTrajectory.txt');
% maxVelocity = importdata('Example_phasePlaneMaxVelocity.txt');
% plot(maxVelocity(:,1), maxVelocity(:,2), maxVelocity(:,1), maxVelocity(:,3), trajectory(:,1), trajectory(:,2), '.')
% legend('maxVelocity(:,1)','maxVelocity(:,2)','maxVelocity(:,3)','trajectory(:,1)','trajectory(:,2)')


%%% Code for plotting from 2d_example.cpp
trajectory = importdata('trajectory.txt');
maxVelocity = importdata('maxVelocity.txt');
plot(maxVelocity(:,1), maxVelocity(:,2), trajectory(:,1), trajectory(:,2), '.')
legend('time optimal trajectory','acceleration limit curve')
xlabel('s') 
ylabel('sdot') 