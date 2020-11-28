package com.servlet;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.model.Page;
import com.model.User;
import com.service.UserService;

/**
 * 用户控制器
 */
public class UserServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    
    public UserServlet() {
        super();
    }

	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf8");
		String action = request.getParameter("action");
		UserService userScervice = new UserService();
		
		if(action != null && action.equals("delete")) {
			String userid = request.getParameter("userid");
			boolean result = userScervice.deleteUser(userid);
			if(result) {
				// 删除成功
				List<User> list = userScervice.findUserList();
				// 跳转首页
				// request.setAttribute("user", user);
				request.setAttribute("list", list);
				request.getRequestDispatcher("index.jsp").forward(request, response);	
			}
		}
		
		// 修改用户
		else if(action != null && action.equals("toUpdate")) {
			// 跳转至修改页面
			String userid = request.getParameter("userid");
			User user = userScervice.findUserById(userid);
			request.setAttribute("user", user);
			request.getRequestDispatcher("update.jsp").forward(request, response);
		}
		
		// 更新用户
		else if(action != null && action.equals("update")) {
			String userid = request.getParameter("userid");
			String name = request.getParameter("name");
			String password = request.getParameter("password");
			String age = request.getParameter("age")!=null?request.getParameter("age"):"0";
			String account = request.getParameter("account");
			
			User user = new User();
			user.setUserid(Integer.parseInt(userid));
			user.setAccount(account);
			user.setAge(Integer.parseInt(age));
			user.setName(name);
			user.setPassword(password);
			
			boolean result = userScervice.updateUser(user);
			if(result) {
				// 修改成功
				List<User> list = userScervice.findUserList();
				// 跳转首页
				// request.setAttribute("user", user);
				request.setAttribute("list", list);
				request.getRequestDispatcher("index.jsp").forward(request, response);	
			}
		}
		
		// 新增用户
		else if(action != null && action.equals("add")) {
			String name = request.getParameter("name");
			String password = request.getParameter("password");
			String age = request.getParameter("age")!=null?request.getParameter("age"):"0";
			String account = request.getParameter("account");
			
			User user = new User();
			user.setAccount(account);
			user.setAge(Integer.parseInt(age));
			user.setName(name);
			user.setPassword(password);
			
			boolean result = userScervice.addUser(user);
			if(result) {
				// 添加成功
				List<User> list = userScervice.findUserList();
				// 跳转首页
				// request.setAttribute("user", user);
				request.setAttribute("list", list);
				request.getRequestDispatcher("index.jsp").forward(request, response);	
			}
		}
		
		// 分页查询
		else if(action != null && action.equals("findPage")) {
			String page = request.getParameter("page")==null?"1":request.getParameter("page");   //当前查询第几页
			Page p = new Page();
			p.setPage(Integer.parseInt(page));
			
			List<User> list = userScervice.findUserListByPage(p);
			// 查询总页数
			int count = userScervice.findUserCount();
			int total = 0;  // 总页数
			if(count%p.getPageSize() > 0) {
				total = count/p.getPageSize() + 1;
			}
			else {
				total = count/p.getPageSize();
			}
			request.setAttribute("list", list);
			request.setAttribute("page", page);          // 记录当前页数
			request.setAttribute("total", total);        // 总页数
			request.getRequestDispatcher("index.jsp").forward(request, response);
			
		}
		
		else {
			String account = request.getParameter("account"); // 取得账号
			
			List<User> list = userScervice.findUserListByAccount(account);
			
			// request.setAttribute("user", user);
			request.setAttribute("list", list);
			request.setAttribute("account", account);
			request.getRequestDispatcher("index.jsp").forward(request, response);
		}
		
	}

}
