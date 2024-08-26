
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入数组总行数：");
        int m = Integer.parseInt(scanner.nextLine());
        int[][] matrix = new int[m][];
        for (int i = 0; i < m; i++) {
            System.out.print("请输入第" + (i + 1) + "行的长度：");
            int n = Integer.parseInt(scanner.nextLine());
            matrix[i] = createRandomArray(n);
            System.out.println("第" + (i + 1) + "行的数组为：" + Arrays.toString(matrix[i]));
        }
        while (true) {
            System.out.print("请输入方向键（a, s, d, w），按 q 退出：");
            String input = scanner.nextLine();
            if (input.equals("q")) {
                break;
            }
            int[][] movedMatrix = moveMatrix(matrix, input);
            printMatrix(movedMatrix);
        }
    }

    // 创建随机数组
    private static int[] createRandomArray(int length) {
        int[] arr = new int[length];
        for (int i = 0; i < length; i++) {
            arr[i] = (int) (Math.random() * 100);
        }
        return arr;
    }

    // 移动数组
    private static int[][] moveMatrix(int[][] matrix, String dir) {
        int m = matrix.length;
        int[][] movedMatrix = new int[m][];
        for (int i = 0; i < m; i++) {
            int n = matrix[i].length;
            movedMatrix[i] = new int[n]; // 添加这行代码
            switch (dir) {
                case "a":
                    // 向左滚动
                    for (int j = 0; j < n; j++) {
                        movedMatrix[i][j] = matrix[i][(j + 1) % n];
                    }
                    break;
                case "d":
                    // 向右滚动
                    for (int j = 0; j < n; j++) {
                        movedMatrix[i][(j + 1) % n] = matrix[i][j];
                    }
                    break;
                case "w":
                    // 向上滚动
                    for (int j = 0; j < n; j++) {
                        movedMatrix[(i + m - 1) % m][j] = matrix[i][j];
                    }
                    break;
                case "s":
                    // 向下滚动
                    for (int j = 0; j < n; j++) {
                        movedMatrix[(i + 1) % m][j] = matrix[i][j];
                    }
                    break;
                default:
                    System.out.println("无效的方向键，请重新输入。");
                    return matrix;
            }
        }
        return movedMatrix;
    }

    // 打印数组
    private static void printArray(int[] arr) {
        System.out.println(Arrays.toString(arr));
    }

    // 打印矩阵
    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            printArray(row);
        }
    }
}
