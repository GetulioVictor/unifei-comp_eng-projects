package br.unifei.edu.ecot12a.codegeass;

import java.util.ArrayList;
import java.util.List;

public class Government {
    private String type;
    private String leadership;
    private List<String> policies = new ArrayList<>();

    public void createLaws() {
        System.out.println("Creating new laws by " + leadership);
    }

    public void implementPolicies() {
        System.out.println("Implementing policies");
    }

    public void conductElections() {
        System.out.println("Conducting elections for " + type);
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getLeadership() {
        return leadership;
    }

    public void setLeadership(String leadership) {
        this.leadership = leadership;
    }

    public List<String> getPolicies() {
        return policies;
    }
}