package com.service;

import java.util.*;

import com.dao.UserDao;
import com.model.Page;
import com.model.User;

/**
 * 
 * 业务层
 * 用户业务类
 * 
 * @author yzp
 *
 */

public class UserService {
	
	UserDao userdao = new UserDao();
	
	/**
	 * 用户登录
	 * @param account 账号
	 * @param password 密码
	 * @return 用户对象
	 */
	
	public User login(String account, String password) {
		
		return userdao.login(account, password);
		
	}
	
	/**
	 * 查询用户列表
	 * @return
	 */
	public List<User> findUserList() {
		return userdao.findUserList();
	}
	/**
	 * 搜索用户
	 * @return
	 */
	public List<User> findUserListByAccount(String account) {
		return userdao.findUserListByAccount(account);
	}
	/**
	 * 删除用户 true:成功，false:失败
	 * @return
	 */
	public boolean deleteUser(String userid) {
		return userdao.deleteUser(userid);
	}
	/**
	 * 根据id查询用户信息
	 * @param userid
	 * @return
	 */
	public User findUserById(String userid) {
		return userdao.findUserById(userid);
	}
	/**
	 * 修改用户
	 * @param user
	 * @return
	 */
	public boolean updateUser(User user) {
		return userdao.updateUser(user);
	}
	
	/**
	 * 新增用户
	 * @param user
	 * @return
	 */
	public boolean addUser(User user) {
		return userdao.addUser(user);
	}
	/**
	 * 分页查询
	 * @param p
	 * @return
	 */
	public List<User> findUserListByPage(Page p) {
		return userdao.findUserListByPage(p);
	}
	/**
	 * 查询用户数据数
	 * @return
	 */
	public int findUserCount() {
		return userdao.findUserCount();
	}

}
