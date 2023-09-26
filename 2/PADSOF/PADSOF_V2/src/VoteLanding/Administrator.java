package VoteLanding;

import java.util.ArrayList;

/**
 * Administrator class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Administrator {
    private String name;
    private String password;
    private ArrayList<Notification> notification;


    public Administrator(String name, String password) {
        this.name = name;
        this.password = password;
    }
    
    /**
     * Getter for the name of Administrator
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * Getter for password of Administrator
     * @return password
     */
    public String getPassword() {
        return password;
    }
    
    /**
     * Getter for he notification of Administrator
     * @return array list of notifications
     */
    public ArrayList<Notification> getNotification() {
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
