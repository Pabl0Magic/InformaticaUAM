package VoteLanding;
import java.util.*;
import java.io.*;
import java.time.LocalDate;
import VoteLanding.Notification.TypeNotification;
import modifiableDates.ModifiableDate;

/**
 * SystemLanding class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class SystemLanding implements java.io.Serializable{
    
	private static String saveFile = "VoteLanding.txt";
	private static final long serialVersionUID = 1L;
	private ArrayList<User> user;
    private ArrayList<Group> group;
    private ArrayList<Project> project;
    private Administrator admin;
    private LocalDate date;
    
    public SystemLanding() {
    	admin = new Administrator("Default", "P6gw82z");    	
    	user = new ArrayList<User>();
    	group = new ArrayList<Group>();
    	project = new ArrayList<Project>();
    	date = ModifiableDate.getModifiableDate();

    }
    
    /**
     * Getter for the user list of SystemLanding
     * @return user
     */
    public List<User> getUser() {
        return user;
    }
    
    /**
     * Adds a user to the user list
     * @param u
     */
    public void addUser(User u) {
    	user.add(u);
    }
    
    /**
     * Getter for the group list of SystemLanding
     * @return group
     */
    public List<Group> getGroup() {
        return group;
    }
    
    /**
     * Adds a group to the group list
     * @param g
     */
    public void addGroup(Group g) {
    	group.add(g);
    }
    
    /**
     * Getter for the project list of SystemLanding
     * @return project
     */
    public List<Project> getProject() {
        return project;
    }
    
    /**
     * Adds a project to the project list
     * @param p
     */
    public void addProject(Project p) {
    	project.add(p);
    }
    
 
    
    /**
     * Getter for the administrator of SystemLanding
     * @return admin
     */
    public Administrator getAdministrator() {
        return admin;
    }
    
     /**
      * Getter for the date of SystemLanding
      * @return date
      */
    public LocalDate getDate() {
    	return date;
    }
    
    /**
     * Calculates the affinity report between two groups
     * @param group1
     * @param group2
     * @return result of affinity report
     */
    public double giveAffinityReport(Group group1, Group group2) {
    	ArrayList<Project> setVoted1;
    	ArrayList<Project> setVoted2;
    	ArrayList<Project> setCreated1;
    	ArrayList<Project> setCreated2;
    	int size1 = 0;
    	int size2 = 0;
    	int n1 = 0;
    	int n2 = 0;
    	int result;
    	if(group1 == null || group2 == null) {
    		System.out.println("Group is missing.");
    		return -1;
    	}
    	
    	setVoted1 = group1.getProjectsVoted();
    	setVoted2 = group2.getProjectsVoted();
    	setCreated1 = group1.getProjectsCreated();
    	setCreated2 = group2.getProjectsCreated();
    	size1 = setCreated1.size();
    	size2 = setCreated2.size();
    	
    	for(Project p1: setVoted1) {    		
    		if (setCreated2.contains(p1)) {
    			n1++;
    		}
    	}
    	
    	for(Project p2: setVoted2) {    		
    		if (setCreated1.contains(p2)) {
    			n2++;
    		}
    	}
    	
    	result = (n1 + n2)/(size1 + size2);
    	
		return result;
    	
    }
    
    /**
     * Sends a notification to a user
     * @param n type of notification
     * @param u User to which the notification is sent
     */
    public void sendNotificationUser(TypeNotification n, User u) {
    	Notification notif = new Notification(n);
    	notif.setTitle();
    	notif.setBody();
    	
    	u.addNotification(notif);    	
    }
    
    /**
     * Sends a notification to the followers of a group
     * @param n notification to be sent
     * @param g group to which the notification is sent
     */
    public void sendNotificationGroup(TypeNotification n, Group g) {    	  	
    	for(User u: g.getFollower()) {
    		sendNotificationUser(n, u);
    	}
    }
    
    /**
     * Sends a notification to the administrator
     * @param n notification to be sent
     */
    public void sendNotificationAdmin(TypeNotification n) {    	  	
    	Notification notif = new Notification(n);
    	notif.setTitle();
    	notif.setBody();
    	
    	admin.addNotification(notif);
    }
    
    /**
     * Removes project from the project list
     * @param p project to be removed
     */
    public void removeProject(Project p) {
    	if (p.checkExpired() == true) {
    		project.remove(p);
    	}
    }
    
    
    
    public void save() {
    	try
        {    
            FileOutputStream file = new FileOutputStream(saveFile); 
            ObjectOutputStream out = new ObjectOutputStream(file); 
              
            out.writeObject(this); 
              
            out.close(); 
            file.close(); 
              
            System.out.println("The system has been saved"); 
  
        } 
          
        catch(IOException ex) 
        { 
            System.out.println("IOException is caught"); 
        }
    }
    
    public static SystemLanding load() {
    	SystemLanding syst = new SystemLanding();
    	
    	try
        {    
    		FileInputStream file = new FileInputStream(saveFile); 
            ObjectInputStream in = new ObjectInputStream(file); 
              
            syst = (SystemLanding)in.readObject();  
              
            in.close(); 
            file.close(); 
              
            System.out.println("The system has been loaded\n"); 
  
        }
    	
    	 catch (IOException ex) { 
             System.out.println("IOException is caught\n"); 
         } 
   
         catch (ClassNotFoundException ex) { 
             System.out.println("ClassNotFoundException is caught\n"); 
         }
    	
    	return syst;
    	
    }
}