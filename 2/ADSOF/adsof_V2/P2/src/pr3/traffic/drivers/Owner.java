package pr3.traffic.drivers;
import java.util.ArrayList;
import pr3.traffic.vehicles.*;

/**
 * This class manages the owners of the vehicles (company or person).
 * It also saves an ArrayList to save all the vehicles that a owner has.
 * 
 * @author pablo pablo.almarza@estudiante.uam.es
 * @author carlos carlos.garciatoledano@estudiante.uam.es
 *
 */
public abstract class Owner {
	private String name;
	private ArrayList<Vehicle> ownedVehicles = new ArrayList<>();
	
	/**
	 * Constructor of Owner
	 * @param name Name of the owner
	 */
	public Owner(String name) {
		this.name = name;
	}
	
	/**
	 * Method that adds a vehicle to the list of owned vehicles
	 * @param v
	 */
	public void addVehicle(Vehicle v) {
		if(!ownedVehicles.contains(v)) {
			ownedVehicles.add(v);
		}
	}
	
	/**
	 * Method that deletes a vehicle to the list of owned vehicles
	 * @param v
	 */
	public void delVehicle(Vehicle v) {
		if(ownedVehicles.contains(v)) {
			ownedVehicles.remove(v);
		}
	}
	
	/**
	 * Abstract class that checks if an owner is underage
	 * 
	 */
	public abstract Boolean checkAge();
	
	/**
	 * Get the ArrayList of owned vehicles
	 * @return the list of owned vehicles
	 */
	public ArrayList<Vehicle> getOwnedVehicles() {
		return ownedVehicles;
	}
	
	/**
	 * Getter for the name
	 * @return name
	 */
	public String getName() {
		return name;
	}
}
