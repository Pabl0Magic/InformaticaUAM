package pr3.traffic.licenses;
import pr3.traffic.vehicles.*;
import pr3.traffic.drivers.*;

public class TesterLicense {
    private void testYoungerThan18CannotHavePermitA() {
        Person ann= new Person("Ann Smith", 17);
        License c= new License(PermitKind.A);
        System.out.println("Test: YoungerThan18CannotHavePermitA");
        System.out.println(c);
        System.out.println(ann.setLicense(c));
        // should return false, since Ann is not 18 years old
    }
    private void testYoungerThan23CannotHavePermitC1() {
        Person ann= new Person("Ann Smith", 19);
        License c= new License(PermitKind.A, PermitKind.C1);
        System.out.println("=================\nTest: YoungerThan23CannotHavePermitC1");
        System.out.println(c);
        System.out.println(ann.setLicense(c));
        // should return false, since Ann is not 23 years old
    }
    private void testLicenseForVehicleKind() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.A, PermitKind.C1));
        Car c= new Car("Fiat 500x", 2019, "1245 HYN", true, ann);
        System.out.println("=================\nTest: LicenseForVehicleKind");
        System.out.println(c);
        // Ann is not the driver, since it has no car permit
        ann.getLicense().addPermit(PermitKind.B);
        c.setDriver(ann);
        System.out.println(c);
        // Now she is
        System.out.println(ann.getLicense());
        // license
    }

    private void testLicenseCarDriverFalse() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.C1));
        Car c= new Car("Fiat 500x", 2019, "1245 HYN", true, ann);
        System.out.println("=================\nTest: testLicenseCarDriverFalse");
        System.out.println(c);
        //Set driver but does not have the corresponding permit
        c.setDriver(ann);
        System.out.println(c);
        // should return false, Ann has not pemit B
    }

    private void testLicenseMotoDriverTrue() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.B, PermitKind.C1));
        Motorcycle c = new Motorcycle("Harley Davidson", 2019, "1234 ABC", true);
        System.out.println("=================\nTest: testLicenseMotoDriverTrue");
        System.out.println(c);
        // Ann is not the driver, since it has no motorcycle permit
        ann.getLicense().addPermit(PermitKind.A);
        c.setDriver(ann);
        System.out.println(c);
        // Now she is
        System.out.println(ann.getLicense());
        // license
    }

    private void testLicenseMotoDriverFalse() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.C1));
        Motorcycle c = new Motorcycle("Harley Davidson", 2019, "1234 ABC", true);
        System.out.println("=================\nTest: testLicenseMotoDriverFalse");
        System.out.println(c);
        //Set driver but does not have the corresponding permit
        c.setDriver(ann);
        System.out.println(c);
        // should be still not registered, Ann has not pemit A
    }

    private void testLicenseTruckDriverTrue() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.B, PermitKind.A));
        Truck c = new Truck("Renault 2000", 2019, "1245 HYN", 2);
        System.out.println("=================\nTest: testLicenseMotoDriverTrue");
        System.out.println(c);
        // Ann is not the driver, since it has no motorcycle permit
        ann.getLicense().addPermit(PermitKind.C1);
        c.setDriver(ann);
        System.out.println(c);
        // Now she is
        System.out.println(ann.getLicense());
        // license
    }

    private void testLicenseTruckDriverFalse() {
        Person ann= new Person("Ann Smith", 24);
        ann.setLicense(new License(PermitKind.A));
        Truck c = new Truck("Renault 2000", 2019, "1245 HYN", 2);
        System.out.println("=================\nTest: testLicenseTruckDriverFalse");
        System.out.println(c);
        //Set driver but does not have the corresponding permit
        c.setDriver(ann);
        System.out.println(c);
        // should be still not registered, Ann has not pemit C1
    }

    public static void main(String[] args) {
        TesterLicense tap3= new TesterLicense();
        tap3.testYoungerThan18CannotHavePermitA();
        tap3.testYoungerThan23CannotHavePermitC1();
        tap3.testLicenseForVehicleKind();
        tap3.testLicenseCarDriverFalse();
        tap3.testLicenseMotoDriverFalse();
        tap3.testLicenseMotoDriverTrue();
        tap3.testLicenseTruckDriverFalse();
        tap3.testLicenseTruckDriverTrue();
        
    }
}