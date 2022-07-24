package main.graph;

import java.util.List;

public class GraphList extends DigraphList {
    protected GraphList(List<Vertex> vertices) {
        super(vertices);
    }

    public GraphList() {
        super();
    }

    @Override
    public void addEdge(Vertex source, Vertex destination) {
        super.addEdge(source, destination);
        super.addEdge(destination, source);
    }

    @Override
    public void addEdge(Vertex source, Vertex destination, float weight) {
        super.addEdge(source, destination, weight);
        super.addEdge(destination, source, weight);
    }

    @Override
    public void removeEdge(Vertex source, Vertex destination) {
        super.removeEdge(source, destination);
        super.removeEdge(destination, source);
    }

    @Override
    public boolean hasAnyEdge(Vertex vertex) {
        int vertexIndex = getVertices().indexOf(vertex);
        return !getAdjacencyList().get(vertexIndex).isEmpty();
    }

    @Override
    public void removeVertex(Vertex vertex) {
        throw new UnsupportedOperationException();
    }

    public void lockEdge(Vertex source, Vertex destination, int lockID) {
        super.lockEdge(source, destination, lockID);
        super.lockEdge(destination, source, lockID);
    }
}
