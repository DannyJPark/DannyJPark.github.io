<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
   
<title>회원 리스트</title>



 <script type="text/javascript">
       
 function gotoMain() {       	
	 location.href="Main.jsp?id = id";
 }    
 
</script>

 
</head>
<body>


<br><br><br>
         <b><font size="6" color="gray">회원 리스트</font></b>   
    <br><br><br>

    
        
 <% 
   
	//String id =    request.getParameter("id") ;
    String IDs =  (String)session.getAttribute("IDs") ; // 세션 id 받아오기
    String masterID="master";
    String masterPW="master";
    
	out.println("<br>");
	out.println("<br>");
	//out.println("안녕하세요^^ " + id + "님 !!<br>");
	// 관리자면
	if (IDs.equals( masterID)) {
		out.println("안녕하세요^^   " + IDs + " 관리자님 !!<br>");
	}
	// 일반회원이면
	else{
		out.println("안녕하세요^^   " + IDs + " 회원님 !!<br>");
	}

	 out.println("<br>"); 
	 out.println("<br>"); 
//int makenewfile = 0;
//int msg = 0;
int max = 100;
int item = 10;
int i=0;
  
String aaa[][] = new String[max][item];  
String lists[] = new String[max];
String arr[] = new String[item];
try { // list 파일 읽어들임
	
	String fileName = "list.txt";
	String filePath = application.getRealPath( fileName);
	FileInputStream fis = new FileInputStream(filePath);
DataInputStream dis = new DataInputStream( fis );

String str ="";
//if (IDs.equals( masterID) ) {
  while((str = dis.readLine()) != null) {
	 lists[i] = str+"\n";
	 arr = str.split("[|]"); 
  //   out.println(i + "   :  ");    
     for( int j = 1; j < arr.length; j++ ){
    	 aaa[i][j] = arr[j];
    	
   // 	 out.println(aaa[i][j] +  "  ");  
    	 
     }
  //   out.println("<br>");   
     
           
     i++;
  } 
 
 
fis.close();

} catch(IOException e) {
out.println( "err1!! : " + e.getMessage() +"\n");
out.println("<br>");

}   



if (IDs.equals( masterID) ) { // 관리자로 접속한 경우
 out.println("번호 아이디 비밀번호 이름 생년월일 핸드폰 이메일<br>");	// 모든 회원정보 출력

 for (int k=0; k < i;k++) {
	out.println(k + "   :  ");   
    for( int j = 1; j < arr.length; j++ ){
   	 out.println(aaa[k][j] +  "    ");  
	}
    out.println("<br>");   
 }

} else { // 일반회원으로 접속한 경우
	 out.println("일반 회원은 ID 목록만 볼 수 있습니다. !!<br><br>");  // id만 출력
	 out.println("번호 아이디 <br>");	
	 for (int k=1; k < i;k++) {
		 out.println(k + "   :  ");
	 	 out.println(aaa[k][1] +  "  "); 
	     out.println("<br>"); 
	 }
	 out.println("<br>");   
		 
}

  
%>


<br><br>   
         
     <input type="button" value="메인화면으로" onclick="gotoMain()" />     
     
 </body>
</html>        
        