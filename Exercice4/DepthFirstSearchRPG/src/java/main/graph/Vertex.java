package main.graph;

import main.answer.Answer;

public class Vertex extends Answer {
    protected Answer object;
    public Vertex(Answer object) {
        super(object.getId(), object.getName(), object.getDescription());
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
