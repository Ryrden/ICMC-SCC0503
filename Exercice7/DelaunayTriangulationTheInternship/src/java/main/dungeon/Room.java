package main.dungeon;

import main.graph.Vertex;

import java.awt.*;

public class Room extends Vertex {

    private boolean isEntrance;
    private boolean isExit;
    private boolean isCheckPoint;
    private int keyId;
    private Rectangle room;

    public boolean isEntrance() {
        return isEntrance;
    }

    public void setEntrance(boolean entrance) {
        isEntrance = entrance;
    }

    public boolean isExit() {
        return isExit;
    }

    public void setExit(boolean exit) {
        isExit = exit;
    }

    public boolean isCheckPoint() {
        return isCheckPoint;
    }

    public void setCheckPoint(boolean checkPoint) {
        isCheckPoint = checkPoint;
    }

    public int getKeyId() {
        return keyId;
    }

    public void setKeyId(int keyId) {
        this.keyId = keyId;
    }

    public Rectangle getRoom() {
        return room;
    }

    public void setRoom(Rectangle room) {
        this.room = room;
    }

    protected Room(Point point, Dimension dimension) {
        super("(" + point.getX() + "," + point.getY() + ")");
        initializeData();
        room = new Rectangle(point, dimension);
    }

    protected Room(Rectangle rectangle) {
        super("(" + rectangle.getX() + "," + rectangle.getY() + ")");
        initializeData();
        room = rectangle;
    }

    private void initializeData() {
        isEntrance = false;
        isExit = false;
        isCheckPoint = false;
    }

    public Point getPoint() {
        return new Point((int) room.getX(), (int) room.getY());
    }

    @Override
    public String toString() {
        return "Room{" + "(X, Y)= (" + room.getX() + "," + room.getY() + ")}";
    }
}
