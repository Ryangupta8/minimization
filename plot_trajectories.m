close all
clear all
clc
%%% This is a plot of the trajectories. 
%%% 1. plot x vs y position
%%% 2. plot x(t) and y(t)
%%% 3. plot xdot(t) and ydot(t)
time = importdata('time.txt');
xt = importdata('xt_pos_vel.txt');
yt = importdata('yt_pos_vel.txt');


% Figure 1
figure; title('x(t) vs y(t)');
plot(xt(:,1), yt(:,1),'.');
xlabel('x(t)');
ylabel('y(t)');
print -djpeg90 -r0 x_vs_y.jpg


% Figure 2
figure; title('x(t) and y(t)');
plot(time(:),xt(:,1),time(:),yt(:,1));
legend('x(t)', 'y(t)');
xlabel('time');
print -djpeg90 -r0 position_vs_time.jpg


% Figure 3
figure; title('xdot(t) and ydot(t)');
plot(time(:),xt(:,2),time(:), yt(:,2));
legend('xdot(t)', 'ydot(t)');
xlabel('time');
print -djpeg90 -r0 velocity_vs_time.jpg