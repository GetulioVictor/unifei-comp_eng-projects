package br.unifei.edu.ecot12a.codegeass;

public class Realm {
    private String name;
    private String territory;
    private int population;

    public void expandTerritory() {
        System.out.println("Expanding territory of " + name);
    }

    public void signTreaty() {
        System.out.println(name + " signing treaty");
    }

    public void mobilizeArmy() {
        System.out.println(name + " mobilizing army");
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getTerritory() {
        return territory;
    }

    public void setTerritory(String territory) {
        this.territory = territory;
    }

    public int getPopulation() {
        return population;
    }

    public void setPopulation(int population) {
        this.population = population;
    }

    
}