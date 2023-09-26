package pr3.traffic.vehicles;
import pr3.traffic.drivers.*;
/**
 * This class manages Vehicles which is an abstract class
 * 
 * @author carlos carlos.garciatoledano@estudiante.uam.es
 * @author pablo pablo.almarza@estudiante.uam.es
 *
 */
public abstract class Vehicle {
	private String model;
	private int purchaseYear;
	private String plate;
	private Owner owner;
	private Person driver;
	
	/**
	 * Vehicle constructor
	 * @param mod vehicle model
	 * @param a purchase year
	 * @param owner owner of the vehicle
	 */
	public Vehicle(String mod, int a, Person owner) {		
		this.model = mod;
		this.purchaseYear = a;
		this.setOwner(owner);
		this.setDriver(owner);
	}
	
	/**
	 * Vehicle constructor
	 * @param mod vehicle model
	 * @param a purchase year
	 * @param plate plate number
	 * @param owner owner of the vehicle
	 */
	public Vehicle(String mod, int a, String plate, Person owner) {		
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
		this.setOwner(owner);
		this.setDriver(owner);		
	}
	
	/**
	 * Vehicle constructor
	 * @param mod vehicle model
	 * @param a purchase year
	 * @param owner owner of the vehicle
	 */
	public Vehicle(String mod, int a, Company owner) {		
		this.model = mod;
		this.purchaseYear = a;
		this.setOwner(owner);
		this.setDriver(owner.getResponsible());
	}
	
	/**
	 * Vehicle constructor
	 * @param mod vehicle model
	 * @param a purchase year
	 * @param plate plate number
	 * @param owner owner of the vehicle
	 */
	public Vehicle(String mod, int a, String plate, Company owner) {		
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
		this.setOwner(owner);
		this.setDriver(owner.getResponsible());		
	}
	
	/**
	 * Vehicle constructor
	 * @param mod vehicle model
	 * @param a purchase year
	 */
	public Vehicle(String mod, int a) {		
		this.model = mod;
		this.purchaseYear = a;
	}
	
	/**
	 * Vehicle constructor
	 * @param mod
	 * @param a
	 * @param plate
	 */
	public Vehicle(String mod, int a, String plate) {		
		this.model = mod;
		this.purchaseYear = a;
		this.plate = plate;
	}
	
	/**
	 * Returns information of a vehucle in string format
	 */
	@Override
	public String toString() {
		String ret = "model "+this.model+ ", number plate: "+this.plate+", purchase date "+this.purchaseYear+", with "+
				this.numWheels()+" wheels, index:"+this.getPollutionIndex();
		
		if (this.owner != null) {
			ret = ret + " owner: "+this.owner.getName();
		}
		
		if(this.driver != null) {
			ret = ret + " driver: "+this.driver.getName();

		}
		
		return ret; 
	}
	
/**
	 * Returns the number of wheels
	 * Abstract method
	 * @return number of wheels
	 */
	public abstract int numWheels();
	
	/**
	 * Returns the pollution index of a vehicle
	 * @return pollution index
	 */
	public PollutionIndex getPollutionIndex() {
		return PollutionIndex.getPollutionIndex(this.purchaseYear);
	}
	
	
	/**
	 * Sets the owner of a vehicle if possible
	 * @param o
	 * @return true if ok, false if underage
	 */
	public Boolean setOwner(Person o) {
		if(o.checkAge()) {
			if(this.owner != null) {
				this.owner.delVehicle(this);
			}
			this.owner = o;
			o.addVehicle(this);
			if(this.driver == null) this.setDriver(o);
			return true;
		}
		return false;
	}
	
	/**
	 * Sets the owner of a vehicle if possible
	 * @param o
	 * @return true if ok, false if underage
	 */
	public Boolean setOwner(Company o) {
		if(o.checkAge()) {
			if(this.owner != null) {
				this.owner.delVehicle(this);
			}
			this.owner = o;
			o.addVehicle(this);
			if(this.driver == null) this.setDriver(o.getResponsible());
			return true;
		}
		return false;
	}

	/**
	 * Sets the driver of a vehicle if possible
	 * @param d
	 * @return true if ok, false if underage
	 */
	public Boolean setDriver(Person d) {
		if(d.checkAge()) { 
			this.driver = d;
			return true;
		}
		return false;
	}
	
}
