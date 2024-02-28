package application;


	import java.io.BufferedReader;
	import java.io.BufferedWriter;
	import java.io.File;
	import java.io.FileNotFoundException;
	import java.io.FileReader;
	import java.io.FileWriter;
	import java.io.IOException;

	/**
	 *
	 * @author Sajeed Ahmed Galib Arnob
	 */
	public class PatientInfo {
	
	    
	    public String username;
	    public String password;
	    public String name;
	    public String age;
	    public String sex;
	    public String phone ;
	    public String phx ;
	    public String fhx ;
	//    public String shx ;
	    
	    public PatientInfo(String newUsername, String newPassword,String newname, String newsex, String newage, String newphone,String newphx,String newfhx)
	    {
	        username = newUsername;
	        password = newPassword;
	        name = newname;
	        age=newage;
	        sex=newsex;
	        phone=newphone;
	        phx=newphx;
	        fhx=newfhx;
	  //      shx=newshx;
	        
	    }
	    
	    public static PatientInfo loadUser(String enteredUsername) throws FileNotFoundException, IOException
	    {
	        File text_file = new File("PatientInfo.txt");
	        
	        
	        
	        try
	        {
	        	if (!text_file.exists())
		        {
		           //throw new FileNotFoundException("User.txt does not exist");
		            text_file.createNewFile();
		        }
	        	
	        	
	        	
	        	
	            FileReader fr = new FileReader("PatientInfo.txt");
	            BufferedReader br = new BufferedReader(fr);

	            String eachLine;

	            while ((eachLine = br.readLine()) != null)
	            {
	         //       if (eachLine.equals(enteredUsername))
	         //       {
	                    String[] credentials = eachLine.trim().split(">");
	                    if (credentials[0].equals(enteredUsername))
		                {
	                    PatientInfo loaded_user = new PatientInfo(credentials[0], credentials[1], credentials[2], credentials[3], credentials[4], credentials[5], credentials[6], credentials[7]);
	              //      PatientInfo loaded_user = new PatientInfo(username, credentials[1], credentials[2], credentials[3], credentials[4], credentials[5]);
	                   
					
	                    
	                    
	                    br.close();
	                    fr.close();
	                    return loaded_user;
	                }
	            }

	            br.close();
	            fr.close();
	        }
	        
	        catch (IOException e)
	        {
	            throw new IOException("PatientInfo.txt에서 찾을 수 없음");
	        }
	        
	        return null;
	    }
	    
	    /**
	     * 
	     * @param enteredPassword the password entered by the user
	     * @return true if the password matches the current user's password
	     */
	    public boolean checkPassword(String enteredPassword)
	    {
	        return (enteredPassword.equals(password));
	    }
	    
	    public void save() throws IOException
	    {
	        File file = new File("PatientInfo.txt");
	        
	        try
	        {
	        	if (!file.exists())
		        {
		            file.createNewFile();
		        }
	         	
	            FileWriter fw = new FileWriter("PatientInfo.txt", true);
	            BufferedWriter bw = new BufferedWriter(fw);
	            
	           
	            
	          

	            bw.write(this.username + '>' + this.password + '>' + this.name+ '>' + this.age+ '>' + this.sex+ '>' + this.phone+ '>' + this.phx+ '>' + this.fhx+ '>' + '\n');

	            bw.close();
	            fw.close();
	        }
	        catch (IOException e)
	        {
	            throw new IOException("PatientInfo.txt에 저장 실패");
	        }
	    }
	    
	    /**
	     * 
	     * @return (String) username and password
	     */
	    @Override
	    public String toString()
	    {
	        return "User <username: " + this.username + ", password: " + this.password + ">";
	    }
	    
	}
	
	
	


