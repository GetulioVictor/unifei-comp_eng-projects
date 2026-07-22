package br.unifei.edu.ecot12a.codegeass;

import java.util.List;
import java.util.Map;

public class StrategicPlanner {
    private List<String> plans;
    private Map<String, Integer> resources;
    private List<Mission> activeMissions;

    public void developPlan(String target, List<String> objectives) {
        plans.add("Plan for " + target);
        System.out.println("Developing plan for " + target);
    }

    public void allocateResources(String plan, String resource, Integer amount) {
        resources.put(resource, resources.getOrDefault(resource, 0) + amount);
        System.out.println("Allocating " + amount + " " + resource + " to " + plan);
    }

    public void analyzePoliticalSystem(PoliticalSystem system) {
        System.out.println("Analyzing political system");
    }

    public void executePlan(String plan) {
        System.out.println("Executing plan: " + plan);
    }

    public void reviewResults(Mission mission) {
        System.out.println("Reviewing results of mission with objective: " + mission.getObjective());
    }

    public List<String> getPlans() {
        return plans;
    }

    public void setPlans(List<String> plans) {
        this.plans = plans;
    }

    public Map<String, Integer> getResources() {
        return resources;
    }

    public void setResources(Map<String, Integer> resources) {
        this.resources = resources;
    }

    public List<Mission> getActiveMissions() {
        return activeMissions;
    }

    public void setActiveMissions(List<Mission> activeMissions) {
        this.activeMissions = activeMissions;
    }

    
}
