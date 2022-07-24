package main.graph;

import java.util.Objects;

public class Vertex {
    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        if (Objects.equals(name, "")) {
            System.out.println("Name cannot be empty");
        }
        this.name = name;
    }

    public Vertex(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Vertex{" + "name='" + name + '\'' + '}';
    }
}
