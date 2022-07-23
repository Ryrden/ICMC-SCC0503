package main.dungeon;

import main.graph.AbstractGraph;
import main.graph.DigraphMatrix;

public class GraphConverter {
    private GraphConverter() {}
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
