package main.graph;

import java.text.DecimalFormat;
import java.util.logging.Logger;

public class FloydWarshallTraversal extends TraversalStrategy {
    private static final Logger LOGGER = Logger.getLogger("FloydWarshallTraversal.class");

    public float[][] getDistanceMatrix() {
        return distanceMatrix;
    }

    public void setDistanceMatrix(float[][] distanceMatrix) {
        this.distanceMatrix = distanceMatrix;
    }

    private float[][] distanceMatrix;

    public FloydWarshallTraversal(AbstractGraph graph) {
        super(graph);
        distanceMatrix = new float[graph.getNumberOfVertices()][graph.getNumberOfVertices()];
    }

    Vertex centralVertex;
    Vertex peripheralVertex;

    @Override
    public void traverseGraph(Vertex source) {
        for (int i = 0; i < getGraph().getNumberOfVertices(); i++) {
            for (int j = 0; j < getGraph().getNumberOfVertices(); j++) {
                Vertex origin = getGraph().getVertices().get(i);
                Vertex destination = getGraph().getVertices().get(j);
                if (getGraph().edgeExists(origin, destination)) {
                    distanceMatrix[i][j] = getGraph().getDistance(origin, destination);
                } else {
                    distanceMatrix[i][j] = Float.POSITIVE_INFINITY;
                }
            }
        }
        for (int k = 0; k < getGraph().getNumberOfVertices(); k++) {
            for (int i = 0; i < getGraph().getNumberOfVertices(); i++) {
                for (int j = 0; j < getGraph().getNumberOfVertices(); j++) {
                    float newDistance = distanceMatrix[i][k] + distanceMatrix[k][j];
                    if (newDistance < distanceMatrix[i][j]) {
                        distanceMatrix[i][j] = newDistance;
                    }
                }
            }
        }
        //printDistanceMatrix();
    }

    private void printDistanceMatrix() {
        var decimalFormat = new DecimalFormat("00.00");
        var distanceMatrixString = new StringBuilder();
        distanceMatrixString.append('\n');
        for (float[] row : distanceMatrix) {
            for (float value : row) {
                distanceMatrixString.append(decimalFormat.format(value));
                distanceMatrixString.append(' ');
            }
            distanceMatrixString.append('\n');
        }
        LOGGER.info(distanceMatrixString.toString());
    }

    public Vertex getFarthestVertexFromPeripheral() {
        int peripheralIndex = getGraph().getVertices().indexOf(peripheralVertex);

        Vertex farthestVertex = null;
        int farthestVertexIndex = 0;
        float maxDistance = Float.NEGATIVE_INFINITY;
        for (int column = 0; column < distanceMatrix.length; column++) {
            if (column == peripheralIndex) {
                continue;
            }
            if (maxDistance < distanceMatrix[peripheralIndex][column]) {
                maxDistance = distanceMatrix[peripheralIndex][column];
                farthestVertexIndex = column;
            }
        }
        farthestVertex = getGraph().getVertices().get(farthestVertexIndex);
        return farthestVertex;
    }

    public Vertex getPeripheralVertex() {
        Vertex peripheralVertex = null;
        int peripheralVertexIndex = 0;
        float[] maximumCostVertexes = getMaximumCostVertexes();

        float max = Float.NEGATIVE_INFINITY;
        for (int i = 0; i < maximumCostVertexes.length; i++) {
            if (max < maximumCostVertexes[i]) {
                max = maximumCostVertexes[i];
                peripheralVertexIndex = i;
            }
        }

        peripheralVertex = getGraph().getVertices().get(peripheralVertexIndex);
        return peripheralVertex;
    }

    public Vertex getCentralVertex() {
        Vertex centralVertex = null;
        int centralVertexIndex = 0;
        float[] maximumCostVertexes = getMaximumCostVertexes();
        float min = Float.POSITIVE_INFINITY;
        for (int i = 0; i < maximumCostVertexes.length; i++) {
            if (min > maximumCostVertexes[i]) {
                min = maximumCostVertexes[i];
                centralVertexIndex = i;
            }
        }

        centralVertex = getGraph().getVertices().get(centralVertexIndex);
        return centralVertex;
    }

    private float[] getMaximumCostVertexes() {
        float[] maximumCostVertexes = new float[distanceMatrix.length];

        for (int column = 0; column < distanceMatrix[0].length; column++) {
            float maxDistance = Float.NEGATIVE_INFINITY;
            for (int row = 0; row < distanceMatrix.length; row++) {
                if (distanceMatrix[row][column] > maxDistance) {
                    maxDistance = distanceMatrix[row][column];
                }
            }
            maximumCostVertexes[column] = maxDistance;
        }
        return maximumCostVertexes;
    }
}