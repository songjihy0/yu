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
 * 用户登录
 */
public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LoginServlet() {
        super();
    }

	/**
	 * 接受get请求
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request, response);
	}

	/**
	 * 接受post请求
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String account = request.getParameter("account");
		String password = request.getParameter("password");
		
		// 调用业务层
		UserService userScervice = new UserService();
		User user = userScervice.login(account, password);
		if(user != null) {
			System.out.println("登陆成功");
			// 查询用户
			List<User> list = userScervice.findUserList();
			Page page = new Page();
			// 查询总页数
			int count = userScervice.findUserCount();
			int total = 0;  // 总页数
			if(count%page.getPageSize() > 0) {
				total = count/page.getPageSize() + 1;
			}
			else {
				total = count/page.getPageSize();
			}
			// 跳转首页
			// request中的数据针对的是某一次的请求，请求结束数据失效
			// request.setAttribute("user", user);
			// session对象针对的是同一个浏览器的不同窗口直接共享的数据
			request.getSession().setAttribute("user", user);
			request.setAttribute("list", list);
			request.setAttribute("page", page.getPage());  // 获得页数
			request.setAttribute("total", total);        // 总页数
			request.getRequestDispatcher("index.jsp").forward(request, response);			
		}
		else {
			System.out.println("登录失败");
			request.getRequestDispatcher("login.html").forward(request, response);
		}

		
	}

}
