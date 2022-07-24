package main;

import main.dungeon.DungeonGraphic;
import main.dungeon.GraphConverter;
import main.dungeon.RandomDungeonGenerator;
import main.dungeon.Room;
import main.graph.*;

import javax.swing.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int randomSeed = scanner.nextInt();
        scanner.nextLine();
        int numberRooms = scanner.nextInt();

        AbstractGraph dungeon = generateDungeonLevel(randomSeed, numberRooms);
        FloydWarshallTraversal floydWarshallTraversal = new FloydWarshallTraversal(dungeon);
        floydWarshallTraversal.traverseGraph(null);

        Room centralRoom= (Room) floydWarshallTraversal.getCentralVertex();
        centralRoom.setCheckPoint(true);
        Room startRoom= (Room) floydWarshallTraversal.getPeripheralVertex();
        startRoom.setEntrance(true);
        Room exitRoom = (Room) floydWarshallTraversal.getFarthestVertexFrom(startRoom);
        exitRoom.setExit(true);

        printDungeonWithDFS(dungeon);
        printDungeonWithBFS(dungeon);
        SwingUtilities.invokeLater(() -> new DungeonGraphic(dungeon).setVisible(true));
    }

    private static void printDungeonWithDFS(AbstractGraph dungeon) {
        var depthFirstTraversal = new DepthFirstTraversal(dungeon);
        depthFirstTraversal.traverseGraph(dungeon.getVertices().get(0));
    }

    private static void printDungeonWithBFS(AbstractGraph dungeon) {
        var breadthFirstTraversal = new BreadthFirstTraversal(dungeon);
        breadthFirstTraversal.traverseGraph(dungeon.getVertices().get(0));
    }

    private static AbstractGraph generateDungeonLevel(int randomSeed, int numberRooms) {
        RandomSingleton.getInstance(randomSeed); //Inicializar gerador de números aleatórios
        var randomDungeonGenerator = new RandomDungeonGenerator(numberRooms); //Gerar 20 salas
        var dungeon = randomDungeonGenerator.getDungeon(); //Pegar o grafo com salas
        DelaunayTriangulation.triangulateGraphVertices(dungeon); //Criar arestas

        int[] predecessorIndexList = cleanEdgesAndGetPredecessorList(dungeon);

        return GraphConverter.predecessorListToGraph(dungeon, predecessorIndexList);
    }

    private static int[] cleanEdgesAndGetPredecessorList(AbstractGraph dungeon) {
        var primTraversal = new PrimMSTTraversal(dungeon);
        primTraversal.traverseGraph(dungeon.getVertices().get(0));
        return primTraversal.getPredecessorArray();
    }

}