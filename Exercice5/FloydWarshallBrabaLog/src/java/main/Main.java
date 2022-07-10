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
            int weight = (int) pointOrigin.euclideanDistance(pointDestination);

            digraphMatrix.addEdge(pointOrigin, pointDestination,weight);
        }
        FloydWarshallTraversal floydWarshallTraversal = new FloydWarshallTraversal(digraphMatrix);
        floydWarshallTraversal.traverseGraph(null);

        Vertex centralVertex = floydWarshallTraversal.getCentralVertex();
        Vertex peripheralVertex = floydWarshallTraversal.getPeripheralVertex();
        Vertex farthestVertexFromPeripheral = floydWarshallTraversal.getFarthestVertexFromPeripheral();

        System.out.println(centralVertex);
        System.out.println(peripheralVertex);
        System.out.print(farthestVertexFromPeripheral);
    }

}