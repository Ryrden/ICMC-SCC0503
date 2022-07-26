package main.graph;


import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.logging.Level;


public class DigraphMatrix extends AbstractGraph {
    private Edge[][] adjacencyMatrix;

    public DigraphMatrix(List<Vertex> vertices) {
        super(vertices);
        initializeAdjacencyMatrix();
    }

    public DigraphMatrix() {
        super();
        initializeAdjacencyMatrix();
    }

    public Edge[][] getAdjacencyMatrix() {
        return adjacencyMatrix.clone();
    }

    private void setAdjacencyMatrix(Edge[][] adjacencyMatrix) {
        this.adjacencyMatrix = adjacencyMatrix;
    }

    private void initializeAdjacencyMatrix() {
        setAdjacencyMatrix(new Edge[getNumberOfVertices()][getNumberOfVertices()]);
        for (int i = 0; i < getNumberOfVertices(); i++) {
            for (int j = 0; j < getNumberOfVertices(); j++) {
                setEdge(i, j, null);
            }
        }
    }

    public void addEdge(Vertex source, Vertex destination, float value) {
        if (!edgeExists(source, destination)) {
            int sourceIndex = getVertices().indexOf(source);
            int destinationIndex = getVertices().indexOf(destination);
            setEdge(sourceIndex, destinationIndex, new Edge(destination, value));
        }
    }

    @Override
    public void addVertex(Vertex vertex) {
        addNewVertexInAdjacencyMatrix();
        super.addVertex(vertex);
    }

    private void addNewVertexInAdjacencyMatrix() {
        Edge[][] matrix = getAdjacencyMatrix();
        Edge[][] newMatrix = new Edge[matrix.length + 1][matrix.length + 1];
        int numberOfVertices = getNumberOfVertices();

        for (int i = 0; i < numberOfVertices; i++) {
            System.arraycopy(matrix[i], 0, newMatrix[i], 0, numberOfVertices);
        }
        for (int i = 0; i < numberOfVertices; i++) {
            newMatrix[i][numberOfVertices] = null;
            newMatrix[numberOfVertices][i] = null;
        }

        setAdjacencyMatrix(newMatrix);
    }

    @Override
    public void removeVertex(Vertex vertex) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void addEdge(Vertex source, Vertex destination) {
        addEdge(source, destination, 1);
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

    public List<Vertex> getAllConnectedVertex(Vertex vertex) {
        if (getAdjacencyMatrix().length == 0)
            return Collections.emptyList();
        var connectedVertices = new ArrayList<Vertex>();
        int vertexIndex = getVertices().indexOf(vertex);
        for(Edge edge : getAdjacencyMatrix()[vertexIndex]) {
            if (edge != null)
                connectedVertices.add(edge.getDestination());
        }
        return connectedVertices;
    }

    @Override
    public void lockEdge(Vertex source, Vertex destination, int lockID) {
        // TODO document why this method is empty
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
