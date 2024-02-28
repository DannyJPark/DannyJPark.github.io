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
	public class DoctorInfo {
	
	    
	    public String username;
	    public String password;
	    public String name;
	    
	    
	    public DoctorInfo(String newUsername, String newPassword,String newName)
	    {
	        username = newUsername;
	        password = newPassword;
	        name = newName;
	        
	        
	    }
	    
	    public static DoctorInfo loadUser(String enteredUsername) throws FileNotFoundException, IOException
	    {
	        File text_file = new File("DoctorInfo.txt");
	        
	        
	        
	        try
	        {
	        	if (!text_file.exists())
		        {
		           //throw new FileNotFoundException("User.txt does not exist");
		            text_file.createNewFile();
		        }
	        	
	        	
	        	
	        	
	            FileReader fr = new FileReader("DoctorInfo.txt");
	            BufferedReader br = new BufferedReader(fr);

	            String eachLine;

	            while ((eachLine = br.readLine()) != null)
	            {
	         //       if (eachLine.equals(enteredUsername))
	         //       {
	                    String[] credentials = eachLine.trim().split(",");
	                    if (credentials[0].equals(enteredUsername))
		                {
	                    DoctorInfo loaded_user = new DoctorInfo(credentials[0], credentials[1], credentials[2]);
	              //      DoctorInfo loaded_user = new DoctorInfo(username, credentials[1], credentials[2], credentials[3], credentials[4], credentials[5]);
	            //       name=load_user.name;
					
	                    
	                    
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
	            throw new IOException("DoctorInfo.txt에서 찾을 수 없음");
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
	        File file = new File("DoctorInfo.txt");
	        
	        try
	        {
	        	if (!file.exists())
		        {
		            file.createNewFile();
		        }
	         	
	            FileWriter fw = new FileWriter("DoctorInfo.txt", true);
	            BufferedWriter bw = new BufferedWriter(fw);

	            bw.write(this.username + ',' + this.password + ',' + this.name+'\n');

	            bw.close();
	            fw.close();
	        }
	        catch (IOException e)
	        {
	            throw new IOException("DoctorInfo.txt에 저장 실패");
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
	


