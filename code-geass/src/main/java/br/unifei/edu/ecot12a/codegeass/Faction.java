package br.unifei.edu.ecot12a.codegeass;

import java.util.List;
import java.util.ArrayList;

public class Faction {
    private String name;
    private String ideology;
    private List<Character> members = new ArrayList<>();

    public Faction(String name, String ideology) {
        this.name = name;
        this.ideology = ideology;
    }

    public void addMember(Character member) {
        members.add(member);
        System.out.println(member.getName() + " has joined " + name);
    }

    public void removeMember(Character member) {
        members.remove(member);
        System.out.println(member.getName() + " has left " + name);
    }

    public void declareWar() {
        System.out.println(name + " has declared war based on " + ideology);
    }

    public void developTechnology(Technology technology) {
        System.out.println(name + " is developing " + technology.getName());
        technology.innovate();
    }
}
