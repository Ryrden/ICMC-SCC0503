package main;

import main.graph.DigraphMatrix;
import main.graph.FloydWarshallTraversal;
import main.graph.Vertex;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int vertexNumber = scanner.nextInt();
        scanner.nextLine();
        ArrayList<Vertex> cartesianMap = new ArrayList<>();
        for (int i = 0; i < vertexNumber; i++) {
            String line = scanner.nextLine();
            int x = Integer.parseInt(line.split(",")[0]);
            int y = Integer.parseInt(line.split(",")[1]);
            Vertex point = new Vertex(x, y);
            cartesianMap.add(point);
        }
        DigraphMatrix digraphMatrix = new DigraphMatrix(cartesianMap);
        int edgeNumber = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < edgeNumber; i++) {
            String line = scanner.nextLine();

            int xOrigin = Integer.parseInt(line.split("[,:]")[0]);
            int yOrigin = Integer.parseInt(line.split("[,:]")[1]);
            int xDestination = Integer.parseInt(line.split("[,:]")[2]);
            int yDestination = Integer.parseInt(line.split("[,:]")[3]);

            Vertex pointOrigin = new Vertex(xOrigin, yOrigin);
            Vertex pointDestination = new Vertex(xDestination, yDestination);
            int weight = (int) pointOrigin.euclideanDistance(pointDestination);

            digraphMatrix.addEdge(pointOrigin, pointDestination,weight);
        }
        Vertex originVertex = new Vertex(0, 0);
        FloydWarshallTraversal floydWarshallTraversal = new FloydWarshallTraversal(digraphMatrix);
        floydWarshallTraversal.traverseGraph(originVertex);

        float[][] distanceMatrix = floydWarshallTraversal.getDistanceMatrix();
        Vertex centralVertex = getCentralVertex(distanceMatrix, digraphMatrix);
        Vertex peripheralVertex = getPeripheralVertex(distanceMatrix, digraphMatrix);
        Vertex farthestVertexFromPeripheral = getFarthestVertexFromPeripheral(distanceMatrix,digraphMatrix, peripheralVertex);

        System.out.println(centralVertex);
        System.out.println(peripheralVertex);
        System.out.print(farthestVertexFromPeripheral);
    }

    private static Vertex getFarthestVertexFromPeripheral(float[][] distanceMatrix,DigraphMatrix digraphMatrix, Vertex peripheralVertex) {
        int peripheralIndex = digraphMatrix.getVertices().indexOf(peripheralVertex);

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
        farthestVertex = digraphMatrix.getVertices().get(farthestVertexIndex);
        return farthestVertex;
    }

    private static Vertex getPeripheralVertex(float[][] distanceMatrix, DigraphMatrix digraphMatrix) {
        Vertex peripheralVertex = null;
        int peripheralVertexIndex = 0;
        float[] maximumCostVertexes = getMaximumCostVertexes(distanceMatrix);

        float max = Float.NEGATIVE_INFINITY;
        for (int i = 0; i < maximumCostVertexes.length; i++) {
            if (max < maximumCostVertexes[i]) {
                max = maximumCostVertexes[i];
                peripheralVertexIndex = i;
            }
        }

        peripheralVertex = digraphMatrix.getVertices().get(peripheralVertexIndex);
        return peripheralVertex;
    }

    private static Vertex getCentralVertex(float[][] distanceMatrix, DigraphMatrix digraphMatrix) {
        Vertex centralVertex = null;
        int centralVertexIndex = 0;
        float[] maximumCostVertexes = getMaximumCostVertexes(distanceMatrix);
        float min = Float.POSITIVE_INFINITY;
        for (int i = 0; i < maximumCostVertexes.length; i++) {
            if (min > maximumCostVertexes[i]) {
                min = maximumCostVertexes[i];
                centralVertexIndex = i;
            }
        }

        centralVertex = digraphMatrix.getVertices().get(centralVertexIndex);
        return centralVertex;
    }

    private static float[] getMaximumCostVertexes(float[][] distanceMatrix) {
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