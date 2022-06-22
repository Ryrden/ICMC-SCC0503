package com.main.graph;

import com.main.answer.Answer;

import java.util.Objects;
public class Vertex extends Answer {
    protected Answer object;
    public Vertex(Answer object) {
        super(object.getID(), object.getName(), object.getDescription());
    }
}
