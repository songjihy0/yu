clc;
clear;
close all;

% reading the RGB image
im = imread('images/crab_nebula.png');
imshow(im);
s = size(im);

% grey image
im_gray = rgb2gray(im);
s_gray = size(im_gray);
imshow(im_gray);

% binary image
im_bw = im2bw(im);
imshow(im_bw);

T = graythresh(im);
im_bw1 = im2bw(im, T);
imshow(im_bw1);

level = 0.7;
im_bw2 = im2bw(im, level);
imshow(im_bw2);

% subplot(1, 3, 1); imshow(im);
% subplot(1, 3, 2); imshow(im_gray);
% subplot(1, 3, 3); imshow(im_bw);

row8 = im(7,:);
row8;
plot(row8); title('Row8'); axis tight;






