package main.graph;

public record Vertex(int x, int y) {

    public float euclideanDistance(Vertex other) {
        return (float) Math.sqrt(Math.pow(x - other.x, 2) + Math.pow(y - other.y, 2));
    }

    public String getName() {
        return "(" + x + "," + y + ")";
    }

    public String toString() {
        return x + "," + y;
    }
}
