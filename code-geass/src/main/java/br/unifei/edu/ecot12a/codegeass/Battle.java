package br.unifei.edu.ecot12a.codegeass;

import java.util.List;

public class Battle {
    private String location;
    private List<Character> participants;
    private String result;

    public void start() {
        System.out.println("Battle starts at " + location);
    }

    public void recordResult() {
        System.out.println("Recording battle result: " + result);
    }

    public void calculateLosses(String type) {
        System.out.println("Calculating losses for: " + type);
    }

    public String getLocation() {
        return location;
    }

    public void setLocation(String location) {
        this.location = location;
    }

    public List<Character> getParticipants() {
        return participants;
    }

    public void setParticipants(List<Character> participants) {
        this.participants = participants;
    }

    public String getResult() {
        return result;
    }

    public void setResult(String result) {
        this.result = result;
    }

    
}