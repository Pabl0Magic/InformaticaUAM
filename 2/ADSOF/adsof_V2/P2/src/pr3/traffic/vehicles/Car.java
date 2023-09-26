package pr3.traffic.vehicles;
import pr3.traffic.drivers.*;

public class Car extends Vehicle {
	private boolean diesel;
	
	/**
	 * @brief Original constructor for exercise 1
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, boolean diesel) {
		super(mod, a);
		this.diesel = diesel;
	}
	
	/**
	 * @brief New constructor to run exercise 2
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, String plate, boolean diesel) {
		super(mod, a, plate);
		this.diesel = diesel;
	}
	
	/**
	 * @brief Original constructor for P3
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, boolean diesel, Person owner) {
		super(mod, a, owner);
		this.diesel = diesel;
	}
	
	/**
	 * @brief Original constructor for P3
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, boolean diesel, Company owner) {
		super(mod, a, owner);
		this.diesel = diesel;
	}
	
	/**
	 * @brief New constructor to run the P3
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, String plate, boolean diesel, Person owner) {
		super(mod, a, plate, owner);
		this.diesel = diesel;
	}
	
	/**
	 * @brief New constructor to run the P3
	 * 
	 * @param mod Model
	 * @param a Year of purchase
	 * @param plate Number plate
	 * @param diesel If it is diesel or not
	 * @param owner Owner of the car
	 */
	public Car(String mod, int a, String plate, boolean diesel, Company owner) {
		super(mod, a, plate, owner);
		this.diesel = diesel;
	}
	
	
	
	/**
	 * Returns the number of wheels of a car
	 * @return number of wheels
	 */
	@Override public int numWheels() { return 4; }
	
	/**
	 * Returns the information of the car in string format
	 * @return string with info
	 */
	@Override public String toString() {
		return "Car "+(this.diesel ? "diesel" : "gasoline") + ", "+ super.toString();
	}
	
	/**
	 * Returns the pollution index of a car (if it is diesel, then its C)
	 * @return pollution index
	 */
	@Override
	public PollutionIndex getPollutionIndex() {
		if (this.diesel) return PollutionIndex.C;
		return super.getPollutionIndex();
	}
	
	public boolean getDiesel() { return this.diesel; }
	public void setDiesel(boolean b) { this.diesel = b; }
}
