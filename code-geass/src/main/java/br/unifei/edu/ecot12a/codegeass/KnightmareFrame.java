package br.unifei.edu.ecot12a.codegeass;

public class KnightmareFrame {
    private String model;
    private String weaponry;
    private double speed;

    public KnightmareFrame(String model, String weaponry, double speed) {
        this.model = model;
        this.weaponry = weaponry;
        this.speed = speed;
    }

    public void attack() {
        System.out.println(model + " attacks with " + weaponry);
    }

    public void defend() {
        System.out.println(model + " is defending");
    }

    public void move() {
        System.out.println(model + " moves at speed " + speed);
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getWeaponry() {
        return weaponry;
    }

    public void setWeaponry(String weaponry) {
        this.weaponry = weaponry;
    }

    public double getSpeed() {
        return speed;
    }

    public void setSpeed(double speed) {
        this.speed = speed;
    }

    
}