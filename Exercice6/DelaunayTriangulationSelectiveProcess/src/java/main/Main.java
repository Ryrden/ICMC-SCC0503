package main;

import main.dungeon.DungeonGraphic;
import main.dungeon.GraphConverter;
import main.dungeon.RandomDungeonGenerator;
import main.graph.*;

import javax.swing.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int randomSeed = scanner.nextInt();
        scanner.nextLine();
        int numberRooms = scanner.nextInt();

        AbstractGraph newDungeon = generateDungeonLevel(randomSeed, numberRooms);

        printDungeonWithBFS(newDungeon);
        SwingUtilities.invokeLater(() -> new DungeonGraphic(newDungeon).setVisible(true));
    }

    private static void printDungeonWithBFS(AbstractGraph newDungeon) {
        var breadthFirstTraversal = new BreadthFirstTraversal(newDungeon);
        breadthFirstTraversal.traverseGraph(newDungeon.getVertices().get(0));
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