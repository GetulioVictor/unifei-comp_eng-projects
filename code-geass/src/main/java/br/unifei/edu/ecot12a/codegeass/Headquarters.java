package br.unifei.edu.ecot12a.codegeass;

import java.util.List;

public class Headquarters {
    private String location;
    private int capacity;
    private List<String> resources; //tirar dps

    public void relocate() {
        System.out.println("Relocating headquarters to: " + location);
    }

    public void strengthenDefenses() {
        System.out.println("Strengthening defenses at HQ.");
    }

    public void coordinateOperations() {
        System.out.println("Coordinating operations with capacity: " + capacity);
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    public List<String> getResources() {
        return resources;
    }

    public void setResources(List<String> resources) {
        this.resources = resources;
    }

    
}