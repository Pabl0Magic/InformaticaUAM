package pr3.traffic.drivers;
import pr3.traffic.vehicles.Vehicle;

public class Person extends Owner {
	private Integer age;
	
	public Person(String name, int age) {
		super(name);
		this.age = age;
	}

	/**
	 * Checks if a person is underage or not
	 */
	@Override
	public Boolean checkAge() {
		if (this.age >= 18) return true;
		return false;
	}
	
	@Override
	public String toString() {
		String ret = super.getName()+" owner of:\n";
		for (Vehicle v : super.getOwnedVehicles()) {
			ret = ret + v + "\n";
		}
		return ret;
	}

}
