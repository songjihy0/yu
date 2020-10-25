function MyEdges(y)
	edge_s = edge(y,'sobel');
	edge_r = edge(y,'roberts');
	edge_p = edge(y,'prewitt');
	edge_c = edge(y,'canny');
	figure();
	subplot(2,2,1);imshow(edge_s);title('Sodel');
	subplot(2,2,2);imshow(edge_r);title('Roberts');
	subplot(2,2,3);imshow(edge_p);title('Prewitt');
	subplot(2,2,4);imshow(edge_c);title('Canny');
end