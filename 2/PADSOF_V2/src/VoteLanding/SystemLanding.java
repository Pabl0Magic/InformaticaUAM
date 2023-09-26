package VoteLanding;
import java.util.*;
import java.io.*;
import java.time.LocalDate;
import VoteLanding.Notification.TypeNotification;
import VoteLanding.User.Acceptance;
import VoteLanding.User.State;
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
	private User currentUser;
	private static ArrayList<User> user;
    private static ArrayList<Group> group;
    private static ArrayList<Project> project;
    private static Administrator admin;
    private static LocalDate date;
    
    public SystemLanding() {
    	admin = new Administrator("Admin", "Admin1");    	
    	user = new ArrayList<User>();
    	group = new ArrayList<Group>();
    	project = new ArrayList<Project>();
    	date = ModifiableDate.getModifiableDate();

    }
    
    /**
     * Getter for the user list of SystemLanding
     * @return user
     */
    public static List<User> getUser() {
        return user;
    }
    
    /**
     * Adds a user to the user list
     * @param user
     */
    public static void addUser(User u) {
    	user.add(u);
    }
    
    /**
     * Getter for the group list of SystemLanding
     * @return group
     */
    public static List<Group> getGroup() {
        return group;
    }
    
    /**
     * Adds a group to the group list
     * @param group
     */
    public void addGroup(Group g) {
    	group.add(g);
    }
    
    /**
     * Getter for the project list of SystemLanding
     * @return project
     */
    public static List<Project> getProject() {
        return project;
    }
    
    /**
     * Adds a project to the project list
     * @param project
     */
    public static void addProject(Project p) {
    	project.add(p);
    }
    
 
    
    /**
     * Getter for the administrator of SystemLanding
     * @return admin
     */
    public static Administrator getAdministrator() {
        return admin;
    }
    
     /**
      * Getter for the date of SystemLanding
      * @return date
      */
    public static LocalDate getDate() {
    	return date;
    }
    
    /**
     * Calculates the affinity report between two groups
     * @param group1
     * @param group2
     * @return result of affinity report
     */
    public static double giveAffinityReport(Group group1, Group group2) {
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
    public static void sendNotificationUser(TypeNotification n, User u) {
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
    public static void sendNotificationGroup(TypeNotification n, Group g) {    	  	
    	for(User u: g.getFollower()) {
    		sendNotificationUser(n, u);
    	}
    }
    
    /**
     * Sends a notification to the administrator
     * @param n notification to be sent
     */
    public static void sendNotificationAdmin(TypeNotification n) {    	  	
    	Notification notif = new Notification(n);
    	notif.setTitle();
    	notif.setBody();
    	
    	admin.addNotification(notif);
    }
    
    /**
     * Removes project from the project list
     * @param p project to be removed
     */
    public static void removeProject(Project p) {
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
    /**
     * 
     */
    public void setCurrentUser(User u) {
    	this.currentUser = u;
    }
    
    /**
     * 
     */
    public User getCurrentUser() {
    	return currentUser;
    }
    
    /**
     * 
     * @param name
     * @param pass
     */
    public int login(String name, String pass) {
    	if(name.equals("") || pass.equals("")){
    		return 0;
    	}else if(name.equals(admin.getName())) {
    		if(pass.equals(admin.getPassword())) {
    			return 1;
    		}else {
    			return -1;
    		}
    	}
    	for(User u : getUser()) {
			if(u.getName().equals(name)) {
				if(u.getAcceptance().equals(Acceptance.Authorized)) {
					if(u.getPassword().equals(pass)) {
						u.setState(State.Online);
						this.setCurrentUser(u);
						return 1;
					}
					return -1;
				}
				return -2;
			}
    	}
    	return -3;
    }
    
    public int signup(String name, String dni, String pass) {	
		if(name.equals("") || pass.equals("") || dni.equals("")) {
			return 0;
		}else if(name.equals("Admin")) {
			return -2;
		}
		
		for(User u : SystemLanding.getUser()) {
			if(u.getDNI().equals(dni) || u.getName().equals(name)) {
				return -1;
			}
		}
		User newUser = new User(name, dni, pass);
		newUser.setAcceptance(Acceptance.Authorized);
		SystemLanding.addUser(newUser);
		return 1;
		
    }
    
    public Group searchGroup(String name){
    	ArrayList<Group> ret = new ArrayList<>();
    	for(Group g : SystemLanding.group) {
    		if(name.equals(g.getName())) {
    			return g;
    		}
    	}
    	return null;
    }
    
    
    
    public Project searchProject(String name) {
    	for(Project p : SystemLanding.project) {
    		if(name.equals(p.getName())) {
    			return p;
    		}
    	}
		return null;
    }
    
    public int createGroup(String name, String description) {
    	
    	if(name.equals("") || description.equals("")) {
    		return -1;
    	}
    	
    	for(Group g: SystemLanding.getGroup()) {
    		if(g.getName().equals(name)==true) {
    			return -2;
    		}
    	}
    	
    	Group gr = new Group(name, description, currentUser);
    	this.addGroup(gr);
    	return 0;
    	
    }
}