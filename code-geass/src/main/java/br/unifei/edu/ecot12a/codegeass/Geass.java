package br.unifei.edu.ecot12a.codegeass;

public class Geass {
    private String power;
    private String restriction;

    public Geass(String power, String restriction) {
        this.power = power;
        this.restriction = restriction;
    }
    
    public void activate() {
        System.out.println("Activating Geass power: " + power);
    }
    
    public void deactivate() {
        System.out.println("Deactivating Geass power");
    }
    
    public boolean checkRestriction() {
        System.out.println("Checking restriction: " + restriction);
        return true; // Placeholder logic
    }

    public String getPower() {
        return power;
    }

    public void setPower(String power) {
        this.power = power;
    }

    public String getRestriction() {
        return restriction;
    }

    public void setRestriction(String restriction) {
        this.restriction = restriction;
    }

}