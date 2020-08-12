clc;
clear;
close all;

im = imread('images/crab_nebula.png');
s = size(im);

% display the gray image
im_gray = rgb2gray(im);
[m, n] = size(im_gray);
imshow(im_gray);

% flip the image
J = im_gray;
for i = 1:m
	for j = 1:n
		J(i, j) = im_gray(m + 1 - i, n + 1 -j);
    end
end

subplot(1, 2, 1); imshow(im_gray); title('Orignal');
subplot(1, 2, 2); imshow(J); title('Flipped');




