%% Infinite impulse response filter export
%%% File info 
%
% *************************************************************************
%
%  @file     export_iir.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     17-Dec-2019 10:33:27
%  @brief    Simple IIR filter unity export
%
% *************************************************************************
%
close all; clc;
clear variables;

%% FILTER EXAMPLE 

% sample time & freq
ts = 0.001; % [s]
fs = 1/ts;  % [Hz]

% Version 1: custom transfer function model -------------------------------

    % -- S-OPERATOR -------------------------------------------------------
    s = tf('s');

    % -- MODEL PARAMS -----------------------------------------------------
    f = 10.0;   % [Hz]
    w = 2*pi*f; % [rad/s]
    e = 0.7;    % [-]

    % -- CONTINUOUS TRANSFER FUNCTION -------------------------------------
    G = 1 / ((1 + 2*e*s/w + s^2 / w^2));

    % -- DISCRETIZATION ---------------------------------------------------
    H = c2d(G,ts, 'zoh');

    % -- DISCRETE FILTER --------------------------------------------------
    b = H.num{1};
    a = H.den{1};

% Version 2: low-pass Chebyshev type I filter -----------------------------

    % -- FILTER PARAMS ----------------------------------------------------
    N = 3;          % [-]
    R = 1;          % [-]
    Wp = 17.5 / fs; % [-]

    % -- DISCRETE FILTER --------------------------------------------------
    [b,a] = cheby1(N,R,Wp,'low');

%% EXPORT FILTER TO .C/.H FILES
biquad_coeffs = generate_biquad_df1('ADC_LPF', b, a);

%% MOVE .C/.H AND .CSV FILES TO Components CATALOG
srcDest = '../Components/Src';
cFiles = dir('*.c');
csvFiles = dir('*.csv');
for i = 1:length(cFiles)
    movefile(cFiles(i).name, fullfile(srcDest, cFiles(i).name));
end
for i = 1:length(csvFiles)
    movefile(csvFiles(i).name, fullfile(srcDest, csvFiles(i).name));
end

incDest = '../Components/Inc';
hFiles = dir('*.h');
for i = 1:length(hFiles)
    movefile(hFiles(i).name, fullfile(incDest, hFiles(i).name));
end