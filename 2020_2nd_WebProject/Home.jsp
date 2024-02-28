<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>

<html>
<head>

<title>홈화면</title>
  
 
<script type="text/javascript">
   
    
    function gotoNewForm() { // 회원가입 화면으로 가기
        	
            location.href="NewForm.jsp"; //회원가입 페이지
        } 
    function gotoLogin() { // 로그인 화면으로 가기
    	
        location.href="LoginForm.jsp"; // 로그인 페이지
    } 
    
   </script>
 
</head>
<body>
      <div id="wrap">
        <br><br><br>
        <b><font size="6" color="gray">박형준의 홈페이지</font></b>
        <br><br><br>
<%         
		int i = 0;
		try { // list.txt (회원리스트) 불러오기
			
			String fileName = "list.txt";
			String filePath = application.getRealPath( fileName);
			FileInputStream fis = new FileInputStream(filePath);
			DataInputStream dis = new DataInputStream( fis );
			
			String str ="";
			
			while((str = dis.readLine()) != null) { //listt.txt에서 한줄씩 읽기
		         i++;
		    }
			fis.close();
			
	} catch(IOException e) { // 읽기 에러 처리
		out.println( "err1!! : " + e.getMessage() +"\n");
		out.println("<br>");
		try{ // list.txt 파일이 없으면
			
			String fileName = "list.txt"; //새로 만들기
			String filePath = application.getRealPath(  fileName);
			FileOutputStream fos = new FileOutputStream(filePath);
			DataOutputStream dos = new DataOutputStream( fos );
			String str1="|master|master|masterName|19990101|010-0000-0000|aaa@aaa.com\n"; // 관리자 저장
		
			dos.writeUTF(str1);// 파일에 저장
			fos.close();
		
			out.println("<br>");
			out.println( "list.txt 화일을 새로 만들었습니다.\n" );
			out.println("<br>");
		
		} catch(IOException ee) {
			out.println( "err2!! : " + ee.getMessage()+"\n" );
			
		}
	}
        
 %>
       <input type="button" value="로그인하기" onclick="gotoLogin()" >  
                  
       <input type="button" value="회원가입하기" onclick="gotoNewForm()" >  
      
    
</body>
</html>


