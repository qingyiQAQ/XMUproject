using System;

namespace Program2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int[] array = { 9, 6, 3, 1, 8, 4, 2, 7, 5 };
            Console.WriteLine("原始数组：");
            PrintArray(array);
            Console.WriteLine();
            QuickSortAlgorithm(array, 0, array.Length - 1);
            Console.WriteLine("\n排序后的数组：");
            PrintArray(array);
        }
        static void PrintArray(int[] arr)
        {
            for (int i = 0; i < arr.Length; i++) Console.Write("+----");
            Console.WriteLine("+");
            for (int i = 0; i < arr.Length; i++) Console.Write($"|{arr[i],3:00} ");
            Console.WriteLine("|");
            for (int i = 0; i < arr.Length; i++) Console.Write("+----");
            Console.WriteLine("+");
        }
        //以表格形式输出数组
        static void PrintPointer(int[] arr, int low, int high)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                if (i == low && low == high) Console.Write("| ij ");
                else if (i == low) Console.Write("| i  ");
                else if (i == high) Console.Write("| j  ");
                else Console.Write("|    ");
            }
            Console.WriteLine("|");
            for (int i = 0; i < arr.Length; i++) Console.Write("+----");
            Console.WriteLine("+");
        }
        //在数组下方输出ij两个指针的位置
        static void QuickSortAlgorithm(int[] array, int low, int high)
        {
            if (low < high)
            {
                int pivot = Partition(array, low, high);
                Console.WriteLine("两指针重合，完成一次排序");
                if (low < pivot - 1)
                {
                    Console.WriteLine("递归左子树");
                    QuickSortAlgorithm(array, low, pivot - 1);
                }
                if (pivot + 1 < high)
                {
                    Console.WriteLine("递归右子树");
                    QuickSortAlgorithm(array, pivot + 1, high);
                }
            }
        }
        //快速排序主要方法
        static int Partition(int[] arr, int low, int high)
        {
            int pivot = arr[low];
            Console.WriteLine($"选取第一个数{pivot}为pivot");
            PrintArray(arr);
            PrintPointer(arr, low, high);
            while (true)
            {
                while (arr[low] < pivot)
                {
                    low++;
                    Console.WriteLine($"指针i所指向的数小于pivot({pivot})，指针右移");
                    PrintArray(arr);
                    PrintPointer(arr, low, high);
                }
                while (arr[high] > pivot)
                {
                    high--;
                    Console.WriteLine($"指针j所指向的数大于pivot({pivot})，指针左移");
                    PrintArray(arr);
                    PrintPointer(arr, low, high);
                }
                if (low < high)
                {
                    if (arr[low] == arr[high])
                        return high;
                    Console.WriteLine("左指针i指向的数大于右指针j所指向的数，两数交换");
                    Swap(arr, low, high);
                    PrintArray(arr);
                    PrintPointer(arr, low, high);
                }
                else
                {
                    return high;
                }
            }
        }
        //进行一趟排序
        static void Swap(int[] array, int i, int j)
        {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        //交换两数组元素
    }
}