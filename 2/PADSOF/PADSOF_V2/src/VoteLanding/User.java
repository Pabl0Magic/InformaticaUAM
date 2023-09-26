package VoteLanding;
import java.util.ArrayList;


/**
 * User class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class User{

    private String name;
    private String DNI;
    private String password;
    private State state;
    private Acceptance acceptance;
    private ArrayList<Notification> notification;


    public enum State{
        Online,
        Absent,
        Offline
    }

    public enum Acceptance{
        Authorized,
        Banned,
        Pending,
        Rejected
    }

    public User(String name, String DNI, String password) {
        this.name = name;
        this.DNI = DNI;
        this.password = password;
        
        notification = new ArrayList<Notification>();
    }

    /**
     * Getter for the name of a user
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * Getter for the DNI of a user
     * @return dni
     */
    public String getDNI() {
        return DNI;
    }

    /**
     * Getter for the password of a user
     * @return password
     */
    public String getPassword() {
        return password;
    }

    /**
     * Getter for the state of a user
     * @return state
     */
    public State getState() {
        return state;
    }
    
    /**
     * Setter for the state of a user
     * @param state
     */
    public boolean setState(State stat) {
    	for(State s: State.values()) {
    		if(s.equals(stat)) {
    			state = stat;
    			return true;
    		}
    	}
		System.out.println("Invalid type of status.");    	
    	return false;
    }

    /**
     * Getter for the acceptance of a user
     * @return acceptance
     */
    public Acceptance getAcceptance() {
        return acceptance;
    }
    
    /**
     * Setter for the acceptance of a user
     * @param acceptance
     */
    public boolean setAcceptance(Acceptance accept) {
    	for(Acceptance a: Acceptance.values()) {
    		if(a.equals(accept)) {
    			acceptance = accept;
    			return true;
    		}
    	}
		System.out.println("Invalid type of acceptance.");    	
    	return false;
    }
    
    /**
     * Getter of the notification list of User
     * @return array list of notifications
     */
    public ArrayList<Notification> getNotification(){
    	return notification;
    }
    
    /**
     * Adds a new notification to the notification array list
     * @param n notification to add
     */
    public void addNotification(Notification n) {
    	if(notification.contains(n)==false){
    		notification.add(n);
    	}
    }
    
    /**
     * Deletes a notification from the notification array list
     * @param n notification to erase
     */
    public void delNotification(Notification n) {
    	notification.remove(n);
    }
    
}