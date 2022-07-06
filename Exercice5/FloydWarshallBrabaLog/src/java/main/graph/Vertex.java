package main.graph;

public record Vertex(int x, int y) {

    public String getName() {
        return "(" + x + "," + y + ")";
    }
    public String toString() {
        return x + "," + y;
    }
}
