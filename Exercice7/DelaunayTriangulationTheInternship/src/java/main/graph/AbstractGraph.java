package main.graph;

import main.dungeon.Room;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


public abstract class AbstractGraph implements GraphInterface, Cloneable {
    protected static final int GRAPHVIZ_IMAGE_WIDTH = 400;
    protected static final String GRAPHVIZ_FOLDER = "example/";
    protected static final String GRAPHVIZ_FILE_EXTENSION = ".png";
    private int numberOfVertices;
    private List<Vertex> vertices;
    private Room entrance;
    private Room exit;

    public Room getEntrance() {
        return entrance;
    }

    public void setEntrance(Room entrance) {
        this.entrance = entrance;
    }

    public Room getExit() {
        return exit;
    }

    public void setExit(Room exit) {
        this.exit = exit;
    }

    protected AbstractGraph(List<Vertex> vertices) {
        numberOfVertices = vertices.size();
        this.vertices = vertices;
    }

    protected AbstractGraph() {
        vertices = new ArrayList<>();
        numberOfVertices = 0;
    }

    public int getNumberOfVertices() {
        return numberOfVertices;
    }

    public void setNumberOfVertices(int numberOfVertices) {
        this.numberOfVertices = numberOfVertices;
    }

    public List<Vertex> getVertices() {
        return vertices;
    }

    protected void setVertices(List<Vertex> vertices) {
        this.vertices = vertices;
    }

    public void addVertex(Vertex vertex) {
        vertices.add(vertex);
        numberOfVertices = vertices.size();
    }

    public void addEdge(Vertex source, Vertex destination) {
        addEdge(source, destination, 1);
    }

    public void addEdge(Vertex source, Vertex destination, float weight) {
        addEdge(source, destination, weight);
    }

    @Override
    protected AbstractGraph clone() throws CloneNotSupportedException {
        var graphClone = (AbstractGraph) super.clone();
        graphClone.setNumberOfVertices(this.getNumberOfVertices());
        graphClone.setVertices(new ArrayList<>(this.getVertices()));
        return graphClone;
    }

    public float calcEuclidianDistance(Room source, Room destination) {
        int x1 = (int) source.getRoom().getX();
        int y1 = (int) source.getRoom().getY();
        int x2 = (int) destination.getRoom().getX();
        int y2 = (int) destination.getRoom().getY();
        return (float) Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
    }
}
