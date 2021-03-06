package main.graph;

import java.util.List;

public abstract class AbstractGraph implements GraphInterface {
    protected static final int GRAPHVIZ_IMAGE_WIDTH = 2000;
    protected static final int GRAPHVIZ_IMAGE_HEIGTH = 2000;
    protected static final String GRAPHVIZ_FOLDER = "graphviz/";
    protected static final String GRAPHVIZ_FILE_EXTENSION = ".png";
    private int numberOfVertices;
    private List<Vertex> vertices;

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

    protected AbstractGraph(List<Vertex> vertices) {
        numberOfVertices = vertices.size();
        this.vertices = vertices;
    }
}
