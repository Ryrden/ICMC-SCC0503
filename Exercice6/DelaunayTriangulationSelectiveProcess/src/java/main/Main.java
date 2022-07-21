package main;

import main.dungeon.DungeonGraphic;
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

        RandomSingleton.getInstance(randomSeed); //Inicializar gerador de números aleatórios
        var randomDungeonGenerator = new RandomDungeonGenerator(numberRooms); //Gerar 20 salas
        var dungeon = randomDungeonGenerator.getDungeon(); //Pegar o grafo com salas
        DelaunayTriangulation.triangulateGraphVertices(dungeon); //Criar arestas
        AbstractGraph finalDungeon = dungeon;
        SwingUtilities.invokeLater(() -> new DungeonGraphic(finalDungeon).setVisible(true));

        var mst = new PrimMSTTraversal(dungeon);
        int[] predecessorIndexList = mst.getPredecessorArray();
        dungeon = predecessorListToGraph(dungeon, predecessorIndexList);

        AbstractGraph finalDungeon1 = dungeon;
        SwingUtilities.invokeLater(() -> new DungeonGraphic(finalDungeon1).setVisible(true));

        var breadthFirstTraversal = new BreadthFirstTraversal(dungeon);
        breadthFirstTraversal.traverseGraph(dungeon.getVertices().get(0));
        AbstractGraph finalDungeon2 = dungeon;
        SwingUtilities.invokeLater(() -> new DungeonGraphic(finalDungeon2).setVisible(true));
    }

    public static AbstractGraph predecessorListToGraph(AbstractGraph dungeon, int[] predecessor){
        AbstractGraph newDungeon = new DigraphMatrix();

        Room newRoom;
        for (int i = 0; i < dungeon.getNumberOfVertices(); i++) {
            newRoom = (Room)dungeon.getVertices().get(i);
            newDungeon.addVertex(newRoom);
        }

        float distance;
        Room source;
        Room destination;
        for (int i = 1; i < predecessor.length; i++) {
            source = (Room)dungeon.getVertices().get(predecessor[i]);
            destination = (Room)dungeon.getVertices().get(i);
            distance = dungeon.calcDistance(source, destination);
            newDungeon.addEdge(source, destination, distance);
            newDungeon.addEdge(destination, source, distance);
        }
        return newDungeon;
    }

}