package pr3.traffic.fines;
import java.io.*;
import java.util.*;

/**
 * Fine Reader Class
 * This abstract class provides the utillity of reading files
 * given the name and turning the contents into Fines, returning a list of these.
 */
public class FineReader {

    public static ArrayList<Fine> read(String filename) {
        ArrayList<Fine> newFine = new ArrayList<> ();
        try {
            BufferedReader buffer = new BufferedReader(new FileReader(filename)); 
  
            String st; 
            while ((st = buffer.readLine()) != null) 
                System.out.println(st); 
            
            buffer.close();
            return newFine;
        }catch (IOException e) {
            System.out.println(e);
            return newFine;
        }
    }
}