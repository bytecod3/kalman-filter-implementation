% finds discrete kalman filter gain matrix and closed loop transfer
% functions 
%{
Credit: Tom Moir

%}

%sampling frequency
fs = 100.0;
Ts = 1/fs;

%define the system 
N =200;
F = [1, -Ts; 0,1]; % system matrix - state
D = [Ts, -0.5*Ts^2; 0, Ts];
H = eye(2); % observation matrix
Q = eye(2); % process noise covariance
R = 1e-2*eye(2);  % measurement noise covariance

% initialize the  error covariance matrix
P = [10,0; 0, 10]; % covariance for initial stae error
D2 = 0* eye(2); % this matrix is zeor and is needed by matlab

% find kalman gain matrix and steady-state P matrix
sysd = ss(F,D,H,0,1);
[kest, kd,p2] = kalman(sysd,Q,R,0);

% display
disp(kd); % KALMAN GAIN MATRIX

% find closed-loop kalman filter transfer function
Fc = F-kd*H;
[num, den]=ss2tf(Fc, kd,H,D2,1);

% transfer functions of steady state kalman filter
sys1 = tf(num(1,:), den, 1);
sys2 = tf(num(2,:),den,1);
Fc = F - kd*H;

