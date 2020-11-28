<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>  
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt"%>  
<%@ taglib uri="http://java.sun.com/jsp/jstl/functions" prefix="fn"%>

<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>图书系统首页</title>

<script type="text/javascript">
/* javascript脚本语言----前端语言
 * 弱类型：JavaScript，强类型：Java
 */
 
// 删除用户
function deleteUser(userid){
	var result = confirm("确定要删除?"); // window，document 浏览器内置对象
	if(result){
		// 删除用户
		location.href="UserServlet?action=delete&userid="+userid;
	}
}

// 下一页
function showNext(){
	var page = document.getElementById("page").value;
	var total = document.getElementById("total").value;
	if(page == total){
		alert("已经是最后一页了！");
		return;
	}
	page++;
	location.href="UserServlet?action=findPage&page="+page;
}

// 上一页
function showPre(){
	var page = document.getElementById("page").value;
	if(page == 1){
		alert("当前已经是第一页了");
		return;
	}
	page--;
	location.href="UserServlet?action=findPage&page="+page;
}

</script>
</head>
<body>
欢迎${user.name}来到图书管理系统<br>
<form action="UserServlet" method="post">
	账号：<input type="text" name="account" id="account" value="${account}"><input type="submit" value="搜索">
</form>
	<a href="add.jsp">新增用户</a>
<table border="1">
	<tr style="font-weight:bold">
		<td>用户ID</td>
		<td>账号</td>
		<td>姓名</td>
		<td>地址</td>
		<td>邮箱</td>
		<td>操作</td>
	</tr>
	<c:forEach var="row" items="${list}"><!-- 从request中取用户列表进行循环显示 -->
		<tr>
		<td>${row.userid}</td>
		<td>${row.account}</td>
		<td>${row.name}</td>
		<td>${row.address}</td>
		<td>${row.email}</td>
		<td><a href="#" onclick="deleteUser('${row.userid}')">删除</a> 
		<a href="UserServlet?action=toUpdate&userid=${row.userid}">修改</a></td>
	</tr>
	</c:forEach>
</table>
<a href="#" onclick="showPre()">上一页</a> &nbsp;&nbsp;<a href="#" onclick="showNext()">下一页</a>
&nbsp;&nbsp; 共${total}页
	<input type="hidden" name="page" id="page" value="${page}"/>
	<input type="hidden" name="total" id="total" value="${total}"/>

</body>
</html>







