package main.graph;

import java.util.Objects;

public class Vertex {
    private String name;
    private int inDegree;
    private int outDegree;

    public Vertex(String name) {
        this.name = name;
        inDegree = 0;
        outDegree = 0;
    }

    public int getInDegree() {
        return inDegree;
    }

    public void setInDegree(int inDegree) {
        this.inDegree = inDegree;
    }

    public int getOutDegree() {
        return outDegree;
    }

    public void setOutDegree(int outDegree) {
        this.outDegree = outDegree;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        if (Objects.equals(name, "")) {
            System.out.println("Name cannot be empty");
        }
        this.name = name;
    }

    public void incrementInDegree() {
        inDegree++;
    }

    public void incrementOutDegree() {
        outDegree++;
    }

    public void decrementInDegree() {
        inDegree--;
    }

    public void decrementOutDegree() {
        outDegree--;
    }

    @Override
    public String toString() {
        return "Vertex{" + "name='" + name + '\'' + '}';
    }


}
