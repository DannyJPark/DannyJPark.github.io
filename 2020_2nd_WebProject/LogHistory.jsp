<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
   
<title>로그 리스트</title>



 <script type="text/javascript">
       
 function gotoMain() {       	
	 location.href="Main.jsp?id = id";
 }    
 
</script>

 
</head>
<body>


<br><br><br>
         <b><font size="6" color="gray">로그 리스트</font></b>   
    <br><br><br>

    
        
 <% 
   
	//String id =    request.getParameter("id") ;
    String IDs =  (String)session.getAttribute("IDs") ; // 세션에서 id 받아오기
    String masterID="master";
    String masterPW="master";
    
	out.println("<br>");
	out.println("<br>");
	//out.println("안녕하세요^^ " + id + "님 !!<br>");
	if (IDs.equals( masterID)) { // 관리자일 경우
		out.println("안녕하세요^^   " + IDs + " 관리자님 !!<br>");
	}
	else{ // 일반회원일 경우
		out.println("안녕하세요^^   " + IDs + " 회원님 !!<br>");
	}

	 out.println("<br>"); 
	 out.println("<br>"); 

int max = 100;
String bbb[][] = new String[max][3];   
String loglist[] = new String[max];
int lognum = 0;
try { // log 파일 읽어들임
	
	String fileName = "log.txt";
	String filePath = application.getRealPath(fileName);
	FileInputStream fis = new FileInputStream(filePath);
	//String filePath = application.getRealPath("c:/list.txt");
	//FileInputStream fis = new FileInputStream();
	//FileInputStream fis = new FileInputStream("c:/javap/test.txt");
	DataInputStream dis = new DataInputStream( fis );

	String str1 ="";

	while((str1 = dis.readLine()) != null) { // 파일에서 한줄 씩 읽어들임
		 loglist[lognum] = str1+"\n";
		 String[] arr = str1.split("[|]"); // | 기준으로 나누기
 		// loglist[lognum]="|";   
 	     for( int j = 1; j < arr.length; j++ ){
 	    	 bbb[lognum][j] = arr[j]; // bbb 배열에 저장
 	    	// loglist[lognum] += str1+"\n";
 	    	 out.println(bbb[lognum][j]);  // bbb배열 출력
 	     }
	     out.println("<br>");    
	     out.println("<br>");  
	           
	     lognum++;
	    
	}
	fis.close();

	} catch(IOException e) {
	out.println( "err1!! : " + e.getMessage() +"\n");
	out.println("<br>");

	}   


  
%>


<br><br>   
         
     <input type="button" value="메인화면으로" onclick="gotoMain()" />     
     
 </body>
</html>        
        