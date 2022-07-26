package main.graph;

import main.graph.AbstractGraph;
import main.graph.TraversalStrategy;
import main.graph.Vertex;

import java.util.List;

public class DepthFirstTraversal extends TraversalStrategy {

    public DepthFirstTraversal(AbstractGraph graph) {
        super(graph);
    }

    @Override
    public void traverseGraph(Vertex source) {
        int sourceIndex = getGraph().getVertices().indexOf(source);
        setDistanceToVertex(sourceIndex, 0);
        setPredecessorVertexIndex(sourceIndex, -1);

        depthFirstTraversalRecursive(source);
        printPath();
    }

    public void depthFirstTraversalRecursive(Vertex source) {
        int sourceIndex = getGraph().getVertices().indexOf(source);
        addToPath(source);
        markVertexAsVisited(sourceIndex);

        List<Vertex> vertexesToVisit = getGraph().getAllConnectedVertex(source);

        for (Vertex currentVisitedVertex : vertexesToVisit) {
            int currentVisitedVertexIndex = getGraph().getVertices().indexOf(currentVisitedVertex);
            if (!hasVertexBeenVisited(getGraph().getVertices().indexOf(currentVisitedVertex))) {
                updateTraversalInfoForVertex(currentVisitedVertexIndex, sourceIndex);
                depthFirstTraversalRecursive(currentVisitedVertex);
            }
        }
    }

    protected void updateTraversalInfoForVertex(int newVertexIndex, int previousVertexIndex) {
        var newVertex = getGraph().getVertices().get(newVertexIndex);
        var oldVertex = getGraph().getVertices().get(previousVertexIndex);
        float newDistance = getGraph().getDistance(oldVertex, newVertex);
        float distance = getDistanceToVertex(previousVertexIndex) + newDistance;
        setDistanceToVertex(newVertexIndex, distance);
        setPredecessorVertexIndex(newVertexIndex, previousVertexIndex);
        setSuccessorVertexIndex(previousVertexIndex, newVertexIndex);
    }
}
