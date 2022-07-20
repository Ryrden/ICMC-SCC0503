package main;

import main.dungeon.DungeonGraphic;
import main.dungeon.RandomDungeonGenerator;
import main.graph.DelaunayTriangulation;
import main.graph.PrimMSTTraversal;
import main.graph.RandomSingleton;

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
        PrimMSTTraversal mst = new PrimMSTTraversal(dungeon);
        mst.traverseGraph(dungeon.getVertices().get(0));
        DelaunayTriangulation.triangulateGraphVertices(dungeon); //Criar arestas

        SwingUtilities.invokeLater(() -> new DungeonGraphic(dungeon).setVisible(true));
    }

}