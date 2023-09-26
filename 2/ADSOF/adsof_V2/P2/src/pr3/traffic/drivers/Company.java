package pr3.traffic.drivers;
import pr3.traffic.vehicles.Vehicle;

public class Company extends Owner {
	private Person responsible;
	
	public Company(String name, Person responsible) {
		super(name);
		this.responsible = responsible;
	}
	
	public Person getResponsible() {
		return this.responsible;
	}
	
	/**
	 * Checks if the responsible of the company is underage
	 */
	@Override
	public Boolean checkAge() {
		return responsible.checkAge();
	}
	
	/**
	 * Returns the name of the company and responsible and the cars owned
	 */
	@Override
	public String toString(){
		String ret = super.getName()+" (responsible: "+responsible.getName()+") owner of:\n";
		for (Vehicle v : super.getOwnedVehicles()) {
			ret = ret + v + "\n";
		}
		return ret;
	}
}
