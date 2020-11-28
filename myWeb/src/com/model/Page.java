package com.model;

public class Page {
	
	private int page = 1;       // 第几页
	private int pageSize = 5;   // 每页多少条
	
	public int getPage() {
		return page;
	}
	public void setPage(int page) {
		this.page = page;
	}
	public int getPageSize() {
		return pageSize;
	}
	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}
	
}
