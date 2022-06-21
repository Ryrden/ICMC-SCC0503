import java.util.Scanner;

public class main {
    public static void main() {
        Scanner scanner = new Scanner(System.in);
        int vertexNumber = scanner.nextInt();
        for (int i = 0; i < vertexNumber; i++) {
            String questName = scanner.nextLine();
            String questDescription = scanner.nextLine();
        }
        int edgeNumber = scanner.nextInt();
        for(int i = 0; i < edgeNumber; i++){
            int originId = scanner.nextInt();
            int destinyId = scanner.nextInt();
        }
        int originVertex = scanner.nextInt();

        //CHAMA GRAFO
    }
}