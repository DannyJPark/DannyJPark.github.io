<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page language="java" import="java.io.*" %>

<html>
<head>

<title>로그인</title>
  
<script type="text/javascript">
       
    
    function errorCheck() //입력 에러 체크
    {
        if(!user.id.value){
            alert("아이디를 입력하세요.");
            return false;
        }
        
        if(!user.password.value){
            alert("비밀번호를 입력하세요.");
            return false;
        }  
 }    
    
    function gotoNewForm() { // 회원가입으로 가기
        	
            location.href="NewForm.jsp";
        } 
    
    function gotoHome() { //홈화면으로 가기
    	
        location.href="Home.jsp";
    } 
    
   </script>
 
</head>
<body>

      <div id="wrap">
        <br><br><br>
        <b><font size="6" color="gray">로그인</font></b>
        <br><br><br>
 
        <form method="post" action="LoginConfirm.jsp" name="user" 
                onsubmit="return errorCheck()">
             <table border = "1" width = "300">
                <tr>
                    <td id="title">아이디</td>
                    <td>
                        <input type="text" name="id" >
                    </td>
                </tr>
                        
                <tr>
                    <td id="title">비밀번호</td>
                    <td>
                        <input type="password" name="password" >
                    </td>
                </tr>
                
                          
            </table>
            
            <br><br>
            <input type="submit" value="로그인"/>  
            <input type="button" value="회원가입" onclick="gotoNewForm()">
            <input type="button" value="홈페이지로" onclick="gotoHome()">
        </form>
        
         <% 
            session.invalidate(); //세션 id 지우기
            String msg=request.getParameter("msg");
           
            if(msg!=null && msg.equals("0")) // LoginConfirm에서 기존 아이디가 없을때 반환값
            {
         
                out.println("<font color='red' size='5'>아이디를 확인해 주세요.</font>"); 
            }
            
            else if(msg!=null && msg.equals("-1")) // 비밀번호가 틀릴 때 반환값
            {    
                
            	//out.println(msg);
            	//out.println("<br>");
                out.println("<font color='red' size='5'>비밀번호를 확인해 주세요.</font>");
            }
            
            else 
            {
            	out.println("   <br>");
            }
        %>    
       
    </div>       
    
</body>
</html>


