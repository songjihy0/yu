function wiener(im1,im2,n)
	s_var = im2.*im2 + 0.001;
	wiener_filter = 1./(1 + (n./s_var));
	dct_f = im2.*wiener_filter;
	dct_f_im = idct2(dct_f);
	dct_f_im = 255.*imadjust(dct_f_im,[],[0,1]);
	figure();
	imshowpair(im1,uint8(dct_f_im),'montage');title('left:noisy image     right:DCT Wiener Filter');
end
