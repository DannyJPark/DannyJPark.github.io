<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
   
<title>리스트 삭제</title>



 <script type="text/javascript">
       
 function gotoMain() {       	
	 location.href="Main.jsp";
 }	 
  
</script>

 
</head>
<body>


<br><br><br>
         <b><font size="6" color="gray">회원 리스트 삭제</font></b>   
    <br><br><br>

    
        
 <% 
   
	//String id =    request.getParameter("id") ;
    String IDs =  (String)session.getAttribute("IDs") ; //세션에서 id 받아오기
    String masterID="master";
    String masterPW="master";
    
	
	

	try{ // list.txt 파일 초기화
		
		String fileName = "list.txt";
		String filePath = application.getRealPath(  fileName);
		FileOutputStream fos = new FileOutputStream(filePath);
		DataOutputStream dos = new DataOutputStream( fos );
		String str1="|master|master|masterName|19990101|010-0000-0000|aaa@aaa.com\n"; // 관리자 정보만 파일에 저장
	
		dos.writeUTF(str1);
		fos.close();
	
		out.println("<br>");
		out.println("<br>");
		out.println( "회원 리스트 파일을 초기화하였습니다.\n" );
		out.println("<br>");
		out.println("<br>");
		out.println("<br>");
	
	} catch(IOException ee) { // 초기화에 실패할 경우
		out.println( "err2!! : " + ee.getMessage()+"\n" );
		
	}
	  
%>


<br><br>   
         
     <input type="button" value="메인화면으로" onclick="gotoMain()" />     
     
 </body>
</html>        
        