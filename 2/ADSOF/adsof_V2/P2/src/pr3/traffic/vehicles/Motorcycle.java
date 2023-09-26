package pr3.traffic.vehicles;
import pr3.traffic.drivers.*;

/**
 * This class manages Motorcycles which are a kind  of vehicle
 * 
 * @author carlos carlos.garciatoledano@estudiante.uam.es
 * @author pablo pablo.almarza@estudiante.uam.es
 *
 */
public class Motorcycle extends Vehicle {
	private boolean electric;

	/**
	 * Motorcycle constructor
	 * @param mod Motorcycle model
	 * @param a Year of purchase
	 * @param numberPlate Plate number
	 * @param electric If it is electric or not
	 */
	public Motorcycle(String mod, int a, String numberPlate, boolean electric) {
		super(mod, a, numberPlate);
		this.electric = electric;
	}
	
	/**
	 * Motorcycle constructor
	 @param mod Motorcycle model
	 * @param a Year of purchase
	 * @param numberPlate Plate number
	 * @param electric If it is electric or not
	 * @param owner Owner of the motorcycle
	 */
	public Motorcycle(String mod, int a, String numberPlate, boolean electric, Person owner) {
		super(mod, a, numberPlate, owner);
		this.electric = electric;
	}
	public Motorcycle(String mod, int a, String numberPlate, boolean electric, Company owner) {
		super(mod, a, numberPlate, owner);
		this.electric = electric;
	}
	
	/**
	 * Returns the number of wheels of a motorcycle
	 * @return num of wheels
	 */
	@Override
	public int numWheels() {
		return 2;
	}

	/**
	 * Returns the pollution index of a motorcycle
	 * @return pollution index
	 */
	@Override 
	public PollutionIndex getPollutionIndex() {
		if(this.electric) return PollutionIndex.A;
		return super.getPollutionIndex();
	}

	/**
	 * Returns the information of the motorcycle in string format
	 * @return string with info
	 */
	@Override
	public String toString() {
		String ret = "Motorcycle";
		if(this.electric) {
			ret += " electric";
		}
		
		return ret+", "+super.toString();
	}
	
}



