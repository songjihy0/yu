I=imread('b_image.jpg'); 
U=imread('r_image.jpg');
y=GrayWorld(I);
y=uint8(y);
x=ScaleByMax(I);
x=uint8(x);
y1=GrayWorld(U);
y1=uint8(y1);
x1=ScaleByMax(U);
x1=uint8(x1);
subplot(2,3,1);imshow(I);title('original');
subplot(2,3,2);imshow(y);title('gray world');
subplot(2,3,3);imshow(x);title('scale by max');
subplot(2,3,4);imshow(U);title('original');
subplot(2,3,5);imshow(y1);title('gray world');
subplot(2,3,6);imshow(x1);title('scale by max');

