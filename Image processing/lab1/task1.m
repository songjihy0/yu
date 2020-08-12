clc;
clear;
close all;

im = imread('images/crab_nebula.png');
s = size(im);

% display the gray image
im_gray = rgb2gray(im);
[m, n] = size(im_gray);
imshow(im_gray);

% display the image with scale
subplot(1, 2, 1); imshow(im_gray); title('image');
subplot(1, 2, 2); imhist(im_gray); title('scale');

% adjust image's scale
J = im_gray;
for i = 1:m
	for j = 1:n
		if J(i, j) < 50
			J(i, j) = 0;
		elseif J(i, j) > 150
			J(i, j) = 255;
		end
	end
end
imshow(J); title('Processed image');







