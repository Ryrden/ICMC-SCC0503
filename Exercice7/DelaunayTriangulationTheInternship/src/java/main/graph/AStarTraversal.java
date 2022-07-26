package main.graph;

import main.dungeon.Room;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public final class AStarTraversal extends TraversalStrategy {
    private final List<Vertex> verticesToVisit;
    private final float[] vertexHeuristic;

    public AStarTraversal(AbstractGraph graph) {
        super(graph);
        verticesToVisit = new LinkedList<>();
        vertexHeuristic = new float[getGraph().getNumberOfVertices()];
        Arrays.fill(vertexHeuristic, Float.POSITIVE_INFINITY);
    }

    public void traverseGraph(Vertex source) {
        throw new UnsupportedOperationException("Not implemented yet");
    }

    public void traverseGraph(Vertex source, Vertex destination) {
        var sourceIndex = getGraph().getVertices().indexOf(source);
        vertexHeuristic[sourceIndex] = getHeuristicDistance((Room) source, (Room) destination);
        setDistanceToVertex(sourceIndex, 0);
        var visitedVertex = new LinkedList<>();
        verticesToVisit.add(source);

        var currentVisitedVertex = source;
        var currentVisitedVertexIndex = getGraph().getVertices().indexOf(currentVisitedVertex);
        while (currentVisitedVertex != destination && !verticesToVisit.isEmpty()) {
            if (currentVisitedVertex != null) {
                var adjacentVertex = getGraph().getFirstConnectedVertex(currentVisitedVertex);
                while (adjacentVertex != null) {
                    var adjacentVertexIndex = getGraph().getVertices().indexOf(adjacentVertex);
                    var currentDistance = getDistanceToVertex(currentVisitedVertexIndex) + getTrueDistance((Room) currentVisitedVertex, (Room) adjacentVertex);
                    setDistanceToVertex(adjacentVertexIndex, currentDistance);
                    if (!visitedVertex.contains(adjacentVertex)) {
                        vertexHeuristic[adjacentVertexIndex] = currentDistance + getHeuristicDistance((Room) adjacentVertex, (Room) destination);
                        verticesToVisit.add(adjacentVertex);
                    }
                    adjacentVertex = getGraph().getNextConnectedVertex(currentVisitedVertex, adjacentVertex);
                }
            }
            currentVisitedVertex = getVertexWithBestHeuristic();
            if (currentVisitedVertex == null)
                break;
            currentVisitedVertexIndex = getGraph().getVertices().indexOf(currentVisitedVertex);
            visitedVertex.add(currentVisitedVertex);
            verticesToVisit.remove(currentVisitedVertex);

        }
        printDistances();
    }

    private Vertex getVertexWithBestHeuristic() {
        return verticesToVisit.stream().min((vertexOne, vertexTwo) -> {
            var vertexOneIndex = getGraph().getVertices().indexOf(vertexOne);
            var vertexTwoIndex = getGraph().getVertices().indexOf(vertexTwo);
            var distance1 = vertexHeuristic[vertexOneIndex];
            var distance2 = vertexHeuristic[vertexTwoIndex];
            return Float.compare(distance1, distance2);
        }).orElse(null);
    }

    private float getHeuristicDistance(Room source, Room destination) {
        //euclidean Distance
        var x1 = source.getPoint().getX();
        var y1 = source.getPoint().getY();
        var x2 = destination.getPoint().getX();
        var y2 = destination.getPoint().getY();
        return (float) Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
    }

    private float getTrueDistance(Room source, Room destination) {
        //manhattan Distance
        var x1 = source.getPoint().getX();
        var y1 = source.getPoint().getY();
        var x2 = destination.getPoint().getX();
        var y2 = destination.getPoint().getY();
        return (float) Math.abs(x1 - x2) + (float) Math.abs(y1 - y2);
    }
}
