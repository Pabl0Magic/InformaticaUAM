package pr3.traffic.vehicles;
import pr3.traffic.drivers.*;

/**
 * @brief This class manages the trucks
 * @author pablo pablo.almarza@estudiante.uam.es
 * @author carlos carlos.garciatoledano@estudiante.uam.es
 *
 */
public class Truck extends Vehicle {
	private int axles;
	
	/**
	 * 
	 * @param mod Model of the vehicle
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param axles Number of axes
	 */
	public Truck(String mod, int a, String plate, int axles) {
		super(mod, a, plate);
		this.axles = axles;
		
	}
	
	/**
	 * 
	 * @param mod Model of the vehicle
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param axles Number of axes
	 */
	public Truck(String mod, int a, String plate, int axles, Person owner) {
		super(mod, a, plate, owner);
		this.axles = axles;
	}
	
	/**
	 * 
	 * @param mod Model of the vehicle
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param axles Number of axes
	 */
	public Truck(String mod, int a, String plate, int axles, Company owner) {
		super(mod, a, plate, owner);
		this.axles = axles;
	}
	
	/**
	 * Returns the number of wheels of a truck ( 2 times the number of axles)
	 * @return number of wheels
	 */
	@Override
	public int numWheels() {
		return 2*this.axles;
	}
	
	/**
	 * Returns the pollution index of a truck (if it has more than 2 axles, its C)
	 * @return pollution index
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if(this.axles > 2) {
			return PollutionIndex.C;
		} else {
			return super.getPollutionIndex();
		}
	}
	
	/**
	 * Returns the information of the truck in string format
	 * @return string with info
	 */
	@Override
	public String toString() {
		return "Truck with "+ this.axles+ " axles, " + super.toString();
	}
}
