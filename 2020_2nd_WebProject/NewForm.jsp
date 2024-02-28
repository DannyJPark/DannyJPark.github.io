<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>

<html>
<head>
    <title>회원가입</title>
  
 
    <script type="text/javascript">
    
      
    function errorCheck()
        {
    	 if(!user.id.value){ //입력을 안했을때
             alert("아이디를 입력하세요.");
             return false;
         }
         
         if(!user.password.value){ 
             alert("비밀번호를 입력하세요.");
             return false;
         }
         
         // 비밀번호와 비밀번호 확인에 입력된 값이 동일한지 확인
         if(user.password.value != user.passwordcheck.value ){
             alert("비밀번호를 동일하게 입력하세요.");
             return false;
         }
         
         if(!user.name.value){
             alert("이름을 입력하세요.");
             return false;
         }
         
         if(!user.birth.value){
             alert("생년월일을 입력하세요.");
             return false;
         }
         if(isNaN(user.birth.value)){
             alert("생년월일은 숫자만 입력가능합니다.");
             return false;
         }

       if(!user.phone.value){
             alert("휴대전화를 입력하세요.");
             return false;
         }
         
         if(!user.email.value){
             alert("이메일을 입력하세요.");
             return false;
         }



     }    
        
   
    function gotoLoginForm() {
            location.href="LoginForm.jsp";
        }
    
    function gotoNewFormComplete() {
    
      location.href="NewFormComplete.jsp"
   
    }
 function gotoHome() {
    	
        location.href="Home.jsp";
    }   
 

  
    </script>
    
</head>
<body>


      <div id="wrap">
        <br><br><br>
        <b><font size="6" color="gray">회원 가입</font></b>
        <br><br><br>
 
         <form method="post" action="NewFormComplete.jsp" name="user" 
                onsubmit="return errorCheck()">
            <table border = "1" width = "500">
                <tr>
                    <td width =200 id="title">아이디</td>
                    <td width =200>
                          <input type="text" name="id" >                 
                         <input type="button" value="중복확인" onclick="return validation()">     
                         <input type="hidden" name="checked_id" value="">
						
                    </td>
                </tr>
                        
                <tr>
                    <td id="title">비밀번호</td>
                    <td >
                        <input type="password" name="password" >
                    </td>
                </tr>
                
                <tr>
                    <td id="title">비밀번호 확인</td>
                    <td >
                        <input type="password" name="passwordcheck">
                    </td>
                </tr>
                    
                <tr>
                    <td id="title">이름</td>
                    <td>
                        <input type="text" name="name" >
                    </td>
                </tr>
                    
               
                <tr>
                    <td id="title">생년월일   (YYYYMMDD)</td>
                    <td>
                        <input type="text" name="birth" >
                        
                    </td>
                </tr>
                
                <tr>
                    <td id="title">휴대전화   (010-0000-0000)</td>
                    <td>
                        <input type="text" name="phone" />
                    </td>
                </tr>
                    
                <tr>
                    <td id="title">이메일      (aaa@aaa.com)</td>
                    <td>
                        <input type="text" name="email" >
                        
                    </td>
                </tr>
                         
            </table>
            
            <br><br>
            <input type="submit" value="회원가입"/>  
            <input type="button" value="로그인하기" onclick="gotoLoginForm()">
             <input type="button" value="홈페이지로" onclick="gotoHome()">
        </form>
        
   <% 
          
           String IDs =  (String)session.getAttribute("IDs") ; 
           session.invalidate(); //세션 정보 종료
           
           int max = 100;
           int item = 10;
           int i=0;
             
           String aaa[][] = new String[max][item];  
           String lists[] = new String[max];
           StringBuffer values = new StringBuffer();

           try { //회원 정보를 읽어들임
           	
           	String fileName = "list.txt";
           	String filePath = application.getRealPath( fileName);
           	FileInputStream fis = new FileInputStream(filePath);
               DataInputStream dis = new DataInputStream( fis );

               String str ="";
              
		
           	
               while((str = dis.readLine()) != null) { //파일 끝이 아닐때 한줄씩 읽어들임
          
           		 String[] arr = str.split("[|]"); // 파일을 | 기준으로 나누고
          		 aaa[i][1] = arr[1]; // aaa 배열에 저장
          		 
          		 if(values.length()>0) { //String buffer인 value에 회원 id 저장
		   			values.append(',');
	    		}

           		values.append('"').append(aaa[i][1]).append('"'); // 파일을 읽을때마다 id 추가
           		//out.println(values + "<br>");
                 i++;
             
           }
           fis.close();

           } catch(IOException e) {
           out.println( "err1!! : " + e.getMessage() +"\n");
           out.println("<br>");

           }   
           
           
          
          %>
  <script type="text/javascript">

function validation() { //같은 id가 있는지 확인

	var id1 = user.id.value; //입력한 id를 var id1에 저장

	var flag = true; 

	var list = [ <%=values.toString()%>]; // list에 id 정보들을 저장

	//아이디 입력 여부

	if(id1=="") {

		alert("아이디를 입력해주세요.");

		return ;

	}

	
	for(var k=0; k<list.length; k++) { // 같은 id가 있는지 리스트와 비교

		if(id1==list[k]){ //같은게 있으면

			flag = false;

			break;

		}

	}
	
	if(flag) // flag가 true면

		alert("사용 가능한 아이디 입니다.");

	else // false면

		alert("중복된 아이디 입니다."); 

	

}

</script> 
           
           
      
        
        
    </div>
    
   
</body>
</html>


