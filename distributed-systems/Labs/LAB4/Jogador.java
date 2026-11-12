import java.io.*;

public class Jogador implements Serializable {
    private String name;
    private int age;
    private int sex;
    private String sport;

    public Jogador(String name, int age, int sex, String sport) {
        this.name = name;
        this.age = age;
        this.sex = sex;
        this.sport = sport;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public int getSex() {
        return sex;
    }

    public String getSport() {
        return sport;
    }

    public void reset() {
        name = null;
        age = 0;
        sex = 0;
        sport = null;
    }

    public String toString() {
        String s;
        if (sex == Bola.MALE)
            s = "Male";
        else if (sex == Bola.FEMALE)
            s = "Female";
        else
            s = "Male or Female";
        return "Jogador: " + name + ", Age: " + age
                + ", Sex: " + s + ", Sport: " + sport;
    }
}
