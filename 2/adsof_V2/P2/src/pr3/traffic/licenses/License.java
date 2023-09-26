package pr3.traffic.licenses;

import java.util.ArrayList;

/**
 * License class
 * Manages a license with multiple permits and number of points left
 */
public class License {
    private static int idCount = 0;
    private int id;
    private int points;
    private ArrayList<PermitKind> permits = new ArrayList<>();

    /**
	 * @brief License constructor
	 * 
	 * @param permitkind One or multiple permits
	 */
    public License(PermitKind ... permitkind) {
        id = idCount;
        idCount++;
        points = 12;
        for(PermitKind p : permitkind) {
            addPermit(p);
        }
    }

    /**
	 * Returns the permits stored 
	 * @return permits
	 */
    public ArrayList<PermitKind> getPermitKind() {
        return permits;
    }

    /**
	 * Adds a permit to the array
	 * @param p permitkind to add
	 */
    public void addPermit(PermitKind p) {
        if(!permits.contains(p))
            permits.add(p);
    }

    /**
     * Checks if a person can drive a car
     * @return boolean true if s/he can, false if not
     */
    public boolean canDriveCar(){
        if(permits.contains(PermitKind.B))
            return true;
        return false;
    }

    /**
     * Checks if a person can drive a truck
     * @return boolean true if s/he can, false if not
     */
    public boolean canDriveTruck(){
        if(permits.contains(PermitKind.C1))
            return true;
        return false;
    }

    /**
     * Checks if a person can drive a motorcycle
     * @return boolean true if s/he can, false if not
     */
    public boolean canDriveMotorcycle(){
        if(permits.contains(PermitKind.A))
            return true;
        return false;
    }

    /**
     * Checks if a person can have a License depending on his/her age
     * @param age Age of the person
     * @return boolean true if s/he can, false if not
     */
    public boolean canHaveLicense(int age){        
		for(PermitKind p: this.permits) {
            if (p == PermitKind.A || p == PermitKind.B) {
                if(age < 18) {
                    return false;
                }
            } else {
                if(age < 23) {
                    return false;
                }
            }
		}
		return true;
    }

    /**
	 * Returns the information of the license in string format
	 * @return string with info
	 */
	@Override
    public String toString(){
        String ret = "License [id="+id+", permits="+permits+", points="+points+"]";
        return ret;
    }

} 