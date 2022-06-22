package com.main.answer;

public class Answer {
    private int ID;
    private String name;
    private String description;

    public Answer(int ID, String name, String description) {
        this.ID = ID;
        this.name = name;
        this.description = description;
    }

    public int getID() {
        return ID;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String toString() {
        return "Quest{\n\tID: " + ID + "\n\tName: " + name + "\n\tDescription: " + description + "\n}";
    }







}
