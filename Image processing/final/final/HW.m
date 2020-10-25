clc;
clear;
close all;

% 1
% 胸透
im1 = im2double(imread('images/chest.jpg'));
% 小孩
im2 = im2double(imread('images/baby.jpg'));
% 上海
im3 = im2double(imread('images/shanghai.jpeg'));
% 青岛
im4 = im2double(imread('images/qingdao.jpeg'));
figure();
subplot(2,2,1); imshow(im1);
subplot(2,2,2); imshow(im2);
subplot(2,2,3); imshow(im3);
subplot(2,2,4); imshow(im4);

% 2
im1_ycbcr = rgb2ycbcr(im1);
im2_ycbcr = rgb2ycbcr(im2);
im3_ycbcr = rgb2ycbcr(im3);
im4_ycbcr = rgb2ycbcr(im4);

y1 = im1_ycbcr(:,:,1);
y2 = im2_ycbcr(:,:,1);
y3 = im3_ycbcr(:,:,1);
y4 = im4_ycbcr(:,:,1);

% 3
y1_n = imnoise(y1,'gaussian');
y2_n = imnoise(y2,'gaussian');
y3_n = imnoise(y3,'gaussian');
y4_n = imnoise(y4,'gaussian');
figure();
subplot(2,2,1); imshow(y1_n);
subplot(2,2,2); imshow(y2_n);
subplot(2,2,3); imshow(y3_n);
subplot(2,2,4); imshow(y4_n);

% 4
[dct_im1,n1,xo1,yo1,xq1,yq1,original1,quadrant1] = ddct(y1_n);
[dct_im2,n2,xo2,yo2,xq2,yq2,original2,quadrant2] = ddct(y2_n);
[dct_im3,n3,xo3,yo3,xq3,yq3,original3,quadrant3] = ddct(y3_n);
[dct_im4,n4,xo4,yo4,xq4,yq4,original4,quadrant4] = ddct(y4_n);

% figure();surface(xq1,yq1,quadrant1);view(60,45);title('im1 high frequency area');
% figure();surface(xo1,yo1,original1);view(60,45);title('im1 original');
% figure();surface(xq2,yq2,quadrant2);view(60,45);title('im2 high frequency area');
% figure();surface(xo2,yo2,original2);view(60,45);title('im2 original');
% figure();surface(xq3,yq3,quadrant3);view(60,45);title('im3 high frequency area');
% figure();surface(xo3,yo3,original3);view(60,45);title('im3 original');
% figure();surface(xq4,yq4,quadrant4);view(60,45);title('im4 high frequency area');
% figure();surface(xo4,yo4,original4);view(60,45);title('im4 original');

% 5
% wiener(y1_n,dct_im1,n1);
% wiener(y2_n,dct_im2,n2);
% wiener(y3_n,dct_im3,n3);
% wiener(y4_n,dct_im4,n4);

% 6
% MyEdges(y1);
% MyEdges(y2);
% MyEdges(y3);
% MyEdges(y4);










