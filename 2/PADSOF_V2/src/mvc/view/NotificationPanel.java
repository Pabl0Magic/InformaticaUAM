package mvc.view;

import java.awt.FlowLayout;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JPanel;

import VoteLanding.Notification;
import VoteLanding.SystemLanding;

public class NotificationPanel extends JPanel{

	private GUIProject gui;

	public NotificationPanel(GUIProject gui) {
		ArrayList<Notification> notification;
		
		this.gui = gui;
	
		/* Show notifications*/
		JPanel notifPanel = new JPanel(new FlowLayout());
		DefaultListModel<Notification> notif = new DefaultListModel<Notification>();
		JList<Notification> notifList = new JList<Notification>(notif);
		
		if(gui.getController().getSl().getCurrentUser() == null) {
			notification = SystemLanding.getAdministrator().getNotification();
			
			for(Notification n: notification) {
				notif.addElement(n);
			}
			
		} else {
			notification = gui.getController().getSl().getCurrentUser().getNotification();
			for(Notification n: notification) {
				notif.addElement(n);
			}
		}
	
	}
	
}
