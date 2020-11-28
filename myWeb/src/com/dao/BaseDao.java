package com.dao;

import java.sql.*;

/**
 * 
 * 数据库基类（公共类，用于操作数据库）
 * 
 * @author yzp
 *
 */

public class BaseDao {
	
	private String driver = "com.mysql.cj.jdbc.Driver";
	private String url = "jdbc:mysql://localhost:3306/student";
	private String account = "root";
	private String password = "2894123953";
	
	public Connection conn;        // 存储数据库连接信息
	public PreparedStatement ps;   // 执行sql命令
	public ResultSet rs;           // 存储执行结果
	
	// 获得数据库连接
	public Connection getConn() {
		try {
			Class.forName(driver);
			Connection conn = DriverManager.getConnection(url, account, password);
			return conn;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	
	}
	

}
