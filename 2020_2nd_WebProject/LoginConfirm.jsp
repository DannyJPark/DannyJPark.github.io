<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>

<%@page import="java.util.Date" %>
<%@page import="java.text.SimpleDateFormat" %>

 <script type="text/javascript">
    
 function errorCheck() //에러 체크
 {
     if(!user.id.value){ //아이디가 없을때
         alert("아이디를 입력하세요.");
         return false;
     }
     
     if(!user.password.value){ // 비번이 없을때
         alert("비밀번호를 입력하세요.");
         return false;
     }
    
  
}    
 
 function gotoNewForm() { //회원가입으로 가기
     	
         location.href="NewForm.jsp";
     } 
 
</script>


    
<% 

//int makenewfile = 0;
//int msg = 0;
int max = 100; //최대 회원수
int item = 10; // 목록 수
int i=0; 
  
String aaa[][] = new String[max][item];  // 회원정보 배열 (id|pw|...)
String lists[] = new String[max]; // 회원목록 배열

try { // 회원 list.txt 파일 읽어들임
	
String fileName = "list.txt";
String filePath = application.getRealPath(fileName);
FileInputStream fis = new FileInputStream(filePath);
DataInputStream dis = new DataInputStream( fis );

String str ="";

while((str = dis.readLine()) != null) { // 파일 끝이 아닐때 한 줄씩 읽기 반복
	 lists[i] = str+"\n";
	 String[] arr = str.split("[|]"); // "|" 로 데이터 나누기
     out.println(i + "   :  ");    
     for( int j = 1; j < arr.length; j++ ){ 
    	 aaa[i][j] = arr[j]; //배열에 넣기
    	 out.println(aaa[i][j]);  
     }
     
     out.println("<br>");   
     out.println(aaa[i][1]);   
     out.println("<br>");  
     out.println(aaa[i][2]);   
     out.println("<br>");  
           
     i++;
    
}
fis.close();

} catch(IOException e) {
out.println( "err1!! : " + e.getMessage() +"\n");
out.println("<br>");

}   

    String id = request.getParameter("id"); //로그인에서  id정보 받아오기
    String password = request.getParameter("password"); //로그인에서 pw정보 받아오기
 
    int check = 0;
    for (int j = 0; j < i ; j++) { // 로그인에서 입력한 id와 pw 가 존재하는지
   
        if (aaa[j][1].equals(id)) {
   
        	if (aaa[j][2].equals(password)) { // 존재하면
        		check = 1;
        		session.setAttribute("IDs", id); //세션에 id를 저장
        	}  
        	else { check = -1; //존재하지 않을때
        	
            } 
           
         }
    }
    
   if(check == 1){ //id pw 가 존재하면
	   String loglist[] = new String[max]; //log.txt 읽어오기
	   String bbb[][] = new String[max][item];  
	   int lognum = 0;
    try {
    	
    	String fileName = "log.txt";
    	String filePath = application.getRealPath(fileName);
    	FileInputStream fis = new FileInputStream(filePath);
    	DataInputStream dis = new DataInputStream( fis );

    	String str1 ="";

    	while((str1 = dis.readLine()) != null) {
    		 
    		 String[] arr = str1.split("[|]"); // 데이터 정보 나누기
    		// loglist[lognum]="|";   
    	     for( int j = 0; j < arr.length; j++ ){
    	    	 bbb[lognum][j] = arr[j];
    	    	// loglist[lognum] += str1+"\n";
    	    	 //out.println(bbb[lognum][j]);  
    	     }
    		 
    	     lognum++;
    	    
    	}
    	fis.close();

    	} catch(IOException e) {
    	out.println( "err1!! : " + e.getMessage() +"\n");
    	out.println("<br>");

    	}   
    
   	 try{ //log파일에 로그기록 저장하기
		
		String fileName = "log.txt";
		String filePath = application.getRealPath(  fileName);
		FileOutputStream fos = new FileOutputStream(filePath);
		DataOutputStream dos = new DataOutputStream( fos );
		
		for(int l = 0; l<lognum; l++){ // 기존 로그 기록 저장하기
			String str1 = "| " + bbb[l][1] + " | "+ bbb[l][2]+ "\n";
			
			dos.writeUTF(str1);
		}
		Date now = new Date();
		SimpleDateFormat sf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); //현재 날짜 및 시간 지정
		 
		String today = sf.format(now);
		String str2 = "| " + id +" | " + today + "\n"; 
		loglist[lognum] = str2;
		dos.writeUTF(loglist[lognum]); // log.txt 파일에 저장
		fos.close();
		
		out.println("<br>");
		out.println( "log.txt 화일에 저장하였습니다.\n" );
		out.println("<br>");
	
		} catch(IOException ee) {
			out.println( "err2!! : " + ee.getMessage()+"\n" );
		
		}
   }
       
    String msg = "Main.jsp?id="+id;
    
    if(check == 1)    // 로그인 성공, 메인화면으로 가기
    { 
       session.setAttribute("IDs", id);
    
    }
    else if(check == -1) // 비밀번호가 틀릴경우, 로그인화면으로 되돌아가기, msg를 -1로 반환
    {
        msg = "LoginForm.jsp?msg=-1";
      //  response.sendRedirect(msg);
    }
    else  if (check == 0)  // 아이디가 틀릴경우, msg를 0으로 반환
    {
        msg = "LoginForm.jsp?msg=0";
      //  response.sendRedirect(msg);
    }
    response.sendRedirect(msg); // msg로 지정된 화면으로 가기
  %> 
 
