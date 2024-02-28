<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>


<html>
<head>
   
    <title>메인화면</title>

 <script type="text/javascript">
    
 function confirmLogout() { // 로그아웃 여부 확인
	    var ret = confirm("로그아웃 할까요?");
	    if(ret == true) {
	    	location.href="LoginForm.jsp"         
	    }
	    else {    
	    }
 }
       
 function gotoMain() {       	// 메인으로 가기
   location.href="Main.jsp";
 }    
 
</script>

 
</head>
<body>
    <br><br><br>
         <b><font size="6" color="gray">회원 가입 완료</font></b>   
    <br><br><br>
 <% 
 
 //회원가입 화면에서 정보 받아오기
    String ID =    request.getParameter("id") ;
	String PW =    request.getParameter("password");
	String Name =  request.getParameter("name") ;
	String Birth = request.getParameter("birth") ;
	String Phone = request.getParameter("phone") ;
	String Email = request.getParameter("email") ;
// 회원가입후 정보 출력하기	
	out.println("<br>");
	out.println("<br>");
	out.println("안녕하세요^^ " + ID + "님 ^^<br>");
	out.println("<br>");
	out.println("<br>");
	out.println("회원 가입이 완료되었습니다. !!<br>");
	out.println("<br>");
	out.println("received ID : " + ID + "<br>");
	out.println("received password : " + PW + "<br>");
	out.println("received name : " + Name + "<br>");
	out.println("received birth : " + Birth + "<br>");
	out.println("received phone : " + Phone + "<br>");
	out.println("received email : " + Email + "<br>");
	out.println("<br>");

	int makenewfile = 0;
	int msg = 0;
	int max = 100;
	int item = 10;
	int i=0;
      
	String aaa[][] = new String[max][item];  
	String lists[] = new String[max];
 
	 session.setAttribute("IDs", ID);
	 
	try { //list를 불러들이고
		
		String fileName = "list.txt";
		String filePath = application.getRealPath( fileName);
		FileInputStream fis = new FileInputStream(filePath);
	DataInputStream dis = new DataInputStream( fis );
	
	String str ="";
	
	while((str = dis.readLine()) != null) { // 파일끝까지 한줄씩 읽어들임
		 lists[i] = str+"\n";
		 String[] arr = str.split("[|]"); // | 기준으로 배열을 나누기
	   //  out.println(i + "   :  ");    
         for( int j = 1; j < arr.length; j++ ){ 
        	 aaa[i][j] = arr[j]; // 배열을 저장
         }
   //      out.println("<br>");   
   //      out.println("<br>");  
   //            
         i++;
        
    }
	fis.close();
	msg=1;
	
} catch(IOException e) {
	out.println( "err1!! : " + e.getMessage() +"\n");
	out.println("<br>");
	
}
 
	    lists[i]="|"+ ID+"|"+PW+"|"+Name+"|"+Birth+"|"+Phone+"|"+Email+"\n"; // 저장할 배열을 만들기
	    
try {	// list.txt에 저장
		String str ;
		String fileName = "list.txt";
		String filePath = application.getRealPath( fileName);
		FileOutputStream fos = new FileOutputStream(filePath);
		DataOutputStream dos = new DataOutputStream( fos );
		
		int j=0;
		
		while(j<=i) {
		 	dos.writeUTF(lists[j]);
			//out.println(j + "   :  "+ lists[j]); 
			j++;
			
			//out.println("<br>");   
	        //out.println("<br>");  
		}
		fos.close();
	
		out.println( "list.txt 화일에 저장하였습니다.\n" );
		out.println("<br>");
	
		makenewfile = 1;
		msg = 1;
	} catch(IOException ee) {
		out.println( "err2!! : " + ee.getMessage()+"\n" );
		//msg = 0;
	}
	
		          
%>        
     <br><br>   
     <input type="button" value="로그아웃" onclick="confirmLogout()" />      
     <input type="button" value="메인화면으로" onclick="gotoMain()" />         
</body>
</html>      