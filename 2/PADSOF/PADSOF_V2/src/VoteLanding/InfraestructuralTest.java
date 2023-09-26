package VoteLanding;

import static org.junit.Assert.*;

import org.junit.Test;

import VoteLanding.Infraestructural.District;
import VoteLanding.Infraestructural.ImageKind;

public class InfraestructuralTest {

	@Test
	public void testGetDistrict() {
		Infraestructural i1 = new Infraestructural(District.Barajas, ImageKind.PNG, "Bridge", "We will create a bridge in order to cross the river", 250);
		
		District dist = i1.getDistrict();
		assertEquals(District.Barajas, dist);
	}

	@Test
	public void testGetImageKind() {
		Infraestructural i1 = new Infraestructural(District.Barajas, ImageKind.PNG, "Bridge", "We will create a bridge in order to cross the river", 250);
		
		ImageKind image = i1.getImageKind();
		assertEquals(ImageKind.PNG, image);
	}
}
