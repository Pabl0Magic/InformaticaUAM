package VoteLanding;

import es.uam.eps.sadp.grants.*;
import es.uam.eps.sadp.grants.GrantRequest.ProjectKind;

import java.io.*;

/**
 * Infrastructural class
 * 
 * @author miguel 	<miguel.arnaiz@estudiante.uam.es>
 * @author pablo 	<pablo.almarza@estudiante.uam.es>
 * @author carlos	<carlos.garciatoledano@estudiante.uam.es>
 *
 */
public class Infraestructural extends Project{
    private District district;
    private ImageKind image;

    enum ImageKind {
        PNG,
        JPG,
        JPEG
    }
    
    enum District {
    	Arganzuela,
    	Barajas,
    	Carabanchel,
    	Centro,
    	Chamartin,
    	Chamberi,
    	CiudadLineal,
    	FuencarralElPardo,
    	Hortaleza,
    	Latina,
    	MoncloaAravaca,
    	Moratalaz,
    	PuenteDeVallecas,
    	Retiro,
    	Salamanca,
    	SanBlasCanillejas,
    	Tetuan,
    	Usera,
    	Vicalvaro,
    	VillaDeVallecas,
    	Villaverde

    }
    
    public Infraestructural(District district, ImageKind image, String name, String desc, double requestedAmount) {
        super(name, desc, requestedAmount);
        this.district = district;
        this.image = image;   
    }

    /**
     * Getter for the district of a infraestructural project
     * @return district
     */
    public District getDistrict() {
        return district;
    }

    /**
     * Getter for the image king of a infraestructural project
     * @return imageKind
     */
    public ImageKind getImageKind() {
        return image;
    }
    
    
    /**
     * Sends a project to the external association 
     * 
     * @throws IOException
     * @throws InvalidRequestException
     */
    @Override
    public void sendExternalAssociation() throws InvalidRequestException, IOException{
    	try {
    		GrantRequest send = new ProjectSend(this, ProjectKind.Infrastructure);
    		CCId = CCGG.getGateway().submitRequest(send);
    	}catch (IOException error1) {
    		System.out.println(error1);
    	}catch(InvalidRequestException error2) {
    		System.out.println(error2);
    	}
    }
     
}

