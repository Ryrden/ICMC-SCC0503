package com.main;

import com.main.answer.Answer;
import com.main.graph.Vertex;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int vertexNumber = scanner.nextInt();
        ArrayList<Vertex> questLog = new ArrayList<>();
        for (int i = 0; i < vertexNumber; i++) {
            String questName = scanner.nextLine();
            String questDescription = scanner.nextLine();
            Answer questN = new Answer(i, questName, questDescription);
            Vertex vertex = new Vertex(questN);
            questLog.add(vertex);
        }

        int edgeNumber = scanner.nextInt();
        for (int i = 0; i < edgeNumber; i++) {
            int originId = scanner.nextInt();
            int destinyId = scanner.nextInt();
        }

        int originVertex = scanner.nextInt();

        //CHAMA GRAFO
    }
}