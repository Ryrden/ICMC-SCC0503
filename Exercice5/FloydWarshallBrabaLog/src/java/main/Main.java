package main;

import main.graph.DigraphMatrix;
import main.graph.FloydWarshallTraversal;
import main.graph.Vertex;

import java.util.ArrayList;
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
            digraphMatrix.addEdge(pointOrigin, pointDestination);
        }
        Vertex originVertex = new Vertex(0, 0);
        FloydWarshallTraversal floydWarshallTraversal = new FloydWarshallTraversal(digraphMatrix);
        floydWarshallTraversal.traverseGraph(originVertex);
        float[][] distanceMatrix = floydWarshallTraversal.getDistanceMatrix();
        Vertex centralVertex = getCentralVertex(distanceMatrix,digraphMatrix);
        //float peripheralVertex = getPeripheralVertex(distanceMatrix);
        //float farthestVertexFromPeripheral = getFarthestVertexFromPeripheral(distanceMatrix, peripheralVertex);
        System.out.println(centralVertex);
    }

    private static Vertex getCentralVertex(float[][] distanceMatrix,DigraphMatrix digraphMatrix) {
        Vertex centralVertex;
        int centralVertexIndex = 0;
        float[] maximumCostVertexes = getMaximumCostVertexes(distanceMatrix);
        float min = Float.POSITIVE_INFINITY;
        for (int i = 0; i < maximumCostVertexes.length;i++){
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
        int indexCount = 0;

        float centralVertexDistance = Float.NEGATIVE_INFINITY;
        for (int column = 0; column < distanceMatrix[0].length; column++) {
            float maxDistance = 0;
            for (int row = 0; row < distanceMatrix.length; row++) {
                if (distanceMatrix[row][column] > maxDistance) {
                    maxDistance = distanceMatrix[row][column];
                }
            }
            if (maxDistance > centralVertexDistance) {
                centralVertexDistance = maxDistance;
                maximumCostVertexes[indexCount] = centralVertexDistance;
                indexCount += 1;
            }
            centralVertexDistance = Float.NEGATIVE_INFINITY;
        }
        return maximumCostVertexes;
    }

}