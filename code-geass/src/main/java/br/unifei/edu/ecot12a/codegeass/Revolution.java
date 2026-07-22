package br.unifei.edu.ecot12a.codegeass;

import java.util.List;

public class Revolution {
    private String cause;
    private List<Character> leaders;
    private boolean publicSupport;

    public void start() {
        System.out.println("Starting revolution due to " + cause);
    }

    public void spreadPropaganda() {
        System.out.println("Spreading propaganda");
    }

    public void recruit() {
        System.out.println("Recruiting new members");
    }

    public String getCause() {
        return cause;
    }

    public void setCause(String cause) {
        this.cause = cause;
    }

    public List<Character> getLeaders() {
        return leaders;
    }

    public void setLeaders(List<Character> leaders) {
        this.leaders = leaders;
    }

    public boolean isPublicSupport() {
        return publicSupport;
    }

    public void setPublicSupport(boolean publicSupport) {
        this.publicSupport = publicSupport;
    }

    
}