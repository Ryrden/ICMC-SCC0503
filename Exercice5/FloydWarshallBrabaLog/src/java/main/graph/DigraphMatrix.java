package main.graph;

import guru.nidi.graphviz.engine.Graphviz;
import guru.nidi.graphviz.model.Label;
import guru.nidi.graphviz.model.MutableGraph;

import java.io.File;
import java.util.List;

import static guru.nidi.graphviz.model.Factory.mutGraph;
import static guru.nidi.graphviz.model.Factory.mutNode;

public class DigraphMatrix extends AbstractGraph {
    private Edge[][] adjacencyMatrix;

    public Edge[][] getAdjacencyMatrix() {
        return adjacencyMatrix.clone();
    }

    private void setAdjacencyMatrix(Edge[][] adjacencyMatrix) {
        this.adjacencyMatrix = adjacencyMatrix;
    }

    public DigraphMatrix(List<Vertex> vertices) {
        super(vertices);
        initializeAdjacencyMatrix();
    }

    private void initializeAdjacencyMatrix() {
        setAdjacencyMatrix(new
                Edge[getNumberOfVertices()][getNumberOfVertices()]);
        for (int i = 0; i < getNumberOfVertices(); i++) {
            for (int j = 0; j < getNumberOfVertices(); j++) {
                setEdge(i, j, null);
            }
        }
    }

    @Override
    public void addVertex(Vertex vertex) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void removeVertex(Vertex vertex) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void addEdge(Vertex source, Vertex destination) {
        addEdge(source, destination, 1);
    }

    @Override
    public void addEdge(Vertex source, Vertex destination, int weight) {
        if (!edgeExists(source, destination)) {
            int sourceIndex = getVertices().indexOf(source);
            int destinationIndex = getVertices().indexOf(destination);
            setEdge(sourceIndex, destinationIndex, new Edge(destination, weight));
        }
    }

    public void removeEdge(Vertex source, Vertex destination) {
        if (edgeExists(source, destination)) {
            int sourceIndex = getVertices().indexOf(source);
            int destinationIndex = getVertices().indexOf(destination);
            setEdge(sourceIndex, destinationIndex, null);
        }
    }

    @Override
    public boolean edgeExists(Vertex source, Vertex destination) {
        int sourceIndex = getVertices().indexOf(source);
        int destinationIndex = getVertices().indexOf(destination);
        return adjacencyMatrix[sourceIndex][destinationIndex] != null;
    }

    @Override
    public boolean hasAnyEdge(Vertex vertex) {
        for (int i = 0; i < getNumberOfVertices(); i++) {
            if (edgeExists(vertex, getVertices().get(i))) {
                return true;
            }
        }
        return false;
    }

    @Override
    public int getFirstConnectedVertexIndex(Vertex vertex) {
        return getNextConnectedVertexIndex(vertex, 0);
    }

    @Override
    public int getNextConnectedVertexIndex(Vertex vertex, int currentEdge) {
        for (int i = currentEdge; i < getNumberOfVertices(); i++) {
            if (edgeExists(vertex, getVertices().get(i))) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public void printInGraphviz(String fileName) {
        MutableGraph g = mutGraph("example1Digraph").setDirected();

        for (var i = 0; i < getNumberOfVertices(); ++i) {
            for (var j = 0; j < getNumberOfVertices(); ++j) {
                if (edgeExists(getVertices().get(i), getVertices().get(j))) {
                    float weight = adjacencyMatrix[i][j].getWeight();
                    g.add(mutNode(getVertices().get(i).getName()).addLink((mutNode(getVertices().get(j).getName())).add(Label.of(String.valueOf(weight)))));
                }
            }
        }
        Graphviz.fromGraph(g).targetSize(GRAPHVIZ_IMAGE_WIDTH, GRAPHVIZ_IMAGE_HEIGTH).renderToFile(new File(GRAPHVIZ_FOLDER + fileName + GRAPHVIZ_FILE_EXTENSION));
    }

    @Override
    public float getDistance(Vertex source, Vertex destination) {
        int sourceIndex = getVertices().indexOf(source);
        int destinationIndex = getVertices().indexOf(destination);
        var edge = getAdjacencyMatrix()[sourceIndex][destinationIndex];

        if (edge == null) return -1;

        return getAdjacencyMatrix()[sourceIndex][destinationIndex].getWeight();
    }

    @Override
    public Vertex getFirstConnectedVertex(Vertex vertex) {
        if (!hasAnyEdge(vertex)) {
            return null;
        } else {
            var currentVertexIndex = 0;
            Vertex connected;
            do {
                connected = getVertices().get(currentVertexIndex++);
            } while (!edgeExists(vertex, connected));
            return connected;
        }
    }

    @Override
    public Vertex getNextConnectedVertex(Vertex source, Vertex currentConnection) {
        Vertex newConnection;
        for (int i = getVertices().indexOf(currentConnection) + 1; i < getNumberOfVertices(); i++) {
            newConnection = getVertices().get(i);
            if (edgeExists(source, newConnection)) {
                return newConnection;
            }
        }
        return null;
    }

    private void setEdge(int source, int destination, Edge edge) {
        adjacencyMatrix[source][destination] = edge;
    }

    @Override
    public String toString() {
        var s = new StringBuilder();
        for (var i = 0; i < getNumberOfVertices(); i++) {
            s.append(i).append(": ");
            for (var j = 0; j < getNumberOfVertices(); ++j) {
                if (edgeExists(getVertices().get(i), getVertices().get(j))) {
                    s.append(getAdjacencyMatrix()[i][j].getWeight()).append(" ");
                } else {
                    s.append(0.0 + " ");
                }
            }
            s.append("\n");
        }
        return s.toString();
    }
}