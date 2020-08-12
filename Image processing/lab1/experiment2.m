clc;

% change the value of gamma to see how image changes

im = imread('images/crab_nebula.png'); 
im_grey = rgb2gray(im);
J = imadjust(im_grey, [], []);
imshow(J);

J1 = imadjust(im_grey, [], [], 0.3);
imshow(J1);



