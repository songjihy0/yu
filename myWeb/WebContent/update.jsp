<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>修改用户</title>
</head>
<body>

<form action="UserServlet?action=update" method="post">
	<input type="hidden" name="userid" value="${user.userid}">
	账号：<input type="text" name="account" id="account" value="${user.account}">
	密码：<input type="text" name="password" id="password" value="${user.password}">
	姓名：<input type="text" name="name" id="name" value="${user.name}">
	年龄：<input type="text" name="age" id="age" value="${user.age}">
	<input type="submit" value="提交">
</form>

</body>
</html>

