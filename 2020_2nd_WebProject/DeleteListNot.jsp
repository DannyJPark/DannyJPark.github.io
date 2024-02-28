<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
   
<title>회원 리스트 초기화 권한 없음 </title>



 <script type="text/javascript">
       
 function gotoMain() {       	
	 location.href="Main.jsp";
 }	 
  
</script>

 
</head>
<body>


<br><br><br>
         <b><font size="6" color="gray">회원리스트 초기화 권한 없음 </font></b>   
    <br><br><br>

    
        
<%
     	out.println("<br>");
		out.println("<br>");
		out.println( "일반 회원은 회원리스트 파일을 초기화할 수 없습니다.\n" ); // 일반회원일 경우 회원 리스트 초기화 불가능
		
		out.println("<br>");
		out.println("<br>");
	
	
%>


<br><br>   
         
     <input type="button" value="메인화면으로" onclick="gotoMain()" />     
     
 </body>
</html>        
        