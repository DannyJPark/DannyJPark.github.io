<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
   
<title>회원리스트 초기화</title>



 <script type="text/javascript">
       
 function gotoMain() {       	
	 location.href="Main.jsp";
 } 
 function confirmDeleteList() { // 초기화 여부 묻기
	 var ret = confirm("정말로 회원리스트를 초기화 할까요?");
	    if(ret == true) {
	    
	    	location.href="DeleteList.jsp";  // 파일 초기화 화면으로 가기
	    }
	    else {    
	    }
		     
			    
 }    
 
</script>

 
</head>
<body>


<br><br><br>
         <b><font size="6" color="gray">회원 리스트 초기화 확인</font></b>   
    <br><br><br>
   
        
 <% 
   
	//String id =    request.getParameter("id") ;
    String IDs =  (String)session.getAttribute("IDs") ;
    String masterID="master";
    String masterPW="master";
    
	out.println("<br>");
	out.println("<br>");
	
    String msg;
	//Boolean condition = false;
	
	if (IDs.equals( masterID)) { // 관리자일 경우 - 초기화 가능
		//msg = "DeleteList.jsp";
	 }
	else {
		msg = "DeleteListNot.jsp";	// 일반회원인 경우 - 초기화 못함
	    response.sendRedirect(msg); // 지정화면으로 보내기(초기화 불가능)
	}
	
	
	  
%>
    <input type="button" value="회원리스트 초기화 " onclick="confirmDeleteList()" />   
     <input type="button" value="메인화면으로" onclick="gotoMain()" />     
     
 <% 
 %>    
     
 </body>
</html>        
        