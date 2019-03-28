import java.net.*; 
import java.io.*; 
  
public class Client 
{ 
    private Socket socket = null; 
    private InputStream input = null;
    private InputStreamReader reader = null; //wrapper for inputstream
    public Client(String address, int port) 
    { 
        try
        { 
            socket = new Socket(address, port); 
            System.out.println("Connected"); 
            input = socket.getInputStream();
            reader = new InputStreamReader(input);
            int character = reader.read(); 
            char key = (char)character;
            System.out.println("User pressed - " + key + " key."); 
            reader.close();
        } 
        catch(UnknownHostException u) 
        { 
            System.out.println("Problem in connect."); 
        } 
        catch(IOException i) 
        { 
            System.out.println("Problem in connect."); 
        } 
    } 
    public void closeConnection()
    {
        try
        { 
            socket.close(); 
            input.close();
            System.out.println("Connection closed."); 
        } 
        catch(IOException i) 
        { 
            System.out.println("Problem in close."); 
        } 
    }
    public static void main(String args[]) 
    { 
        Client client = null;
        try
        {
            do {
                client = new Client("127.0.0.1", 8080); 
                Thread.sleep(1000);
            }while(client != null);
            client.closeConnection();
        }
        catch(InterruptedException e)
        {
            System.out.println("Problem in waiting."); 
        }

    } 
} 