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
        depthFirstTraversalRecursive(source);
        printPath();
    }

    public void depthFirstTraversalRecursive(Vertex source) {
        int sourceIndex = getGraph().getVertices().indexOf(source);
        addToPath(source);
        markVertexAsVisited(sourceIndex);
        setDistanceToVertex(sourceIndex, 0);
        setPredecessorVertexIndex(sourceIndex, -1);

        List<Vertex> vertexesToVisit = getGraph().getAllConnectedVertex(source);

        for (Vertex currentVisitedVertex : vertexesToVisit) {
            if (!hasVertexBeenVisited(getGraph().getVertices().indexOf(currentVisitedVertex))) {
                depthFirstTraversalRecursive(currentVisitedVertex);
            }
        }
    }
}
