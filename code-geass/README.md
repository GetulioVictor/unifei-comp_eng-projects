# Code Geass — Java OOP Project

A Java object-oriented modeling project inspired by the Code Geass anime universe.
Built as an academic exercise for the ECOT12A course at UNIFEI.

## Overview

The project models the political, military, and character dynamics of the Code Geass world using core OOP principles: inheritance, abstraction, interfaces, and design patterns (Strategy and Observer).

## Structure

Package: br.unifei.edu.ecot12a.codegeass

All classes live under this single package.

## Class Summary

### Characters

| Class | Description |
|---|---|
| Character | Abstract base class. Holds name, role, and faction. Methods: speak(), move() |
| Protagonist | Extends Character. Has loyalty, plan, geassActive. Methods: leadArmy(), executePlan(), update(geassState). Implements GeassObserver |
| Antagonist | Extends Character. Has rival, motivation. Methods: confrontProtagonist(), scheme() |
| Ally | Extends Character. Has trustLevel, motivationToHelp. Methods: provideSupport(), negotiateAlliance() |
| Spy | Extends Character. Has alias, disguiseSkill. Methods: infiltrate(), gatherInfo(), report() |
| Informant | Extends Character |

### Factions and Politics

| Class | Description |
|---|---|
| Faction | Has name, ideology, members. Methods: addMember(), removeMember(), declareWar(), developTechnology(Technology) |
| Alliance | Groups factions. Has members (List<Faction>), commonGoal. Methods: form(), dissolve(), renegotiateTerms() |
| Government | Represents a governing body |
| PoliticalSystem | Models the political structure |
| Realm | Represents a territory or nation |
| Revolution | Models a revolutionary movement |

### Military and Operations

| Class | Description |
|---|---|
| Battle | Has location, participants (List<Character>), result. Methods: start(), recordResult(), calculateLosses(type) |
| Mission | Represents a mission |
| Operation | Represents a military or covert operation |
| Headquarters | Has location, capacity, resources. Methods: relocate(), strengthenDefenses(), coordinateOperations() |
| KnightmareFrame | Has model, weaponry, speed. Methods: attack(), defend(), move() |
| StrategicPlanner | Plans strategy |

### Strategy Pattern

| Class/Interface | Description |
|---|---|
| Strategy | Interface. Methods: execute(), adjust() |
| OffensiveStrategy | Implements Strategy. Aggressive combat behavior |
| DefensiveStrategy | Implements Strategy. Defensive combat behavior |

### Observer Pattern

| Class/Interface | Description |
|---|---|
| GeassObserver | Interface. Implemented by characters that react to Geass state changes |
| Geass | Has power, restriction. Methods: activate(), deactivate(), checkRestriction(). Notifies observers |

### Technology and AI

| Class | Description |
|---|---|
| Technology | Has name, application, developer. Methods: innovate(), upgrade(), implement() |
| ArtificialIntelligence | Has name, capability, limitations. Methods: processData(), calculateProbabilities() |

## Design Patterns Used

- Strategy: OffensiveStrategy and DefensiveStrategy implement the Strategy interface, allowing combat behavior to be swapped at runtime.
- Observer: Geass acts as the subject, GeassObserver is the observer interface, and Protagonist receives Geass state updates via update(geassState).

## Requirements

- Java 8+
- Maven

## Build and Run

mvn compile
mvn exec:java -Dexec.mainClass="br.unifei.edu.ecot12a.codegeass.Main"

## Diagram

The UML class diagram is available in geass.dia (open with Dia Diagram Editor)
