clc;
clear;
close all;

im1 = imread('images/image1.png');
im2 = imread('images/image2.png');
im3 = imread('images/image3.png');
im4 = imread('images/image4.png');
subplot(2,2,1);imshow(im1);title('image1'); 
subplot(2,2,2);imshow(im2);title('image2');
subplot(2,2,3);imshow(im3);title('image3');
subplot(2,2,4);imshow(im4);title('image4');

s1 = size(im1);
s2 = size(im2);
s3 = size(im3);
s4 = size(im4);

im1_lab = rgb2lab(im1);
im1_xyz = rgb2xyz(im1);
im1_ycbcr = rgb2ycbcr(im1);
subplot(2,4,1);imshow(im1);title('image1');
subplot(2,4,2);imshow(im1_lab);title('im1 lab');
subplot(2,4,3);imshow(im1_xyz);title('im1 xyz');
subplot(2,4,4);imshow(im1_ycbcr);title('im1 ycbcr');
im1_lab_r = lab2rgb(im1_lab);
im1_xyz_r = xyz2rgb(im1_xyz);
im1_ycbcr_r = ycbcr2rgb(im1_ycbcr);
subplot(2,4,6);imshow(im1_lab_r);title('im1 lab');
subplot(2,4,7);imshow(im1_xyz_r);title('im1 xyz');
subplot(2,4,8);imshow(im1_ycbcr_r);title('im1 ycbcr');

im1_r = im1(:,:,1);
im1_g = im1(:,:,2);
im1_b = im1(:,:,3);
smoothingR = filter2(fspecial('average',7)/255, im1_r);
smoothingG = filter2(fspecial('average',7)/255, im1_g);
smoothingB = filter2(fspecial('average',7)/255, im1_b);
smoothingRGB(:,:,1) = smoothingR;
smoothingRGB(:,:,2) = smoothingG;
smoothingRGB(:,:,3) = smoothingB;
sharpeningRGB = im1.*2 - uint8(smoothingRGB);
subplot(1,3,1);imshow(im1);title('original');
subplot(1,3,2);imshow(smoothingRGB);title('smoothing');
subplot(1,3,3);imshow(sharpeningRGB);title('sharpening');

im4_gauss = imnoise(im4,'gaussian');
im4_spepper = imnoise(im4,'salt & pepper');


im4_favg_gauss = filter2(fspecial('average', 5)/255, im4_gauss);
im4_fmed_spepper = medfilt2(im4_spepper);
subplot(2,2,1);imshow(im4_gauss);title('gaussian noise');
subplot(2,2,2);imshow(im4_spepper);title('salt & pepper noise');
subplot(2,2,3);imshow(im4_favg_gauss);title('gaussian noise - average filter');
subplot(2,2,4);imshow(im4_fmed_spepper);title('salt & pepper noise - median filter');

colormap(gray);
image = 100*ones(100);
image(50:100,:) = 50;
image(:,50:100) = 2*image(:,50:100);
image_gauss = imnoise(image,'gaussian');
image_gauss = im2double(image_gauss);
denoise1 = simple_nlm(image_gauss,t,f,h1,h2,selfsim);
image_average = filter2(fspecial('average', 5)/255, image_gauss);
subplot(1,3,1);imagesc(image_gauss);title('gauss noise');
subplot(1,3,2);imagesc(denoise1);title('simple nlm');
subplot(1,3,3);imagesc(image_average);title('simple nlm');












