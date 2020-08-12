clc;
clear;
close all;

% histogram equalization
im = imread('images/crab_nebula.png'); 
J = histeq(im); 
subplot(1,2,1); imshow(im); title('Original');
subplot(1,2,2); imshow(J); title('Processed');

J1 = histeq(im); 
subplot(1,2,1); imhist(im); title('Original');
subplot(1,2,2); imhist(J1); title('Processed');