package com.dao;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.model.Page;
import com.model.User;

@SuppressWarnings("unused")

public class UserDao extends BaseDao{
	
	/**
	 * 用户登录
	 * @param account 账号
	 * @param password 密码
	 * @return 用户对象
	 */
	
	public User login(String account, String password) {
		
		String sql = "select * from bookdb where account='"+ account +"' and password='"+ password +"'";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			this.rs = ps.executeQuery();
			
			while(rs.next()) {
				String name = rs.getString("name");    // 数据库列名
				int age = rs.getInt("age");
				String email = rs.getString("email");
				String address = rs.getString("address");
				int userid = rs.getInt("userid");
				
				User user = new User();
				user.setAddress(address);
				user.setUserid(userid);
				user.setAge(age);
				user.setName(name);
				user.setEmail(email);
				user.setPassword(password);
				user.setAccount(account);
				
				return user;
				
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return null;
		
	}
	
	/**
	 * 查询用户列表
	 * @return
	 */
	public List<User> findUserList() {
		String sql = "select * from bookdb limit 0,5";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			this.rs = ps.executeQuery();
			
			List<User> list = new ArrayList<User>();
			
			while(rs.next()) {
				String name = rs.getString("name");    // 数据库列名
				int age = rs.getInt("age");
				String email = rs.getString("email");
				String address = rs.getString("address");
				int userid = rs.getInt("userid");
				String account = rs.getString("account");
				
				User user = new User();
				user.setAddress(address);
				user.setUserid(userid);
				user.setAge(age);
				user.setName(name);
				user.setEmail(email);
				user.setAccount(account);
				
				list.add(user);
			}
			return list;
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return null;
		
	}

	public List<User> findUserListByAccount(String aaccount) {
		String sql = "select * from bookdb where account like '%" + aaccount + "%'";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			this.rs = ps.executeQuery();
			
			List<User> list = new ArrayList<User>();
			
			while(rs.next()) {
				String name = rs.getString("name");    // 数据库列名
				int age = rs.getInt("age");
				String email = rs.getString("email");
				String address = rs.getString("address");
				int userid = rs.getInt("userid");
				String account = rs.getString("account");
				
				User user = new User();
				user.setAddress(address);
				user.setUserid(userid);
				user.setAge(age);
				user.setName(name);
				user.setEmail(email);
				user.setAccount(account);
				
				list.add(user);
			}
			return list;
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return null;
		
	}

	public boolean deleteUser(String userid) {
		String sql = "delete from bookdb where userid=" + userid;
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			// 执行删除、修改、新增命令
			int result = ps.executeUpdate();  // 成功或失败
			// result:数据库受影响行数
			if(result == 1) {
				// 成功
				return true;
			}
			else {
				// 失败
				return false;
			}
					
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return true;
	}

	public User findUserById(String userid) {
		String sql = "select * from bookdb where userid=" + userid;
		// 执行sql查询
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			this.rs = ps.executeQuery();
			
			User user = new User();
			
			while(rs.next()) {
				String name = rs.getString("name");    // 数据库列名
				int age = rs.getInt("age");
				String email = rs.getString("email");
				String address = rs.getString("address");
				String account = rs.getString("account");
				String password = rs.getString("password");
				
				user.setAddress(address);
				user.setUserid(Integer.parseInt(userid));
				user.setAge(age);
				user.setName(name);
				user.setEmail(email);
				user.setAccount(account);
				user.setPassword(password);
				
			}
			return user;
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

	public boolean updateUser(User user) {
		String sql = "update bookdb set account=?,password=?,`name`=?,age=? where userid=?";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			
			ps.setString(1, user.getAccount());
			ps.setString(2, user.getPassword());
			ps.setString(3, user.getName());
			ps.setInt(4, user.getAge());
			ps.setInt(5, user.getUserid());
			
			// 执行删除、修改、新增命令
			int result = ps.executeUpdate();  // 成功或失败
			// result:数据库受影响行数
			if(result == 1) {
				// 成功
				return true;
			}
			else {
				// 失败
				return false;
			}
					
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return true;
	}

	public boolean addUser(User user) {
		String sql = "insert into bookdb (account,password,name,age) values (?,?,?,?)";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			
			ps.setString(1, user.getAccount());
			ps.setString(2, user.getPassword());
			ps.setString(3, user.getName());
			ps.setInt(4, user.getAge());
			
			// 执行删除、修改、新增命令
			int result = ps.executeUpdate();  // 成功或失败
			// result:数据库受影响行数
			if(result > 0) {
				// 成功
				return true;
			}
			else {
				// 失败
				return false;
			}
					
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return true;
	}

	public List<User> findUserListByPage(Page p) {
		String sql = "select * from bookdb limit ?,?";
		// 执行sql查询
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			
			ps.setInt(1, (p.getPage() -	1)*p.getPageSize());
			ps.setInt(2, p.getPageSize());
			
			this.rs = ps.executeQuery();
			
			List<User> list = new ArrayList<User>();
			
			while(rs.next()) {
				String name = rs.getString("name");    // 数据库列名
				int age = rs.getInt("age");
				String email = rs.getString("email");
				String address = rs.getString("address");
				int userid = rs.getInt("userid");
				String account = rs.getString("account");
				
				User user = new User();
				user.setAddress(address);
				user.setUserid(userid);
				user.setAge(age);
				user.setName(name);
				user.setEmail(email);
				user.setAccount(account);
				
				list.add(user);
			}
			return list;
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return null;
	}

	public int findUserCount() {

		String sql = "select count(*) as count from bookdb";
		// 执行sql查询
		int count = 0;
		
		try {
			this.conn = this.getConn();
			this.ps = conn.prepareStatement(sql);
			this.rs = ps.executeQuery();
			
			while(rs.next()) {
				count = rs.getInt("count");    // 数据库列名
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return count;
	}

}
