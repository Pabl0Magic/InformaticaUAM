import java.util.SortedSet;
import java.util.TreeSet;

public class SortAndSum{
	private SortedSet<Integer> odd = new TreeSet<>();
	private SortedSet<Integer> even = new TreeSet<>();
	
	public SortAndSum(String ... args){
		Integer n;
		for(String s: args){
			n = Integer.parseInt(s);
			if (n%2==0){
				even.add(n);
			}else{
				odd.add(n);
			}
		}
	}
	
	public Integer getEvenSum(){
		Integer sum=0;
		for(Integer n: even){
			sum += n;
		}
		return sum;
	}

	public Integer getOddSum(){
		Integer sum=0;
		for(Integer n: odd){
			sum += n;
		}
		return sum;
	}

	public void add(Integer n){
		if(n%2==0){
			even.add(n);
			return;
		}
		odd.add(n);
	}

	public String toString(){
		return "Even numbers "+even+" (sum: "+getEvenSum()+")\n"+"Odd numbers "+odd+" (sum: "+getOddSum()+")\n";
	}

	public static void main(String ... args){
		if (args.length < 2){
			System.out.println("At least two numbers are expected");
			System.out.println("Returns the ordered even and odd numberswithoutrepetitionand their sum");
		}
		else{
			SortAndSum c = new SortAndSum(args);
			System.out.println(c);
			c.add(30);
			c.add(33);
			System.out.println(c);
			System.out.println("Sum even numbers: "+c.getEvenSum());
			System.out.println("Sum odd numbers: "+c.getOddSum());
			System.out.println("Total sum: "+(c.getEvenSum()+c.getOddSum()));
		}
	}
}