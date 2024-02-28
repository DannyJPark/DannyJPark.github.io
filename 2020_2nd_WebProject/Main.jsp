<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>


<html>
<head>
   
    <title>메인화면</title>

 <script type="text/javascript">
    
 function confirmLogout() { // 로그아웃 여부 묻기
	    var ret = confirm("로그아웃 할까요?");
	    if(ret == true) {
	    	//session.invalidate();
	    	location.href="LoginForm.jsp"   ;      
	    }
	    else {    
	    }
 }
       
 function gotoLoginForm() {       //로그인 화면으로 가기	
   location.href="LoginForm.jsp";
 }    
 
 function gotoMemberList() { // 멤버 리스트 보기
	// a href ="MemberList.jsp?id=id";
	 location.href="MemberList.jsp";
	// response.sendRedirect(msg);
	    
	 } 
 
 function gotoDeleteList() { // 멤버 리스트 지우기
	    	location.href="DeleteListConfirm.jsp"   ;      
	   
 } 
 function gotoHome() { //홈화면으로 가기
	 
 	
     location.href="Home.jsp";
 } 
 
 function gotoLogHistory() {    // 로그 기록 화면으로 가기 	
	   location.href="LogHistory.jsp";
	 }    
 
</script>

 
</head>
<body>
   
<br><br><br>
         <b><font size="6" color="gray">메인 화면</font></b>   
    <br><br><br>
    
        
 <% 
   
	//String id =    request.getParameter("id") ;
    String IDs =  (String)session.getAttribute("IDs") ;
    
    String masterID="master";
    String masterPW="master";
    
	out.println("<br>");
	out.println("<br>");
	// 관리자일 경우
	if (IDs.equals( masterID)) {
		out.println("안녕하세요^^   " + IDs + " 관리자님 !!<br>");
	}
	// 일반 회원일 경우
	else{
		out.println("안녕하세요^^   " + IDs + " 회원님 !!<br>");
	}
	out.println("<br>");
	out.println("<br>");
	

	int makenewfile = 0;
	int msg = 0;
	int max = 100;
	int item = 10;
      
	String aaa[][] = new String[max][item];   
 
    String lists[] = new String[max];
 	
		int i = 0;
		try { //list 파일 읽어들임
			
			String fileName = "list.txt";
			String filePath = application.getRealPath( fileName);
			FileInputStream fis = new FileInputStream(filePath);
			DataInputStream dis = new DataInputStream( fis );
			
			String str ="";
			
			while((str = dis.readLine()) != null) {
				 lists[i] = str+"\n";
				 String[] arr = str.split("[|]"); 
				 //names[i]= arr[1];
			     //out.println(names[i] +  "<br>");  
			    // pws[i]=arr[2];
			     //out.println(pws[i] + "<br>");  
		      // out.println(i + "   :  ");    
		         for( int j = 1; j < arr.length; j++ ){
		        	 //lists[i] +=arr[j];
		        	 aaa[i][j]=arr[j];
			         
		         }  
		        // lists[i] +="\n";
		     //    out.println(aaa[i][1] +  "<br>");  
		     //    out.println(aaa[i][2] +  "<br>"); 
		         
		     //    out.println(lists[i]);
		     //    out.println("<br>");   
		     //    out.println("<br>");  
		               
		         i++;
		        
		    }
			fis.close();
			msg=1;
			
		
	} catch(IOException e) {
		out.println( "err1!! : " + e.getMessage() +"\n");
		out.println("<br>");
				
	}
	
%>   

 
    <table>
                <tr>
                   <input type="button" value="회원리스트" onclick="gotoMemberList()" >  
                   <input type="button" value="회원리스트 초기화" onclick="gotoDeleteList()" >  
                   <input type="button" value="로그기록" onclick="gotoLogHistory()" >  
                </tr>
     </table> 
     <br><br>
            
     <br><br>   
      
     <input type="button" value="로그아웃" onclick="confirmLogout()" >   
               
</body>
</html>      