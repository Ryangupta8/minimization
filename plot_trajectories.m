close all
clear all
clc
%%% This is a plot of the trajectories. 
%%% 1. plot x vs y position
%%% 2. plot x(t) and y(t)
%%% 3. plot xdot(t) and ydot(t)
%%% 4. plot xdotdot(t) and ydotdot(t)
time = importdata('/home/ryangupta/min_ws/src/minimization/output/time.txt');
xt = importdata('/home/ryangupta/min_ws/src/minimization/output/xt_pos_vel.txt');
yt = importdata('/home/ryangupta/min_ws/src/minimization/output/yt_pos_vel.txt');


% Figure 1
figure; 
plot(xt(:,1), yt(:,1),'.');
title('x(t) vs y(t)');
xlabel('x(t)');
ylabel('y(t)');
print -djpeg90 -r0 py_coverage_x_vs_y.jpg


% Figure 2
figure; 
plot(time(:),xt(:,1),time(:),yt(:,1));
title('x(t) and y(t)');
legend('x(t)', 'y(t)');
xlabel('time');
print -djpeg90 -r0 py_coverage_position_vs_time.jpg


% Figure 3
figure; 
plot(time(:),xt(:,2),time(:), yt(:,2));
title('xdot(t) and ydot(t)');
legend('xdot(t)', 'ydot(t)');
xlabel('time');
print -djpeg90 -r0 py_coverage_velocity_vs_time.jpg

% Figure 4
figure;
dydt = diff(yt(:,2))./diff(time(:));
dxdt = diff(xt(:,2))./diff(time(:));
plot(time(1:end-1),dxdt(:),time(1:end-1), dydt(:));
title('xdotdot(t) and ydotdot(t)');
legend('xdotdot(t)', 'ydotdot(t)');
xlabel('time');
print -djpeg90 -r0 py_coverage_accel_vs_time.jpg