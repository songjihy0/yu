function y=ScaleByMax(img)
R = img(:,:,1);
G = img(:,:,2);
B = img(:,:,3);
Rmax=max(max(R));
Gmax=max(max(G));
Bmax=max(max(B)); 
Cmax=min([Rmax,Gmax,Bmax]);
Ng=sum(G(:)>=Cmax);
Nb=sum(B(:)>=Cmax);
Nmax=max([Nr,Ng,Nb]);
for pix=Rmax:-1:0 
	if nr>=Nmax
		Rth=pix;
		break;
    end
end
for pix=Gmax:-1:0
	Lr=G>=pix;
	nr=sum(Lr(:));
	if nr>=Nmax
		Gth=pix;
    end
end
for pix=Bmax:-1:0
	Lr=B>=pix; 
	nr=sum(Lr(:)); 
	if nr>=Nmax
		Bth=pix;
		break;
    end
end
result(:,:,1) = Cmax/Rth*R;
result(:,:,2) = Cmax/Gth*G;
result(:,:,3) = Cmax/Bth*B;
y = result;
