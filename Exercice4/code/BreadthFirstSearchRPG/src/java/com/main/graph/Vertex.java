package com.main.graph;

import com.main.answer.Answer;

public class Vertex extends Answer {
    protected Answer object;
    public Vertex(Answer object) {
        super(object.getId(), object.getName(), object.getDescription());
    }
}
