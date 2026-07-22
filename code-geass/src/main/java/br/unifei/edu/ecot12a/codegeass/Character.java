package br.unifei.edu.ecot12a.codegeass;

public abstract class Character {
    private String name;
    private String role;
    private String faction;

    public Character(String name, String role, String faction) {
        this.name = name;
        this.role = role;
        this.faction = faction;
    }
    
    public void speak() {
        System.out.println(name + " speaks about their role as " + role);
    }
    
    public void move() {
        System.out.println(name + " moves strategically within " + faction);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public String getFaction() {
        return faction;
    }

    public void setFaction(String faction) {
        this.faction = faction;
    }

    
    
    // Getters and setters
}