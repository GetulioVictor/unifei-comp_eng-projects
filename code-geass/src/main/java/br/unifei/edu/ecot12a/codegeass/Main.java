package br.unifei.edu.ecot12a.codegeass;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Create Realm
        Realm realm = new Realm();
        realm.setName("Pendragon");
        realm.setTerritory("Britannia");
        realm.setPopulation(1000000);

        // Create Government
        Government government = new Government();
        government.setType("Monarchy");
        government.setLeadership("Emperor Charles");

        // Create Revolution
        Revolution revolution = new Revolution();
        revolution.setCause("Freedom");
        revolution.setPublicSupport(true);

        // Create Protagonist
        Protagonist protagonist = new Protagonist("Lelouch", "Britannia", "High", "Liberate Japan");
        protagonist.setGeassActive(true);

        // Create Antagonist
        Antagonist antagonist = new Antagonist("Suzaku", "Britannia", "Lelouch", "Maintain order");
        
        // Create PoliticalSystem
        PoliticalSystem politicalSystem = new PoliticalSystem();
        List<Realm> realms = new ArrayList<>();
        realms.add(realm);
        politicalSystem.setRealms(realms);

        // Create StrategicPlanner
        StrategicPlanner strategicPlanner = new StrategicPlanner();
        strategicPlanner.setPlans(new ArrayList<>());
        strategicPlanner.setResources(new HashMap<>());
        
        // Demonstrate interactions
        politicalSystem.manageRealm(realm);
        politicalSystem.implementPolicy(government, "New Tax Law");
        politicalSystem.suppressRevolution(government, revolution);
        politicalSystem.mobilizeForces(realm);
        politicalSystem.negotiatePeace(government, revolution);

        strategicPlanner.developPlan("Britannia", List.of("Overthrow the emperor", "Free the colonies"));
        strategicPlanner.allocateResources("Plan A", "Soldiers", 1000);
        strategicPlanner.analyzePoliticalSystem(politicalSystem);
        strategicPlanner.executePlan("Plan A");

        // Demonstrate Protagonist and Antagonist
        protagonist.leadArmy();
        protagonist.executePlan();
        antagonist.confrontProtagonist();
        antagonist.scheme();

        // Anonymous Mission example
        Mission mission = new Mission() {
            @Override
            public void start() {
                System.out.println("Mission starting...");
            }

            @Override
            public void complete() {
                System.out.println("Mission completed!");
            }

            @Override
            public void fail() {
                System.out.println("Mission failed...");
            }

            @Override
            public String getObjective() {
                return "Capture the royal palace";
            }
        };

        mission.start();
        mission.complete();
        strategicPlanner.reviewResults(mission);
    }
}