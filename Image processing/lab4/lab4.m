clc;
clear;
close all;

im1 = im2double(imread('images/chest.jpg'));
im2 = im2double(imread('images/baby.jpg'));
figure();
subplot(1, 2, 1); imshow(im1); 
subplot(1, 2, 2); imshow(im2);

im1ycbcr = rgb2ycbcr(im1);
im2ycbcr = rgb2ycbcr(im2);
Y1 = im1ycbcr(:,:,1);
Y2 = im2ycbcr(:,:,1);

Y1_N = imnoise(Y1,'gaussian');
Y2_N = imnoise(Y2,'gaussian');


s1 = size(Y1_N');
s2 = size(Y2_N'); 
dct_im1 = dct2(Y1_N);
dct_im2 = dct2(Y2_N);
original1 = dct_im1 .* dct_im1;
quadrant1 = dct_im1(400:end,344:end).*dct_im1(400:end,344:end); 
original2 = dct_im1 .* dct_im1;
quadrant2 = dct_im1(198:end,275:end).*dct_im1(198:end,275:end); 
s_o1 = size(original1');
s_q1 = size(quadrant1');
s_o2 = size(original2');
s_q2 = size(quadrant2');
xo1 = [1:s_o1(1)];
yo1 = [1:s_o1(2)];
xq1 = [1:s_q1(1)];
yq1 = [1:s_q1(2)];
xo2 = [1:s_o2(1)];
yo2 = [1:s_o2(2)];
xq2 = [1:s_q2(1)];
yq2 = [1:s_q2(2)];
[xo1,yo1] = meshgrid(xo1,yo1);
[xq1,yq1] = meshgrid(xq1,yq1);
[xo2,yo2] = meshgrid(xo2,yo2);
[xq2,yq2] = meshgrid(xq2,yq2); 
figure;surface(xq1,yq1,quadrant1);view(60,45);title('im1 high frequency area');
figure;surface(xo1,yo1,original1);view(60,45);title('im1 original');
figure;surface(xq2,yq2,quadrant2);view(60,45);title('im2 high frequency area');
figure;surface(xo2,yo2,original2);view(60,45);title('im2 original');
n_var1 = mean(mean(quadrant1));
n_var2 = mean(mean(quadrant2));

s_var1 = dct_im1 .* dct_im1 + 0.001;
wiener_filter1 = 1./(1 + (n_var1./s_var1));
dct_f1 = dct_im1.*wiener_filter1;
dct_f_im1 = idct2(dct_f1);
dct_f_im1 = 255.*imadjust(dct_f_im1,[],[0,1]); 
figure;imshowpair(Y1_N,uint8(dct_f_im1),'montage');title('Left:Noisy Image1 Right:DCT Wiener Filter');
s_var2 = dct_im2 .* dct_im2 + 0.001;
wiener_filter2 = 1./(1 + (n_var2./s_var2));
dct_f2 = dct_im2.*wiener_filter2;
dct_f_im2 = idct2(dct_f2);
dct_f_im2 = 255.*imadjust(dct_f_im2,[],[0,1]); 
figure;imshowpair(Y2_N,uint8(dct_f_im2),'montage');title('Left:Noisy Image2 Right:DCT Wiener Filter');

im1_f = wiener2(Y1_N,n_var1);
im1_f = 255.*imadjust(im1_f,[],[0,1]); 
figure;imshowpair(Y1_N,uint8(im1_f),'montage');title('Left:Noisy Image1 Right:Wiener Filter');
im2_f = wiener2(Y2_N,n_var2);
im2_f = 255.*imadjust(im2_f,[],[0,1]); figure;imshowpair(Y2_N,uint8(im2_f),'montage');title('Left:Noisy Image2 Right:Wiener Filter');

t = 1;
f = 1;
h1 = 0.01;
h2 = 100;
selfsim = 0;
de_im1 = simple_nlm(Y1_N,t,f,h1,h2,selfsim);
de_im1 = 255.*imadjust(de_im1,[],[0,1]); figure;imshowpair(Y1_N,uint8(de_im1),'montage');title('Left:Noisy Image1 Right:Nonlocal Mean Filter');

t = 1;
f = 1;
h1 = 0.0001;
h2 = 1;
selfsim = 0;
de_im2 = simple_nlm(Y2_N,t,f,h1,h2,selfsim);
de_im2 = 255.*imadjust(de_im2,[],[0,1]); figure;imshowpair(Y2_N,uint8(de_im2),'montage');title('Left:Noisy Image2 Right:Nonlocal Mean Filter');

im = imread('images/alisa.jpg');
im = im(1:256,51:306); 
p = 256;
s = size(im);
wavelet = zeros(s);
N = log2(s(1));
[C,S] = wavedec2(im,N,'haar');
for i = 1:N
	[H,V,D] = detcoef2('all',C,S,i); A = appcoef2(C,S,'haar',i);
	HH = wcodemat(H,255,'mat',1);
	VV = wcodemat(V,255,'mat',1);
	DD = wcodemat(D,255,'mat',1);
	AA = wcodemat(A,255,'mat',1); 
	wavelet(1:p/2,1:p/2) = AA; 
	wavelet(1:p/2,p/2+1:p) = HH;
	wavelet(p/2+1:p,1:p/2) = VV;
	wavelet(p/2+1:p,p/2+1:p) = DD;
	p = p/2;
end

subplot(1,2,1);imshow(im);title('one channel of image');
subplot(1,2,2);imshow(uint8(wavelet));title('2D Haar Wavelet transform');















