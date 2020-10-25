function [im_dct,n,xo,yo,xq,yq,original,quadrant] = ddct(im)
	s = size(im');
	im_dct = dct2(im);
	original = im_dct.*im_dct;
	quadrant = im_dct(400:end,344:end).*im_dct(400:end,344:end);
	s_o = size(original');
	s_q = size(quadrant');
	xo = [1:s_o(1)];
	yo = [1:s_o(2)];
	xq = [1:s_q(1)];
	yq = [1:s_q(2)];
	[xo,yo] = meshgrid(xo,yo);
	[xq,yq] = meshgrid(xq,yq);
	n = mean(mean(quadrant));
end