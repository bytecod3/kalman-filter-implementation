data = csvread('kalman-test.csv');
x_raw = data(:,1);
x_filtered = data(:,2);

% plot 
plot(x_raw);
hold on;
plot(x_filtered);

grid on;
ylabel("x acceleration");
legend("Raw X acceleration", "Filtered X acceleration");
title("Kalman Filter for X acceleration");