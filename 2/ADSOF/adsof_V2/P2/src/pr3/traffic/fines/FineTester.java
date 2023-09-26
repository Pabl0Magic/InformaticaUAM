package pr3.traffic.fines;
import java.util.List;

public class FineTester {
    
    public static void main(String[] args) {
        List<Fine> fines= FineReader.read("fines_radar1.txt");
        for(Fine m: fines) System.out.println(m+"\n------------");
    }
}