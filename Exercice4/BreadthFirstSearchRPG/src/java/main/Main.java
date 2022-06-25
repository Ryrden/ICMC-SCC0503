package main;

import main.answer.Answer;
import main.graph.BreadthFirstTraversal;
import main.graph.DigraphList;
import main.graph.Vertex;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int vertexNumber = scanner.nextInt();
        scanner.nextLine();
        ArrayList<Vertex> questLog = new ArrayList<>();
        for (int i = 0; i < vertexNumber; i++) {
            String questName = scanner.nextLine();
            String questDescription = scanner.nextLine();
            Answer questN = new Answer(i, questName, questDescription);
            Vertex vertex = new Vertex(questN);
            questLog.add(vertex);
        }
        DigraphList digraphList = new DigraphList(questLog);
        int edgeNumber = scanner.nextInt();
        for (int i = 0; i < edgeNumber; i++) {
            int originId = scanner.nextInt();
            int destinyId = scanner.nextInt();
            digraphList.addEdge(questLog.get(originId), questLog.get(destinyId));
        }
        int originVertex = scanner.nextInt();
        BreadthFirstTraversal breadthFirstTraversal = new BreadthFirstTraversal(digraphList);
        breadthFirstTraversal.traverseGraph(questLog.get(originVertex));
    }
}