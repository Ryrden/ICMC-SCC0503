package main.graph;

import main.graph.AbstractGraph;
import main.graph.Vertex;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DigraphList extends AbstractGraph {

    public List<List<Edge>> getAdjacencyList() {
        return adjacencyList;
    }

    public void setAdjacencyList(List<List<Edge>> adjacencyList) {
        this.adjacencyList = adjacencyList;
    }

    List<List<Edge>> adjacencyList;

    public DigraphList(List<Vertex> vertices) {
        super(vertices);
        initializeAdjacencyList();
    }

    private void initializeAdjacencyList() {
        setAdjacencyList(new ArrayList<>());
        for (int i = 0; i < getNumberOfVertices(); i++) {
            getAdjacencyList().add(new ArrayList<>());
        }
    }

    @Override
    public void addVertex(Vertex vertex) {
        getVertices().add(vertex);
    }

    @Override
    public void removeVertex(Vertex vertex) {
        if (!getVertices().contains(vertex)) {
            throw new IllegalArgumentException("Vertex not found");
        }
        getVertices().remove(vertex);
    }

    @Override
    public void addEdge(Vertex source, Vertex destination) {
        if (!edgeExists(source, destination)) {
            int sourceIndex = getVertices().indexOf(source);
            getAdjacencyList().get(sourceIndex).add(new Edge(destination));
        }
    }

    @Override
    public void addEdge(Vertex source, Vertex destination, int weight) {
        if (!edgeExists(source, destination)) {
            int sourceIndex = getVertices().indexOf(source);
            getAdjacencyList().get(sourceIndex).add(new Edge(destination, weight));
        }
    }

    @Override
    public void removeEdge(Vertex source, Vertex destination) {
        int sourceIndex = getVertices().indexOf(source);
        List<Edge> sourceEdges = getAdjacencyList().get(sourceIndex);
        sourceEdges.removeIf(edge -> edge.getDestination() == destination);
    }

    @Override
    public boolean edgeExists(Vertex source, Vertex destination) {
        int sourceIndex = getVertices().indexOf(source);
        List<Edge> sourceEdges = getAdjacencyList().get(sourceIndex);
        for (Edge edge : sourceEdges) {
            if (edge.getDestination() == destination) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean hasAnyEdge(Vertex vertex) {
        int vertexIndex = getVertices().indexOf(vertex);

        if (!getAdjacencyList().get(vertexIndex).isEmpty()) {
            return true;
        }

        for (int i = 0; i < getNumberOfVertices(); i++) {
            for (Edge edge : getAdjacencyList().get(i)) {
                if (edge.getDestination() == vertex) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public int getFirstConnectedVertexIndex(Vertex vertex) {
        int vertexIndex = getVertices().indexOf(vertex);
        if (getAdjacencyList().get(vertexIndex).isEmpty()) {
            return -1;
        } else {
            Vertex destinationVertex = getAdjacencyList().get(vertexIndex).get(0).getDestination();
            return getVertices().indexOf(destinationVertex);
        }
    }

    @Override
    public int getNextConnectedVertexIndex(Vertex vertex, int currentEdge) {
        int vertexIndex = getVertices().indexOf(vertex);
        int currentAdjacentVertexIndex = 0;
        Vertex currentDestinationVertex = getVertices().get(currentEdge);
        List<Edge> destinations = getAdjacencyList().get(vertexIndex);
        while (destinations.get(currentAdjacentVertexIndex).getDestination() != currentDestinationVertex) {
            currentAdjacentVertexIndex++;
        }
        currentAdjacentVertexIndex++;
        if (getAdjacencyList().get(vertexIndex).size() > currentAdjacentVertexIndex) {
            Vertex destinationVertex = getAdjacencyList().get(vertexIndex)
                    .get(currentAdjacentVertexIndex).getDestination();
            return getVertices().indexOf(destinationVertex);
        }
        return -1;
    }

    @Override
    public float getDistance(Vertex source, Vertex destination) {
        int vertexIndex = getVertices().indexOf(source);
        for (Edge edge : getAdjacencyList().get(vertexIndex)) {
            if (edge.getDestination() == destination) {
                return edge.getWeight();
            }
        }
        return -1;
    }

    @Override
    public Vertex getFirstConnectedVertex(Vertex vertex) {
        if (getAdjacencyList().get(getVertices().indexOf(vertex)).isEmpty()) {
            return null;
        } else {
            return getAdjacencyList().get(getVertices().indexOf(vertex)).get(0).getDestination();
        }
    }

    @Override
    public Vertex getNextConnectedVertex(Vertex source, Vertex currentConnection) {
        int vertexIndex = getVertices().indexOf(source);
        var currentAdjacentVertexIndex = 0;
        while (getAdjacencyList().get(vertexIndex).get(currentAdjacentVertexIndex).getDestination() != currentConnection) {
            currentAdjacentVertexIndex++;
        }
        currentAdjacentVertexIndex++;
        if (getAdjacencyList().get(vertexIndex).size() > currentAdjacentVertexIndex) {
            return getAdjacencyList().get(vertexIndex).get(currentAdjacentVertexIndex).getDestination();
        } else {
            return null;
        }
    }

    @Override
    public String toString() {
        var s = new StringBuilder();
        for (var i = 0; i < getNumberOfVertices(); i++) {
            s.append(i).append(": ");
            for (var j = 0; j < getAdjacencyList().get(i).size(); ++j) {
                s.append(getAdjacencyList().get(i).get(j).getWeight()).append(" ");
            }
            s.append("\n");
        }
        return s.toString();
    }

    @Override
    public void printInGraphviz(String fileName) {
    }
}