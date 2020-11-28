<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>新增用户</title>
</head>
<body>

<form action="UserServlet?action=add" method="post">
	账号：<input type="text" name="account" id="account" value="">
	密码：<input type="text" name="password" id="password" value="">
	姓名：<input type="text" name="name" id="name" value="">
	年龄：<input type="text" name="age" id="age" value="">
	<input type="submit" value="提交">
</form>

</body>
</html>

