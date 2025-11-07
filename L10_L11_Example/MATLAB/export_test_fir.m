%% Finite impulse response filter export
%%% File info 
%
% ************************************************************************
%
%  @file     unit_test_fir.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     12-Dec-2020 19:59:05
%  @brief    Simple FIR digital low-pass filter design and export
%
% ************************************************************************
%
close all; clc;
clear variables;

%% FILTER EXAMPLE 

% sample time & freq
ts = 0.001; % [s]
fs = 1/ts;  % [Hz]

% Filter desired parameters
% cut-off frequency
f1 = 10;  % [Hz]
% frequency at the end transition band
f2 = 50; % [Hz]
% transition band length
df = f2 - f1;
% stopband attenuation of A [dB] at f2 [Hz]
A = 50; % [dB]
               
% Filter order estimation
% with 'fred harris rule of thumb'
N = round( (fs/df)*A / 22 );

% Filter object with fir1 funcion
% normalised frequency
w = f1 / (fs/2); % [-]
% low pass filter
b = fir1(N, w, 'low');

%% EXPORT FILTER TO .C/.H FILES
generate_fir('ADC_LPF', b, 1);

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
